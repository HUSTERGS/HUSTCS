/*-----------------------------------------------------------------------*
 * filename - fullpath.c
 *
 * function(s)
 *        isSlash   - check for directory separator character
 *        _fullpath - make an absolute path name from a relative path name
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <ctype.h>
#include <direct.h>
#include <dos.h>
#include <stdlib.h>
#include <string.h>

/*---------------------------------------------------------------------*

Name            isSlash - check for directory separator character

Usage           int isSlash(int c);

Prototype in    local

Description     isSlash returns true if the character c is a valid
                directory separator character (\ or / on DOS, / on UNIX).
                It returns false otherwise.

Return value    Describe above.

*---------------------------------------------------------------------*/
static int pascal near isSlash (int c)
{
    return (c == '\\' || c == '/');
}

/*---------------------------------------------------------------------*

Name            _fullpath - makes new file name

Usage           #include <dir.h>
                char *_fullpath(char *buffer, const char * pathname,
                                size_t maxlen);

Prototype in    stdlib.h

Description     _fullpath converts the relative path name name 'pathname'
                to a fully qualified pathname, stored in 'buffer'.  The
                relative path can contain ".\" and "..".

                The maximum size of the supplied buffer is 'maxlen'.
                If the fully qualified path is longer than 'maxlen',
                NULL is returned.  The buffer should be at least _MAX_PATH
                bytes long (this constant is defined in stdlib.h).

                If 'buffer' is NULL, a buffer to store the fully qualified
                path is allocated and is returned.  The calling program
                must free this buffer with free() when it is no longer needed.

                If the pathname does not specify a disk drive, the current
                drive is used.

Return value    A pointer to the buffer containing the fully qualified
                path is returned.  If there is an error, NULL is returned.

Note            This function is a rewrite of the FExpand procedure
                in the Turbo Pascal RTL, with modifications for MSC
                compatibility.

*---------------------------------------------------------------------*/
char * _CType _FARFUNC _fullpath(char *buffer,
                                 const char *pathname,
                                 size_t maxlen
                                )
{
    char *tempbuf;
    char *dst, *src;
    int c, len, driveletter;
    unsigned drive;

    /* Allocate a temporary buffer to hold the fully qualified path.
     */
    if ((tempbuf = malloc(_MAX_PATH*2+1)) == NULL)
        return (NULL);

    /* Check for a drive name.  If one is not provided,
     * get the current drive.  Point src at the first
     * character in pathname after the drive name, if any.
     */
    src = (char *)pathname;
    if (isalpha(src[0]) && src[1] == ':')
        {
        drive = toupper(driveletter = src[0]) - 'A' + 1;
        src += 2;
        }
    else
        {
        _dos_getdrive(&drive);          /* get current drive */
        driveletter = drive + 'A' - 1;
        }

    /* If supplied path is relative, append it to the drivename
     * and its current directory.  Otherwise append it to the
     * drivename only.
     */
    if (!isSlash(src[0]))               /* path is relative? */
        {
        /* Get drivename and its current directory.
         */
        if (_getdcwd(drive,tempbuf,_MAX_PATH*2+1) == NULL)
            {
            free(tempbuf);
            return (NULL);
            }
        dst = &tempbuf[strlen(tempbuf)];
        if (!isSlash(*(dst-1)))         /* if directory doesn't end in slash */
            *dst++ = '\\';              /* append one */
        }
    else
        {
        /* Path is absolute.  Store the drivename only.
         */
        dst = tempbuf;
        *dst++ = driveletter;
        *dst++ = ':';
        }
    strcpy(dst,src);                    /* concatenate supplied path */

    /* Scan the path, squeezing out "..\" and ".\", and
     * squeezing out the previous directory when "..\" is found.
     */
    src = dst = tempbuf;
    for (;;)
        {
        /* If this the end of the path, or end of a directory,
         * we must check for "." or ".."
         */
        if ((c = *src++) == '\0' || isSlash(c))
            {
            /* If last directory copied was "\.", back up over it.
             */
            if (*(dst-1) == '.' && isSlash(*(dst-2)))
                dst -= 2;

            /* If last directory copied was "\..", back up over it
             * AND the previous directory.
             */
            else if (*(dst-1) == '.' && *(dst-2) == '.' && isSlash(*(dst-3)))
                {
                dst -= 3;               /* back up over "\.." */
                if (*(dst-1) == ':')    /* can't back up over drivename */
                    {
                    free(tempbuf);
                    return(NULL);
                    }
                while (!isSlash(*--dst))
                    ;                   /* back up to start of prev. dir. */
                }

            if (c == '\0')              /* end of path? */
                {
                if (isSlash(*(dst-1)))  /* if last char is slash */
                    dst--;              /*  back up over it */
                if (*(dst-1) == ':')    /* if path is just a drivename */
                    *dst++ = '\\';      /*  append a slash */
                *dst = '\0';            /* append null terminator */
                break;
                }
            else
                *dst++ = c;             /* copy the slash */
            }
        else
            *dst++ = c;                 /* copy the character */
        }

    /* Copy the temp buffer to the user's buffer, if present.
     * Otherwise shrink the temp buffer and return a pointer to it.
     */
    len = strlen(tempbuf) + 1;                  /* length of path and null */
    if (buffer != NULL)
        {
        if (len > maxlen)                       /* user buffer too small? */
            {
            free(tempbuf);
            return (NULL);
            }
        else
            {
            strcpy(buffer,tempbuf);
            free(tempbuf);
            return (buffer);
            }
        }
    else
        return (realloc(tempbuf,len));          /* shrink the buffer */
}
