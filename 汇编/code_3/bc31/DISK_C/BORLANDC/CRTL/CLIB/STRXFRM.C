/*-----------------------------------------------------------------------*
 * filename - strxfrm.c
 *
 * function(s)
 *        strxfrm - copies one string into another
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <string.h>

size_t strxfrm(char *dest, const char *src, size_t n)
{
    int l = strlen( src );

    while( n-- && (*dest++ = *src++) != 0)
        ;

    if (dest)
        *(dest-1) = '\0';

    return l;
}


