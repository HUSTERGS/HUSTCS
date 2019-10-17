;   FILENAME: IWHEREIS.ASM
;
;   Copyright (c) 1988, 1992 by Borland International, Inc.
;
;   DESCRIPTION:  This program does a search for the file(s) specified on the
;   command line. It can also perform a DOS command on each file that is
;   found.
;
; Syntax: WHEREIS [d:][path]filename filename filename... [dos_command]
;  dos_command is a command surrounded by "",'', or []. It will be called
;  for each file that is found. It should include at least one of these:
;     %1 - Insert full path, filename and extension
;     %2 - Filename and extension (no path)
;     %3 - Only the path.
;     %4 - Only the filename before the extension followed by a .
;     %5 - Only the extension, preceeded by a .
;  For example to delete all .BAK files on a drive:
;     WHEREIS  *.BAK [DEL %2]",13,10>
;
;   Note that dos_command may be any valid DOS command, including invoking
;   batch files or built-in DOS commands. Note that the RMDIR, (also RD),
;   command should not be used on the directory that WHEREIS is currently
;   executing in.
;
;
;   ASSEMBLY INSTRUCTIONS: To assemble this module use the following
;   TASM command line.
;
;       TASM /m /dMDL=memorymodel iwhereis
;
;   /m in the above command line allows TASM to use extra passes to resolve
;   jumps and other operations to their shortest form and get rid of extra NOPs.
;   'memorymodel' in the above command line may be replaced by TINY, SMALL,
;   MEDIUM, COMPACT, LARGE or HUGE. If assembling this module to run on
;   a 286/386 machine, turn on the P286 directive in order to take advantage of
;   286/386 specific instructions. For example:
;
;       TASM /m /dMDL=memorymodel /jP286 iwhereis
;
;   SYSTEM REQUIREMENTS:
;       TASM 2.0
;       256K
;       DOS 2.0 or later

; TURBO ASSEMBLER NEW FEATURES:
; TASM 2.0 has many new features. The following is a list of a few of
; them that have been used to make this program easier and more readable.
; To find the examples in the code, just seach for "**n", where n is a
; number from the following table.

; Special TASM 2.0 features:
;    **1  - TASM automatically pushes the immediate value in a way that
;           preserves all registers if the processor mode is 8086. If
;           186 or above, then TASM pushes the value directly.
;    **2  - Many lines of assembler are replaced by the use of the
;           extended call syntax.
;    **3  - Conditional jumps that go out of range are automatically
;           adjusted to a different code sequence that allows the
;           further jump. Other jumps, even if forward referenced, are
;           automatically changed to the shortest possible code sequence
;           without extra NOPs, because of multipass capability.
;    **4  - TASM handles forward referenced variables that occur
;           in a segment other than DS: by automatically inserting
;           the proper segment override, and without causing phase errors.
;    **5  - TASM's ability to handle multiple objects on a single
;           PUSH or POP command makes coding shorter.
;    **6  - TASM's new line continuation feature while in IDEAL mode
;           makes long argument lists very easy.


jumps      ; Have TASM automatically resolve out of range jumps

%tabsize 4

ifndef  MDL
    display "Error: This module requires that you provide a memory model"
    display "    definition on the command line. I.E. /dMDL=SMALL."
    err ; Force a fatal error
else

    ideal                   ; Use TASM's Ideal mode
%   model   MDL,pascal      ; Define the memory model
                            ; Set language to PASCAL so we can rely on TASM's
                            ; new extended call features.

    ProgramVersion EQU "2.01"

    include "iwhglobl.inc"  ; Public symbol declarations
    include "imacros.mac"   ; Various macros
    include "bios.inc"
    include "ibios.mac"
    include "kbd.inc"      ; Keyboard scan codes
    include "dos.inc"      ; Equates representing DOS functions/services
    include "idos.mac"

    stack   7FFFh           ; Allocate 32K stack




    codeseg
    SavedDS     dw  ?       ; For the control-break handler to find the path
                            ; variables for restoring the original path and
                            ; drive.

    BreakPressed    db 0    ; Set by Int1B handler to one if
                            ; CTRL-BREAK pressed. Allows us to break even
                            ; if DOS BREAK is set to off.
    global BreakPressed:byte     ; So other modules can check it!


    dataseg

    PspAddress  dw  ?       ; Segment address of Program Segment Prefix(PSP)
    DisplayPage db  0       ; Current display page

    Old1BHandlerSeg dw ?
    Old1BHandlerOfs dw ?


    include "WHUSAGE.INC"   ; Usage screen declaration

    ; Pascal style strings to store the parsed file specification.

    Drive       db  0," :  "
    Path        db  MAX_PATH_LENGTH  dup (0)

    ; Following is used as a scratchpad when parsing additional filespecs
    ; from the command line.
    tempDrive   db  0," :  "
    tempPath    db  MAX_PATH_LENGTH  dup (0)


    FileSpecCounter db 0    ; Count how many filespecs we parsed
    NextFileSpec    dw 0    ; Location of where to put next filespec

    DrivePtr    dw   ?      ; Points to where the file parse routine should
    PathPtr     dw   ?      ; place its results.


    FileSpec    db  MAX_FILE_SPECS dup (FILE_SPEC_SIZE dup (0))
                            ; Make room for the filenames, each with a
                            ; preceeding length byte and terminating 0

    db  '\'
    HomeDirectory   db  MAX_PATH_LENGTH dup (0)
    OldDrive        db  ?

    ; When working through the arguments on the command line to setup
    ; filespecs,
    CurrentArgument db  MAX_PATH_LENGTH+FILE_SPEC_SIZE dup (0)

    codeseg

    proc    GetArgument
    ;   This procedure gets an argument transfered into a temporary
    ;   buffer where all leading spaces are removed from the string.
    ;
    ;   Input
    ;       AL contains number of argument to get.
    ;   Output
    ;       If argument exists:
    ;          AL number of argument
    ;          ES:DI points to temporary argument buffer
    ;       If argument does not exist:
    ;          AL contains 0
    ;   Calling conventions
    ;       NA
    ;   Registers modified
    ;       all

        call    ParamString
        or      al,al
        jz      @@Finished      ; A zero return means no more arguments.



        push    ax              ; Save it to restore return value from ParamString

; **2
;   The following lines are neatly replaced by a single line CALL with
;   extended syntax. All the variables are automatically pushed on the
;   stack in the proper order, automatically.
;
;        push    es
;        push    di
;
;        if (@Cpu and 100b) eq 100b
;            push    seg CurrentArgument
;        else
;            mov     ax, seg CurrentArgument
;            push    ax
;        endif
;        if (@Cpu and 100b) eq 100b
;            push    offset CurrentArgument
;        else
;            mov     ax, offset CurrentArgument
;            push    ax
;        endif

        xor     ah,ah
        mov     al,[byte es:di]
        inc     ax

        call    ByteCopy,es,di,seg CurrentArgument,Offset CurrentArgument

    @@DeleteSpaces:
        cmp     [CurrentArgument+1], SPACE
        jne     @@NoMoreSpaces

; **2
;        if (@Cpu and 100b) eq 100b
;            push    seg CurrentArgument
;        else
;            mov     ax, seg CurrentArgument
;            push    ax
;        endif
;        if (@Cpu and 100b) eq 100b
;            push    offset CurrentArgument
;        else
;            mov     ax, offset CurrentArgument
;            push    ax
;        endif

        mov     cx, 1           ; Remove the first character
        mov     ax, 1           ; from the string
        call    DeleteChar,seg CurrentArgument,offset CurrentArgument

        jmp     @@DeleteSpaces
    @@NoMoreSpaces:
        mov     ax,seg CurrentArgument
        mov     es,ax
        mov     di,offset CurrentArgument

        pop     ax



    @@Finished:
        ret
    endp    GetArgument



    dataseg

MakePascalString  SearchMssg,<"WHEREIS parameters:",13,10>

    codeseg
    proc    Show_Args
    ;   This procedure displays all the command line parameters sent
    ;   to the program.
    ;
    ;   Input
    ;       none
    ;   Output
    ;       none
    ;   Calling conventions
    ;       NA
    ;   Registers modified
    ;       all

        push es di ax                 ;**5
        call WritePascalString,ds,offset SearchMssg
        mov  [argcount],1             ;**4

    @@Show_loop:
        mov  al,[argcount]
        call GetArgument
        or   al,al         ; Check for zero return. Means no more arguments.
        jz   @@Show_Exit

        call WritePascalString,es,di  ; Show the current argument

        push seg BlankLine            ;**1
        push offset BlankLine
        call WritePascalString

        inc  [argcount]               ;**4
        jmp  @@Show_loop

    @@Show_Exit:
        pop  ax di es                 ;**5
        ret

    argcount db 1                     ;**4
    endp    Show_Args



    proc Main

    ;************************* Program Entry Point ***************************
    ; Execution of the program begins here.

    EntryPoint:
        mov     ax, @data       ; Initialize ds by moving segment address
        mov     ds, ax          ; of data segment into ds register
        push    bp              ; Setup a starting stack frame.
        mov     bp, sp

        call    Initialize      ; Initialize data structures, etc.

        call    Show_Args


        mov     [FileSpecCounter],0  ; FileSpecCounter has # files found so far
        mov     [NextFileSpec],offset FileSpec
        mov     [PathPtr],offset Path
        mov     [DrivePtr],offset Drive


        mov     al,[FileSpecCounter]
    ProcessFileSpec:                 ; Jump to here if AL already loaded
        cmp     al,MAX_FILE_SPECS
        je      @@StartFileSearch    ;**3

        inc     al
        call    GetArgument
        or      al,al
        jz      @@StartFileSearch    ; If al=0, we are at the end of arguments.

        mov     al,[byte es:di+1]
        call    IsDelimiter
        jc      HandleDosCommand

; **2
;        push    es              ; Store the location of the unparsed file spec.
;        push    di
;
;        ; Pull apart the drive, path and filename so we can store the
;        ; filename specification.
;
;        push    ds              ; Push the address to store the drive spec. in
;        if (@Cpu and 100b) eq 100b
;            push    offset Drive
;        else
;            mov     ax, offset Drive
;            push    ax
;        endif
;        push    ds              ; Push the address to store the path spec. in
;        if (@Cpu and 100b) eq 100b
;            push    offset Path
;        else
;            mov     ax, offset Path
;            push    ax
;        endif
;        push    ds              ; Push address to store filename spec. in
;        if (@Cpu and 100b) eq 100b
;            push    offset FileSpec
;        else
;            mov     ax, offset FileSpec
;            push    ax
;        endif

        ; Parse the filename into it's components
        call    ParseFilename,es,di, \             ;Filespec to be parsed
                              ds,[DrivePtr],   \   ;**6
                              ds,[PathPtr],    \
                              ds,[NextFileSpec]

        mov     al,[FileSpecCounter]
        or      al,al
        jz      CheckFirstArg     ; If al is zero, we are checking first
                                  ; argument, so we can allow drive and
                                  ; path specification.

        mov     bx,[PathPtr]
        cmp     [byte bx], 0      ; Check if the parsed path is empty
        jne     @@IllegalPath
        mov     bx,[DrivePtr]     ; Check if the parsed drive is empty
        cmp     [byte bx],0
        jne     @@IllegalPath

        jmp     @@GetAnotherFileSpec

    @@IllegalPath:                ; Give an error for path on parameter other
                                  ; than the first.
        call    PathAfterFirst


    CheckFirstArg:
       ; For the next arguments, set the pointers to dummy areas
       ; since we don't pay attention to the path and drive for
       ; arguments other than the first.
        mov     [PathPtr],offset tempPath
        mov     [DrivePtr],offset tempDrive

        cmp     [byte Path], 0          ; Check if the path is empty
        jne     HaveAPath
        mov     [byte Path], 1
        mov     [byte Path+1], '\'
    HaveAPath:
        cmp     [byte Drive], 0         ; Check if a drive definition exists
        je      DontChangeDrives
        cmp     [byte Drive+1], 61h     ; Check if the drive letter is lower
        jng     IsCapitalized           ; case
        sub     [byte Drive+1], 20h     ; Capitalize the drive letter
    IsCapitalized:
        mov     al, [byte Drive+1]
        sub     al, 'A'
        ChangeDrive <al>                ; Change to the appropriate drive
        jmp     DoneWithFirstArg
    DontChangeDrives:
        mov     [byte Drive], 2         ; Initialize the drive
        mov     al, [byte OldDrive]
        mov     [byte Drive+1], al      ; string with the
        add     [byte Drive+1], 'A'     ; current drive.
    DoneWithFirstArg:
        jmp     @@GetAnotherFileSpec


    HandleDosCommand:
        ; If a DOS command is given, it is surrounded by quotes.
        ; We need to strip the quotes, and store it in the module that
        ; handles executing DOS commands.
        call    ParseDosCommand
        jnc     @@DoneWithArg           ; If no errors, we are done with this arg
        call    OnlyOneDosCommand

    @@GetAnotherFileSpec:
        add     [NextFileSpec],FILE_SPEC_SIZE

        ; Increment the FileSpecCounter
        mov     al,[FileSpecCounter]
        inc     al
        mov     [FileSpecCounter],al  ; FileSpecCounter has # files found so far
    @@DoneWithArg:
        jmp     ProcessFileSpec

    @@StartFileSearch:
        ; We are now done analyzing the command line parameters.
        ; Copy the start path onto the stack

        sub     sp, MAX_PATH_LENGTH     ; Make room on the stack
        mov     si, sp

        xor     ah, ah
        mov     al, [byte Path]         ; Get the path length
        inc     al                      ; We want to copy the length byte also
        inc     al                      ; And the null terminator
        call    ByteCopy,ds,offset Path,ss,si   ; Copy the path onto the stack


        call    FindFiles               ; Do the search for the file(s)
        call    Terminate               ; End the program
    ;*************************************************************************
    endp    main


    proc    Terminate

    ;   This procedure handles exiting from WHEREIS and restoring the
    ;   original directory and drive.

        mov     ax, [SavedDS]
        mov     ds,ax
        mov     al, [byte OldDrive]     ; Get the original disk drive
        ChangeDrive <al>                ; Restore the original disk drive
        ChangeDirectory <seg HomeDirectory>, <((offset HomeDirectory) - 1)>

        mov     es,[Old1BHandlerSeg]
        mov     bx,[Old1BHandlerOfs]
        SetVector  1Bh, es, bx

        mov     ah, DOS_TERMINATE_EXE
        int     DOS_FUNCTION
    endp    Terminate


    proc    Int1B far

    ;   This procedure handles intercepting CTRL-BREAK so that the
    ;   main directory searching loop can break out.

        mov     [BreakPressed],1        ; Set break flag
        iret

    endp    Int1B



    proc    Initialize

    ;   This procedure initializes all global variables and data structures
    ;   used by the program.
    ;
    ;   Input
    ;       none
    ;   Output
    ;       none
    ;   Calling conventions
    ;       NA
    ;   Registers modified
    ;       ax, flags

        ; Store the PSP address by storing es in the variable PspAddress.
        ; Note that we do it this way instead of using DOS function 62h because
        ; the function is only available on DOS 3.0 or later.

        mov     [PspAddress], es

        push    ds
        GetCurrentDir   <0>, <seg HomeDirectory>, <offset HomeDirectory>
        pop     ds
        GetDrive                        ; Get the current disk drive
        mov     [byte OldDrive], al     ; Save it


        ; Install a control break handler.
        push    ds
        mov     ax,ds         ; Save DS for future reference by break handler!
        mov     [SavedDS],ax
        SetVector  23h,<seg Terminate>,<offset Terminate>
;        mov     ah,25h        ; Int 25 = Set interrupt
;        mov     al,23h
;        mov     dx,seg Terminate
;        mov     ds,dx
;        mov     dx,offset Terminate
;        int     21h

        ; Also, so the main loop for going thru directories can respond
        ; in a timely fashion to ctrl-break being pressed, install a
        ; handler for vector 1Bh.

        GetVector  1Bh

        pop     ds
        mov     [Old1BHandlerSeg],es
        mov     [Old1BHandlerOfs],bx
        push    ds

        SetVector  1Bh, <seg Int1B>, <offset Int1B>

        pop     ds


        ; Verify that the user provided command line parameters.

        call    ParamCount
        or      al, al                  ; Were any parameters passed by user?
        jnz     @@Exit
        call    UsageScreen             ; If no, display usage screen

    @@Exit:

        ret
    endp    Initialize


    proc    UsageScreen

    ;   This routine displays a 'usage' screen that describes the syntax for
    ;   using WHEREIS. It then terminates the program.
    ;
    ;   Input
    ;       ds - Points to data segment where usage screen text is located
    ;   Output
    ;       none
    ;   Calling conventions
    ;       NA
    ;   Registers modified
    ;       ax, cx, dx

        call    WriteAsciizString,ds,offset Syntax
        call    Terminate               ; Terminate program
    endp    UsageScreen


    proc    PathAfterFirst

    ;   This routine displays a 'usage' screen that tells the user that
    ;   drive and path info may only be given on the first argument.
    ;   It then terminates the program.
    ;
    ;   Input
    ;       ds - Points to data segment where usage screen text is located
    ;   Output
    ;       none
    ;   Calling conventions
    ;       NA
    ;   Registers modified
    ;       ax, cx, dx

        call    WritePascalString,ds,offset OnlyFirst    ;**2
        call    Terminate               ; Terminate program
    endp


    proc    OnlyOneDosCommand

    ;   This routine displays a 'usage' screen that tells the user that
    ;   drive and path info may only be given on the first argument.
    ;   It then terminates the program.
    ;
    ;   Input
    ;       ds - Points to data segment where usage screen text is located
    ;   Output
    ;       none
    ;   Calling conventions
    ;       NA
    ;   Registers modified
    ;       ax, cx, dx

        call    WritePascalString,ds,offset OnlyOneCommand
        call    Terminate               ; Terminate program
    endp    OnlyOneDosCommand


endif   ; ifndef MDL

end EntryPoint
