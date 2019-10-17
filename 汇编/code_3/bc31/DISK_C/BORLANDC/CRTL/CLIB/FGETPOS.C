/*------------------------------------------------------------------------
 * filename - fgetpos.c
 *
 * function(s)
 *        fgetpos - gets the current file pointer
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <stdio.h>

/*-----------------------------------------------------------------------*

Name            fgetpos - gets the current file pointer

Usage           #include <stdio.h>
                int fgetpos(FILE *stream, fpos_t *pos);

Prototype in    stdio.h

Description     stores the position of the file pointer associated
                with stream in the location pointed to by pos

Return value    success : 0
                failure : non-zero

*-----------------------------------------------------------------------*/


int     fgetpos(FILE *stream, fpos_t *pos)
{
        return ((*pos = ftell(stream)) == -1) ? -1 : 0;
}
