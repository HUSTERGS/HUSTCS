
;   FILENAME: IFINDFIL.ASM
;
;   Copyright (c) 1988, 1992 by Borland International, Inc.
;
;   DESCRIPTION:  This module implement a routine that performs a recursive
;   search through a hard disk of a specified file.
;
;   ASSEMBLY INSTRUCTIONS: To assemble this module use the following
;   TASM command line.
;
;       TASM /dMDL=memorymodel ifindfil
;
;   'memorymodel' in the above command line may be replaced by TINY, SMALL,
;   MEDIUM, COMPACT, LARGE or HUGE. If assembling this module to run on
;   a 286/386 machine, turn on the P286 directive in order to take advantage of
;   286/386 specific instructions. For example:
;
;       TASM /dMDL=memorymodel /jP286 ifindfil

jumps

%tabsize 4

ifndef  MDL
    display "Error: This module requires that you provide a memory model"
    display "    definition on the command line. I.E. /dMDL=SMALL."
    err ; Force a fatal error
else
    ideal                   ; Use TASM's Ideal mode
%   model   MDL,pascal      ; Define the memory model

    include "iwhglobl.inc"
    include "imacros.mac"
    include "idos.inc"
    include "dos.inc"
    include "idos.mac"
    include "kbd.inc"
    include "bios.inc"
    include "ibios.mac"

    codeseg
        global      BreakPressed:byte  ; Check this often for a nonzero
                                       ; value. Terminate if a nonzero
                                       ; value is found.

    dataseg
        AllFiles    db  "*.*",0     ; ASCIIZ string representing all files
        SwitchChar  db  1,'\'       ; Directory seperating character
        CurrentDir  db  MAX_PATH_LENGTH dup (0)
        MakePascalString BlankLine, <13, 10>

        ; The following variable keep track of going through the
        ; file specifications that were given on the command line.
        FileSpecIndex db ?
        FileSpecPtr   dw ?


    codeseg

    macro   NewLine                 ; Force a new line
;;        ifdef  _286_
;;            push    seg BlankLine
;;            push    offset BlankLine
;;        else
;;            mov     ax, seg BlankLine
;;            push    ax
;;            mov     ax, offset BlankLine
;;            push    ax
;;        endif
        call    WritePascalString,seg BlankLine,offset BlankLine
    endm

TerminateKeyMssg db 13,10
                 db '**ERROR** Whereis terminated due to keypress.'
                 db 13,10,0

    ; The following messages should not include a line feed.
PauseKeyMssg      db 'Press space to continue....',13,0
PauseKeyEraseMssg db '                           ',13,0

    proc    FindFiles

    ;   This routine does a recursive search down through the directory
    ;   structure of a disk looking for a file. If the routine finds a
    ;   match it displays the complete drive\path\filename. The routine
    ;   uses the following algorithm:
    ;
    ;       make room for a local copy of the Dta
    ;       change directories to the location of the file we're looking for
    ;       find all matches in the current directory
    ;       for each sub-directory in the current directory
    ;           Do a recursive call to this routine
    ;       restore the original directory
    ;
    ;   The routine uses the global variable FileSpec as the specification
    ;   of the file to search for.
    ;   If any key is pressed, a message is printed and then this routine
    ;   calls Terminate.
    ;
    ;   Input
    ;       DS - points to the segment in which FileSpec resides
    ;       Path - A pascal style string representing the path in which to
    ;              search for the file
    ;   Output
    ;       none
    ;   Calling convention
    ;       Pascal
    ;   Registers modified
    ;       ax, bx, cx, dx, si, es, flags

    arg     Path:byte:MAX_PATH_LENGTH=PARM_SIZE
    local   DataTransferArea:byte:DTA_SIZE=LOCAL_SIZE ;

    ; The PASCAL calling convention on the MODEL statement causes TASM
    ; to do the following automatically.
;        push    bp
;        mov     bp, sp
;        ; make room for the Dta, Drive, Path and Filename on the stack
;        sub     sp, LOCAL_SIZE

        mov     [FileSpecIndex],1       ; Keep track which one we are searching
        mov     [FileSpecPtr],offset FileSpec


        mov     si, bp                  ; Get the address of the Dta buffer
        sub     si, DTA_SIZE
        push    ds                      ; Store ds before call to SetDTA
        SetDTA  <ss>, <si>              ; Set the current Dta address
        pop     ds                      ; Restore ds after SetDTA
        if @CodeSize eq 0               ; FindFiles is near
            add     si, DTA_SIZE + 5    ; Get the address of the Path
        else
            add     si, DTA_SIZE + 7    ; Get the address of the Path
        endif

        xor     bx, bx
        mov     bl, [byte ss:si-1]      ; Get the length byte
        cmp     bl, 1                   ; Check if the path is 1 letter. If it
        jle     ChangeDirs              ; is we don't want to remove it.
        cmp     [byte ss:si+bx-1], '\'  ; Check if the path ends with a '\'. If
        jne     ChangeDirs              ; it does, remove it.
        mov     [byte ss:si+bx-1], 0
        dec     [byte ss:si-1]
    ChangeDirs:
        push    ds
        ChangeDirectory <ss>, <si>      ; Change the directory
        GetCurrentDir   <0>, <seg CurrentDir>, <offset CurrentDir>
        pop     ds
        if (@Cpu and 100b) eq 100b
            push    seg CurrentDir
            push    offset CurrentDir
        else
            mov     ax, seg CurrentDir
            push    ax
            mov     ax, offset CurrentDir
            push    ax
        endif
        mov     ax, 0020h               ; Replace spaces with 0
        mov     cx, MAX_PATH_LENGTH
        call    FindAndReplace

    FirstFile:
        mov     ax,[FileSpecPtr]
        inc     ax                      ; Get past length byte
        FindFirst   <0FFh>, <ds>, <ax>
    NextFile:                           ; Find each of the matching files
        cmp     ax, 0
        jne     CheckNextFileSpec

        ; Check if the user has pressed a key to interrupt WHEREIS.
        GetKbdStatus
        jz      NoKey

        call    KeyWasPressed


        ; Come here to print a matching file.
    NoKey:
        if (@Cpu and 100b) eq 100b
            push    seg Drive           ; Get the address of the drive
            push    offset Drive        ; description
        else
            mov     ax, seg Drive
            push    ax
            mov     ax, offset Drive
            push    ax
        endif
        mov     al, [Drive]
        xor     ah, ah
        call    WritePascalString       ; Display the drive description
        mov     ax, seg CurrentDir
        mov     es, ax
        mov     di, offset CurrentDir
        cmp     [byte es:di], 'A'       ; Check if the string is empty
        jl      DontNeedBackSlash
        dec     di                      ; Decrement the offset of the pointer
    DontNeedBackSlash:
        push    es
        push    di
        call    WriteASCIIZString
        if (@Cpu and 100b) eq 100b
            push    seg SwitchChar
            push    offset SwitchChar
        else
            mov     ax, seg SwitchChar
            push    ax
            mov     ax, offset SwitchChar
            push    ax
        endif
        call    WritePascalString

        mov     si, bp
        sub     si, DTA_SIZE - (offset (Dta).Filename)
        push    ss  si  ; Push an extra copy of offset of filename

        ; Write the filename. Pass the address of the filename
        call    WriteASCIIZString,ss,si
        NewLine

        pop     si ax  ; Offset of filename   ax:si
        mov     di,offset CurrentDir
        push    ds                      ; Store ds before call to
                                        ; ExecuteDosCommand and SetDTA
        call    ExecuteDosCommand       ; Do the command for the file.

        mov     si, bp                  ; Get the address of the Dta buffer
        sub     si, DTA_SIZE
        SetDTA  <ss>, <si>              ; Set the current Dta address
        pop     ds                      ; Restore ds after SetDTA

        FindNext
        jmp     NextFile

    CheckNextFileSpec:
        cmp     [BreakPressed],0        ; Check for CTRL-BREAK
        jnz     GiveAbortMessage

        add     [FileSpecPtr],FILE_SPEC_SIZE    ; Point to next filespec
        mov     al,[FileSpecIndex]              ; Bump up counter
        inc     al
        mov     [FileSpecIndex],al
        cmp     al,[FileSpecCounter]
        jle     FirstFile                       ; Go back to search another filespec

    CheckDirectories:
        push    ds
        FindFirst   <010000b>, <(seg AllFiles)>, <(offset AllFiles)>
        pop     ds
    NextDirectory:
        cmp     ax, 0                   ; Check if we've found a sub-directory
        je      CheckAttributes
        jmp     Exit
    CheckAttributes:                    ; Check if it's a directory
        mov     si, bp                  ; Get the address of the attribute
        sub     si, DTA_SIZE - (offset (Dta).FileAttribute)
        mov     al, [byte ss:si]        ; Get the directory entries attributes
        and     al, 10000b
        cmp     al, 10000b
        jne     GetNextDirectory

        ; Check if the directory is '.' or '..'

        mov     si, bp                  ; Get the address of the attribute
        sub     si, DTA_SIZE - (offset (Dta).Filename)
        cmp     [byte ss:si], '.'       ; If it's '.' or '..' then skip
        je      GetNextDirectory        ; it

        ; Copy the new path onto the stack

        sub     sp, MAX_PATH_LENGTH     ; Make room on the stack
        mov     bx, sp
        push    ss                      ; Push segment address of Path
        mov     si, bp
        if @CodeSize eq 0               ; FindFiles is near
            add     si, 4               ; get offset of current path string
        else
            add     si, 6
        endif
        push    si                      ; Push offset of path
        push    ss                      ; Push address to copy to
        push    bx
        mov     al, [byte Path]         ; Get the path length
        inc     al                      ; Copy the length byte also
        call    ByteCopy                ; Copy the path onto the stack

        ; Append the new directory to the path on the stack

        push    es di                   ; Save es:di before call to
                                        ; GetASCIIZStrLen
        mov     si, bp                  ; Get the address of the current Dta

        ; Get the address of the directory name from it's location in the Dta

        sub     si, DTA_SIZE - (offset (Dta).Filename)
        call    GetASCIIZStrLen,ss,si   ; Get the length of the directory name
        pop     di es                   ; Restore es:di

        cmp     [byte es:di-1], '\'     ; Check if the path on the stack ends
        je      HasBackSlash            ; with a '\'. If not append one.
        mov     [byte es:di], '\'
        inc     di
        push    si
        mov     si, sp                  ; Adjust the length byte of the string
        inc     [byte ss:si+2]
        pop     si
    HasBackSlash:
        ; Copy the directory name
        call    ByteCopy,ss,si, \       ; Address of the directory name.
                         es,di          ; Address to copy directory name to

        mov     si, sp                  ; Adjust the length byte of the string
        dec     al                      ; we appended to. Don't include the
        add     [byte ss:si], al        ; terminating 0 in the length

        ; Do recursive call

        call    FindFiles               ; Do the search for the file(s)
        push    ds
        mov     ax, bp
        if  @CodeSize eq 0              ; Near code models
            add     ax, 5
        else
            add     ax, 7
        endif
        ChangeDirectory <ss>, <ax>      ; Change to the directory that was
        pop     ds                      ; active before the recursive call

;; Remember, the following cleanup is done automatically by Pascal Model.
;;        add     sp, MAX_PATH_LENGTH     ; Remove space allocated on the stack

        mov     si, bp
        sub     si, DTA_SIZE
        push    ds
        SetDTA  <ss>, <si>              ; Restore the Dta
        pop     ds
    GetNextDirectory:
        FindNext                        ; Find the next sub-directory
        jmp     NextDirectory
    Exit:

     ; Once again, the cleanup is done automatically because of PASCAL model.
;        add     sp, LOCAL_SIZE
;        pop     bp
        ret
    endp    FindFiles


    proc    KeyWasPressed

    ;   This routine handles pausing if a space or ^S was pressed,
    ;   or terminating WHEREIS if any other key was pressed.

        ; Throw out the key(s) that were pressed.
    DiscardKeys:
        GetChar
        cmp     al,' '          ; Check for space pressed to pause
        je      JustPausing
        cmp     al,'s'-'a'+1    ; Check for ^S pressed to pause
        je      JustPausing

    FlushKeyboard:
        GetKbdStatus
        jz   GiveAbortMessage
        GetChar
        jmp  FlushKeyboard


    GiveAbortMessage:
        ; Give a message to the user that WHEREIS is terminating.
        call    WriteASCIIZString,seg TerminateKeyMssg,offset TerminateKeyMssg

        call    Terminate


    JustPausing:
        ; Give a message to the user that WHEREIS is pausing
        call    WriteASCIIZString,seg PauseKeyMssg,offset PauseKeyMssg

    WaitForSpace:
        GetKbdStatus
        jz   WaitForSpace
        GetChar
        cmp  al,' '
        jne  FlushKeyboard

        ; Now get rid of the reminder
        call    WriteASCIIZString,seg PauseKeyEraseMssg,offset PauseKeyEraseMssg

        ret
    endp    KeyWasPressed


endif   ; ifndef MDL

end
