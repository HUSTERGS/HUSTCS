/*-----------------------------------------------------------------------*
 * filename - strncat.c
 *
 * function(s)
 *        strncat - appends strings
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

Name            strncat - appends strings

Usage           char *strncat(char *destin, const char *source, size_t maxlen);

Prototype in    string.h

Description     strncat copies at most maxlen characters of source to the end
                of destin and then appends a null character. The maximum length
                of the resulting string is strlen(destin) + maxlen.

Return value    pointer to destin

*---------------------------------------------------------------------*/
#undef strncat                  /* not an intrinsic */

#if defined(__FARFUNCS__)
#include <_farfunc.h>
#endif

char _FAR * _CType _FARFUNC strncat(char _FAR *dest, const char _FAR *src, size_t maxlen)
{
    register unsigned len;
    unsigned dlen;

    dlen = strlen(dest);
    len = strlen(src);
    if (len > maxlen)
        len = maxlen;
    movmem((void *)src, dest + dlen, len);
    dest[dlen + len] = 0;
    return (dest);
}
