/*-----------------------------------------------------------------------*
 * filename - strset.c
 *
 * function(s)
 *        strset - sets all characters in a string to a given
 *                 character
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

Name            strset - sets all characters in a string to a given
                         character

Usage           char *strset(char *str, int ch);

Prototype in    string.h

Description     strset sets all characters in the string str to the
                character ch.

Return value    pointer to str

*---------------------------------------------------------------------*/
#undef strset            /* not an intrinsic */

#if defined(__FARFUNCS__)
#include <_farfunc.h>
#endif

char _FAR * _FARFUNC strset(char _FAR *s, int ch)
{
        setmem(s, strlen(s), ch);
        return (s);
}

