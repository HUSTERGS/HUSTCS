; Turbo Assembler    Copyright (c) 1988, 1991 By Borland International, Inc.

; CONCISE.ASM

; From the Turbo Assembler Users Guide

    .MODEL   small,C
    EXTRN    C IntDivide:PROC
    .CODE
    PUBLIC   C Average
Average      PROC  C ValuePtr:DWORD,NumberOfValues:WORD
    les      bx,ValuePtr
    mov      cx,NumberOfValues
    mov      ax,0
AverageLoop:
    add      ax,es:[bx]
    add      bx,2              ;point to the next value
    loop     AverageLoop
    call     IntDivide C,ax,NumberOfValues
    ret
Average      ENDP
    END
