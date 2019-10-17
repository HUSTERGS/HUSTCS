/*-----------------------------------------------------------------------*
 * filename - memicmp.c
 *
 * function(s)
 *        memicmp - compares two memory areas
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <mem.h>
#include <ctype.h>

/*------------------------------------------------------------------------*

Name            memicmp - compares two memory areas

Usage           int memicmp(const void *s1, const void *s2, size_t n);

Prototype in    mem.h & string.h

Description     memicmp compares the  first n bytes of s1  and s2, ignoring
                character case (upper or lower).

Return value    < 0     if s1 is less than s2
                = 0     if s1 is the same as s2
                > 0     if s1 is greater than s2

*---------------------------------------------------------------------------*/

#undef toupper

#if defined(__FARFUNCS__)
#include <_farfunc.h>
#endif

int _FARFUNC memicmp(const void *s1, const void *s2, size_t n)
{
        int dif;

        for (; n-- >0; ((unsigned char *)s1)++, ((unsigned char *)s2)++ )
        {
                dif = toupper(*(unsigned char *)s1) - toupper(*(unsigned char *)s2);
                if (dif != 0)
                        return(dif);
        }
        return(0);
}

