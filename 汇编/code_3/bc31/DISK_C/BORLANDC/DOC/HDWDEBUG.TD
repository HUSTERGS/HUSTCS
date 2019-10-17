/*************************************************************************/
                             TURBO DEBUGGER 
                   USING THE HARDWARE DEBUGGING FEATURES


CONFIGURING YOUR SYSTEM
=======================

Before you can do hardware debugging, you must either have loaded
TDH386.SYS (for DOS debugging) or TDDEBUG.386 (for Windows debugging).
See Chapter 1 of the "Turbo Debugger User's Guide" to find out how
to load these programs.


SETTING HARDWARE BREAKPOINTS
============================

There are several ways to set a hardware-assisted breakpoint:

o Choose Breakpoints|Changed memory global. 

    In the input box of the dialog box that opens, enter a memory 
    address followed by the number of bytes Turbo Debugger is to 
    watch to determine if your program has changed anything in that
    part of memory.  If you enter a variable name or expression as 
    the address, the count refers to how many objects of that size 
    to watch.
    
    For example, if your program contains a word-sized variable x, 
    typing "x,2" causes two objects of size sizeof(x) (4 bytes total)
    to be watched.

    When you set a breakpoint using the Changed Memory Global command, 
    Turbo Debugger automatically determines whether that breakpoint 
    can make use of the available hardware.  If it can, Turbo Debugger
    sets a hardware breakpoint for you and indicates that the breakpoint 
    is set in hardware by putting an asterisk (*) after the global 
    breakpoint number in the left pane of the Breakpoints window.

o Choose Breakpoints|Hardware Breakpoint.

    Use this command to set a general-purpose hardware breakpoint. This 
    command displays the Hardware Breakpoint Options dialog box (described
    later).

o Use the Breakpoint Options dialog box (see the paragraphs after the next
  one for an explanation of how to display this dialog box) to get to the 
  Hardware Breakpoint options dialog box (described later).

    In the Breakpoint Options dialog box, check the Global checkbox, then
    press the Change button to display the Conditions and Actions dialog
    box. In this dialog box, select the Hardware radio button in the
    Condition group, then press the Hardware button at the bottom of the 
    box to display the Hardware Breakpoint Options dialog box.

    You can get to the Breakpoint Options dialog box from two locations:
    the Breakpoints menu or the Breakpoints view window.

    - Choose Breakpoints|At (Alt-B A) to display the Breakpoint Options
      dialog box.

    - Choose View|Breakpoints to display the Breakpoints window. In the left
      pane, highlight the breakpoint you want to work with, then display the
      local menu (Alt-F10 or right-hand mouse click) and choose the Set
      Options or the Add command to display the Breakpoint Options dialog box.


USING THE HARDWARE BREAKPOINT OPTIONS DIALOG BOX
================================================

This section starts with a description of the hardware and software 
limitations on the hardware conditions you can set with Turbo Debugger,
and then explains all the options you can set from the Hardware 
Breakpoints Dialog box.


Hardware conditions permitted with TDH386.SYS and TDDEBUG.386
-------------------------------------------------------------

When you're using TDH386.SYS with Turbo Debugger or TDDEBUG.386 with 
Turbo Debugger for Windows, you can set the following types of hardware 
breakpoints from the Hardware Breakpoint dialog box:

o instruction fetch

o read from memory

o write to memory

o access memory

Because you can't set any type of data matching when you use TDH386.SYS
or TDDEBUG.386, you must always set the Data Match radio buttons to 
Match All. You can also match only a single memory address or range of 
memory addresses. A range can encompass from 1 to 16 bytes, depending on 
how many other hardware breakpoints you have set and the address of the 
beginning of the range.

The other options in the Hardware Breakpoint dialog are for other hardware 
debuggers and device drivers that might support more matching modes.

You can also use TDH386.SYS with Turbo Debugger and with the virtual
debugger (TD386). In this case, you can use many more types of
hardware breakpoints, including matching on any size ranges of memory
or I/O access.


The Hardware Breakpoint Options dialog box
------------------------------------------

This section describes the options on the Hardware Breakpoint Options 
dialog box. Remember that your hardware isn't likely to support 
all combinations of matching that you can specify from this menu. The 
previous section describes the combinations that are allowed for the 
TDH386.SYS and TDDEBUG.386 device drivers supplied with Turbo Debugger.

The Hardware Breakpoint Options dialog box lets you set the three matching
criteria that make up a hardware breakpoint:

o the bus cycle type to be matched

o the range of addresses to be matched

o the range of data values to be matched

For example, a hardware breakpoint might say "Watch for an I/O write
anywhere from address 3F8 to 3FF as long as the data value is equal to
1." This breakpoint will then be triggered any time a byte of 1 is
written to any of the I/O locations that control the COM1 serial port.

Usually, you set far simpler hardware breakpoints than this, such
as "Watch for I/O to address 200."

  Cycle Type radio buttons
  ------------------------

    With these radio buttons, you can make one of the following settings:

    Read Memory          Match memory reads
    Write Memory         Match memory writes
    Access Memory        Match memory read or write
    Input I/O            Match I/O input
    Output I/O           Match I/O Output
    Both I/O             Match I/O input or output
    Fetch Instruction    Match instruction fetch

    The Access Memory option is a combination of the Read Memory and Write
    Memory options--it matches either memory reads or writes. Likewise,
    the Both I/O option matches I/O reads or writes.

    Some hardware debuggers are capable of distinguishing between simple
    data reads from memory and instruction fetches. In this case, if you
    set a breakpoint to match on read memory, an instruction fetch from
    that location will not trigger the hardware breakpoint. Instruction
    cycles include all the bytes that the processor reads in order to
    determine the instruction operation to perform, including prefix
    bytes, operand addresses, and immediate values. The actual data read
    or written to memory referenced by an operand's address is not
    considered to be part of the instruction fetch. For example,

      MOV    AX,[1234]

    fetches 3 instruction bytes from memory and reads 2 data bytes. If you
    use instruction fetch matching, remember that the 80x86 processor
    family prefetches instructions to be executed, so you may get false
    matches, depending on whether your hardware debugger can sort out
    prefetched instructions from ones that are really executed.

  Address radio buttons
  ---------------------

    With these radio buttons, you can make one of the following settings:

    Above              Match above an address
    Below              Match below an address
    Range              Match within address range
    Not Range          Match outside address range
    Less or Equal      Match below or equal to address
    Greater or Equal   Match above or equal to address
    Equal              Match a single address
    Unequal            Match all but a single address
    Match All          Match any address


  Data Match radio buttons
  ------------------------

    The Data Match radio buttons let you make the following settings:
    
    Above              Match above a value
    Below              Match below a value
    Range              Match within value range
    Not Range          Match outside value range
    Less or Equal      Match below or equal to value
    Greater or Equal   Match above or equal to value
    Equal              Match a single value
    Unequal            Match all but a single value
    Match All          Match any value
    
    If you turn on a Data or Address option that involves any less-than or
    greater-than condition, a single address match range either starts at
    zero and extends to the value you specified, or starts at the value
    you specified and extends to the highest allowed value for addresses
    or data.

/***************************** END OF FILE *******************************/
