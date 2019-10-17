
;    FILENAME: OFILWRIT.ASM
;    Copyright (c) 1988, 1989 by Borland International, Inc.
;
;    Description: This module implements the routine FileWrite. FileWrite 
;    writes to a file. 
; 
;    ASSEMBLY INSTRUCTIONS:  To assemble this module use the following  
;    TASM command line.  
;  
;        TASM ofilwrit

include globals.inc

_TEXT   segment

    FileWrite proc

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


    pushf
    push    cx
    push    dx
    push    di
    push    si
    cld
    mov     dx, [bx+6]      ;buffer segment

    ;--- copy bytes to buffer

filwrt1:
    mov     ax, [bx+2]      ;buffer size
    mov     di, [bx+4]      ;data pointer
    sub     ax, di          ;buffer space available
    jz      filwrt3         ;jump if none, must flush first

    push    es
    push    cx
    cmp     ax, cx          ;check if all bytes fit
    jae     filwrt2
    mov     cx, ax          ;set to maximum

filwrt2:
    push    cx
    mov     es, dx
    rep     movsb
    pop     ax
    pop     cx
    pop     es
    mov     [bx+4], di      ;save data pointer
    sub     cx, ax          ;get bytes not yet written
    jz      filwrt4         ;jump if finished

    ;--- write buffer

filwrt3:
    call    FileFlush       ;flush buffer first
    jnc     filwrt1         ;loop back if no error

    ;--- finished

filwrt4:
    pop     si
    pop     di
    pop     dx
    pop     cx
    jc      filwrt5
    popf
    clc
    ret

filwrt5:
    popf
    stc
    ret
    FileWrite endp

_TEXT    ends

end
