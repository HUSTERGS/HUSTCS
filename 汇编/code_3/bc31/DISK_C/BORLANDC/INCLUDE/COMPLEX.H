/* complex.h

    Complex Number Library - Include File
    class complex:  declarations for complex numbers.

    Copyright (c) 1990, 1992 by Borland International
    All Rights Reserved.

All function names, member names, and operators have been borrowed
from AT&T C++, except for the addition of:

    friend complex _Cdecl acos(complex _FAR &);
    friend complex _Cdecl asin(complex _FAR &);
    friend complex _Cdecl atan(complex _FAR &);
    friend complex _Cdecl log10(complex _FAR &);
    friend complex _Cdecl tan(complex _FAR &);
    friend complex _Cdecl tanh(complex _FAR &);
    complex _Cdecl operator+();
    complex _Cdecl operator-();
*/

#ifndef __cplusplus
#error Must use C++ for the type complex.
#endif

#if !defined(__COMPLEX_H)
#define __COMPLEX_H

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

_CLASSDEF(complex)

class _CLASSTYPE complex {

public:
    // constructors
    complex(double __re_val, double __im_val=0);
    complex();

    // complex manipulations
    friend double _Cdecl _FARFUNC real(complex _FAR &);   // the real part
    friend double _Cdecl _FARFUNC imag(complex _FAR &);   // the imaginary part
    friend complex _Cdecl _FARFUNC conj(complex _FAR &);  // the complex conjugate
    friend double _Cdecl _FARFUNC norm(complex _FAR &);   // the square of the magnitude
    friend double _Cdecl _FARFUNC arg(complex _FAR &);    // the angle in the plane

    // Create a complex object given polar coordinates
    friend complex _Cdecl polar(double __mag, double __angle=0);

    // Overloaded ANSI C math functions
    friend double  _Cdecl _FARFUNC abs(complex _FAR &);
    friend complex _Cdecl _FARFUNC acos(complex _FAR &);
    friend complex _Cdecl _FARFUNC asin(complex _FAR &);
    friend complex _Cdecl _FARFUNC atan(complex _FAR &);
    friend complex _Cdecl _FARFUNC cos(complex _FAR &);
    friend complex _Cdecl _FARFUNC cosh(complex _FAR &);
    friend complex _Cdecl _FARFUNC exp(complex _FAR &);
    friend complex _Cdecl _FARFUNC log(complex _FAR &);
    friend complex _Cdecl _FARFUNC log10(complex _FAR &);
    friend complex _Cdecl _FARFUNC pow(complex _FAR & __base, double __expon);
    friend complex _Cdecl _FARFUNC pow(double __base, complex _FAR & __expon);
    friend complex _Cdecl _FARFUNC pow(complex _FAR & __base, complex _FAR & __expon);
    friend complex _Cdecl _FARFUNC sin(complex _FAR &);
    friend complex _Cdecl _FARFUNC sinh(complex _FAR &);
    friend complex _Cdecl _FARFUNC sqrt(complex _FAR &);
    friend complex _Cdecl _FARFUNC tan(complex _FAR &);
    friend complex _Cdecl _FARFUNC tanh(complex _FAR &);

    // Binary Operator Functions
    friend complex _Cdecl _FARFUNC operator+(complex _FAR &, complex _FAR &);
    friend complex _Cdecl _FARFUNC operator+(double, complex _FAR &);
    friend complex _Cdecl _FARFUNC operator+(complex _FAR &, double);
    friend complex _Cdecl _FARFUNC operator-(complex _FAR &, complex _FAR &);
    friend complex _Cdecl _FARFUNC operator-(double, complex _FAR &);
    friend complex _Cdecl _FARFUNC operator-(complex _FAR &, double);
    friend complex _Cdecl _FARFUNC operator*(complex _FAR &, complex _FAR &);
    friend complex _Cdecl _FARFUNC operator*(complex _FAR &, double);
    friend complex _Cdecl _FARFUNC operator*(double, complex _FAR &);
    friend complex _Cdecl _FARFUNC operator/(complex _FAR &, complex _FAR &);
    friend complex _Cdecl _FARFUNC operator/(complex _FAR &, double);
    friend complex _Cdecl _FARFUNC operator/(double, complex _FAR &);
    friend int _Cdecl _FARFUNC operator==(complex _FAR &, complex _FAR &);
    friend int _Cdecl _FARFUNC operator!=(complex _FAR &, complex _FAR &);
    complex _FAR & _Cdecl operator+=(complex _FAR &);
    complex _FAR & _Cdecl operator+=(double);
    complex _FAR & _Cdecl operator-=(complex _FAR &);
    complex _FAR & _Cdecl operator-=(double);
    complex _FAR & _Cdecl operator*=(complex _FAR &);
    complex _FAR & _Cdecl operator*=(double);
    complex _FAR & _Cdecl operator/=(complex _FAR &);
    complex _FAR & _Cdecl operator/=(double);
    complex _Cdecl operator+();
    complex _Cdecl operator-();

// Implementation
private:
        double re, im;
};


// Inline complex functions

inline complex::complex(double __re_val, double __im_val)
{
    re = __re_val;
    im = __im_val;
}

inline complex::complex()
{
/* if you want your complex numbers initialized ...
    re = im = 0;
*/
}

inline complex _Cdecl complex::operator+()
{
    return *this;
}

inline complex _Cdecl complex::operator-()
{
    return complex(-re, -im);
}


// Definitions of compound-assignment operator member functions

inline complex _FAR & _Cdecl complex::operator+=(complex _FAR & __z2)
{
    re += __z2.re;
    im += __z2.im;
    return *this;
}

inline complex _FAR & _Cdecl complex::operator+=(double __re_val2)
{
    re += __re_val2;
    return *this;
}

inline complex _FAR & _Cdecl complex::operator-=(complex _FAR & __z2)
{
    re -= __z2.re;
    im -= __z2.im;
    return *this;
}

inline complex _FAR & _Cdecl complex::operator-=(double __re_val2)
{
    re -= __re_val2;
    return *this;
}

inline complex _FAR & _Cdecl complex::operator*=(double __re_val2)
{
    re *= __re_val2;
    im *= __re_val2;
    return *this;
}

inline complex _FAR & _Cdecl complex::operator/=(double __re_val2)
{
    re /= __re_val2;
    im /= __re_val2;
    return *this;
}


// Definitions of non-member complex functions

inline double _Cdecl real(complex _FAR & __z)
{
    return __z.re;
}

inline double _Cdecl imag(complex _FAR & __z)
{
    return __z.im;
}

inline complex _Cdecl conj(complex _FAR & __z)
{
    return complex(__z.re, -__z.im);
}

inline complex _Cdecl polar(double __mag, double __angle)
{
    return complex(__mag*cos(__angle), __mag*sin(__angle));
}


// Definitions of non-member binary operator functions

inline complex _Cdecl operator+(complex _FAR & __z1, complex _FAR & __z2)
{
    return complex(__z1.re + __z2.re, __z1.im + __z2.im);
}

inline complex _Cdecl operator+(double __re_val1, complex _FAR & __z2)
{
    return complex(__re_val1 + __z2.re, __z2.im);
}

inline complex _Cdecl operator+(complex _FAR & __z1, double __re_val2)
{
    return complex(__z1.re + __re_val2, __z1.im);
}

inline complex _Cdecl operator-(complex _FAR & __z1, complex _FAR & __z2)
{
    return complex(__z1.re - __z2.re, __z1.im - __z2.im);
}

inline complex _Cdecl operator-(double __re_val1, complex _FAR & __z2)
{
    return complex(__re_val1 - __z2.re, -__z2.im);
}

inline complex _Cdecl operator-(complex _FAR & __z1, double __re_val2)
{
    return complex(__z1.re - __re_val2, __z1.im);
}

inline complex _Cdecl operator*(complex _FAR & __z1, double __re_val2)
{
    return complex(__z1.re*__re_val2, __z1.im*__re_val2);
}

inline complex _Cdecl operator*(double __re_val1, complex _FAR & __z2)
{
    return complex(__z2.re*__re_val1, __z2.im*__re_val1);
}

inline complex _Cdecl operator/(complex _FAR & __z1, double __re_val2)
{
    return complex(__z1.re/__re_val2, __z1.im/__re_val2);
}

inline int _Cdecl operator==(complex _FAR & __z1, complex _FAR & __z2)
{
    return __z1.re == __z2.re && __z1.im == __z2.im;
}

inline int _Cdecl operator!=(complex _FAR & __z1, complex _FAR & __z2)
{
    return __z1.re != __z2.re || __z1.im != __z2.im;
}


// Complex stream I/O

ostream _FAR & _Cdecl _FARFUNC operator<<(ostream _FAR &, complex _FAR &);
istream _FAR & _Cdecl _FARFUNC operator>>(istream _FAR &, complex _FAR &);

#pragma option -Vo.
#if defined(__BCOPT__)
#pragma option -po.
#endif

#endif  // __COMPLEX_H
