/*-----------------------------------------------------------------------*
 * filename - files.c
 *
 * function(s)
 *    none
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <stdio.h>
#include <_nfile.h>

#define _F_STDIN    (_F_READ | _F_TERM | _F_LBUF)
#define _F_STDOUT   (_F_WRIT | _F_TERM | _F_LBUF)
#define _F_STDERR   (_F_WRIT | _F_TERM)
#define _F_STDAUX   (_F_RDWR | _F_TERM | _F_BIN)
#define _F_STDPRN   (_F_WRIT | _F_TERM | _F_BIN)

/*---------------------------------------------------------------------*

Name            _streams

Description     _streams is the array of FILE structures used by the
                stream handling functions.

*---------------------------------------------------------------------*/

#if !defined( _RTLDLL )

FILE    _streams [_NFILE_] =
{
    { 0, _F_STDIN,   0, 0, 0, NULL, NULL, 0, (short) stdin },
    { 0, _F_STDOUT,  1, 0, 0, NULL, NULL, 0, (short) stdout },
    { 0, _F_STDERR,  2, 0, 0, NULL, NULL, 0, (short) stderr },
    { 0, _F_STDAUX,  3, 0, 0, NULL, NULL, 0, (short) stdaux },
    { 0, _F_STDPRN,  4, 0, 0, NULL, NULL, 0, (short) stdprn }
};

#endif  // _RTLDLL
