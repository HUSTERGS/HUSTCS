/*-----------------------------------------------------------------------*
 * filename - _fsopen.c
 *
 * function(s)
 *        _fsopen       - opens a stream with file sharing (MSC compatible)
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1991, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <stdio.h>
#include <_stdio.h>

/*---------------------------------------------------------------------*

Name            _fsopen -  open a stream with file sharing

Usage           FILE *_fsopen(const char *filename, char *type, int shflag);

Prototype in    stdio.h

Description     Similar to fopen, except that it has a third parameter,
                which specifies the file sharing mode.  This sharing mode
                can be one of the constants defined in share.h; see the
                sopen documention for a complete description.
*---------------------------------------------------------------------*/
FILE * _FARFUNC _fsopen (const char *filename, const char *type, int shflag)
{
        register FILE   *fp;

        if ((fp = __getfp()) == NULL)
                return NULL;
        else
                return __openfp (fp, filename, type, shflag);
}
