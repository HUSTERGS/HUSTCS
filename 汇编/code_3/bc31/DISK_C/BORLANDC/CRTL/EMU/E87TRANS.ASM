;
;       C/C++ Run Time Library - Version 5.0
; 
;       Copyright (c) 1986, 1992 by Borland International
;       All Rights Reserved.
; 

subttl  e87trans

ifdef _WINDOWS

f87_Sine    equ <__f87_Sine>
f87_Cosine  equ <__f87_Cosine>
f87_Tangent equ <__f87_Tangent>
f87_ArcTan  equ <__f87_ArcTan>
f87_Log     equ <__f87_Log>
f87_Log2    equ <__f87_Log2>
f87_Log10   equ <__f87_Log10>
f87_Exp     equ <__f87_Exp>
f87_Exp2    equ <__f87_Exp2>
f87_Exp10   equ <__f87_Exp10>


        PUBLIC  __f87_Sine,  __f87_Cosine,  __f87_Tangent,  __f87_ArcTan
        PUBLIC  __f87_Log,   __f87_Log2 ,  __f87_Log10
        PUBLIC  __f87_Exp,   __f87_Exp2,  __f87_Exp10

else

E87Seg@

endif


; special constants are placed here

piBy4   dt      3FFEC90FDAA22168C235r
piBy2   dt      3FFFC90FDAA22168C235r

    NANtrig             dd      0FFC04200r
    NANlog              dd      0FFC04800r
    NANpower            dd      0FFC04A00r
half            dd      03F000000r

sqrt2   dt      3FFFB504F333F9DE6485r

infinity        dd      7F800000R               ; plus infinity



; {
; General notes:

; - operands are on the iNDP stack
; - results will be on the iNDP stack
; - AX,BX,CX,DX may be consumed.  Others must be preserved.
; - SS, DS, ES belongs to the application program and must be preserved.
; - all procedures are near and should quit by near return.

ASSUME  SS: nothing
ASSUME  DS: nothing
ASSUME  ES: nothing

; - unnormals are not specifically processed because this module is
;       intended to work with HLL's which place results into IEEE
;       "double" format, whereas only the IEEE "temporary" format can
;       handle unnormals.  If you want to run with assembler programs
;       that may use unnormals then you should check these algorithms
;       for what happens with un-normal parameters.  De-normals are
;       processed correctly, since they have been arranged to follow
;       the same paths as zeroes with only slight extra care needed to
;       accomodate them.
; }



f87_Sine:

        mov     cl, 0           ; remember we want the Sine
        jmp     short   trig


f87_Cosine:

        mov     cl, 2           ; remember we want the Cosine
        jmp     short   trig



f87_Tangent   PROC

        mov     cl, 4           ; remember we want the Tangent


; the following code is shared by Sine, Cosine, and Tangent

trig:

; trig_sign     CH
; trig_fun      CL
; trig_octant   AL
trig_status     equ     [bp-2].w0

        fxam                            ; '87 works while we enter routine

        push    bp
        mov     bp, sp
        lea     sp, trig_status

        fstsw   trig_status
        wait
        mov     ah, trig_status.by1
        sahf                            ; FL now reflects FXAM status
        jc      trig_badParam
        jnz     trig_normal

trig_tiny:                              ; denormal or zero
        cmp     cl, 2                   ; are we trying for cosine ?
        jne     trig_noChange           ;   Sin or Tan (tiny) = tiny
        fstp    ST(0)                   ; pop stack
        fld1                            ; Cos (tiny) = 1.0
trig_noChange:
        jmp     short   trig_endJmp

trig_badParam:                          ; NAN, infinite, or Empty
        jz      trig_empty              ; st(0) was empty
        jnp     trig_NAN                ; st(0) was NAN
        fstp    st(0)                   ; pop st(0)
        fld     NANtrig                 ; st(0) was infinite, now NAN
        ftst                            ; trigger exception
trig_NAN:
trig_empty:
        jmp     short   trig_endJmp


; For numbers of size 2^62 or larger in magnitude, the error of just
;       one lsb in the parameter is equivalent to at least 0.25 radian,
;       and so it is spurious to compute exact results.

; Note that parameters between 2^62 and 2^64 could be exact integers, for
;       which the result may be valid.  However, as we are designing
;       this module to support an HLL which will be using IEEE Long for
;       ordinary storage of variables, only numbers up to 2^53 could be
;       exactly represented (and indeed the limit of 2^62 on parameter is
;       far beyond accurate range).

; This reasoning is also convenient, since the 8087 REM instruction
;       does not process numbers differing by more than 64 bits magnitude.

trig_tooBig:
        fcompp          ; convenient double pop
        fld     NANtrig
        ftst                            ; trigger exception
trig_endJmp:
        jmp     trig_end



trig_normal:                            ; or un-normal
        fabs
        fld     piBy4
ifdef _WINDOWS
        fxam            ; From Intel 287 doc, if quotient is less than 2 then
                        ; C3 equals the value C1 had before the FPREM.
                        ; The FXAM clears C1 since PI/4 is positive.
                        ; NOTE: This behavior does not happen on my 287, but
                        ; it does in the Windows emulator
endif
        fxch
        fprem

; while the '87 crunches that, we check the sign the parameter had

        mov     ch, 2
        and     ch, ah                  ; what was the sign ?
        shr     ch, 1                   ; CH = sign

        fstsw   trig_status
        wait
        mov     ah, trig_status.by1
        sahf
        jp      trig_tooBig


; apologies for the following mindbending paragraph.  It takes fewer
;       bytes than a table look-up.

        mov     al, 3
        and     al, ah          ; select the C3, C1, and C0 status bits
        shl     ah, 1
        shl     ah, 1
        rcl     al, 1           ; arrange them in the ls 3 bits of BX
        add     al, 0FCh
        rcl     al, 1           ; al now contains the octant number

        cmp     cl, 2                   ; are we doing Cosine ?
        jne     trig_notCosine

        add     al, cl                  ; Cos (x) = Sin (x + 2 octants)
        mov     ch, 0                   ; Cosine has even symmetry around 0
trig_notCosine:
        and     al, 7


; the octants 1,3,5,7 need (pi/4 - x) as their operand

        test    al, 1
        jz      trig_evens

        fsub                            ; overwrites pi/4 in st(1), pops.
        jmp     short   trig_ptan

; the octants 0,2,4,6 must check against zero operand and remove pi/4
;       from st(1)

trig_evens:
        fstp    st(1)                   ; st(0) overwrites st(1), pops

trig_ptan:
        fptan           ; returns ST(1)/ST(0) = Tan

; while the '87 crunches that, lets decide what to do with the result

        cmp     cl, 4                   ; was it Tangent ?
        je      trig_tangent

; sine or cosine, are similar, varying only in phase of the octant, which
;       we have already adjusted so that the calculation is now only for
;       Sine.

;   octant      sine
;       0       sin (x)
;       1       cos (pi/4 - x)
;       2       cos (x)
;       3       sin (pi/4 - x)
;       4       - sin (x)
;       5       - cos (pi/4 - x)
;       6       - cos (x)
;       7       - sin (pi/4 - x)

        test    al, 3
        jpe     trig_sineOctant         ; even-parity is Sine forms

; Sin (s) = ST(1) / Sqrt (ST(0)^2 + ST(1)^2)
; Cos (x) = ST(0) / Sqrt (ST(0)^2 + ST(1)^2)

trig_cosOctant:
        fxch

trig_sineOctant:
        fld     st(1)           ; make a copy of ST(1)

        fmul    st, st(0)
        fxch
        fmul    st, st(0)
        fadd
        fsqrt

; while sqrt is crunching, what sign do we give the final result ?

        shr     al, 1
        shr     al, 1
        xor     al, ch
        jz      trig_sineDiv

        fchs                    ; cause result to be negative

trig_sineDiv:
        fdiv
        jmp     short   trig_end  ; complete calculation in the caller's time



trig_tangent:

; Tangent is a repeating pattern over 4 octants:

;   octant      tangent
;       0       sin (x) / cos (x)
;       1       cos (pi/4-x) / sin (pi/4 - x)
;       2       -cos (x) / sin (x)
;       3       -sin (pi/4 - x) / cos (pi/4 - x)

; When we arrive here AL = octant and ST(0) = x OR pi/4-x, already
;       adjusted for the octant.

; The PTAN instruction is already initiated, so we now decide what
;       to do with the result.

        mov     ah, al
        shr     ah, 1
        and     ah, 1                   ; octants 2, 3 are negatives
        xor     ah, ch                  ; combine with parameter's sign
        jz      trig_tanSigned

        fchs

trig_tanSigned:
        test    al, 3
        jpe     trig_ratio      ; octants 0, 3 have even parity

; in a freak case, like arg = pi/2 exactly, might get divide by 0
; return tan(pi/2) = +INF, although arguably it should generate an exception
        fxch
        ftst
        fstsw   trig_status
        fwait
        test    trig_status.by1, 40h    ; C3 flag
        jz      trig_ratio
        fcompp                          ; pop st(0) and st(1)
        fld     infinity
        jmp     short   trig_end  ; complete calculation in the caller's time

trig_ratio:
        fdiv
trig_end:
        mov     sp, bp
        pop     bp
        ret                     ; '87 calculates while we return

f87_Tangent   ENDP



; There are two symmetries used here:

; a)    ATan (1/x) = Pi/2 - ATan (x)
; b)     ATan (-x) = - ATan (x)

; Special cases are:

;  0 = ArcTan (0)
;  Pi/2 = ArcTan (infinity)


f87_ArcTan    PROC

atan_status     equ     [bp-2].w0

        fxam                            ; keep '87 busy in parallel

        push    bp
        mov     bp, sp
        lea     sp, atan_status

        fstsw   atan_status
        wait
        mov     ah, atan_status.by1
        sahf                            ; FL now reflects FXAM status
        xchg    cx, ax                  ; save for later negation check
        jc      atan_badParam
        jnz     atan_normal

atan_tiny:                              ; denormal or zero
        jmp     short   atan_end        ; Atan (tiny) = tiny


atan_badParam:                          ; NAN, infinite, or Empty
        jz      atan_empty              ; st(0) was empty
        jnp     atan_NAN                ; st(0) was NAN
        fstp    st(0)                   ; st(0) was infinite, pop it
        fld     piBy2                   ;   Atan (infinity) = pi/2
        jmp     short   atan_setSign


atan_of1:
        fcompp                          ; pop stack twice
        fld     piBy4
        jmp     short   atan_setSign


atan_normal:
        fabs
        fld1
        fcom
        fstsw   atan_status
        wait
        mov     ah, atan_status.by1
        sahf                            ; FL now reflects FCOM status

        je      atan_of1                ; st(1)=st(0)=1 is a special case
        jnc     atan_ordered

        fxch                            ; st(1) > st(0) requires inversion

atan_ordered:
        fpatan
        jnc     atan_setSign            ; flags still indicate FCOM status

        fld     piBy2
        fsub
        xor     ch, 02                  ; invert sign flag

atan_setSign:
        test    ch, 02                  ; what was parameters true sign ?
        jz      atan_end

        fchs                            ; parameter was negative

atan_NAN:
atan_empty:
atan_end:
        mov     sp, bp
        pop     bp
        ret

f87_ArcTan    ENDP



; Log2 (X) = Log2 (X)

f87_Log2:
        fld1
        jmp     short   DoLogs


; Log10 (X) = Log10 (2) * Log2 (X)

f87_Log10:
        fldlg2
        jmp     short   DoLogs


; Log (X) = Log (2) * Log2 (X)

f87_Log:
        fldln2
;       jmp     short   DoLogs
;       fall thru to DoLogs




DoLogs  PROC

log_temp                equ     [bp-10]
log_status      equ     [bp-10].w0

        fxch                            ; keep '87 busy in parallel

        push    bp
        mov     bp, sp

        fxam

        lea     sp, log_status

        fstsw   log_status
        wait
        mov     ah, log_status.by1
        sahf                            ; FL now reflects FXAM status
        jc      log_badParam
        jz      log_tiny
        test    ah, 2                   ; was parameter negative ?
        jz      log_normal

log_negative:
log_tiny:                               ; denormal or zero
log_tooBig:
        fstp    st(0)                   ; pop st(0)
        jmp     short   log_indefinite

log_badParam:                           ; NAN, infinite, or Empty
        jz      log_empty               ; st(0) was empty
        fstp    st(1)                   ; pop st(1)
        jnp     log_NAN                 ; st(0) was NAN

;infinite arg
        fstp    st(1)                   ; pop st(1)
        test    ah, 2                   ; was parameter negative ?
        jz      log_end

log_indefinite:
        fstp    st(0)                   ; pop st(0)
        fld     NANlog                  ; st(0) was infinite, now NAN

log_NAN:
log_empty:
        ftst                            ; trigger exception
        jmp     short   log_end


log_normal:

; the first million 8087s and 80287s had a bug
; fyl2x failed if x = smallest 10-byte real > 1
; FYL2X(1,x) gave you garbage *only* if x = 1+2**-63:

;If you looked at Intel's CEL library code, you would see some code that
;checks if difference between x and 1 is < 2^-16, and if so does a ylogxp1
;instead.  This was explicitly commented there as a work around for an old
;chip bug.  The problem comes in the argument reduction not normalizing the
;mantissa after subtracting 1 from it, prior to doing the Cordic reduction.

; If anyone decides this case is too obscure to bother with,
; or that everyone has bug-free chips,
; then just delete the code from here to log_normal1.

; test whether number is near +1 by examining bits directly
        fld     st(0)           ; duplicate TOS
;       lea     sp, log_temp    ; space already allocated
        fstp    tbyte ptr log_temp;
        fwait

; +1 is stored as 0000 0000 0000 8000 3FFF
        cmp     word ptr log_temp[8], 3FFFh
        jne     log_normal1
        cmp     word ptr log_temp[6], 8000h
        jne     log_normal1

; arg now in range [1,1+2^-16].
        fld1
        fsub
        fyl2xp1
        jmp     short log_end

log_normal1:
        fyl2x

log_end:
        mov     sp, bp
        pop     bp
        ret


DoLogs  ENDP



; Exp2 (X) = 2^(X)

f87_Exp2:
        sub     cx, cx                  ; scale not needed
        jmp     short   DoExps


; Exp10 (X) = 2^(X * Log2of10)

f87_Exp10:
        fldl2t
        mov     cl, 1                   ; scaling is needed
        fxch
        jmp     short   DoExps

; Exp (X) = 2^(X * Log2ofE)

f87_Exp:
        fldl2e
        mov     cl, 1                   ; scaling is needed
        fxch
;       jmp     short   DoExps
; fall thru



; Use the following method:

; The basic limitation of X2M1 is that it accepts parameters only in the
; range 0 <= X <= 0.5.  Thus we must reduce the parameter to that range.
; Another limitation is that we shall consider any parameter of more than
; 2047 to generate an infinite result, since the result is too large to
; express in the long IEEE format.

; (Q, R) := Rem (X, 0.5);

; { X = Q/2 + R exactly, and 0 <= R < 0.5 }

; 2^X   = 2^(Q/2 + R)
;       = 2^(Q/2) * 2^R
;       = 2^(Q DIV 2) * (Sqrt(2))^(Q MOD 2) * 2^R

; Each of those three terms is easily calculated.
; The first term is a fraction of 0.5 with exponent (Q DIV 2) + 1.
; The second term is a choice of constants 1.0 or Sqrt(2).
; The third is  1 + 2XM1 (R).

DoExps  PROC

exp_term1       equ     [bp-2].w0
exp_status      equ     [bp-4].w0

;       jcxz    exp_swapped
;       fxch
;exp_swapped:
        fxam

        push    bp
        mov     bp, sp
        lea     sp, exp_status

        fstsw   exp_status
        jcxz    exp_deppaws
        fxch
exp_deppaws:
        wait
        mov     ah, exp_status.by1
        sahf                            ; FL now reflects FXAM status
        jc      exp_badParam
        jnz     exp_normal

exp_tiny:                               ; denormal or zero
        fstp    st(0)                   ; pop TOS
        jcxz    exp_result1             ; was there a scale factor also ?
        fstp    st(0)
exp_result1:
        fld1
        jmp     exp_end

exp_badParam:                           ; NAN, infinite, or Empty
        jcxz    exp_badNowTos           ; was there a scale factor also ?
        fstp    st(0)                   ; pop TOS
exp_badNowTos:
        jz      exp_empty               ; st(0) was empty
        jnp     exp_NAN                 ; st(0) was NAN

exp_tooBig:
        fstp    st(0)                   ; pop st(0)
        fld     infinity
        jmp     exp_setSign

exp_NAN:
exp_empty:
        ftst                            ; trigger exception
        jmp     exp_end

exp_normal:
        jcxz    exp_scaled
        fmul

exp_scaled:
        fabs
        fcom    half
        fstsw   exp_status
        wait
        test    exp_status.by1, 41h
        jz      exp_notSimpleRange

; We can run |st(0)| <= 0.5 as a special case because it is quick and easy.

        f2xm1
        fld1
        fadd
        jmp     short   exp_setSign

; to get a rapid division by 0.5 we double and truncate.

exp_notSimpleRange:
        fld1
        fld     st(1)
        fstcw   exp_status
        fscale
        or      exp_status.by1, 0Fh     ; specify truncation mode
        fldcw   exp_status
        frndint
        and     exp_status.by1, 0F3h    ; default back to round-nearest
        fldcw   exp_status
        fist    exp_term1

; then to obtain the remainder we scale back to normal and
;       subtract from the original.

        fxch
        fchs
        fxch
        fscale
        fstp    st(1)           ; fscale did not adjust stack
        fsub                    ; st(0) is now 0 <= R < 0.5

; is this test useful?
;       cmp     exp_term1, 4095
;       jg      exp_tooBig

; now we are into the final section.  First calculate the
;       exponent of TOS, the remainder.

        f2xm1
        fld1
        fadd                    ; calculated third term, 2^R

        shr     exp_term1, 1
        jnc     exp_noHalf

        fld     sqrt2           ; multiply by second term
        fmul

exp_noHalf:
        fild    exp_term1
        fxch
        fscale                  ; multiply by first term, 2^(Q DIV 2)
        fstp    st(1)           ; (fscale doesn't adjust stack)


exp_setSign:
        test    ah, 02          ; was original parameter negative ?
        jz      exp_end         ; jump if it was positive

        fld1
        fdivr

exp_end:
        mov     sp, bp
        pop     bp
        ret


DoExps  ENDP

ifndef _WINDOWS

E87SegEnd@

endif
