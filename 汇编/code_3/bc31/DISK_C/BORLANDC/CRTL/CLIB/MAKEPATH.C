/*-----------------------------------------------------------------------*
 * filename - makepath.c
 *
 * function(s)
 *        _makepath - make new filename
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <string.h>

/*---------------------------------------------------------------------*

Name            _makepath - makes new file name

Usage           #include <stdlib.h>
                void _makepath(char *path, const char * drive, const char * dir,
                             const char * name, const char * ext);

Related
functions usage void _splitpath(const char *path, char *drive, char *dir,
                            char *name, char *ext);

Prototype in    stdlib.h

Description     _makepath makes a file name from its components. The
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
                constant _MAX_PATH (defined in stdlib.h), which includes space
                for the null-terminator.

                _splitpath and _makepath are invertible; if you split a given
                path with _splitpath, then merge the resultant components
                with _makepath, you end up with path.

Return value    None

*---------------------------------------------------------------------*/

void _FARFUNC _makepath(register char *pathP,
                        const char *driveP,
                        const char *dirP,
                        const char *nameP,
                        const char *extP
                       )
{
        if (driveP && *driveP)
            {
                *pathP++ = *driveP++;
                *pathP++ = ':';
            }
        if (dirP && *dirP)
            {
                pathP = _stpcpy(pathP,dirP);
                if (*(pathP-1) != '\\' && *(pathP-1) != '/') *pathP++ = '\\';
            }
        if (nameP)
        pathP = _stpcpy(pathP,nameP);
        if (extP && *extP)
            {
                if (*extP != '.') *pathP++ = '.';
                pathP = _stpcpy(pathP,extP);
            }
        *pathP = 0;
}
