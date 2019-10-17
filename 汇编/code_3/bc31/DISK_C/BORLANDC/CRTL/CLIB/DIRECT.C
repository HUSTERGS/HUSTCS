/*-----------------------------------------------------------------------*
 * filename - direct.c
 *
 * functions:
 *        diropen       - opens a directory stream
 *        readdir       - read entry from directory stream
 *        rewinddir     - position directory stream at first entry
 *        closedir      - close directory stream
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1991, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <dirent.h>
#include <dos.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define DIRMAGIC 0xdd

/*----------------------------------------------------------------------
Name            opendir - open a directory stream

Usage           #include <dirent.h>
                DIR *opendir(char *dirname);

Related
functions usage struct dirent *readdir(DIR *dirp);
                void rewinddir(DIR *dirp);
                int closedir(DIR *dirp);

Prototype in    dirent.h

Description     The opendir() function opens a directory stream for reading
                The name of the directory to read is dirname.  The stream
                is set to read the first entry in the directory.

Return value    On a successful open, opendir() returns a pointer to
                an object of type DIR.  On an error, opendir() returns
                NULL and sets errno as follows:

                ENOENT  The directory does not exist.
                ENOMEM  Not enough memory to allocate a DIR object.

*---------------------------------------------------------------------*/

DIR * _FARFUNC opendir(char *dirname)
{
    char *name;
    DIR *dir;
    int len;

    /* Allocate space for a copy of the directory name, plus
     * room for the "*.*" we will concatenate to the end.
     */
    len = strlen(dirname);
    if ((name = malloc(len+5)) == NULL)
        {
            errno = ENOMEM;
            return (NULL);
        }
    strcpy(name,dirname);
    if (len-- && name[len] != ':' && name[len] != '\\' && name[len] != '/')
            strcat(name,"\\*.*");
    else
            strcat(name,"*.*");

    /* Allocate space for a DIR structure.
     */
    if ((dir = malloc(sizeof(DIR))) == NULL)
        {
            errno = ENOMEM;
            free(name);
            return (NULL);
        }

    /* Search for the first file to see if the directory exists,
     * and to set up the DTA for future _dos_findnext() calls.
     */
    if (_dos_findfirst(name, _A_HIDDEN|_A_SYSTEM|_A_RDONLY|_A_SUBDIR,
                (struct find_t *)&dir->_d_reserved) != 0)
        {
            free(name);
            free(dir);
            return (NULL);              /* findfirst sets errno for us */
        }

    /* Everything is OK.  Save information in the DIR structure, return it.
     */
    dir->_d_dirname = name;
    dir->_d_first = 1;
    dir->_d_magic = DIRMAGIC;
    return dir;
}

/*----------------------------------------------------------------------
Name            rewinddir - rewind a directory stream

Usage           #include <dirent.h>
                void rewinddir(DIR *dirp);

Related
functions usage struct dirent *readdir(DIR *dirp);
                DIR *opendir(char *dirname);
                int closedir(DIR *dirp);

Prototype in    dirent.h

Description     The rewinddir() function resets the directory stream dirp to the
                first entry in the directory.

Return value    The rewinddir() function does not return a value.

*---------------------------------------------------------------------*/

void _FARFUNC rewinddir(DIR *dir)
{
    /* Verify the handle.
     */
    if (dir->_d_magic != DIRMAGIC)
            return;

    /* Search for the first file and set up the DTA for future
     * _dos_findnext() calls.
     */
    _dos_findfirst(dir->_d_dirname,_A_HIDDEN|_A_SYSTEM|_A_RDONLY|_A_SUBDIR,
                (struct find_t *)&dir->_d_reserved);
    dir->_d_first = 1;
}


/*----------------------------------------------------------------------
Name            readdir - read directory entry from a directory stream

Usage           #include <dirent.h>
                struct dirent *readdir(DIR *dirp);
Related
functions usage void rewinddir(DIR *dirp);
                DIR *opendir(char *dirname);
                int closedir(DIR *dirp);

Prototype in    dirent.h

Description     The readdir() function reads the directory entry at the
                current position in the directory stream dirp, and
                advances the directory stream position to the next entry.
                The directory entry is an object of type 'struct dirent'
                that contains the member
                        char d_name[]
                which is an array of characters containing the null-terminated
                filename.

                The readdir() function reads directory entries for all files,
                including directories.  On DOS, it also reads directory
                entries for system and hidden files.  It does not read
                volume labels or unused directory entries.

Return value    On a successful read, readdir() returns a pointer
                to an object of type 'struct direct'.  This structure
                will be overwritten by subsequent operations on the
                same directory stream.  It will not be overwritten
                by operations on other directory streams.

                When the end of the directory is reached, readdir()
                returns NULL but does not set errno.

                On an error, readdir() returns NULL and sets errno:

                EBADF   The dirp parameter does not point to a valid
                        open directory stream.

*---------------------------------------------------------------------*/

struct dirent * _FARFUNC readdir(DIR *dir)
{
    /* Verify the handle.
     */
    if (dir->_d_magic != DIRMAGIC)
        {
            errno = EBADF;
            return (NULL);
        }

    /* If this isn't the first file, call _dos_findnext() to get the next
     * directory entry.  Opendir() fetches the first one.
     */
    if (!dir->_d_first)
        {
            if (_dos_findnext((struct find_t *)&dir->_d_reserved) != 0)
                return (NULL);
        }
    dir->_d_first = 0;
    return &dir->_d_dirent;
}

/*----------------------------------------------------------------------
Name            closedir - close directory stream

Usage           #include <dirent.h>
                int closedir(DIR *dirp);

Related
functions usage void rewinddir(DIR *dirp);
                struct dirent *readdir(DIR *dirp);
                DIR *opendir(char *dirname);

Prototype in    dirent.h

Description     The closedir() function closes the directory stream dirp.
                Subsequently, dirp will not refer to a valid directory
                stream.

Return value    On a successful close, closedir() returns 0.
                On an error, closedir() returns -1 and sets errno:

                EBADF   The dirp parameter does not point to a valid
                        open directory stream.

*---------------------------------------------------------------------*/

int _FARFUNC closedir(DIR *dir)
{
    /* Verify the handle.
     */
    if (dir == NULL || dir->_d_magic != DIRMAGIC)
        {
            errno = EBADF;
            return (-1);
        }
    dir->_d_magic = 0;          /* prevent use after closing */

    free(dir->_d_dirname);
    free(dir);
    return 0;
}
