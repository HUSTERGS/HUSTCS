/*-----------------------------------------------------------------------*
 * filename - multbyte.c
 *
 * function(s)
 *        mblen    - determines number of bytes in multibyte character
 *        mbtowc   - converts multibyte character to wide character
 *        wctomb   - converts wide character to multibyte character
 *        mbstowcs - converts a multibyte string to a wide character string
 *        wcstombs - converts a wide character string to a multibyte string
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <stdlib.h>

#pragma argsused
int _FARFUNC mblen(const char *s, size_t n)
{
    if (s == NULL)
        return 0;
    if (*s == 0)
        return 0;
    else
        return 1;
}


#pragma argsused
int _FARFUNC mbtowc(wchar_t *pwc, const char *s, size_t n)
{
    if (s == NULL)
        return 0;
    if (pwc != NULL)
        *pwc = *s;
    if (*s == 0)
        return 0;
    else
        return 1;
}


int _FARFUNC wctomb(char *s, wchar_t wc)
{
    if (s == NULL)
        return 0;
    *s = wc;
    return 1; /* zero if wc == 0 ? */
}


size_t _FARFUNC mbstowcs(wchar_t *pwcs, const char *s, size_t n)
{
    int i;

    for (i=0; i<n && *s; i++)
        *pwcs++ = *s++;
    if (i<n)
        *pwcs = 0;
    return i;
}


size_t _FARFUNC wcstombs(char *s, const wchar_t *pwcs, size_t n)
{
    int i;

    for (i=0; i<n && *pwcs; i++)
        *s++ = *pwcs++;
    if (i<n)
        *s = 0;
    return i;
}
