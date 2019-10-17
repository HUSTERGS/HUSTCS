/*-----------------------------------------------------------------------*
 * filename - tmpnam.c
 *
 * function(s)
 *        tmpnam   - builds a unique file name
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

#if !defined( _RTLDLL )
extern unsigned _tmpnum;
#endif

/*---------------------------------------------------------------------*

Name            tmpnam - builds a unique file name

Usage           char *tmpnam(char *s);

Prototype in    stdio.h

Return value    a unique temporary file name

*---------------------------------------------------------------------*/

char * _FARFUNC tmpnam(char *s)
{
    return (__tmpnam(s, &_RTLInstanceData(_tmpnum)));
}
