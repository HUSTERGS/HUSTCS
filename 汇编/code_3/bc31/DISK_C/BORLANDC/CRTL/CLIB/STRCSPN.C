/*-----------------------------------------------------------------------*
 * filename - strcspn.c
 *
 * function(s)
 *        strcspn - scans a string for the first segment not containing
 *                  any subset of a given set of characters
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

Name            strcspn - scans a string for the first segment not containing
                          any subset of a given set of characters

Usage           size_t strcspn(const char *str1, const char *str2);

Prototype in    string.h

Description     strcspn returns the length of the initial segment of string
                str1 that consists entirely of characters not from string str2.

Return value    strcspn returns the length of the initial segment of string
                str1 that consists entirely of characters not from string str2.

*---------------------------------------------------------------------*/
#if defined(__FARFUNCS__)
#include <_farfunc.h>
#endif

size_t _FARFUNC strcspn(const char *s1, const char *s2)
{
        register const char *srchs2;
        int len;

        for (len = 0; *s1; s1++, len++)
                for (srchs2 = s2; *srchs2; srchs2++)
                        if (*s1 == *srchs2) goto bye;
bye:
        return (len);
}
