/*-----------------------------------------------------------------------*
 * filename - stpcpy.c
 *
 * function(s)
 *        stpcpy - copies one string to another
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

Name            stpcpy - copies one string to another

Usage           char *stpcpy(char *destin, const char *source)

Prototype in    string.h

Description     stpcpy copies the bytes of source into destin and stops after
                copying the terminating null character of source. stpcpy (a, b)
                is the same as strcpy (a, b) except that the return values
                differ.

                strcpy(a, b) returns a, while stpcpy (a, b) returns a +
                strlen (b).

Return value    returns destin + strlen(source);

*---------------------------------------------------------------------*/
#undef stpcpy                  /* not an intrinsic */

char _FAR * _CType stpcpy(char _FAR *to, const char _FAR *from)
{
    register unsigned len;

    len = strlen(from);
    memcpy(to, from, len+1);
    return (to+len);
}
