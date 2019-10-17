;[]-----------------------------------------------------------------[]
;|      FBSTP.ASM                                                    |
;[]-----------------------------------------------------------------[]

;
;       C/C++ Run Time Library - Version 5.0
; 
;       Copyright (c) 1987, 1992 by Borland International
;       All Rights Reserved.
; 

        include rules.asi

        emul            ; generated emulated instructions

ld_temp        STRUC
        ld_fraction     dw      ?
                        dw      ?
                        dw      ?
                        dw      ?
        ld_exponent     dw      ?
ld_temp ENDS


Code_Seg@

; void _fbstp  ( long double z, short *packedDecimal)

; This is a helper function for __xcvt() used only on Windows,
; which currently doesn't emulate the FBSTP instruction.
;
; It pops and converts the floating point number on the top of the x87
; stack to a packed decimal integer, storing the result at ES:DI.

; int exp;              /* exponent part of z */
; short frac[4];        /* fractional part of z */
; short res[5]          /* packed BCD number */

; void PutFourDigits ( int rem, int posn )

;     res.digits [posn] = rem % 10;
;     rem = rem / 10;
;     res.digits [posn+1] = rem % 10;
;     rem = rem / 10;
;     res.digits [posn+2] = rem % 10;
;     res.digits [posn+3] = rem / 10;

PutFourDigits   PROC    ;  rem in DX, posn in DI

        push    ax
        push    cx

        mov     al, 100
        mov     cl, 4
        xchg    ax, dx

        div     dl
        mov     dl, ah
        aam                     ; AH, AL = AL DIV 10, AL MOD 10
        shl     ah, cl
        or      ah, al
        xchg    ax, dx
        aam
        shl     ah, cl
        or      al, ah
        mov     ah, dh
        stosw

        pop     cx
        pop     ax
        ret

PutFourDigits   ENDP


; exp  = z.exp;
; frac = z.frac;

; if (exp < 1) res = 0;

; else if (exp > 60) res = +infinity;

; else
;     while (exp < 64)
;         frac = frac DIV 2;
;         exp  = exp + 1;

;     frac = frac + carry; /* rounding */

;     res = 0;

;     PutFourDigits (frac % 10000, 0);
;     frac = frac / 10000;
;     PutFourDigits (frac % 10000, 4);
;     frac = frac / 10000;
;     PutFourDigits (frac % 10000, 8);
;     frac = frac / 10000;
;     PutFourDigits (frac % 10000, 12);
;     frac = frac / 10000;

;     res.digits [16] = frac % 10;
;     res.digits [17] = frac / 10;

;     res.sign = z.sign;

;     return res;

        public  __fbstp
__fbstp PROC    NEAR

; Convert floating point value on TOS to packed BCD at ES:DI

        push    bp
        mov     bp, sp
        push    si                      ; save SI
        push    di                      ; ES:DI points to result
po?zPtr equ     ([bp - 4].w0)

        cld                             ; forward string direction

; exp  = z.exp;
; frac = z.frac;

        FSTP    tbyte ptr es:[di]       ; value is converted in place
        FWAIT
        mov     ax, es:[di].ld_exponent
        and     ax, 07fffh              ; remove sign bit
        sub     ax, 03ffeh              ; subtract (bias+1)
        mov     bx, es:[di].ld_fraction.w0
        mov     cx, es:[di].ld_fraction.w1
        mov     dx, es:[di].ld_fraction.w3
        mov     si, es:[di].ld_fraction.w2


; if (exp < 1)
;    res = 0
;
; /* will the result exceed 999,999,999,999,999,999 ? */
; else (z > [3C, DE0B 6B3A 763F FFF0])
;    res = +infinity

        cmp     ax, 0
        jl      po@underflowJmp

        sub     ax, 3Ch
        jl      po@inRange
        jg      po@overflowJmp
        cmp     dx, 0DE0Bh
        jb      po@inRange
        ja      po@overflowJmp
        cmp     si, 06B3Ah
        jb      po@inRange
        ja      po@overflowJmp
        cmp     cx, 0763Fh
        jb      po@inRange
        ja      po@overflowJmp
        cmp     bx, 0FFF0h
        ja      po@overflowJmp


; else
;     while (exp < 64)
;         frac = frac / 2;
;         exp  = exp + 1;

po@inRange:
        mov     ah, 0                           ; excess precision for rounding
        sub     al, 4

po@wordAlign:
        add     al, 16
        jg      po@bitAlign

        mov     ah, bh
        mov     bx, cx
        mov     cx, si
        mov     si, dx
        sub     dx, dx
        jmp     po@wordAlign

;----
po@underflowJmp:        jmp     short   po@underflow
po@overflowJmp:         jmp     short   po@overflow
;----

po@bitAlign:
        sub     al, 16
        jnl     po@aligned
po@anotherBit:
        shr     dx, 1
        rcr     si, 1
        rcr     cx, 1
        rcr     bx, 1
        rcr     ah, 1
        inc     al
        jl      po@anotherBit

po@aligned:

;     frac = frac + carry; /* rounding */

        add     ah, ah
        adc     bx, 0
        adc     cx, 0
        adc     si, 0
        adc     dx, 0           ; DX:SI:CX:BX is now an integer < 2^60

;     PutFourDigits (frac % 10000, 0);
;     frac = frac / 10000;

                                ; DX < 4096 since 2^60 = 4096 * 2^48
        xchg    ax, si
        mov     si, 10000
        div     si
        xchg    ax, cx
        div     si
        xchg    ax, bx
        div     si              ; frac = CX:BX:AX < 2^47, DX = mod 10000

        call    PutFourDigits   ; DX is parameter

;     PutFourDigits (frac % 10000, 4);
;     frac = frac / 10000;

        sub     dx, dx
        xchg    ax, cx
        div     si
        xchg    ax, bx
        div     si
        xchg    ax, cx
        div     si              ; frac = BX:CX:AX < 2^34, DX = mod 10000

        call    PutFourDigits   ; DX is parameter

;     PutFourDigits (frac % 10000, 8);
;     frac = frac / 10000;

        mov     dx, bx
        xchg    ax, cx
        div     si
        xchg    ax, cx
        div     si              ; frac = CX:AX < 2^20, DX = mod 10000

        call    PutFourDigits   ; DX is parameter


;     PutFourDigits (frac % 10000, 12);
;     frac = frac / 10000;

        mov     dx, cx
        div     si              ; frac = AX < 2^7, DX = mod 10000

        call    PutFourDigits   ; DX is parameter

;     res.digits [16] = frac % 10;
;     res.digits [17] = frac / 10;

        aam                     ; AH, AL = AL / 10, AL % 10
        mov     cl, 4
        shl     ah, cl
        or      al, ah
        stosb

po@end:

;     res.sign = z.sign;

        mov     si, po?zPtr
        mov     al, es:[si].ld_exponent.by1
        and     al, 080h        ; isolate sign bit
        stosb

        pop     di
        pop     si
        pop     bp
        ret

; ----

po@underflow:
        mov     al, 0

po@extreme:
        mov     cx, 9
rep     stosb
        jmp     short   po@end


po@overflow:
        mov     al, 99h
        jmp     short   po@extreme


; ----


__fbstp endp

Code_EndS@

        end
