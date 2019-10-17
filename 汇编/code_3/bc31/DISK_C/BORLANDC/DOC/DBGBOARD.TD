/*************************************************************************/
               TURBO DEBUGGER HARDWARE DEBUGGER INTERFACE
               ==========================================

Hardware debugging boards greatly speed up certain types of breakpoints;
in particular, those that watch for an area of memory or a program variable
to change. Turbo Debugger has a general interface for accessing these boards.

This appendix describes how to write a device driver that Turbo Debugger
can communicate with in order to make use of the capabilities of a
particular hardware debugger. This information is intended for vendors
of hardware debuggers who want to make their boards usable with Turbo 
Debugger. (Note that you must know the general architecture of DOS 
device drivers. Refer to the DOS Technical Reference for more information 
on how to write device drivers.)


TDH386.SYS: 80386 hardware device driver
----------------------------------------
The Turbo Debugger distribution disk contains the file TDH386.SYS,
which is a hardware device driver that lets Turbo Debugger use the
debug registers on the 80386 processor. You can use this driver by
copying it to your DOS disk and putting the following line in your
CONFIG.SYS file:

   DEVICE = TDH386.SYS

Turbo Debugger will then use the hardware assistance of the 80386
whenever it can to speed up breakpoint processing.

This means, of course, that you can only use this device driver if
your system uses the 80386 processor or higher.


Setting hardware breakpoints
----------------------------
If you need information on using the Turbo Debugger hardware debugging
features, see the file HDWDEBUG.TD.


Hardware debugger overview
--------------------------
The device driver interface provides device-independent access to the
capabilities of different hardware debuggers. To accomplish this, the
common features of several hardware debuggers have been combined into
one generic hardware debugger. Turbo Debugger then uses this abstract
model to make requests to the device driver. 

A particular board might not be able to support all the operations 
specified by the abstract interface. In this case, the device driver 
can inform Turbo Debugger that a requested operation can't be performed. 
A hardware board also might offer more capabilities than the abstract 
interface defines. In this case, Turbo Debugger can't make use of the 
added features of the board.

Because we expect the device driver interface to encompass new features
in future releases, we have defined an "implementation level" status
field that the device driver returns when requested. This lets Turbo
Debugger know what the device driver is capable of doing and provides
compatibility with older drivers, while allowing new drivers to take
advantage of capabilities in future releases of the interface.

The hardware debugger interface breaks the capabilities of debugger
boards into three main areas of functionality:

o memory and I/O access breakpoints

o instruction trace-back memory

o extra onboard memory for symbol tables

This version of the interface supports only the first category. Future
releases will define an interface that accesses the other features.
When you write a device driver, keep in mind that these other
capabilities will be supported at a later date.


Device driver interface
-----------------------
The device driver is an ordinary character-type device driver named
TDH386.SYS. You must put the following statement in your CONFIG.SYS
file in order for the driver to be loaded when you boot the system:

   DEVICE = <drvrname.ext>

<drvrname.ext> is the name of the device driver file you have created.


Device driver function calls
----------------------------
The device driver must support the following function calls:


INIT (command code = 0)
  Called once when the device driver is first loaded. Your code for this
  function must make sure that the hardware board is disabled and in a
  quiescent state.


READ (command code = 4)
  Called by Turbo Debugger to read the status block from the last
  command sent to the device driver. You should keep the last status in
  a data area inside the driver and return as many bytes as requested.
  Each time a read is issued, you must start sending from the beginning
  of the status block, even if the previous read request was not long
  enough to send the entire block.

  The section "Status blocks returned by the device driver" describes
  the various status blocks the device driver can return in response to
  different command blocks.


READNOWAIT (command code = 5)
  Returns the first byte of the status block. The busy bit should always
  be set to 0, indicating that data is available at all times.


READSTATUS (command code = 6)
  Always sets the busy bit to 0, indicating that a subsequent read
  request would complete immediately.


READFLUSH (command code = 7)
  Simply sets the done bit in the return status.


WRITE (command code = 8)
  Called by Turbo Debugger to send a command to the device driver. The
  command will have a variable length depending on the command type.
  You can either copy the data into a work area inside the device
  driver or access it directly using the data pointer that is part 
  of the device driver request.


The following function calls are command blocks Turbo Debugger can 
send to the device driver:


WRITEVERIFY (command code = 9)
  Does the same thing as WRITE (command code 8).


WRITESTATUS (command code = 10)
  Simply sets the done bit in the return status.


WRITEFLUSH (command code = 11)
  Simply sets the done bit in the return status.

All other function calls should set the error bit (bit 15) in the
return status word, and put an "Unknown command" error code (3) in the
low byte of the status word.


Command blocks sent to driver
-----------------------------
All command blocks sent to the device driver by the WRITE function
call start with a byte that describes the operation to perform. The
subsequent bytes provide additional information for the particular
command.

When a hardware breakpoint is set, it is the device driver's
responsibility to check that it has been handed an acceptable
parameter block. It can't just ignore fields that request an operation
it can't perform. You must check each field to make sure that the
hardware can support the requested operation, and if it can't, you
must set the appropriate return code.

The first byte can contain one of the following command codes:

0   Install vectors
1   Get hardware capabilities
2   Enable the hardware breakpoints
3   Disable the hardware breakpoints
4   Set a hardware breakpoint
5   Clear a hardware breakpoint
6   Set I/O base address, resets hardware
7   Remove vectors

The following commands send additional data after the command code:

0 (Install vectors)
  
  4 bytes     Far pointer to vector routine

              This is a 32-bit pointer, the first word being the offset,
              and the second being the segment. You must save this address
              to enable the device driver to jump to it when a hardware
              breakpoint occurs. This routine should also install any
              interrupt vectors that the device driver needs. Turbo Debugger
              calls this routine once when it first starts up. The Remove
              Vectors (code 10) function is called once by Turbo Debugger
              when it no longer needs to use the hardware debugger device
              driver. At this time, you should replace any vectors that you
              took over when function 0 was called and make sure the hardware
              is disabled.


4 (Set a hardware breakpoint)

  1 byte      Breakpoint type

              0   Memory read
              1   Memory write
              2   Memory read or write
              3   I/O read
              4   I/O write
              5   I/O read or write
              6   Instruction fetch

  1 byte      Address-matching mode

              0   Match any address, don't care
              1   Equal to test value
              2   Not equal to test value
              3   Above test value
              4   Below test value
              5   Below or equal to test value
              6   Above or equal to test value
              7   Within inclusive range
              8   Outside range

  4 bytes     Low address

              A memory address in 32-bit linear form. If the address-matching
              mode requires one or more addresses to test against, any single 
              value or the low value of multiple addresses comes here.

  4 bytes     High address

              A memory address, in 32-bit linear form. If the address-matching
              mode requires two addresses to test against a range, the second 
              and higher value comes here.

  2 bytes     Pass count

  1 byte      Data-matching size: 1 = byte, 2 = word, 4 = doubleword

  1 byte      Source of matched bus cycle:

              1   CPU
              2   DMA
              3   Either CPU or DMA
                 
  1 byte      Data-matching mode

              0   Match any data, don't care
              1   Equal to test value
              2   Not equal to test value
              3   Above test value
              4   Below test value
              5   Below or equal to test value
              6   Above or equal to test value
              7   Within inclusive range
              8   Outside range

  4 bytes     Low data value

              If the data-matching mode requires one or more data values, 
              this field supplies the first or only value. The data-matching
              size determines how many bytes of this field are significant.

  4 bytes     High data value

              If the data-matching mode requires two data values, this field
              supplies the second value. The data-matching size determines 
              how many bytes of this field are significant.

  4 bytes     Data mask

              If the hardware supports it, this field controls which bits in
              the data are examined for the match condition.


5 (Clear a hardware breakpoint)

  1 byte      The handle of the breakpoint to clear. The handle was given
              to Turbo Debugger by command 4 (Set Hardware Breakpoint).


6 (Set I/O board base address)

  2 bytes     The base address of the hardware debugger board.


Status blocks returned by device driver
---------------------------------------
The READ function call returns the status block from the device
driver. Different commands written to the device driver result in
various status blocks being built to report what happened. All the
status blocks start with a single byte that describes the overall
result of the requested operation. The subsequent bytes return
additional information particular to the command that generated the
status block.

The following status codes can be returned in the first byte:

0   Command was successful.

1   Invalid handle supplied.

2   Full, can't set any more breakpoints.

3   Breakpoint was too complex for the hardware.

    The breakpoint could never be set because the hardware is not capable
    of supporting the combination of bus cycle, address, and data-matching
    that Turbo Debugger requested.

4   Command can't be performed due to restrictions imposed by a
    previous command.

    The command could have been performed if it weren't for some previous
    operation's preventing it. This could happen, for example, if the
    hardware only permits a single data match value, but Turbo Debugger
    tries to set a second hardware breakpoint with a different data match
    value than the first breakpoint.

5   The device driver can't find the hardware board.

6   A hardware failure has occurred.

7   An invalid command code was sent to the driver.

8   The driver hasn't been initialized with function code 0, so
    nothing can be done yet.

The following commands return additional status information after the
status code byte:

1 (Get hardware capabilities)

  2 bytes     Device driver interface version number. The current 
              version is 1.

  2 bytes     Device driver software version number.

              For each released version of your device driver that behaves
              differently, this field should contain a different number. 
              This lets Turbo Debugger take special measures if necessary, 
              based on this field.

  1 byte      Maximum number of hardware breakpoints that this
              driver and board combination can support.

  1 byte      Configuration bits

              Bit  Meaning when set
              ---  ----------------
               0   can distinguish between CPU and DMA accesses
               1   can detect DMA transfers
               2   has data mask
               3   breakpoints have hardware pass counter
               4   can match on data as well as address

  1 byte      Breakpoint types supported (bit mask)

              Bit  Function
              ---  --------
               0   Memory read
               1   Memory write
               2   Memory read or write
               3   I/O read
               4   I/O write
               5   I/O read or write
               6   Instruction fetch

  2 bytes     Addressing match modes supported (bit mask)

              Bit  Function
              ---  --------
               0   Match any address, don't care
               1   Equal to test value
               2   Not equal to test value
               3   Above test value
               4   Below test value
               5   Below or equal to test value
               6   Above or equal to test value
               7   Within inclusive range
               8   Outside range

  2 bytes     Data-matching modes supported (bit mask)

              Bit  Function
              ---  --------

               0   Match any data, don't care
               1   Equal to test value
               2   Not equal to test value
               3   Above test value
               4   Below test value
               5   Below or equal to test value
               6   Above or equal to test value
               7   Within inclusive range
               8   Outside range

  1 byte      Maximum data match length

              Set to 1, 2, or 4 depending on the widest data match or 
              mask that the hardware can perform.

  2 bytes     Size of onboard memory in kilobytes.

  2 bytes     Maximum number of trace-back events that can be recalled.

  2 bytes     Address of hardware breakpoint enable byte

              Specifies the segment address where Turbo Debugger must 
              write a byte with a value of 1 to enable hardware breakpoints. 
              The field must contain 0 if the device driver does not or 
              cannot support this capability. If it is supported, this 
              byte lets Turbo Debugger inform the device driver that it 
              has finished writing to the address space of the program 
              being debugged, and that subsequent accesses can cause 
              hardware breakpoints.

4 (Set a hardware breakpoint)

  1 byte      A handle that Turbo Debugger will use to refer to this
              breakpoint in the future. The device driver also uses this 
              handle when calling back into Turbo Debugger after a hardware
              breakpoint has occurred. The handle must be greater than or
              equal to zero (0). Negative values (top bit on) indicate a
              special condition when the device driver calls Turbo Debugger
              with a hardware breakpoint.

-2 (Recursive entry)

  1 byte      The special value FE (hex) can be returned by the hardware
              device driver if it has been recursively entered while 
              processing a hardware breakpoint. This can happen if a 
              hardware breakpoint has been set in the 6 bytes below the
              current top of stack in the program being debugged. If
              Turbo Debugger receives this entry code, it displays a
              message that the device driver can't proceed because of
              a breakpoint's being set near the top of the stack.


Device driver call into Turbo Debugger
--------------------------------------
When the hardware board and the device driver software have determined
that a hardware breakpoint has occurred, control must be transferred
to the address inside Turbo Debugger that was specified with command
code 0 (Set Hardware Breakpoint Vector).

The vector address must be jumped to with the CPU state exactly as it
was when the hardware breakpoint occurred, but with the program's AX
register pushed on the stack and an entry code now in the AH register.
The entry code can be

>= 0        The handle of the triggered breakpoint

-1 (FF)     The breakout button was pressed

Turbo Debugger will never return to the device driver once it is
jumped into from a hardware breakpoint.

/**************************** END OF FILE ********************************/
