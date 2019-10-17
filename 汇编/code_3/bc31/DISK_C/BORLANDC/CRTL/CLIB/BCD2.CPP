/*-----------------------------------------------------------------------*
 * filename - bcd2.cpp
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1990, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#ifndef __cplusplus
#error Must use C++ for the type bcd.
#endif

#include "bcd.h"

// Stream I/O function definitions

ostream _FAR & pascal _FARFUNC operator<<(ostream _FAR & s, bcd _FAR & a)
{
    return s << real(a);
}

istream _FAR & pascal _FARFUNC operator>>(istream _FAR & s, bcd _FAR & a)
{
    long double x;
    s >> x;
    a = bcd(x);
    return s;
}

/*
These don't work, unless the bcd rep is unique.

inline int operator==(bcd _FAR & a, bcd _FAR & b)
{
    return a.mantissa[0] == b.mantissa[0]
        && a.mantissa[1] == b.mantissa[1] && a.expo == b.expo;
}

inline int operator!=(bcd _FAR & a, bcd _FAR & b)
{
    return a.mantissa[0] != b.mantissa[0]
        || a.mantissa[1] != b.mantissa[1] || a.expo != b.expo;
}
*/
