
;    FILENAME: OFILCLOS.ASM
;    Copyright (c) 1988, 1989 by Borland International, Inc.
;
;    Description: This module implements the routine FileClose. FileClose 
;    closes a file.
; 
;    ASSEMBLY INSTRUCTIONS:  To assemble this module use the following  
;    TASM command line.     
;  
;        TASM ofilclos

include globals.inc

_TEXT   segment

    FileClose proc

    ;    Input 
    ;        bx - file record offset
    ;        cx - number of bytes
    ;        si - location of bytes
    ;    Output
    ;        cf - set if error occurred
    ;        ax - error code
    ;        (cf set and ax = 0 if EOF)
    ;            0 - if EOF and 0 bytes are read
    ;    Registers modified
    ;        None

    push    bx

    ;--- flush file buffer

    test    WORD PTR [bx], 1  ;test if open for writing
    jz      filclo1
    call    FileFlush         ;flush buffer
    jc      filclo2

    ;--- close file

filclo1:
    mov     ah, 3eh         ;function
    mov     bx, [bx+8]      ;handle
    int     21h             ;execute
    pop     bx
    ret

    ;--- close file, error on flush

filclo2:
    push    ax
    mov     ah, 3eh         ;function
    mov     bx, [bx+8]      ;handle
    int     21h             ;execute
    pop     ax
    pop     bx
    stc
    ret
    FileClose endp

_TEXT    ends

end
