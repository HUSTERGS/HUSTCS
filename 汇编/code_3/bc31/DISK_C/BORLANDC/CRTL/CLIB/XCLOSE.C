/*-----------------------------------------------------------------------*
 * filename - xclose.c
 *
 * function(s)
 *        _xclose - closes files
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <io.h>

/*---------------------------------------------------------------------*

Name            _xclose - closes files

Usage           void _xclose(void)

Description     called at exit to close open files

*---------------------------------------------------------------------*/
void _xclose(void)
{
        register int    i;

        for (i = 2; i < _nfile; i++)
                close(i);
}

