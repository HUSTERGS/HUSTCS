/*------------------------------------------------------------------------
 * filename - atof.c
 *
 * function(s)
 *        atof - converts a string to a floating point number
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <stdio.h>
#include <stddef.h>
#include <_math.h>
#include <math.h>
#include <stdlib.h>

/*--------------------------------------------------------------------------*

Name            atof - converts a string to a floating point number

Usage           double atof(const char *strP);

Prototype in    stdlib.h & math.h

Description     atof converts a string pointed to by strP to a double; this
                functions recognizes:
                        - an optional string of tabs and spaces
                        - an optional sign
                        - the  a string of  digits and an  optional decimal
                          point
                        - the  an optional e  or E followed  by an optional
                          signed integer

                The first unrecognized character ends the conversion. There
                are no provisions for overflow.

Return value    atof returns  the converted value  of the input  string. If
                the  string cannot  be converted  to a  number of  the type
                double, the return value is 0.

*---------------------------------------------------------------------------*/
double atof(const char *strP)
{
    return strtod(strP, NULL);
}
