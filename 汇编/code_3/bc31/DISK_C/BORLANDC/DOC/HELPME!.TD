/*************************************************************************/
                      TURBO DEBUGGER TIPS AND HINTS

CONTENTS:
1.  Answers to common questions
2.  Turbo Debugger for Windows (TDW), Windows debugging hints
3.  TDW mouse support
4.  TD mouse support

1. Answers to common questions
------------------------------
  Following is a list of the most commonly asked questions about Turbo
  Debugger.

  1. How does Turbo Debugger handle screen output for graphics-
     and text-based programs?

     There are a number of strategies that can be used to control
     how and when the screen gets refreshed. You should review the
     following tips if you are debugging a program that uses a graphics
     display mode and you want to do either of the following:

        - use a Borland pop-up utility such as SideKick or
          Sidekick Plus while inside Turbo Debugger

        - run programs from Turbo Debugger's DOS Shell that write
          directly to video memory

     The default screen-updating mode, "Swap," causes Turbo Debugger
     to use a single display adapter and display page and swap the
     contents of the user and Turbo Debugger screens in software.
     "Swap" is the slowest method of display swapping, but is the most
     protective and least disruptive.

     Pop-up utilities might not appear on the screen if your screen
     updating is set to "Flip," even though they are active and proces-
     sing your keystrokes. You must select "Swap" mode for display
     updating in order for these programs to work properly. Use Turbo
     Debugger's -ds command-line option to do this or use the TDINST
     utility to permanently set this mode. "Swap" mode makes screen
     updating slower, but it ensures that Turbo Debugger's screen
     doesn't interfere with either your program's or any other program's
     display.

     You might also need to use "Swap" when you use the DOS Shell
     command or run an editor from within Turbo Debugger. Most programs
     expect to run on video page 0 and don't check to see what
     the current video page is. Turbo Debugger's DOS Shell and any
     editors that Turbo Debugger runs in "Flip" mode don't run from
     video page 0, and the programs might appear to hang, even though
     you will be able to type in keystrokes normally. If this happens,
     use the -ds command-line option when you run Turbo Debugger or
     reinstall Turbo Debugger to use "Swap" instead of "Flip."

     If you are debugging a graphics mode application, you must specify
     the -ds command-line option ("Swap" contents), and you might want
     to use Turbo Debugger's -vg command-line option (Graphics Save). This
     option causes additional memory to be set aside for saving the
     entire graphics image your program produces. If you don't use this
     option, a "red cloud" may appear on your program's screen. These
     options can also be set permanently by using the TDINST program.
     The Graphics Save option takes an additional 8K of memory and slows
     screen-swapping.

     If you're running a graphics program that changes the EGA or VGA
     palette, make sure you use the -vp command-line option to save the
     palette.

  2. Can Turbo Debugger execute other programs while you're still debugging?

     The DOS Shell and Edit commands in the Module and File
     windows can swap to disk the program you are debugging in
     order to make room to run DOS or your editor. The default
     amount of memory to swap is 128K. You can use TDINST to set a
     different amount if that's not enough memory to run your editor
     or other programs. Setting the swap size to 0K tells Turbo Debugger
     to swap the entire user program to disk before running the DOS
     command processor.

     Only your program gets swapped to disk; Turbo Debugger remains in memory.

  3. How can I break out of a program even though interrupts are
     disabled?

     If you have an 80386 computer and are using TD386, the -B option
     allows a break even when interrupts are disabled. For example, this
     option enables a break from

       CLI
       JMP $

  4. Why can't I press Ctrl-Break to get out of a program
     running on a remote machine?

     The program running on the remote machine has taken control
     of Interrupt 1B (Ctrl-Break). TDREMOTE and WREMOTE don't take
     back control of Interrupt 1B until you stop execution of the
     running program. To stop execution, run the program to completion
     or press Ctrl-F2 (Program Reset) on the local machine.


  5. What are some of the syntactic and parsing differences
     between Turbo Debugger's built-in assembler and the
     standalone Turbo Assembler?

     A discussion follows this short example program:

              .model small
              .data

       abc    struc
       mem1   dd      ?
       mem2   db      ?
       mem3   db      "   "
       abc    ends

              align   16
       a      abc     <1,2,"xyz">

       msg1   db      "testing 1 2 3", 0
       msg2   db      "hello world", 0
       nmptr  dw      msg1
       fmptr  dd      msg1,msg2
       nfmptr dw      fmptr
       xx     dw      seg a

              .code

              push   cs
              pop    ds
              mov    bx,offset a
              mov    bx,nmptr
              les    si,fmptr
              mov    ah,4ch
              int    21h
              end

     Because the assembler expression parser does not accept all legal
     TASM instruction operands, Turbo Debugger assembler expressions
     can be more general than those of TAMS and can use multiple levels
     of memory-referencing, much like C and Pascal. However, there are a
     few constructs that you may be used to that you'll have to specify
     differently for the TD assembler expression parser to accept them:

       a. Size overrides should always appear inside the
          brackets; PTR is optional after the size. Also, when
          referring to a structure, you must use the name of the
          struc, not the name of the variable:

            OK:  [byte ptr bx]   [dword si]        [abc bx]

            BAD: byte ptr[bx]    [struc abc bx]    [a bx]

       b. You must specify a structure name when accessing the
          members of a structure with a register pointer.

            OK:  [abc ptr bx].mem1  [abc bx].mem3 + 1

            BAD: [bx].mem1

       c. You can't use multiple instances of brackets ([]) unless they are
          adjacent, and you can only follow a bracketed expression with
          a dot and a structure member name or another bracketed
          expression:

            OK:  4[bx][si]    [abc bx].mem2

            BAD: [bx]4[si]    [bx]+4

       d. If you use a register as part of a memory expression
          and you don't specify a size, WORD is assumed:

            [bx] is the same as [word bx]

       e. You can use any register you want between brackets ([]),
          not just the combinations of BX, BP, SI, and DI allowed in
          instruction operands. For example,

            [ax+bx]
            [bx+sp]

       f. You can use multiple levels of brackets to follow chains of
          pointers. For example,

            [byte [[nfmptr]+4]]

       g. Be careful with using registers to access memory locations.
          You might get unexpected results if your segment
          registers are not set up properly. If you don't
          explicitly specify a segment register, Turbo Debugger
          uses the DS register to reference memory.

       h. When you do specify a segment register, make sure you
          follow the same rule for size overrides: put it
          INSIDE the brackets, as follows:

            OK:  [byte es:di]    [es:fmptr]

            BAD: es:[byte di]

       i. Use the OFFSET operator to get the address of a
          variable or structure. Turbo Debugger automatically
          supplies the brackets around a variable name if you just type
          the variable name alone.

            a            contents of structure a
            [a]          contents of structure a
            offset a     address of structure a

       j. You can use the type overrides and the format control
          count to examine any area of memory displayed as you
          wish.

            [byte es:bx],10  10 bytes pointed to by es:bx
            [dword ds:si],4  4 dwords pointed to by ds:si

          This is very useful when specifying watch expressions.

       k. Sometimes you use a word memory location or register to
          point to a paragraph in memory that contains a data
          structure. Access the structure with expressions like

            [abc [xx]:0].mem1
            [abc es:0].mem3

  6. Are there any syntactic or parsing differences between Turbo
     Debugger's C expression evaluation and Borland C++'s?

     You can't pass constant-string arguments when evaluating
     functions.

       OK:   myfunc(123)   myfunc(string_variable)

       BAD:  myfunc("constant")

  7. What should I be aware of when I'm debugging multilanguage
     programs with Turbo Debugger?

     Turbo Debugger's default source language is "Source," which
     means it chooses the expression language based on the current
     source module. This can cause some confusion if your program
     has source modules written in different languages (like C
     and assembler). Since you are actually entering a language
     expression any time Turbo Debugger prompts you for a value
     or an address, you can encounter unexpected results.

     a. Even if you are in a CPU window or a Dump window, you
        must still enter addresses in the source language,
        despite the fact that the window displays in hex.
        For example, to display the contents of memory address
        1234:5678, you must type one of the following
        expressions, depending on your current source language:

          C            0x1234:0x5678
          Pascal        $1234:$5678
          Assembler     1234H:5678H

     b. When your current language is assembler, you must be
        careful when entering hex numbers, since they are
        interpreted EXACTLY as they would be in an assembler
        source file. This means that if you want to enter a
        number that starts with one of the hex digits A - F, you
        must first precede the letter with a 0 so Turbo Debugger
        knows you are entering a number. Likewise, if your
        number ends in B or D (indicating a binary or decimal
        number), you must add an H to indicate that you really want
        a hex number. For example,

          OK:   0aaaa   123dh   89abh

          BAD:  aaaa    123d    89ab

  9. Why does the text "Cannot be changed" come up when I do an
     assignment in the Data|Evaluate|Modify "New value" pane?

     If you use the Data|Evaluate|Modify command (Ctrl-F4) to
     change a variable by direct assignment, the "New value" pane
     will say "Cannot be changed." This doesn't mean the
     assignment didn't take effect. What it does mean is that the
     assignment expression as a whole is not a memory-referencing
     expression whose value you can change by moving to the
     bottom pane. Here are some examples of direct assignment
     expressions.

       C              x = 4
       Pascal         ratio := 1.234
       Assembler      wval = 4 shl 2

     If you had typed just "x", "ratio", or "wval" into the top
     pane, you would be able to move to the bottom pane and
     enter a new value. The direct assignment method using the
     "=" or ":=" assignment operator is quicker and more
     convenient if you don't care about examining the value of
     the variable before modifying it.

 10. Why does an inspector occasionally display question marks
     when inspecting a Borland C++ register variable?

     If you inspect a register variable that is not in the
     current scope, you'll see ???? for the value. A register
     variable only displays a value if the register is in your
     current scope (valid at the current location in your
     program).

 11. What is the most likely reason for Turbo Debugger to hang
     when starting up on a PC-compatible computer?

     If your computer is a Tandy 1000A, IBM PC Convertible, or NEC
     MultiSpeed, or if Turbo Debugger hangs when loading on your system,
     run TDINST and change an item in the Options|Miscellaneous
     menu so that NMI Intercept isn't set. Some computers use the NMI
     (Non-Maskable Interrupt) in ways that conflict with Turbo Debugger,
     so you must disable Turbo Debugger's use of this interrupt in order
     to run the program.

     Also, if you're using an 80386-based machine and have the
     SuperKey utility loaded, be careful not to press a key when
     TD386 is loading, since SuperKey may capture the keystroke
     and cause unexpected results.

 12. What could happen when global breakpoints are set on local
     variables?

     When you set global breakpoints using local variables, make
     sure the breakpoints are cleared before you exit the
     procedure or function that the variables are defined in. The
     best way to do this is to put a breakpoint on the last line
     of the procedure or function. If you do not clear the
     breakpoints, your program will break unexpectedly and may
     even hang on some machines because the breakpoints are being
     set in memory that is not currently being used by the
     procedure or function.

 13. How can I save options set in TDINST to TD286.EXE?

     If you have a configuration file (tdconfig.td) already made for
     TD.EXE, TD286.EXE will automatically use this configuration file.
     You can save a configuration made in TDINST to TD286.EXE directly
     if you state this on the command line. For instance,

       TDINST TD286.EXE

     When you want to save this configuration in TDINST, just select
     Save\Modify td.exe.

 14. Why is execution slower when tracing (F7) than when stepping
     (F8) through my programs?

     Turbo Debugger can do reverse execution. When you're tracing
     through your program, Turbo Debugger is saving all the information
     about the source line you just traced over. If you want faster
     execution you can (F8) step over the instruction or toggle the
     Full History option to "No" in the Execution History window.
     (Although reverse execution is always available in the CPU
     viewer this option must be toggled to "Yes" to work in the Module
     viewer.  The default setting is "No".)

 15. What are some of the issues I should be aware of with TD386?

     TD386.EXE is a small kernel program that puts the processor into
     virtual-86 mode, maps one chunk of extended memory into the low
     640K area, and loads TD.EXE into it.  It communicates with TD.EXE
     through the TDH386.SYS device driver.  When instructed to, TD386 maps a
     different chunk of extended memory into the low 640K area. It then
     loads the program to be debugged, into that same area.

     The debugging process continues with TD's telling TD386 what to do
     through TDH386.  When any exceptions occur, they are vectored off to
     the resident TD386 code which handles them. TD386 either switches back
     to TD's area and informs TD that an exception occurred or, if TD386
     can't figure out what happened, it simply dumps the registers to
     the screen and halts the CPU (since something bad could have
     happened to cause the exception)

     Because TD386 uses the virtual-86 mode of the 80386, it cannot
     coexist with any other programs that put the processor into v-86
     mode.  Programs that simulate EMS memory on a 386 or 486 machine
     usually use virtual-86 mode to do so.  These programs (such as
     QEMM, 386^MAX, CEMM, EMM386,...) are not compatible with TD386.

     If you need to use one of these EMS simulators for your program,
     then you should consider using TD286.EXE, which uses a different
     aspect of protected mode and IS compatible with these other
     programs.

     Note: HIMEM.SYS does not use virtual-86 mode and behaves
           just fine with TD386.


     As well as providing a communication path between TD386 and TD,
     TDH386 (the device driver) allows for the use of hardware
     breakpoints.  You can use the hardware breakpoints on any 386 or
     486 machine that has the device driver loaded and is running TD.EXE,
     TD286.EXE, or TD386.EXE.

     The only real difference between TD386 and the other two debuggers
     is that TD386 allows some extra breakpoints that the other debuggers
     do not (I/O access breaks, ranges greater than 16 bytes, and so on).

     A typical setup would be to load QEMM and then load TDH386.SYS into
     high memory.  With this setup, both TD.EXE and TD286.EXE will support
     hardware breakpoints and will take up the same amount of memory as
     they do without the device driver loaded.

     If you are using a SCSI device in your machine and TD386 gives you
     unexpected interrupt reports, make sure that the SCSI device driver
     is protected-mode-aware.  Adaptech SCSI cards come with a driver that
     should work just fine.  IBM PS/2's usually have a driver called
     DISK386.SYS that works in this situation.

 16. Why does TD286INS tell me that my A20 line is already enabled?

     If you are using a version of DOS that allows you to specify the
     "DOS=HIGH" command in CONFIG.SYS, you won't be able to run
     TD286INS.  What you should do is remove the 'DOS=HIGH' line, then run
     TD286INS, and then replace the "DOS=HIGH" line in CONFIG.SYS.

 17. Why do I have mouse problems when debugging Windows programs?

     When debugging, the first time you execute a Windows program, the mouse
     will work normally. For the second and subsequent runs, you must press
     any key before the mouse will function. This is a known problem with
     Windows.

     When the mouse driver is disabled for Windows, it will be disabled for
     TDW as well.  Starting TDW with the mouse support option (-p) has no
     effect.




2. Turbo Debugger for Windows (TDW), Windows debugging hints
------------------------------------------------------------
  View|Windows Messages

      If you set up View|Windows Messages to display messages for
      more than one procedure or handle or both, do not log all
      messages.  Instead, log specific messages for each procedure or
      handle.  If you log all messages, the system might hang, in
      which case you will have to reboot to continue.  This behavior
      is due to the large number of messages being transferred
      between Windows and TDW.

      When setting a break on the Mouse class of messages, note that
      a "mouse down" message must be followed by a "mouse up" message
      before the keyboard will become active again.  When you return
      to the application, you might have to press the mouse button
      several times to get Windows to receive a "mouse up" message.
      You'll know Windows has received the message when you see it in the
      bottom pane of the Windows Message window after the program breaks.

      If you enter a handle name but indicate that it's a
      procedure, TDW will accept your input and will not complain.
      However, when you run your program, TDW will not log any
      messages.  If TDW is not logging messages when you think you've
      set a handle, check the Add Window dialog box of the top left pane of
      the Windows Messages window to see if you've pressed the Handle button.

  View|Module

      The Debug Startup radio buttons are used for DLLs only.  To
      debug EXE startup, begin TDW with the Assembler-mode Startup
      command-line option (-l).

      When a program loaded into TDW is reset, the Load symbols
      radio buttons default to YES for all DLLs and applications
      with symbols, even if you specified NO for a given DLL or
      application prior to resetting the program.


3. TDW mouse support
--------------------
  TDW provides mouse support that allows you to manipulate elements
  of the user interface. Most TDW mouse operations are similar to
  Windows mouse operations. In the material that follows, we discuss
  tips for using a mouse under Windows and some uses of the mouse under
  TDW that are different from Windows mouse usage.

  o When the mouse driver is disabled for Windows, it will be disabled
    for TDW as well.  Starting TDW with the mouse support option
    (-p) has no effect unless you enable the Windows mouse driver.

  o If you have a mouse driver installed by default, TDW and the
    installation utilities will try to use your mouse. If you
    don't want to use your mouse during a debugging session, you
    can use the command-line switch '-p-' to turn the mouse off.
    You can also set this option in TDWINST in the Options\Input &
    Prompting dialog box.

  o When you're debugging a Windows application that uses the mouse
    and you reset the application and then run the program, it won't
    accept mouse clicks until you make a keyboard entry.

  o Using the mouse

    -  Most mice provide two or three buttons that allow for various
       functions inside an application. With TDW you can, among other
       things, use the left mouse button to select options, move items
       around on the screen, and set breakpoints.

    -  Double-clicking the mouse on an item in a list chooses the item.
       For instance, in the File|Open dialog box clicking the mouse once
       just highlights a file. Double-clicking loads the file.

    -  The right mouse button has some of the same functionality as the
       left mouse button, but you can also open local menus within TDW
       windows by using this button.

  o You can also choose the commands shown at the bottom of the screen,
    like F1-Help, by using the mouse.


4. TD mouse support
-------------------
  You use the mouse with TD just as you do with TDW. However, with
  TD you must install a mouse driver, which makes your mouse active
  with TD and other programs. Most mouse drivers will work with TD,
  but might have to be updated to a newer version if you're having
  problems using your current version. If you have problems with the
  mouse after you've loaded TD or TDINST, you might try using the
  Display Swap option that you can specify either in TDINST or on
  the command-line with the -ds switch.

  Consult your mouse manual to ensure proper use of the mouse
  and its driver. Early versions of mouse drivers don't support
  screen display modes larger than 80 columns by 24 lines. As a
  result, your mouse driver might not work correctly when you
  use TD's enhanced display modes (EGA 80x43, VGA 80x50, or
  EGA/VGA graphics modes).

/**************************** END OF FILE ********************************/

