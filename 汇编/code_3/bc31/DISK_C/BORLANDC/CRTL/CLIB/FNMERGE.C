/*-----------------------------------------------------------------------*
 * filename - fnmerge.c
 *
 * function(s)
 *        fnmerge - make new filename
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <stdlib.h>

/*---------------------------------------------------------------------*

Name            fnmerge - makes new file name

Usage           #include <dir.h>
                void fnmerge(char *path, const char * drive, const char * dir,
                             const char * name, const char * ext);

Related
functions usage int fnsplit(const char *path, char *drive, char *dir,
                            char *name, char *ext);

Prototype in    dir.h

Description     fnmerge makes a file name from its components. The
                new file's full path name is

                        X:\DIR\SUBDIR\NAME.EXT

                where

                        X is given by drive
                        \DIR\SUBDIR\ is given by dir
                        NAME.EXT is given by name and ext

                If the drive, dir, name, or ext parameters are null or empty,
                they are not inserted in the path string.  Otherwise, if
                the drive doesn't end a colon, one is inserted in the path.
                If the dir doesn't end in a slash, one is inserted in the
                path.  If the ext doesn't start with a dot, one is inserted
                in the path.

                The maximum sizes for the path string is given by the
                constant MAXPATH (defined in dir.h), which includes space
                for the null-terminator.

                fnsplit and fnmerge are invertible; if you split a given path
                with fnsplit, then merge the resultant components with fnmerge,
                you end up with path.

Return value    None

*---------------------------------------------------------------------*/
void _CType _FARFUNC fnmerge(register char *pathP, const char *driveP,
const char *dirP, const char *nameP, const char *extP)
{
        _makepath(pathP,driveP,dirP,nameP,extP);
}
