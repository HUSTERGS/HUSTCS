/*-----------------------------------------------------------------------*
 * filename - tempnam.c
 *
 * function(s)
 *        tempnam   - builds a unique file name in any directory
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
#include <string.h>
#include <stdlib.h>
#include <dir.h>
#include <dos.h>
#include <io.h>

/*---------------------------------------------------------------------*

Name            tempnam - builds a unique file name

Usage           char *tempnam(char *dir, char *prefix);

Prototype in    stdio.h

Description     The tempnam function creates a unique filename
                in arbitrary directories.  It attempts to use the following
                directories, in order, when creating the file:

                1. The directory specified by the TMP environment variable.
                2. The dir argument.
                3. The P_tmpdir definition in stdio.h.
                4. The current working directory.

                The prefix parameter specifies the first part
                of the filename; it cannot be longer than 5 characters.
                A unique filename is created by concatenating the directory,
                the prefix, and 6 unique characters.  Space for the
                resulting filename is allocated with malloc; the caller
                must free this filename by calling free().  The unique
                file is not actually created; tempnam only verifies that
                it does not current exist.

Return value    a pointer to the unique temporary file name, which the
                caller may pass to free() when no longer needed; or NULL if a
                no unique filename can be created.

*---------------------------------------------------------------------*/

char * _FARFUNC tempnam(char *dir, char *prefix)
{
    char *dirs[4];
    int tries;

    /* Make sure the prefix is 5 characters or less and has no '.' in it.
     */
    if (strlen(prefix) > 5 || strchr(prefix, '.') != NULL)
        return (NULL);

    /* Set up the four directories we'll try searching.
     */
    dirs[0] = getenv("TMP");            /* TMP enviroment variable */
    dirs[1] = dir;                      /* dir parameter */
    dirs[2] = P_tmpdir;                 /* stdio.h temp dir */
    dirs[3] = "";                       /* current directory */

    /* Search the four directories.
     */
    for (tries = 0; tries < 4; tries++)
    {
        char *dir, *p, *buf;
        unsigned err, attr, num;

        /* Allocate a buffer big enough for the complete filename.
        /* Put the directory name in the buffer, then repeatedly use
         * __mkname to append a weird name until we get one that
         * gives a filename that doesn't exist.
         */
        if ((dir = dirs[tries]) == NULL)
            continue;           /* skip NULL directory */
        if ((buf = malloc(strlen(dir)+strlen(prefix)+8)) == NULL)
            continue;           /* can't allocate space for dir\preXXXXXX */
        p = _stpcpy(buf,dir);
        if (p != buf && *(p-1) != '/' && *(p-1) != '\\' && *(p-1) != ':')
            *p++ = '\\';        /* add trailing slash */

        for (num = 0; num != TMP_MAX; num++)
        {
            __mkname(p, prefix, num);
            if ((err = _dos_getfileattr(buf, &attr)) != 0)
            {
                if (err == 2)           /* file not found? */
                    return (buf);       /* return unique name */
                else                    /* some other error */
                    break;              /* give up on this directory */
            }
        }
        free(buf);                      /* try next directory */
    }
    return (NULL);              /* all four directories failed */
}
