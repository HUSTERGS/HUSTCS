/*  float.h

    Defines implementation specific macros for dealing with
    floating point.

    Copyright (c) 1987, 1992 by Borland International
    All Rights Reserved.
*/

#ifndef __FLOAT_H
#define __FLOAT_H

#if !defined(___DEFS_H)
#include <_defs.h>
#endif

#define FLT_RADIX           2
#define FLT_ROUNDS          1
#define FLT_GUARD           1
#define FLT_NORMALIZE       1

#define DBL_DIG             15
#define FLT_DIG             6
#define LDBL_DIG            19

#define DBL_MANT_DIG        53
#define FLT_MANT_DIG        24
#define LDBL_MANT_DIG       64

#define DBL_EPSILON         2.2204460492503131E-16
#define FLT_EPSILON         1.19209290E-07F
#define LDBL_EPSILON        1.084202172485504E-19

/* smallest positive IEEE normal numbers */
#define DBL_MIN             2.2250738585072014E-308
#define FLT_MIN             1.17549435E-38F
#define LDBL_MIN            _tiny_ldble

#define DBL_MAX             _huge_dble
#define FLT_MAX             _huge_flt
#define LDBL_MAX            _huge_ldble

#define DBL_MAX_EXP         +1024
#define FLT_MAX_EXP         +128
#define LDBL_MAX_EXP        +16384

#define DBL_MAX_10_EXP      +308
#define FLT_MAX_10_EXP      +38
#define LDBL_MAX_10_EXP     +4932

#define DBL_MIN_10_EXP      -307
#define FLT_MIN_10_EXP      -37
#define LDBL_MIN_10_EXP     -4931

#define DBL_MIN_EXP         -1021
#define FLT_MIN_EXP         -125
#define LDBL_MIN_EXP        -16381

extern float        _Cdecl _huge_flt;
extern double       _Cdecl _huge_dble;
extern long double  _Cdecl _huge_ldble;
extern long double  _Cdecl _tiny_ldble;

#ifdef __cplusplus
extern "C" {
#endif
unsigned int _Cdecl _FARFUNC _clear87(void);
unsigned int _Cdecl _FARFUNC _control87(unsigned int __newcw, unsigned int __mask);
void         _Cdecl _FARFUNC _fpreset(void);
unsigned int _Cdecl _FARFUNC _status87(void);
#ifdef __cplusplus
}
#endif

#if !__STDC__

/* 8087/80287 Status Word format   */

#define SW_INVALID      0x0001  /* Invalid operation            */
#define SW_DENORMAL     0x0002  /* Denormalized operand         */
#define SW_ZERODIVIDE   0x0004  /* Zero divide                  */
#define SW_OVERFLOW     0x0008  /* Overflow                     */
#define SW_UNDERFLOW    0x0010  /* Underflow                    */
#define SW_INEXACT      0x0020  /* Precision (Inexact result)   */

/* 8087/80287 Control Word format */

#define MCW_EM              0x003f  /* interrupt Exception Masks*/
#define     EM_INVALID      0x0001  /*   invalid                */
#define     EM_DENORMAL     0x0002  /*   denormal               */
#define     EM_ZERODIVIDE   0x0004  /*   zero divide            */
#define     EM_OVERFLOW     0x0008  /*   overflow               */
#define     EM_UNDERFLOW    0x0010  /*   underflow              */
#define     EM_INEXACT      0x0020  /*   inexact (precision)    */

#define MCW_IC              0x1000  /* Infinity Control */
#define     IC_AFFINE       0x1000  /*   affine         */
#define     IC_PROJECTIVE   0x0000  /*   projective     */

#define MCW_RC          0x0c00  /* Rounding Control     */
#define     RC_CHOP     0x0c00  /*   chop               */
#define     RC_UP       0x0800  /*   up                 */
#define     RC_DOWN     0x0400  /*   down               */
#define     RC_NEAR     0x0000  /*   near               */

#define MCW_PC          0x0300  /* Precision Control    */
#define     PC_24       0x0000  /*    24 bits           */
#define     PC_53       0x0200  /*    53 bits           */
#define     PC_64       0x0300  /*    64 bits           */

/* 8087/80287 Initial Control Word */
/* use affine infinity, mask underflow and precision exceptions */

#define CW_DEFAULT  _default87
extern unsigned int _Cdecl _default87;

/*
    SIGFPE signal error types (for integer & float exceptions).
*/
#define FPE_INTOVFLOW       126 /* 80x86 Interrupt on overflow  */
#define FPE_INTDIV0         127 /* 80x86 Integer divide by zero */

#define FPE_INVALID         129 /* 80x87 invalid operation      */
#define FPE_ZERODIVIDE      131 /* 80x87 divide by zero         */
#define FPE_OVERFLOW        132 /* 80x87 arithmetic overflow    */
#define FPE_UNDERFLOW       133 /* 80x87 arithmetic underflow   */
#define FPE_INEXACT         134 /* 80x87 precision loss         */
#define FPE_STACKFAULT      135 /* 80x87 stack overflow         */
#define FPE_EXPLICITGEN     140 /* When SIGFPE is raise()'d     */

/*
            SIGSEGV signal error types.
*/
#define SEGV_BOUND          10  /* A BOUND violation (SIGSEGV)  */
#define SEGV_EXPLICITGEN    11  /* When SIGSEGV is raise()'d    */

/*
            SIGILL signal error types.
*/
#define ILL_EXECUTION       20  /* Illegal operation exception  */
#define ILL_EXPLICITGEN     21  /* When SIGILL is raise()'d     */

#endif  /* !__STDC__ */

#endif
