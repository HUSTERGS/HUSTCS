
;    FILENAME: OFLFLUSH.ASM
;    Copyright (c) 1988, 1989 by Borland International, Inc.
;
;    Description: This module implements the routine FileFlush. FileFlush
;    flushes the write buffer.
;
;    ASSEMBLY INSTRUCTIONS: To assemble this module use the following 
;    TASM command line. 
; 
;        TASM oflflush

include globals.inc

_TEXT   segment

    FileFlush proc

    ;    Input 
    ;        bx - file record offset
    ;        cx - number of bytes to write
    ;    Output (of INT 21h, Function 40h)
    ;        cf - set if error occurred
    ;        ax - error code
    ;            0 - if disk full
    ;            5 - if access denied
    ;            6 - if handle invalid or not open
    ;    Registers modified
    ;        ax

    push    cx
    push    dx
    push    ds

    ;--- check if buffer needs flushing

    mov     ax, [bx+8]         ;handle
    lds     cx, [bx+4]         ;data pointer
    or      cx, cx             ;check if any data
    jz      filflu3

    ;--- write buffer

    mov     WORD PTR es:[bx+4], 0 ;clear data pointer
    push    bx
    mov     bx, ax
    sub     dx, dx             ;start of segment
    mov     ah, 40h            ;function
    int     21h                ;execute
    pop     bx
    jc      filflu2            ;jump if error
    cmp     ax, cx             ;check if all bytes written
    je      filflu3

    ;--- finished, error writing buffer

filflu1:
    sub     ax, ax             ;code 0 if bytes not all written
filflu2:
    stc
    pop     ds
    pop     dx
    pop     cx
    ret

    ;--- finished, no error

filflu3:
    clc
    pop     ds
    pop     dx
    pop     cx
    ret
    ret
    FileFlush endp

_TEXT    ends

end
