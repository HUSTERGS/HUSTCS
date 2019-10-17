/*-----------------------------------------------------------------------*
 * filename - sopen.c
 *
 * function(s)
 *        sopen         - open a file for file sharing (MSC compatible)
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#define __IN_SOPEN

#include <stdio.h>
#include <io.h>
#include <fcntl.h>

/*-----------------------------------------------------------------------*

Name            sopen - opens a file for file sharing

Usage           #include <fcntl.h>
                #include <sys\stat.h>
                #include <share.h>
                #include <io.h>

                int sopen(const char *pathname, int access, int shflag
                          [, unsigned permiss] );

Prototype in    io.h

Description     Similar to open, except that it has an extra parameter shflag,
                which specifies the file sharing mode.  This sharing mode
                can be one of the constants defined in share.h; see the
                sopen documention for a complete description.
*------------------------------------------------------------------------*/
/* sopen declared old style since prototype has ... */

int  sopen(pathP, oflag, shflag, mode)
const char *pathP;
int oflag;
int shflag;
unsigned mode;  /* optional -- only used when oflag contains O_CREAT */
{
    if (oflag & O_CREAT)
        return (open(pathP, oflag|shflag, mode));
    else
        return (open(pathP, oflag|shflag));
}
