/*-----------------------------------------------------------------------*
 * filename - freopen.c
 *
 * function(s)
 *        freopen       - replaces a stream
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <stdio.h>
#include <_stdio.h>


/*---------------------------------------------------------------------*

Name            freopen -  replaces a stream

Usage           FILE *freopen(const char *filename, const char *type,
                              FILE *stream);

Prototype in    stdio.h

Description     See description of fopen() in fopen.c

*---------------------------------------------------------------------*/
FILE * _FARFUNC freopen(const char *filename, const char *type, FILE *fp)
{
        if (fp->token != (short) fp)
                return NULL;    /* validate pointer */

        fclose (fp);

        return __openfp (fp, filename, type, 0);
}
