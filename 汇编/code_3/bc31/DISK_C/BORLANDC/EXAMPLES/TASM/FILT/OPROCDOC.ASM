
;    FILENAME: OPROCDOC.ASM
;    Copyright (c) 1988, 1989 by Borland International, Inc.
;
;    Description: This module implements the routine ProcDoc. ProcDoc
;    processes an entire document, one line at a time.
;
;    This module uses MASM mode syntax and standard segment directives. 
; 
;    ASSEMBLY INSTRUCTIONS: To assemble this module use the following 
;    TASM command line. 
; 
;        TASM oprocdoc

include globals.inc

_TEXT   segment

    ProcDoc proc

    ;    This procedure processes an entire document line by line.
    ;
    ;    Input 
    ;       INP_EOF - designates an end-of-file condition
    ;       INP_ERR - designates an input error condition
    ;       OUT_ERR - output error
    ;       Options - the options being used
    ;       SUP_EOF - suppress output EOF
    ;       LinBuf - starting location of the line buffer
    ;       EOF - ASCII 26
    ;       OutBlk - output control block
    ;    Output 
    ;       si - Line buffer updated
    ;    Registers modified 
    ;       bx, cx, si

propag1:
    call    ProcLine
    push    ax
    sub     ax, ax
    or      ax, INP_EOF
    or      ax, INP_ERR
    or      ax, OUT_ERR
    test    InpSta, ax
    pop     ax
    jz      propag1

    ;--- write EOF

    test    Options, SUP_EOF    ;check if suppressed
    jnz     propag2
    test    InpSta, INP_ERR     ;
    jnz     propag2             ;-- check for errors
    test    InpSta, OUT_ERR     ;
    jnz     propag2

    mov     cx, 1               ;bytes to write
    lea     si, LinBuf          ;put it in line buffer
    mov     BYTE PTR [si], EOF  ;EOF character
    lea     bx, OutBlk          ;output control block
    call    FileWrite           ;write to file

propag2:
    ret
    ProcDoc endp

_TEXT    ends

end
