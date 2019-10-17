/*-----------------------------------------------------------------------*
 * filename - srchpath.c
 *
 * function(s)
 *        searchpath   - searches the DOS path
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <dir.h>
#include <_dir.h>

/*-----------------------------------------------------------------------*

Name            searchpath - searches the DOS path

Usage           char *searchpath(const char *filename);

Prototype in    dir.h

Description     searchpath simply calls __searchpath to search the current
                directory and MS DOS path for filename.

Return value    see __searchpath in searchp.cas.

*------------------------------------------------------------------------*/
char * _CType searchpath(const char *file)
{
        return __searchpath(file, _USEPATH);
}
