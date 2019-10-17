/*------------------------------------------------------------------------
 * filename - necp.c
 *
 * function(s)
 *        necPow10 - power function, 10^p
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */

#pragma inline
#define I asm

/*--------------------------------------------------------------------------*

Name            necPow10 - power function, 10^p

Usage           double  necPow10(int  p);

Prototype in    math.h

Description     Calculate 10  raised to power.  A lookup table  is used for
                values  from  10  through  10^15,  then this is augmented by
                multiplying with  table entries for  10^16/32/64/128/256,
                which allows any power up to the implementation limit of 511.

                The usual range of double precision is  10e308 but necPow10
                has a wider  range so that it can be used for long double
                calculations when the result is retrieved off the TOS
                explicitly by inline code doing a store of an 80 bit #.

                Negative powers are provided by a final division.

                All registers  are preserved except   AX ! This  is done to
                enable  use by  xcvt(), which  was designed  to assume  its
                registers will be undisturbed.

Return value    necPow10 returns 10^p.

*---------------------------------------------------------------------------*/

double  pascal near __necPow10  (int  p)
{
#define MAX_87_EXP      511

I       mov     ax, p
    if ((int)_AX < -MAX_87_EXP)     /* Extremely small -> Zero      */
    {
I       FLDZ
I       jmp     p10_end
/*
        This is a convenient place to tuck our tables into.
        We want to force the tables to reside in the code segment.
        To do this in TC, disguise them as PROCs.
*/
I e0to10        PROC
I       dd      1.e0,  1.e1,  1.e2,  1.e3,  1.e4
I       dd      1.e5,  1.e6,  1.e7,  1.e8,  1.e9,  1.e10
I e0to10        ENDP

I e11to15       PROC
I       dq      1.e11, 1.e12, 1.e13, 1.e14, 1.e15
I e11to15       ENDP

I e16   PROC
I       dq      1.e16
I e16   ENDP
I e32   PROC
I       dt      40699DC5ADA82B70B59Eh
I e32   ENDP
I e64   PROC
I       dt      40D3C2781F49FFCFA6D5h
I e64   ENDP
I e128  PROC
I       dt      41A893BA47C980E98CDFh
I e128  ENDP
I e256  PROC
I       dt      4351AA7EEBFB9DF9DE8Ch
I e256  ENDP

I eINF  PROC
I       dd      7F800000h       /* +infinity    */
I eINF  ENDP
    }

    if ((int)_AX >  MAX_87_EXP)     /* Extremely large -> Infinity  */
    {
I       FLD     dword ptr eINF
I       jmp     p10_end
    }

I       or      ax, ax
I       jnl     p10_abs
I       neg     ax

p10_abs:
I       mov     si, 15
I       and     si, ax
I       shl     si, 1
I       shl     si, 1
I       sub     si, 44
I       jnl     p10_11to15
I       FLD     dword ptr (e0to10) [si+44]
I       jmp     short   p10_bigger

p10_11to15:
I       shl     si, 1
I       FLD     qword ptr (e11to15) [si]

p10_bigger:
I       shr     ax, 1
I       shr     ax, 1
I       shr     ax, 1
I       shr     ax, 1
I       jz      p10_checkSign           /* optimization, skip if all done */
I       shr     ax, 1
I       jnc     p10_maybe32
I       FMUL    qword ptr (e16)

p10_maybe32:
I       shr     ax, 1
I       jnc     p10_maybe64
I       FLD     tbyte ptr (e32)
I       FMUL

p10_maybe64:
I       shr     ax, 1
I       jnc     p10_maybe128
I       FLD     tbyte ptr (e64)
I       FMUL

p10_maybe128:
I       shr     ax, 1
I       jnc     p10_maybe256
I       FLD     tbyte ptr (e128)
I       FMUL

p10_maybe256:
I       shr     ax, 1
I       jnc     p10_checkSign
I       FLD     tbyte ptr (e256)
I       FMUL

p10_checkSign:
I       test    byte ptr (p) [1], 80h
I       jz      p10_end

/* 10^(-n) = 1 / 10^n, so we need the reciprocal of TOS. */

I       FLD1
I       FDIVR                           /* TOS = 1.0 / TOS */

/* Now the value 10^p is on TOS. */

p10_end:
#pragma warn -rvl
    return;
#pragma warn .rvl
}

