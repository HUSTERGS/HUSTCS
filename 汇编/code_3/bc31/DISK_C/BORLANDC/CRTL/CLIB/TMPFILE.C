/*-----------------------------------------------------------------------*
 * filename - tmpfile.c
 *
 * function(s)
 *        tmpfile - creates a unique temporary file
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
#include <RtlData.h>

/*---------------------------------------------------------------------*

Name            tmpfile - creates a unique temporary file

Usage           #include <stdio.h>
                FILE *tmpfile(void);

Prototype in    stdio.h

Return value    On successful completion, the associated stream.
                In the event of error, NULL is returned.

*---------------------------------------------------------------------*/

#if !defined( _RTLDLL )
unsigned _tmpnum;
#endif

FILE * _FARFUNC tmpfile(void)
{
    FILE    *stream;
    char    *s;

    s = __tmpnam(NULL,&_RTLInstanceData(_tmpnum)); /* Get a unique file name */
    if ((stream = fopen(s, "w+b")) != NULL)
            stream->istemp = _RTLInstanceData(_tmpnum);

    return (stream);
}
