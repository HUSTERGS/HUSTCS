;[]-----------------------------------------------------------------[]
;|      SETJMP.ASM -- entry points for Windows versions of setjmp()  |
;[]-----------------------------------------------------------------[]

;
;       C/C++ Run Time Library - Version 5.0
; 
;       Copyright (c) 1987, 1992 by Borland International
;       All Rights Reserved.
; 

        INCLUDE RULES.ASI

        assume cs:_TEXT

public  SETJMP
public  LONGJMP

extrn   CATCH : far
extrn   THROW : far

_TEXT   segment

SETJMP  proc DIST
        jmp CATCH       ; the catch buffer used by Windows is smaller
                        ; than the one used by TC, so we can simply
                        ; call the Windows function with our buffer
SETJMP  endp

LONGJMP proc DIST
        push    bp
        mov     bp, sp
        pushf
        cmp     word ptr [bp+6], 1      ; generates carry if param == 0
        adc     word ptr [bp+6], 0      ; if it was zero now it's one
        popf
        pop     bp
        jmp THROW
LONGJMP endp

ends

end
