/*------------------------------------------------------------------------
 * filename - pow10l.c
 *
 * function(s)
 *        pow10l - long double power function, 10^p
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */

#include <_math.h>
#include <math.h>

/*--------------------------------------------------------------------------*

Name            pow10l - long double power function, 10^p

Usage           long double  pow10l(int  p);

Prototype in    math.h

Description     Calculate 10  raised to power.  A lookup table  is used for
                values  from  10  through  10^7,  then this is augmented by
                multiplying with  table entries for  10^8/16/32/64/128/256,
                512/1024/2048/4096 which allows any power up to the
                implementation limit of 4932.

                Negative powers are provided by a final division.

                All registers  are preserved except   AX.  This  is done to
                enable  use by  xcvt(), which  was designed  to assume  its
                registers will be undisturbed.

Return value    pow10l returns 10^p.

*---------------------------------------------------------------------------*/

long double _FARFUNC pow10l  (int  p)
{
    return (__pow10(p));
}
