/*------------------------------------------------------------------------
 * filename - gets.c
 *
 * function(s)
 *        gets - gets a string from a stream
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

Name            gets - gets a string from a stream

Usage           char *gets(char *string);

Prototype in    stdio.h

Description     gets reads a string into string from the
                standard input stream stdin. The string is terminated by a
                newline character, which is replaced in @i{string} by a null
                character (\0).

Return value    on success, returns the string argument string;
                else returns NULL on end-of-file or error.

*---------------------------------------------------------------------*/
char *gets(char *s)
{
        register int     c;
        register char   *P;

        P = s;

        while ((c = getc (stdin)) != EOF && c != '\n')
                *P++ = c;

        if (EOF == c && P == s)
                return( NULL );
        *P = 0;
        return(((ferror (stdin)) ? NULL : s));
}
