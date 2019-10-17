/*-----------------------------------------------------------------------*
 * filename - strtok.c
 *
 * function(s)
 *        strtok - searches one string for tokens, which are
 *                 separated by delimiters defined in a second string
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <string.h>
#include <RtlData.h>

#if !defined( _RTLDLL )
static  char *Ss;
#endif

/*---------------------------------------------------------------------*

Name            strtok - searches one string for tokens, which are
                         separated by delimiters defined in a second string

Usage           char *strtok(char *str1, const char *str2);

Prototype in    string.h

Description     strtok considers the string str1 to consist of a sequence of
                zero or more text tokens, separated by spans of one or more
                characters from the separator string str2.

                The first call to strtok returns a pointer to the first
                character of the first token in str1 and writes a null character
                into str1 immediately following the returned token. Subsequent
                calls with NULL for the first argument will work through the
                string str1 in this way until no tokens remain.

                The separator string, str2, may be different from call to
                call.

Return value    pointer to the scanned token.  When no tokens remain in str1,
                strtok returns a NULL pointer.

*---------------------------------------------------------------------*/
#if defined(__FARFUNCS__)
#include <_farfunc.h>
#endif

char * _CType _FARFUNC strtok(char *s1, const char *s2)
{
    register const char *sp;
    char *tok;
    _QRTLDataBlock;

    if (s1) _QRTLInstanceData(Ss) = (char *)s1;

    /* First skip separators */

    while (*_QRTLInstanceData(Ss))
    {
        for (sp = s2; *sp; sp++)
            if (*sp == *_QRTLInstanceData(Ss))
                break;
        if (*sp == 0)
            break;
        _QRTLInstanceData(Ss)++;
    }
    if (*_QRTLInstanceData(Ss) == 0)
        return (0);
    tok = _QRTLInstanceData(Ss);
    while (*_QRTLInstanceData(Ss))
    {
        for (sp = s2; *sp; sp++)
            if (*sp == *_QRTLInstanceData(Ss))
            {
                *_QRTLInstanceData(Ss)++ = 0;
                return (tok);
            }
        _QRTLInstanceData(Ss)++;
    }
    return (tok);
}
