/*-----------------------------------------------------------------------*
 * filename - stpcpy.c
 *
 * function(s)
 *        _stpcpy - copies one string to another
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

Name            _stpcpy - copies one string to another

Usage           char *_stpcpy(char *destin, const char *source)

Prototype in    string.h

Description     _stpcpy copies the bytes of source into destin and stops after
                copying the terminating null character of source. _stpcpy (a, b)
                is the same as strcpy (a, b) except that the return values
                differ.

                strcpy(a, b) returns a, while _stpcpy (a, b) returns a +
                strlen (b).

Return value    returns destin + strlen(source);

*---------------------------------------------------------------------*/
char *_stpcpy(char *to, const char *from)
{
        register unsigned len;

        len = strlen(from);
        memcpy(to, from, len+1);
        return (to+len);
}
