/*-----------------------------------------------------------------------*
 * filename - bcd1.c
 * Library for long double / binary code decimal conversions
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <_defs.h>

/*
about 17 digits precision
exponent range, about 1e-125 to 1e+125

bcd format:
expo            mantissa                value
0               0                       0
1               +1 or -1                +INF or -INF
2               ?                       NAN
3-255           x                       x * 10 ^ (expo - Bias)

The Bias is 147, so exponent range is 3-147=-144 to 255-147=+108.
Caution: The decimal representation is not unique.
Eg, { 1L, 0L, 1+Bias } is the same as { 10L, 0L, 0+Bias }.
*/

#pragma  inline

typedef unsigned short bits16;

typedef struct
{
    bits16      frac [4];
    bits16      signExp;
}
    IEEE80;

struct decimal {
        long mantissa[2];
        short expo;
};

typedef struct decimal bcd;

enum bcdexpo {
        ExpoZero,
        ExpoInf,
        ExpoNan,
};

#define Bias    147

#define I asm

#define REAL    qword ptr
#define REAL1   dword ptr
#define REAL2   qword ptr
#define REAL3   tbyte ptr

#define BYTE    byte ptr
#define WORD    word ptr
#define LONG    dword ptr
#define LONG64  qword ptr

static const long e0toF [8] =
{
    1, 10, 100, 1000, 10000, 100000L, 1000000L, 10000000L
};

static const IEEE80 expo [10] =
{
    {{0,      0,      0x2000, 0xBEBC}, 0x4019},    /* 1e8    */
    {{0,      0x0400, 0xC9BF, 0x8E1B}, 0x4034},    /* 1e16   */
    {{0xB59E, 0x2B70, 0xADA8, 0x9DC5}, 0x4069},    /* 1e32   */
    {{0xA6D5, 0xFFCF, 0x1F49, 0xC278}, 0x40D3},    /* 1e64   */
    {{0x8CE0, 0x80E9, 0x47C9, 0x93BA}, 0x41A8},    /* 1e128  */
    {{0xDE8E, 0x9DF9, 0xEBFB, 0xAA7E}, 0x4351},    /* 1e256  */
    {{0x91C7, 0xA60E, 0xA0AE, 0xE319}, 0x46A3},    /* 1e512  */
    {{0x0C17, 0x8175, 0x7586, 0xC976}, 0x4D48},    /* 1e1024 */
    {{0x5DE5, 0xC53D, 0x3B5D, 0x9E8B}, 0x5A92},    /* 1e2048 */
    {{0x979B, 0x8A20, 0x5202, 0xC460}, 0x7525},    /* 1e4096 */
};

static void near pascal scale10(int p)
/* return
        TOS *= 10 ^ p
        preserves ax! (except in HUGE)
*/
{
I       mov     si, p
I       or      si, si
I       mov     dx, si
I       jz      scale_num
I       jns     scale_abs
I       neg     si
scale_abs:
I       cmp     si, 4999
I       jbe     scale_max
I       mov     si, 4999
scale_max:
/* load e0toF[_SI & 7] */
I       mov     bx, 7
I       and     bx, si
I       shl     bx, 1
I       shl     bx, 1
I       add     bx, offset e0toF
I       fild    LONG [bx]

I       mov     cl, 3
I       shr     si, cl
I       mov     di, offset expo
expo_loop:
I       or      si, si
I       jz      scale_num
I       shr     si, 1
I       jnc     expo_next
I       fld     REAL3 [di]
I       fmul

expo_next:
I       add     di, 10
I       jmp     expo_loop

scale_num:
I       or      dx, dx
I       jz      scale_end
I       jns     scale_mul
I       fdiv
I       jmp     short scale_end
scale_mul:
I       fmul

scale_end:
        return;
}

static const float inf = 1.0/0.0;
static const float nan = 0.0/0.0;

/*
Convert a decimal number to binary.
*/

long double pascal _FARFUNC __bcd_tobinary(const bcd far *p)
{
I       les     bx, p
I       fild    LONG64 es:[bx]          /* p->mantissa */
I       mov     ax, es:[bx+8]           /* p->expo */

I       cmp     al, 2
I       jbe     special
I       sub     ax, Bias
#ifdef __HUGE__
I   push ax
#endif
        scale10(_AX);           /* Preserves AX except in huge model */
#ifdef __HUGE__
I   pop ax
#endif
I       jmp     short done

special:
I       je      nan
I       or      al, al
I       jz      zero

I       fmul    REAL1 inf               /* mantissa was +1 or -1 */
I       jmp     short done

nan:
I       fstp    st(0)
I       fld     REAL1 nan
        /* fall thru */

zero:
/* assume mantissa is 0 */
done:
#pragma warn -rvl       /* Function should return a value */
        return;
#pragma warn .rvl       /* Function should return a value */
}

/*
round x to n decimal places
fixed point!
eg,
x = 123.4567;
round(x, 0) = 123.
round(x, 1) = 123.5
round(x, 2) = 123.46
round(x, -1) = 120.
round(x, -2) = 100.

uses banker's rounding

Convert a binary number to decimals.
Use at most 'decimals' after the decimal point.
For maximum accuracy, use decimals=5000.
*/

void pascal _FARFUNC __bcd_todecimal(long double x, int decimals, bcd far *p)
{
I       mov     ax, x[8]
I       mov     dx, x[6]
I       mov     cx, 7FFFh
I       les     si, p

I       and     ax, cx
I       jz      zero
I       cmp     ax, cx
I       je      special

I       sub     ax, 3FFFh + 60
I       neg     ax

#if 0
I       shl     dx, 1
I       shl     dx, 1
I       rcl     ax, 1
I       shl     dx, 1
I       rcl     ax, 1

I       mov     dx, 92A0h shr 1
I       imul    dx

I       xchg    ax, dx
I       sar     ax, 1
I       sar     ax, 1

#else
I       mov     dx, 9A20h shr 1 /* log10(2) */
I       imul    dx
I       xchg    ax, dx
#endif

/* use min(ax,n) */
I       mov     dx, decimals
I       cmp     ax, dx
I       jl      min
I       xchg    ax, dx
min:

/* -ax is unbiased exponent, not special, so -144 <= -ax <= 108 */
I       cmp     ax, +144
I       jg      underflow
I       cmp     ax, -108
I       jl      overflow

I       fld     REAL3 x
#ifdef __HUGE__
I   push ax
#endif
        scale10(_AX);           /* Preserves AX except in huge model */
#ifdef __HUGE__
I   pop ax
#endif

I       neg     ax
I       add     ax, Bias
I       jmp     short done

special:
I       or      dx, dx
I       jz      nan

overflow:
I       fld1
I       mov     al, ExpoInf
I       test    BYTE x[9], 80h
I       jz      done
I       fchs
I       jmp     short done

nan:
I       fldz
I       mov     al, ExpoNan
I       jmp     short done

underflow:
zero:
I       fldz
I       mov     al, ExpoZero

done:
I       fistp   LONG64 es:[si]
I       mov     ah, 0
I       mov     es:[si+8], ax
I       fwait
}

#if     DEBUG
/* for debugging */
long double pascal load64(long far *a)
{
I       les     bx, a
I       fild    LONG64 es:[bx]
        return;
}
#endif

/* from _mathl.h */
typedef enum {
        _Sine_,_CoSine_,_Tangent_,_ArcTan_,
        _Log_,_Log2_, _Log10_,
        _Exp_,_Exp2_, _Exp10_,_Power_
} FLIB_functions;

#define FLIB_(fun)      _FAST_(0ECh + 2*fun)
#define _FAST_(shortCode)       int     3Eh;  asm db    shortCode, 90h

#pragma warn -rvl
long double pascal _FARFUNC __bcd_log10(bcd far *p)
{
I       les     bx, p
I       fild    LONG64 es:[bx]
asm     FLIB_   (_Log10_)
I       sub     WORD es:[bx+8], Bias
I       fiadd   WORD es:[bx+8]
I       add     WORD es:[bx+8], Bias
I       fwait
        return;
}
#pragma warn .rvl

void pascal _FARFUNC __bcd_pow10(int n, bcd far *p)
{
        p->mantissa[0] = 1;
        p->mantissa[1] = 0;
        _AX = n;
I       add     ax, Bias
I       cmp     ax, 255
I       jg      inf
I       cmp     ax, 3
I       jl      zero
        p->expo = _AX;
        return;

zero:
        p->mantissa[0] = 0;
        p->expo = 0;
        return;

inf:
        p->expo = ExpoInf;
        return;
}

