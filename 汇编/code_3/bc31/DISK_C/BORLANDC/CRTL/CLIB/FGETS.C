/*------------------------------------------------------------------------
 * filename - fgets.c
 *
 * function(s)
 *        fgets - gets a string from a stream
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <stdio.h>

/*---------------------------------------------------------------------*

Name            fgets - gets a string from a stream

Usage           char *fgets(char *string, int n, FILE *stream);

Prototype in    stdio.h

Description     reads characters from stream into the string string:
                The function stops reading when it either reads n-1
                characters or reads a newline character (whichever
                comes first).  fgets retains the newline character.
                The last character read into string is followed by a
                null character.

Return value    success : pointer to string
                failure : NULL

*---------------------------------------------------------------------*/
char * _FARFUNC fgets (char *s, int n, FILE *fp)
{
        register    int    c = 0;
        register    char    *P;

        P = s;

        while ('\n' != c && --n > 0  &&  (c = getc(fp)) != EOF)  *P++ = c;

        if (EOF == c && P == s)  return( NULL );
        *P = 0;
        return (ferror (fp)) ? NULL : s;
}
