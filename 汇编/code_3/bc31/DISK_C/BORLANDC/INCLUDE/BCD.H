/*  bcd.h

    BCD Number Library - Include File
    class bcd:  declarations for decimal numbers.

    Copyright (c) 1987, 1992 by Borland International
    All Rights Reserved.
*/

#ifndef __cplusplus
#error Must use C++ for the type bcd.
#endif

#if !defined(__BCD_H)
#define __BCD_H

#if !defined(___DEFS_H)
#include <_defs.h>
#endif

#if !defined(__IOSTREAM_H)
#include <iostream.h>
#endif

#if !defined(__MATH_H)
#include <math.h>
#endif

#pragma option -Vo-
#if defined(__BCOPT__) && !defined(_RTL_ALLOW_po)
#pragma option -po-
#endif

#define _BcdMaxDecimals     5000

_CLASSDEF(bcd)

class _CLASSTYPE bcd {

public:
    // constructors
    _Cdecl bcd();
    _Cdecl bcd(int x);
    _Cdecl bcd(unsigned int x);
    _Cdecl bcd(long x);
    _Cdecl bcd(unsigned long x);
    _Cdecl bcd(double x, int decimals = _BcdMaxDecimals);
    _Cdecl bcd(long double x, int decimals = _BcdMaxDecimals);

    // bcd manipulations
    friend long double _Cdecl real(bcd _FAR &);   // Return the real part

    // Overloaded ANSI C math functions
    friend bcd _Cdecl _FARFUNC abs(bcd _FAR &);
    friend bcd _Cdecl _FARFUNC acos(bcd _FAR &);
    friend bcd _Cdecl _FARFUNC asin(bcd _FAR &);
    friend bcd _Cdecl _FARFUNC atan(bcd _FAR &);
    friend bcd _Cdecl _FARFUNC cos(bcd _FAR &);
    friend bcd _Cdecl _FARFUNC cosh(bcd _FAR &);
    friend bcd _Cdecl _FARFUNC exp(bcd _FAR &);
    friend bcd _Cdecl _FARFUNC log(bcd _FAR &);
    friend bcd _Cdecl _FARFUNC log10(bcd _FAR &);
    friend bcd _Cdecl _FARFUNC pow(bcd _FAR & base, bcd _FAR & expon);
    friend bcd _Cdecl _FARFUNC sin(bcd _FAR &);
    friend bcd _Cdecl _FARFUNC sinh(bcd _FAR &);
    friend bcd _Cdecl _FARFUNC sqrt(bcd _FAR &);
    friend bcd _Cdecl _FARFUNC tan(bcd _FAR &);
    friend bcd _Cdecl _FARFUNC tanh(bcd _FAR &);

    // Binary Operator Functions
    friend bcd _Cdecl _FARFUNC operator+(bcd _FAR &, bcd _FAR &);
    friend bcd _Cdecl _FARFUNC operator+(long double, bcd _FAR &);
    friend bcd _Cdecl _FARFUNC operator+(bcd _FAR &, long double);
    friend bcd _Cdecl _FARFUNC operator-(bcd _FAR &, bcd _FAR &);
    friend bcd _Cdecl _FARFUNC operator-(long double, bcd _FAR &);
    friend bcd _Cdecl _FARFUNC operator-(bcd _FAR &, long double);
    friend bcd _Cdecl _FARFUNC operator*(bcd _FAR &, bcd _FAR &);
    friend bcd _Cdecl _FARFUNC operator*(bcd _FAR &, long double);
    friend bcd _Cdecl _FARFUNC operator*(long double, bcd _FAR &);
    friend bcd _Cdecl _FARFUNC operator/(bcd _FAR &, bcd _FAR &);
    friend bcd _Cdecl _FARFUNC operator/(bcd _FAR &, long double);
    friend bcd _Cdecl _FARFUNC operator/(long double, bcd _FAR &);
    friend int _Cdecl _FARFUNC operator==(bcd _FAR &, bcd _FAR &);
    friend int _Cdecl _FARFUNC operator!=(bcd _FAR &, bcd _FAR &);
    friend int _Cdecl _FARFUNC operator>=(bcd _FAR &, bcd _FAR &);
    friend int _Cdecl _FARFUNC operator<=(bcd _FAR &, bcd _FAR &);
    friend int _Cdecl _FARFUNC operator>(bcd _FAR &, bcd _FAR &);
    friend int _Cdecl _FARFUNC operator<(bcd _FAR &, bcd _FAR &);
    bcd _FAR & _Cdecl operator+=(bcd _FAR &);
    bcd _FAR & _Cdecl operator+=(long double);
    bcd _FAR & _Cdecl operator-=(bcd _FAR &);
    bcd _FAR & _Cdecl operator-=(long double);
    bcd _FAR & _Cdecl operator*=(bcd _FAR &);
    bcd _FAR & _Cdecl operator*=(long double);
    bcd _FAR & _Cdecl operator/=(bcd _FAR &);
    bcd _FAR & _Cdecl operator/=(long double);
    bcd  _Cdecl operator+();
    bcd  _Cdecl operator-();

// Implementation
private:
    long mantissa[2];
    int expo;
};

// const bcd bcd_zero(0);

enum bcdexpo {
    ExpoZero,
    ExpoInf,
    ExpoNan,
};

extern "C" {
long double pascal _FARFUNC __bcd_tobinary(const bcd far *p);
void pascal _FARFUNC __bcd_todecimal(long double x, int decimals, bcd far *p);
long double pascal _FARFUNC __bcd_log10(bcd far *p);
void pascal _FARFUNC __bcd_pow10(int n, bcd far *p);
}

inline _Cdecl bcd::bcd()
{
/* if you want zero ...
    mantissa[0] = 0;
    mantissa[1] = 0;
    expo = ExpoZero;
*/
}

inline _Cdecl bcd::bcd(long double x, int decimals)
{
    __bcd_todecimal(x,decimals,this);
}

inline _Cdecl bcd::bcd(double x, int decimals)
{
    __bcd_todecimal(x,decimals,this);
}

inline _Cdecl bcd::bcd(int x)
{
    mantissa[0] = x;
    mantissa[1] = x >= 0 ? 0 : -1;
    expo = 0;
}

inline _Cdecl bcd::bcd(unsigned int x)
{
    mantissa[0] = x;
    mantissa[1] = 0;
    expo = 0;
}

inline _Cdecl bcd::bcd(long x)
{
    mantissa[0] = x;
    mantissa[1] = x >= 0 ? 0 : -1;
    expo = 0;
}

inline _Cdecl bcd::bcd(unsigned long x)
{
    mantissa[0] = x;
    mantissa[1] = 0;
    expo = 0;
}

inline long double _Cdecl real(bcd& z)
{
    return __bcd_tobinary(&z);
}

// Definitions of compound-assignment operator member functions

inline bcd& _Cdecl bcd::operator+=(bcd& b)
{
    __bcd_todecimal(real(*this)+real(b),_BcdMaxDecimals,this);
    return *this;
}

inline bcd& _Cdecl bcd::operator+=(long double b)
{
    __bcd_todecimal(real(*this)+b,_BcdMaxDecimals,this);
    return *this;
}

inline bcd& _Cdecl bcd::operator-=(bcd& b)
{
    __bcd_todecimal(real(*this)-real(b),_BcdMaxDecimals,this);
    return *this;
}

inline bcd& _Cdecl bcd::operator-=(long double b)
{
    __bcd_todecimal(real(*this)-b,_BcdMaxDecimals,this);
    return *this;
}

inline bcd& _Cdecl bcd::operator*=(bcd& b)
{
    __bcd_todecimal(real(*this)*real(b),_BcdMaxDecimals,this);
    return *this;
}

inline bcd& _Cdecl bcd::operator*=(long double b)
{
    __bcd_todecimal(real(*this)*b,_BcdMaxDecimals,this);
    return *this;
}

inline bcd& _Cdecl bcd::operator/=(bcd& b)
{
    __bcd_todecimal(real(*this)/real(b),_BcdMaxDecimals,this);
    return *this;
}

inline bcd& _Cdecl bcd::operator/=(long double b)
{
    __bcd_todecimal(real(*this)/b,_BcdMaxDecimals,this);
    return *this;
}


// Definitions of non-member binary operator functions

inline bcd _Cdecl operator+(bcd& a, bcd& b)
{
    return bcd(real(a) + real(b));
}

inline bcd _Cdecl operator+(long double a, bcd& b)
{
    return bcd(a + real(b));
}

inline bcd _Cdecl operator+(bcd& a, long double b)
{
    return bcd(real(a) + b);
}

inline bcd _Cdecl operator-(bcd& a, bcd& b)
{
    return bcd(real(a) - real(b));
}

inline bcd _Cdecl operator-(long double a, bcd& b)
{
    return bcd(a - real(b));
}

inline bcd _Cdecl operator-(bcd& a, long double b)
{
    return bcd(real(a) - b);
}

inline bcd _Cdecl operator*(bcd& a, bcd& b)
{
    return bcd(real(a) * real(b));
}

inline bcd _Cdecl operator*(bcd& a, long double b)
{
    return bcd(real(a) * b);
}

inline bcd _Cdecl operator*(long double a, bcd& b)
{
    return bcd(a * real(b));
}

inline bcd _Cdecl operator/(bcd& a, bcd& b)
{
    return bcd(real(a) / real(b));
}

inline bcd _Cdecl operator/(long double a, bcd& b)
{
    return bcd(a / real(b));
}

inline bcd _Cdecl operator/(bcd& a, long double b)
{
    return bcd(real(a) / b);
}

inline int _Cdecl operator==(bcd& a, bcd& b)
{
    return real(a) == real(b);
}

inline int _Cdecl operator!=(bcd& a, bcd& b)
{
    return real(a) != real(b);
}

inline int _Cdecl operator>=(bcd& a, bcd& b)
{
    return real(a) >= real(b);
}

inline int _Cdecl operator<=(bcd& a, bcd& b)
{
    return real(a) <= real(b);
}

inline int _Cdecl operator>(bcd& a, bcd& b)
{
    return real(a) > real(b);
}

inline int _Cdecl operator<(bcd& a, bcd& b)
{
    return real(a) < real(b);
}

inline bcd _Cdecl bcd::operator+()
{
    return *this;
}

inline bcd _Cdecl bcd::operator-()
{
//  return bcd(-real(this));

// 1's comp
    mantissa[0] = - ++ mantissa[0];
    mantissa[1] = - ++ mantissa[1];
// inc
    if (++mantissa[0] == 0) ++mantissa[1];
    return *this;
}

inline bcd _Cdecl abs(bcd& a)   { return bcd(fabs(real(a)));}
inline bcd _Cdecl acos(bcd& a)  { return bcd(acos(real(a)));}
inline bcd _Cdecl asin(bcd& a)  { return bcd(asin(real(a)));}
inline bcd _Cdecl atan(bcd& a)  { return bcd(atan(real(a)));}
inline bcd _Cdecl cos(bcd& a)   { return bcd(cos(real(a)));}
inline bcd _Cdecl cosh(bcd& a)  { return bcd(cosh(real(a)));}
inline bcd _Cdecl exp(bcd& a)   { return bcd(exp(real(a)));}
inline bcd _Cdecl log(bcd& a)   { return bcd(log(real(a)));}
inline bcd _Cdecl log10(bcd& a) { return bcd(__bcd_log10(&a));}
inline bcd _Cdecl sin(bcd& a)   { return bcd(sin(real(a)));}
inline bcd _Cdecl sinh(bcd& a)  { return bcd(sinh(real(a)));}
inline bcd _Cdecl sqrt(bcd& a)  { return bcd(sqrt(real(a)));}
inline bcd _Cdecl tan(bcd& a)   { return bcd(tan(real(a)));}
inline bcd _Cdecl tanh(bcd& a)  { return bcd(tanh(real(a)));}

inline bcd _Cdecl pow(bcd& a, bcd& b)   { return bcd(pow(real(a),real(b)));}
inline void _Cdecl pow10(int n, bcd& a) { __bcd_pow10(n,&a);}


// bcd stream I/O

ostream _FAR & pascal _FARFUNC operator<<(ostream _FAR &, bcd _FAR &);
istream _FAR & pascal _FARFUNC operator>>(istream _FAR &, bcd _FAR &);

#pragma option -Vo.
#if defined(__BCOPT__)
#pragma option -po.
#endif

#endif  // __BCD_H
