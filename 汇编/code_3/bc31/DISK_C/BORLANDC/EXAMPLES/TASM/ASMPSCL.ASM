; Turbo Assembler    Copyright (c) 1988, 1991 By Borland International, Inc.

; ASMPSCL.ASM

; From the Turbo Assembler Users Guide

; Called as: TEST(i, j, k);
;
i       equ     8           ;leftmost parameter
j       equ     6
k       equ     4           ;rightmost parameter
;
        .MODEL  small
        .CODE
        PUBLIC  TEST
TEST    PROC
        push    bp
        mov     bp,sp
        mov     ax,[bp+i]   ;get i
        add     ax,[bp+j]   ;add j to i
        sub     ax,[bp+k]   ;subtract k from the sum
        pop     bp
        ret     6           ;return, discarding 6 parameter bytes
TEST    ENDP
        END
