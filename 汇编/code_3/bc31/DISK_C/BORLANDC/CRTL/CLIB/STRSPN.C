/*-----------------------------------------------------------------------*
 * filename - strspn.c
 *
 * function(s)
 *        strspn - scans a string for the first segment that is a
 *                 subset of a given set of characters
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <string.h>

/*---------------------------------------------------------------------*

Name            strspn - scans a string for the first segment that is a
                         subset of a given set of characters

Usage           size_t strspn(const char *str1, const char *str2);

Prototype in    string.h

Description     strspn returns the length of the initial segment of string
                str1 that consists entirely of characters from string str2.

Return value    strspn returns the length of the initial segment of string
                str1 that consists entirely of characters from string str2.


*---------------------------------------------------------------------*/
#if defined(__FARFUNCS__)
#include <_farfunc.h>
#endif

size_t _FARFUNC strspn(const char *s1, const char *s2)
{
        register const char *srchs2;
        int                 len;

        for (len = 0; *s1; s1++, len++)
        {
                for (srchs2 = s2; *srchs2; srchs2++)
                        if (*s1 == *srchs2)
                                break;
                if (*srchs2 == 0)
                        break;
        }
        return (len);
}
