/*-----------------------------------------------------------------------*
 * filename - labs.c
 *
 * function(s)
 *        labs - gives long absolute value
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <stdlib.h>

/*---------------------------------------------------------------------*

Name            labs - gives long absolute value

Usage           long labs(long n);

Prototype in    stdlib.h

Description     calculates the absolute value of n, a long integer.

Return value    the absolute value of n.

*---------------------------------------------------------------------*/
long labs(long n)
{
        return(n < 0 ? -n : n);
}
