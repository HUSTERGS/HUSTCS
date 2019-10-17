/*-----------------------------------------------------------------------*
 * filename - getcwd.c
 *
 * function(s)
 *        getcwd - gets current working directory
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <dir.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <alloc.h>


/*---------------------------------------------------------------------*

Name            getcwd - gets current working directory

Usage           char *getcwd(char *buf, int n);

Prototype in    dir.h

Description     getcwd gets the full path name of the cwd (current
                working directory, including the drive), up to n bytes
                long, and stores it in buf. If the full path name length
                (including the null-terminator) is longer than n, an
                error occurs.

                If buf is NULL, a buffer n bytes long will be allocated
                for you with malloc. You can later free the allocated buffer
                by passing the getcwd return value to the function free.

Return value    getcwd returns buf; on error, it returns NULL.

                In the event of an error return, the global variable errno is
                set to one of the following:

                        ENODEV  No such device
                        ENOMEM  Not enough core
                        ERANGE  Result out of range

*---------------------------------------------------------------------*/
char * _FARFUNC getcwd(char _FAR *bufP, int bufL)
{
        char    bufI[MAXDIR + 2];

        /* Get current disk */
        bufI[0] = getdisk() + 'A';
        bufI[1] = ':';
        bufI[2] = '\\';

        /* Get current directory in a work buffer */
        if (getcurdir(0, &bufI[3]) == -1)
                return  NULL;
        if (strlen(bufI) >= bufL)
        {
                errno = ERANGE;
                return  NULL;
        }

        /* Allocate a buffer if bufP is NULL */
        if (bufP == NULL)
                if ((bufP = malloc(bufL)) == NULL)
                {
                        errno = ENOMEM;
                        return  NULL;
                }
        strcpy(bufP, bufI);
        return  bufP;
}
