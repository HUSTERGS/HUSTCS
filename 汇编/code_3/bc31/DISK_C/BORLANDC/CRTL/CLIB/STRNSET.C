/*-----------------------------------------------------------------------*
 * filename - strnset.c
 *
 * function(s)
 *        strnset - sets all characters in a string to a given
 *                  character
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <string.h>
#include <mem.h>

/*---------------------------------------------------------------------*

Name            strnset - sets all characters in a string to a given
                          character

Usage           char *strnset(char *str, int ch, size_t n);

Prototype in    string.h

Description     strnset sets up to the first n bytes of the string str to the
                character ch. If n > strlen(str), then strlen(str) replaces n.

Return value    pointer to str

*---------------------------------------------------------------------*/
#undef strnset                  /* not an intrinsic */

#if defined(__FARFUNCS__)
#include <_farfunc.h>
#endif

char * _FARFUNC strnset(char _FAR *s, int ch, size_t n)
{
        unsigned len;

        len = strlen(s);
        if (len < n)
                n = len;
        setmem(s, n, ch);
        return (s);
}

