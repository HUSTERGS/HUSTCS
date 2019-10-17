/*------------------------------------------------------------------------
 * filename - gcvt.c
 *
 * function(s)
 *        gcvt - converts floating-point number to a string
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <stdlib.h>
#include <_printf.h>

/*--------------------------------------------------------------------------*

Name            gcvt - converts floating-point number to a string

Usage           char *gcvt(double value, int ndec, char *bufP);

Prototype in    stdlib.h

Description     gcvt converts  value to a  null-terminated ASCII string  in
                bufP and returns a pointer  to bufP. It attempts to produce
                ndec  significant digits  in FORTRAN  F-format if possible;
                otherwise,  E-format  (ready  for  printing)  is  returned.
                Trailing zeros may be suppressed.

Return value    gcvt returns the string pointed to by bufP.

*---------------------------------------------------------------------------*/
char   *gcvt  (double value, int ndec, char *bufP )
{
        __realcvt (&value, ndec, bufP, 'g', 0, F_8byteFloat);
        return  bufP;
}
