/*  math.h

    Definitions for the math floating point package.

    Copyright (c) 1987, 1992 by Borland International
    All Rights Reserved.
*/

#ifndef  __MATH_H
#define  __MATH_H

#if !defined(___DEFS_H)
#include <_defs.h>
#endif

#define HUGE_VAL    _huge_dble
extern double _Cdecl _huge_dble;
#define _LHUGE_VAL   _huge_ldble
extern long double _Cdecl _huge_ldble;

#ifdef __cplusplus
extern "C" {
#endif
double  _Cdecl _FARFUNC acos  (double __x);
double  _Cdecl _FARFUNC asin  (double __x);
double  _Cdecl atan  (double __x);
double  _Cdecl _FARFUNC atan2 (double __y, double __x);
double  _Cdecl _FARFUNC ceil  (double __x);
double  _Cdecl _FARFUNC cos   (double __x);
double  _Cdecl _FARFUNC cosh  (double __x);
double  _Cdecl _FARFUNC exp   (double __x);
double  _Cdecl fabs  (double __x);
double  _Cdecl __fabs__  (double __x);          /* Intrinsic */
double  _Cdecl _FARFUNC floor (double __x);
double  _Cdecl _FARFUNC fmod  (double __x, double __y);
double  _Cdecl _FARFUNC frexp (double __x, int _FAR *__exponent);
double  _Cdecl _FARFUNC ldexp (double __x, int __exponent);
double  _Cdecl _FARFUNC log   (double __x);
double  _Cdecl _FARFUNC log10 (double __x);
double  _Cdecl _FARFUNC modf  (double __x, double _FAR *__ipart);
double  _Cdecl _FARFUNC pow   (double __x, double __y);
double  _Cdecl _FARFUNC sin   (double __x);
double  _Cdecl _FARFUNC sinh  (double __x);
double  _Cdecl _FARFUNC sqrt  (double __x);
double  _Cdecl _FARFUNC tan   (double __x);
double  _Cdecl _FARFUNC tanh  (double __x);

long double _Cdecl _FARFUNC acosl  (long double __x);
long double _Cdecl _FARFUNC asinl  (long double __x);
long double _Cdecl _FARFUNC atan2l (long double __x, long double __y);
long double _Cdecl atanl  (long double __x);
long double _Cdecl _FARFUNC ceill  (long double __x);
long double _Cdecl _FARFUNC coshl  (long double __x);
long double _Cdecl _FARFUNC cosl   (long double __x);
long double _Cdecl _FARFUNC expl   (long double __x);
long double _Cdecl fabsl  (long double __x);
long double _Cdecl _FARFUNC floorl (long double __x);
long double _Cdecl _FARFUNC fmodl  (long double __x, long double __y);
long double _Cdecl _FARFUNC frexpl (long double __x, int _FAR *__exponent);
long double _Cdecl _FARFUNC ldexpl (long double __x, int __exponent);
long double _Cdecl _FARFUNC log10l (long double __x);
long double _Cdecl _FARFUNC logl   (long double __x);
long double _Cdecl _FARFUNC modfl  (long double __x, long double _FAR *__ipart);
long double _Cdecl _FARFUNC powl   (long double __x, long double __y);
long double _Cdecl _FARFUNC sinhl  (long double __x);
long double _Cdecl _FARFUNC sinl   (long double __x);
long double _Cdecl _FARFUNC sqrtl  (long double __x);
long double _Cdecl _FARFUNC tanhl  (long double __x);
long double _Cdecl _FARFUNC tanl   (long double __x);

typedef enum
{
    DOMAIN = 1,    /* argument domain error -- log (-1)        */
    SING,          /* argument singularity  -- pow (0,-2))     */
    OVERFLOW,      /* overflow range error  -- exp (1000)      */
    UNDERFLOW,     /* underflow range error -- exp (-1000)     */
    TLOSS,         /* total loss of significance -- sin(10e70) */
    PLOSS,         /* partial loss of signif. -- not used      */
    STACKFAULT     /* floating point unit stack overflow       */
}   _mexcep;

#ifdef __cplusplus
}
#endif


#if !__STDC__

struct  exception
{
    int type;
    char   _FAR *name;
    double  arg1, arg2, retval;
};

struct  _exceptionl
{
    int type;
    char   _FAR *name;
    long double  arg1, arg2, retval;
};

#ifdef __cplusplus
extern "C" {
#endif
int     _Cdecl abs   (int __x);
double  _Cdecl atof  (const char _FAR *__s);
double  _Cdecl _FARFUNC hypot (double __x, double __y);
long    _Cdecl labs  (long __x);
int     _Cdecl _FARFUNC matherr (struct exception _FAR *__e);
double  _Cdecl _FARFUNC poly  (double __x, int __degree, double _FAR *__coeffs);
double  _Cdecl _FARFUNC pow10 (int __p);
int     _Cdecl _FARFUNC _matherrl (struct _exceptionl _FAR *__e);

long double _Cdecl _atold (const char _FAR *__s);
long double _Cdecl _FARFUNC hypotl (long double __x, long double __y);
long double _Cdecl _FARFUNC polyl  (long double __x, int __degree, long double _FAR *__coeffs);
long double _Cdecl _FARFUNC pow10l (int __p);

#ifdef __cplusplus
    /* use class complex instead of cabs in C++ */
#else
struct complex      /* as used by "cabs" function */
{
    double  x, y;
};

struct _complexl    /* as used by "cabsl" function */
{
    long double  x, y;
};

#define cabs(z)     (hypot  ((z).x, (z).y))
#define cabsl(z)    (hypotl ((z).x, (z).y))
#endif

#ifdef __cplusplus
}
#endif

/* Constants rounded for 21 decimals. */
#define M_E         2.71828182845904523536
#define M_LOG2E     1.44269504088896340736
#define M_LOG10E    0.434294481903251827651
#define M_LN2       0.693147180559945309417
#define M_LN10      2.30258509299404568402
#define M_PI        3.14159265358979323846
#define M_PI_2      1.57079632679489661923
#define M_PI_4      0.785398163397448309616
#define M_1_PI      0.318309886183790671538
#define M_2_PI      0.636619772367581343076
#define M_1_SQRTPI  0.564189583547756286948
#define M_2_SQRTPI  1.12837916709551257390
#define M_SQRT2     1.41421356237309504880
#define M_SQRT_2    0.707106781186547524401

#define EDOM    33      /* Math argument */
#define ERANGE  34      /* Result too large */

#endif  /* !__STDC__ */

#endif
