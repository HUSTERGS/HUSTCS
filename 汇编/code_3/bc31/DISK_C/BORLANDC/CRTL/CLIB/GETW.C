/*-----------------------------------------------------------------------*
 * filename - getw.c
 *
 * function(s)
 *        getw - gets a word from a stream
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

Name            getw - gets a word from a stream

Usage           #include <stdio.h>
                int getw(FILE * stream);

Prototype in    stdio.h

Description     see getc

*---------------------------------------------------------------------*/
int getw(FILE *fp)
{
        int     c, res;

        if ((c = getc(fp)) != EOF)
                if ((res = getc(fp)) == EOF)
                        c = EOF;
                else
                        (*((char *)&(c) + 1)) = res;

        return(c);
}
