/*-----------------------------------------------------------------------*
 * filename - system.c
 *
 * function(s)
 *    system - issues an MS-DOS command
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <dos.h>
#include <stdlib.h>
#include <_process.h>
#include <errno.h>
#include <string.h>

/*---------------------------------------------------------------------*

Name            system - issues an MS-DOS command

Usage           int system(const char *command);

Prototype       in stdlib.h

Description     system invokes the MS-DOS command processor to
                execute a command given in the string command, as if the command
                had been typed at the DOS prompt.

                The COMSPEC environment variable is used to find the
                command processor file, so the file does not need to be in
                the current directory.

Return value    If command is a NULL pointer then system() returns nonzero if
                a command processor is available.  If command is not a NULL pointer,
                system() returns zero if the command processor was successfully
                started.  If an error occurred, a -1 is returned and errno is set to
                ENOENT, ENOMEM, E2BIG, or ENOEXEC.

                ENOENT  - command processor not found
                ENOMEM  - not enough memory
                E2BIG   - argument list too long
                ENOEXEC - the command processor is not a valid executable

*---------------------------------------------------------------------*/
int _FARFUNC system(const char _FAR *cmd)
{
    register char   *cmdP;
    int             cmdS;

    register char   *envP;
    void            *envSave;
    char            *pathP;
    int             rc;

//  Check whether user just wants to test if command processor is available.
//
    if (cmd == NULL)
        {
        if ((pathP = getenv("COMSPEC")) == NULL)
            {
            errno = ENOENT;
            return 0;
            }
        else
            return 1;
        }

//  Get COMMAND.COM path
//
    if ((pathP = getenv("COMSPEC")) == NULL)
        {
        errno = ENOENT;
        return (-1);
        }

//  Build command line
//
    cmdS = 1 + 3 + strlen(cmd) + 1;
    if (cmdS > 128)
        {
        errno = E2BIG;
        return (-1);
        }
    if ((cmdP = malloc(cmdS)) == NULL)
        {
        errno = ENOMEM;
        return (-1);
        }

    if (cmdS == 5)
        {
        cmdP[0] = 0;
        cmdP[1] = '\r';
        }
    else
        {
        *cmdP++ = cmdS - 2;
        *cmdP++ = getswitchar();
        cmdP = _stpcpy(cmdP, "c ");
        cmdP = _stpcpy(cmdP, cmd);
        *cmdP++ = '\r';
        cmdP -= cmdS;
        }

//  Build environment
//
    if ((envP = __DOSenv(environ, pathP, &envSave)) == NULL)
        {
        errno = ENOMEM;
        free(cmdP);
        return (-1);
        }

//  Flush all byte streams
//
    (*_exitbuf)();

//  Now, call the low level _spawn function
//
    rc = _spawn(pathP, cmdP, envP);

//  Release all buffers
//
    free(envSave);
    free(cmdP);
    return ((rc == -1) ? -1 : 0);
}
