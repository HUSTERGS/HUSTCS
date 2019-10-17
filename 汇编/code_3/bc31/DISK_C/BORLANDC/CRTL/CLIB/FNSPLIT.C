/*------------------------------------------------------------------------
 * filename - fnsplit.c
 *
 * function(s)
 *        fnsplit - splits a full path name into its components
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <dir.h>

/*---------------------------------------------------------------------*

Name            fnsplit - splits a full path name into its components

Usage           #include <dir.h>
                void fnsplit(const char *path, char * drive, char * dir,
                             char * name, char * ext);

Related
functions usage int fnmerge(char *path, const char *drive, const char *dir,
                            const char *name, const char *ext);

Prototype in    dir.h

Description     fnsplit takes a file's full path name (path) as a string
                in the form

                        X:\DIR\SUBDIR\NAME.EXT

                and splits path into its four components. It then stores
                those components in the strings pointed to by drive, dir,
                name and ext. (Each component is required but can be a
                NULL, which means the corresponding component will be
                parsed but not stored.)

                The maximum sizes for these strings are given by the
                constants MAXDRIVE, MAXDIR, MAXPATH, MAXNAME and MAXEXT,
                (defined in dir.h) and each size includes space for the
                null-terminator.

                        Constant        (Max.)  String

                        MAXPATH         (80)    path
                        MAXDRIVE        (3)     drive; includes colon (:)
                        MAXDIR          (66)    dir; includes leading and
                                                trailing backslashes (\)
                        MAXFILE         (9)     name
                        MAXEXT          (5)     ext; includes leading dot (.)

                fnsplit assumes that there is enough space to store each
                non-NULL component. fnmerge assumes that there is enough
                space for the constructed path name. The maximum constructed
                length is MAXPATH.

                When fnsplit splits path, it treats the punctuation as
                follows:

                * drive keeps the colon attached (C:, A:, etc.)

                * dir keeps the leading and trailing backslashes
                  (\turboc\include\,\source\, etc.)

                * ext keeps the dot preceding the extension (.c, .exe, etc.)

                These two functions are invertible; if you split a given path
                with fnsplit, then merge the resultant components with fnmerge,
                you end up with path.

Return value    fnsplit returns an integer (composed of five flags,
                defined in dir.h) indicating which of the full path name
                components were present in path; these flags and the components
                they represent are:

                        EXTENSION       an extension
                        FILENAME        a filename
                        DIRECTORY       a directory (and possibly
                                        sub-directories)
                        DRIVE           a drive specification (see dir.h)
                        WILDCARDS       wildcards (* or ? cards)

*---------------------------------------------------------------------*/
int _CType _FARFUNC fnsplit(const char *pathP, char *driveP, char *dirP,
char *nameP, char *extP)
{
        return (_fnsplit(pathP,driveP,dirP,nameP,extP));
}
