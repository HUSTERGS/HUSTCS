;********************************************************************
;* Show87 - Copyright (c) 1988, 1989 by Borland International, Inc. *
;* CONVERT2.INC - Include module for Show87                         *
;********************************************************************
;
;=============================================================================
; 8087 Number Conversion Routines
;
; These are routines to convert from floating point to integer numbers. All
; registers are preserved except those used to return parameters. All
; parameters are passed through registers. It is assumed that DS = ES = CS.

;================================================
; Convert a floating point real number to a
; decimal integer and a base ten exponent.
; Expects the number to be converted in ST and
; the number of significant bits (i.e. bits to
; place in the significand) in AX.  The
; significand integer value is returned in ST
; and the signed exponent is returned in AX.
;===================================================
;
Flt2dec proc near
        push    bp
        sub     sp, 8
        mov     bp, sp

        fstcw   word ptr [bp]                   ;save control word
        mov     word ptr [bp+2], 03bfh          ;new control word, round
                                                ;  to nearest
        fldcw   word ptr [bp+2]                 ;load control word
        mov     word ptr [bp+4], ax

         ;--- convert number

        fld     st(0)
        fxtract                                 ;extract exponent
        fstp    st(0)                           ;pop top (significand)
        fisubr  word ptr [bp+4]                 ;subtract bits for significand
        fldl2t                                  ;load log2(10)
        fdiv                                    ;divide, get 10**X
        frndint                                 ;round to nearest
        fist    word ptr [bp+6]                 ;save exponent
        call    Exp10                           ;get exponent factor
        fmul                                    ;adjust real number for exponent

        ;--- finished

        fldcw   word ptr [bp]                   ;restore control word
        add     sp, 6
        pop     ax
        neg     ax
        pop     bp
        ret
 Endp           ;Flt2dec

;================================================
; Calculate 10 to the power of ST. Return result
; in ST. Uses 10**N = 2**(N*Log2(10)).

Exp10 proc near
        fldl2t                                  ;load Log2(10)
        fmul                                    ;multiply
        call    Exp2                            ;raise 2 to ST power.
        ret
 Endp           ;Exp10

;================================================
; Calculate 2 to the power of ST. Return result
; in ST(0).

Exp2 proc near
        push    bp
        sub     sp, 6                           ;room for local data
        mov     bp, sp                          ;start of local data

        fstcw   word ptr [bp]                   ;save control word
        mov     word ptr [bp+2], 03bfh          ;new control word, round
                                                ;   to nearest
        fldcw   word ptr [bp+2]                 ;load control word

;--- for 2**X, where X = W + F or X = W - F, where W is a whole number and
;--- F is between 0 and .5 (inclusive), ST gets F and ST(1) gets W

        fld     st(0)                           ;duplicate number
        frndint                                 ;round to integer,
                                                ;  ST => W
        fxch                                    ;exchange
        fsub    st, st(1)                       ;get difference,
                                                ;  ST => F

;--- check sign of fractional portion (F)

        ftst                                    ;set flags
        fstsw   word ptr [bp+4]                 ;save flags
        fwait
        and     byte ptr [bp+5], 45h            ;mask relevant bits
        cmp     byte ptr [bp+5], 1              ;check negative bit
        ja      Exp2err                         ;jump if other bits
                                                ;   set, error
        je      Exp2neg                         ;jump if negative

;--- fractional part is positive for

        f2xm1                                   ;ST => (2**F) - 1
        fld1                                    ;load one
        fadd                                    ;ST => 2**F
        fxch                                    ;put whole portion (W)
                                                ;   on top
        fld1                                    ;load one
        fscale                                  ;ST => 2**W
        fmulp   st(2), st                       ;ST(2) => (2**F) * (2**W)
        fstp    st(0)                           ;pop stack
        jmp     short Exp2don

;--- fractional part is negative

Exp2neg :
        fabs                                    ;take absolute value
        f2xm1                                   ;ST => (2**F) - 1
        fld1                                    ;load one
        fadd                                    ;ST => 2**F
        fxch                                    ;put whole portion (W) on top
        fld1                                    ;load one
        fscale                                  ;ST => 2**W
        fdivrp  st(2), st                       ;ST(2) => (2**W) / (2**F)
        fstp    st(0)                           ;pop stack

;--- finished

Exp2don :
        fldcw   word ptr [bp]                   ;restore control word
        add     sp, 6
        pop     bp
        ret

;--- zero or error

Exp2err :
        fstp    st(0)
        fstp    st(0)                           ;clear stack
        fld1                                    ;return one
        jmp     Exp2don
 endp           ;Exp2
