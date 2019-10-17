
;   FILENAME: IDELCHAR.ASM
;
;   Copyright (c) 1988, 1992 by Borland International, Inc.
;
;   DESCRIPTION:  This module implements a routine that deletes n characters
;   from a string starting at a specified index.
;
;   ASSEMBLY INSTRUCTIONS: To assemble this module use the following
;   TASM command line.
;
;       TASM /dMDL=memorymodel idelchar
;
;   'memorymodel' in the above command line may be replaced by TINY, SMALL,
;   MEDIUM, COMPACT, LARGE or HUGE.

%tabsize 4

ifndef  MDL
    display "Error: This module requires that you provide a memory model"
    display "    definition on the command line. I.E. /dMDL=SMALL."
    err ; Force a fatal error
else

    ideal                   ; Use TASM's Ideal mode
%   model   MDL             ; Define the memory model

    codeseg

    global  DeleteChar:proc

    proc    DeleteChar

    ;   This routine deletes a specified number of characters from a pascal
    ;   style string starting at position n. Note that the routine doesn't
    ;   check to make sure enough characters are left before deleting them.
    ;
    ;   Input
    ;       StrAddress - Far pointer to the string
    ;       cx - Number of characters to delete
    ;       ax - Starting position
    ;   Output
    ;       none
    ;   Calling conventions
    ;       Pascal
    ;   Registers modified
    ;       ax, cx, di, si, es, flags

    arg StrAddress:dword=PARM_SIZE

        push    bp
        mov     bp, sp
        push    ds
        cld
    DeleteNextChar:
        push    cx
        les     di, [StrAddress]        ; Get strings address
        dec     [byte es:di]            ; Decrement the length byte
        mov     cl, [byte es:di]
        lds     si, [StrAddress]
        add     di, ax                  ; Point to the appropriate
        add     si, ax                  ; memory locations for the move
        inc     si
        rep     movsb                   ; Move the bytes
        pop     cx
        loop    DeleteNextChar
        pop     ds
        pop     bp
        ret     PARM_SIZE
    endp    DeleteChar

endif   ; ifdef MDL

end
