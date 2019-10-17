/*-----------------------------------------------------------------------*
 * filename - fsetpos.c
 *
 * function(s)
 *        fsetpos - positions the file pointer on a stream
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

Name            fsetpos - positions the file pointer on a stream

Usage           #include <stdio.h>
                int fsetpos(FILE *stream, const fpos_t *pos);

Prototype in    stdio.h

Description     sets the file pointer using fseek

Return value    success : 0
                failure : non-zero

*------------------------------------------------------------------------*/


int     fsetpos(FILE *stream, const fpos_t *pos)
{
        return fseek(stream, *pos, SEEK_SET);
}
