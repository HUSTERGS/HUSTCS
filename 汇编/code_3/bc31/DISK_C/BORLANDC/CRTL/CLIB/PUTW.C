/*-----------------------------------------------------------------------*
 * filename - putw.c
 *
 * function(s)
 *        putw - puts word on a stream
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

Name            putw - puts a character or word on a stream

Usage           #include <stdio.h>
                int putw(int w, FILE *stream);

Prototype in    stdio.h

Description     putw outputs the integer w to the output stream. putw neither
                expects nor causes special alignment in the file.

Return value    On success putw returns the integer w.

                On error, putw returns EOF.

                Since EOF is a legitimate integer, ferror
                should be used to detect errors with putw.

*---------------------------------------------------------------------*/
int _FARFUNC putw(int w, FILE *fp)
{
        if (putc(*((unsigned char *)&(w)), fp) != EOF)
                if (putc(*((unsigned char *)&(w) + 1), fp) != EOF)
                        return(w);

        return EOF;
}
