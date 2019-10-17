/*------------------------------------------------------------------------
 * filename - atold.c
 *
 * function(s)
 *        _atold - converts a string to a long double
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */

#include <stdlib.h>

/*--------------------------------------------------------------------------*

Name            _atold - converts a string to a long double number

Usage           long double _atold(const char *strP);

Prototype in    stdlib.h & math.h

Description     _atold converts a string pointed to by strP to a long double;
                this functions recognizes:
                        - an optional string of tabs and spaces
                        - an optional sign
                        - the  a string of  digits and an  optional decimal
                          point
                        - the  an optional e  or E followed  by an optional
                          signed integer

                The first unrecognized character ends the conversion. There
                are no provisions for overflow.

Return value    _atold returns  the converted value  of the input  string. If
                the  string cannot  be converted  to a  number of  the type
                long double, the return value is 0.

*---------------------------------------------------------------------------*/
long double _atold(const char *strP)
{
    return _strtold(strP, NULL);
}
