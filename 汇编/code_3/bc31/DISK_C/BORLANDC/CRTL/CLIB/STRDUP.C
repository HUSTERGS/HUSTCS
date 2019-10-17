/*-----------------------------------------------------------------------*
 * filename - strdup.c
 *
 * function(s)
 *        strdup - copies a string into a newly-created location
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <string.h>
#include <stddef.h>
#include <alloc.h>

/*---------------------------------------------------------------------*

Name            strdup - copies a string into a newly-created location

Usage           char *strdup(const char *str);

Prototype in    string.h

Description     strdup makes a duplicate of string str, obtaining space with a
                call to malloc. The allocated space is (strlen (str) + 1)
                bytes long.

Return value    strdup returns a pointer to the storage location containing
                the duplicated str, or returns NULL if space could not be
                allocated.

*---------------------------------------------------------------------*/
#if defined(__FARFUNCS__)
#include <_farfunc.h>
#endif

char * _FARFUNC strdup(const char *s)
{
        char    *p;
        unsigned n;

        n = strlen(s) + 1;
        if ((p = (char *)malloc(n)) != NULL)
                memcpy(p, s, n);
        return (p);
}

