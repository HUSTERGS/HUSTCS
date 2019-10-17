/*------------------------------------------------------------------------
 * filename - pow10d.c
 *
 * function(s)
 *        pow10 - power function, 10^p
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

Name            pow10 - power function, 10^p

Usage           double  pow10(int  p);

Prototype in    math.h

Description     Calculate 10  raised to power.  A lookup table  is used for
                values  from  10  through  10^7,  then this is augmented by
                multiplying with  table entries for  10^8/16/32/64/128/256,
                512/1024/2048/4096 which allows any power up to the
                implementation limit of 4932.
                The usual range of double precision is  10e308 but pow10
                has a wider  range so that it can be used for long double
                calculations when the result is retrieved off the TOS
                explicitly by inline code doing a store of an 80 bit #.

                Negative powers are provided by a final division.

                All registers  are preserved except   AX ! This  is done to
                enable  use by  xcvt(), which  was designed  to assume  its
                registers will be undisturbed.

Return value    pow10 returns 10^p.

*---------------------------------------------------------------------------*/

double  _FARFUNC pow10  (int  p)
{
    return ((double)__pow10(p));
}
