
;   FILENAME: IPARAM.ASM
;
;   Copyright (c) 1988, 1992 by Borland International, Inc.
;
;   DESCRIPTION: This module implements two routines that manage the
;   command line parameters passed to the program. The routine ParamCount
;   returns the number of parameters passed to the program while the
;   routine ParamString returns a pointer to the referenced parameter
;   string. This module uses ideal mode syntax.
;
;   ASSEMBLY INSTRUCTIONS: To assemble this module use the following
;   TASM command line.
;
;       TASM /m /dMDL=memorymodel iparam
;
;   /m in the above command line allows TASM to resolve jumps and other
;   operations to their shortest form and get rid of extra NOPs.
;   'memorymodel' in the above command line may be replaced by TINY, SMALL,
;   MEDIUM, COMPACT, LARGE or HUGE. If assembling this module to run on
;   a 286/386 machine, turn on the P286 directive in order to take advantage of
;   286/386 specific instructions. I.E.
;
;       TASM /m /dMDL=memorymodel /jP286 iparam
;
;   NOTE: This module requires that the main program declare and initialize
;   the global variable PspAddress.

%tabsize 4

ifndef  MDL
    display "Error: This module requires that you provide a memory model"
    display "       definition on the command line. I.E. /dMDL=SMALL."
    err ; Force a fatal error
else

    ideal                           ; Use TASM's Ideal mode
%   model   MDL,pascal              ; Define the memory model

    include "dos.inc"
    include "idos.inc"
    include "kbd.inc"
    include "iwhglobl.inc"

    NotCalled  equ 0FFh ; ParamCount was already called once

    dataseg
        ; Declare variables to store the parsed parameters and parameter
        ; count.

        ParmCount   DB  NotCalled       ; ParamCount initializes this variable
                                        ; the first time it is called.
        ParmList    DB  7Fh DUP (0)     ; Allocate enough space for a 127
                                        ; character command line
;        global  PspAddress:word         ; Define extrn variable

    codeseg

;    global  ParamCount:proc             ; Public procs
;    global  ParamString:proc

;    global  LocateString:proc           ; Declare external procs
;    global  FindBytePos:proc
;    global  FindAndReplace:proc
;    global  ByteCopy:proc
;    global  SkipSpaces:proc

    proc    IsDelimiter
    ;   This routine checks the character in AL to see if it is a delimiter.
    ;   Valid delimiters are   ''  ""  []
    ;
    ;   Input
    ;       al - Character to check
    ;   Output
    ;       al contained a delimiter:
    ;            al - matching delimiter
    ;            Carry set
    ;       al did not contain a delimiter
    ;            Carry not set
    ;   Calling conventions
    ;       NA
    ;   Registers modified
    ;       al

        cmp     al,'"'
        je      ItIs
        cmp     al,"'"
        je      ItIs
        cmp     al,"]"
        je      ItIs
        cmp     al,"["
        je      ItIsSquare
        jmp     IsNot
    ItIsSquare:
        mov     al,"]"
    ItIs:
        stc
        ret
    IsNot:
        clc
        ret
    endp    IsDelimiter



    ; Use the following pattern to look for trailing spaces.
    label TrailingSpace word
        db " ",0dh


    proc    ParamCount

    ;   This routine returns the number of command line parameters passed to
    ;   the program. Parameters are delimited by spaces or tabs. Double or
    ;   single quotes can enclose parameters that include spaces or tabs
    ;   inside them.
    ;
    ;   While the function is parsing the command line it stores copies of
    ;   each of the parameters in the modules data segment. The strings are
    ;   stored in Turbo Pascal format. That is they are stored with a
    ;   preceeding length byte. The first time the routine is called it also
    ;   stores the result in the variable ParmCount in the modules data
    ;   segment. Any subsequent calls simply return the contents of
    ;   ParmCount.
    ;
    ;   Input
    ;       none
    ;   Output
    ;       al - Number of parameters
    ;   Calling conventions
    ;       NA
    ;   Registers modified
    ;       ax, bx, cx, DX, di, si, es, Flags

    local   SearchChar:byte=LocalSymbolSize ; Declare local variables

        ; Point es:di to location where the parsed parameters will be stored

        if  @DataSize   eq  0
            mov     ax, @data       ; Using near data model
        else
            mov     ax, @fardata    ; Using far data model
        endif
        mov     es, ax

        ; Check if the function was called previously. If it was we
        ; don't want to parse the command line again.

        cmp     [es:ParmCount], NotCalled
        je      FirstCall
        jmp     AlreadyCalled

    FirstCall:
        mov     di, offset ParmList ; es:di now points to modules storage
        push    ds

        ; Note that we don't actually allocate any memory to store the
        ; DOS Psp. We simply use the STRUC declaration to determine
        ; the offsets of the fields in the memory allocated by DOS.

        mov     ds, [PspAddress]    ; Load the segment address of the Psp
        mov     si, offset (Psp).CommandTail + 1

        xor     cx, cx              ; Initialize cx
        xor     bx, bx              ; Store # of parameters in bx


        ; Get the length of the DOS command line from the Psp.

        mov     cl, [ds:Psp.CommandTail.LengthByte]

        ; Check if the command line is empty and leave if it is.

        cmp     cl, 0
        jne     ReplaceTabs
        jmp     InitParmCount

    ReplaceTabs:

        ; Convert any tabs in the command line to spaces in order to
        ; make the parsing simpler.

        push    cx  ; Store value of cx & es:di because call to
        push    es  ; FindAndReplace modifies them.
        push    di

        ; Push the address of the DOS command line

        push    ds
        if (@Cpu and 100b) eq 100b
            push    offset (Psp).CommandTail + 1
        else
            mov     ax, offset (Psp).CommandTail + 1
            push    ax
        endif

        ; Define the bytes to search/replace

        mov     ax, (SPACE shl 8) + TAB
        call    FindAndReplace          ; Replace all tabs with spaces
        pop     di es
                                        ; Restore previous values of cx & es:di
        pop     cx


        ; Now we need to trim the end of the string

        mov     ax,[TrailingSpace]
        mov     bx,cx

    CheckForTrailing:
        cmp     ax,[si+bx-1]
        jne     StringTrimmed           ; String trimmed, but some still left

        ; Space found at end, move the carriage return forward a byte
        mov     [byte ptr si+bx-1],0dh
        dec     cx
        dec     bx
        cmp     cl, 0
        jne     CheckForTrailing

    StringTrimmed:
        mov     bx,0                    ; Set it back to zero for counting
                                        ; parameters

        jz      InitParmCount           ; If CL=0, then Z set.
                                        ; If end of string, Z not set!


        ; Skip any spaces at the beginning of the parameter list.

        push    es di                   ; Save registers that will be modified

        push    ds si                   ; Pass the address of the string
        call    SkipSpaces
        pop     si ds                   ; Update ds:si with start of next
                                        ; parameter
        pop     di es                   ; Restore es:di to point to location
                                        ; to store the next parameter

        ; Now parse the command line. Note that after each iteration of
        ; this loop ds:si points to the beginning of the next parameter
        ; and es:di points to location in the modules data segment where
        ; the next parameter will be stored.

    ParseCmdLine:
        inc     bx                      ; Increment the parameter count
        mov     al,[si]
        call    IsDelimiter
        jc      HandleDelimiter
        jmp     WhiteSpace

    HandleDelimiter:
        mov     [SearchChar], al
        inc     si  ; Point to the next character in the parameter list
        dec     cx  ; Adjust number of bytes left to check
        jmp     FindDelimiter

    WhiteSpace:
        mov     al, SPACE
        mov     [SearchChar], al         ; Use space, tab or eoln as delimiter

    FindDelimiter:
        push    bx es di                 ; Store bx, es:di

        ; Push the address of the start of the next parameter for the call
        ; to FindBytePos

        push    ds
        push    si

        ; Find the end of the parameter. After the call to FindBytePos
        ; ax = the number of bytes searched and es:di is pointing to
        ; the byte after the last one checked. cx=# of bytes left to
        ; check in the command line string.

        call    FindBytePos
        push    es                      ; Move the pointer returned by
        pop     ds                      ; FindBytePos into ds:si
        mov     si, di

        pop     di es bx                ; Restore es:di, bx


    ; Now copy the parameter into its storage location

    CopyParameter:
        mov     dx, si                  ; Calculate the offset of the source
        sub     dx, ax                  ; string
        dec     dx

        ; If there was a delimiter other than a space, we want to make
        ; sure that we get the trailing delimiter too.
        cmp     [SearchChar],SPACE
        jne     BumpCopyCount

        or      cx,cx                   ; Check if CX=0 (If at end of arguments)
        jnz     StoreLength

    BumpCopyCount:
        inc     al   ; We need to copy and extra character

    StoreLength:
        push    cx bx es si di          ; Save the values of registers
                                        ; modified by the call to ByteCopy
        mov     [byte es:di], al        ; Store length of parameter in
        inc     di                      ; the length byte

        ; Copy the array of characters
        call    ByteCopy,ds,dx,\  ; Source string
                         es,di    ; Destination string

        pop     di si es bx cx          ; Restore the previous values of the
                                        ; registers modified by ByteCopy
        add     di, ax                  ; Move pointer past end of parameter
        inc     di

        cmp     [byte ds:si], SPACE
        jne     NoWhiteSpace

        ; Now find the first character of the next parameter.

        push    es di                   ; Save registers that will be modified

        push    ds si                   ; Pass the address of the string
        call    SkipSpaces

        pop     si ds                   ; Update ds:si with start of next
                                        ; parameter
        pop     di es                   ; Restore es:di to point to location
                                        ; to store the next parameter

    NoWhiteSpace:
        jcxz    InitParmCount
        jmp     ParseCmdLine            ; Get the next parameter on the
                                        ; command line.
    InitParmCount:

        ; Initialize ParmCount so the routine doesn't have to parse the
        ; command line more than once.

        mov     [byte es:ParmCount], bl
        pop     ds                      ; Restore the programs data segment

    AlreadyCalled:
        mov     al, [byte es:ParmCount] ; Return the previously determined
        ret
    endp    ParamCount

    proc    ParamString

    ;   This routine returns a far pointer to the parameter referenced in
    ;   al. Before looking for the parameter, the function calls ParamCount
    ;   to assure that the parameter exists. This has the side-affect of
    ;   assuring that ParamCount parses and copies the parameters into the
    ;   modules data segment.
    ;
    ;   Input
    ;       al - Parameter to return
    ;   Output
    ;       al = Desired Parameter
    ;           es:di - Far pointer to parameter
    ;       al = 0 - Parameter doesn't exist
    ;   Calling conventions
    ;       NA
    ;   Registers modified
    ;       ax, bx, cx, di, si, es, Flags

        ; First check if the parameter exists

        push    ax                  ; Save index to desired parameter
        call    ParamCount
        pop     bx                  ; Restore index to desired parameter
        cmp     bl, al              ; Check if the parameter exists
        jg      InvalidParameter
        mov     al, bl              ; Pass parameter index in al

        ; Point to modules data segment

        if  @DataSize   eq  0
            mov     bx, @data       ; Using near data model
        else
            mov     bx, @fardata    ; Using far data model
        endif
        mov     es, bx              ; Make es:si point to the data area
        mov     di, offset ParmList

        call    LocateString        ; Determine the address of the string
        jmp     Exit

    InvalidParameter:
        xor     al, al

    Exit:
        ret
    endp    ParamString

endif   ; ifndef MDL

end

