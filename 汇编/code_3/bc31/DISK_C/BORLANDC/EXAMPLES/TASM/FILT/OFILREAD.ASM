
;    FILENAME: OFILREAD.ASM
;    Copyright (c) 1988, 1989 by Borland International, Inc.
;
;    Description: This module implements the routine FileRead. FileRead
;    reads from a file.
;
;    ASSEMBLY INSTRUCTIONS: To assemble this module use the following 
;    TASM command line. 
; 
;        TASM ofilread

include globals.inc

_TEXT   segment

    FileRead proc

    ;    Input 
    ;        bx - file record offset
    ;        cx - buffer size
    ;        di - location of bytes
    ;    Output
    ;        cf - set if error occurred
    ;        ax - error code
    ;        (cf set and ax = 0 if EOF)
    ;            0 - if EOF and 0 bytes are read
    ;        cx - number of bytes read
    ;    Registers modified
    ;        None

    pushf
    push    cx
    push    dx
    push    di
    push    si
    cld
    mov     dx, [bx+6]      ;buffer segment

    ;--- read bytes from buffer

filred1:
    mov     ax, [bx+10]     ;bytes in buffer
    mov     si, [bx+4]      ;data pointer
    sub     ax, si          ;bytes available
    jz      filred3         ;jump if none

    push    ds
    push    cx
    cmp     ax, cx          ;check if enough
    jae     filred2
    mov     cx, ax          ;read what's available

filred2:
    push    cx
    mov     ds, dx
    rep     movsb                   ;copy bytes
    pop     ax
    pop     cx
    pop     ds
    mov     [bx+4], si      ;save data pointer
    sub     cx, ax          ;get bytes not yet read
    jz      filred4         ;jump if finished

    ;--- read into buffer

filred3:
    call    FileFill        ;read a buffer full
    jnc     filred1

    ;--- finished

filred4:
    pop     si
    pop     di
    pop     dx
    pop     cx
    jc      filred5
    popf
    clc
    ret

filred5:
    popf
    stc
    ret
    FileRead endp

_TEXT    ends

end
