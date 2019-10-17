/*-----------------------------------------------------------------------*
 * filename - loadprog.c
 *
 * function(s)
 *        _LoadProg -- Load and Execute a program
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <_process.h>
#include <process.h>
#include <stdlib.h>
#include <_dir.h>
#include <errno.h>
#include <string.h>


/*-----------------------------------------------------------------------*

Name            _LoadProg -- Load and Execute a program

Usage           #include <_process.h>
                int _LoadProg(int (* Func)(char *, char *, char *),
                              char *pathP,
                              char *argP[],
                              char *envV[],
                              int UsePath)

Prototype in    _process.h

Description     _Loadprog loads  and runs another  program, known as  child
                process.

                The child process overlays the  current program if _exec is
                passed  as  Func  argument,  otherwise  the  calling parent
                process regains  control after program execution  if _spawn
                is passed as Func argument.

                *pathP  is  the  file  name  of  the  called child process.
                _LoadProg searches  for pathname using the  standard MS-DOS
                search algorithm:

                        . no  extension or no period - search  for exact file
                          name;  if  not  successful,  add .EXE and search
                          again

                        . extension given - search only for exact file name

                        . period  given - search only for file name with no
                          extension

                UsePath, if  true, specifies that the  function will search
                for  the child  in those  directories specified  by the DOS
                PATH  environment   variable.  If  false,   _LoadProg  only
                searches the root and current working directory.

                At   execution  time,   the  child   process  receives  two
                arguments:
                        - a command string built from argP
                        - an environment built from envV.

Return value    A successful _exec does not return, and a successful _spawn
                returns  the exit  code of   the child  process. On  error,
                _LoadProg  returns  -1,  and  errno  is  set  to one of the
                following:
                        E2BIG   Argument list too long
                        EACCES  Permission denied
                        EMFILE  Too many open files
                        ENOENT  Path or file name not found
                        ENOEXEC Exec format error
                        ENOMEM  Not enough core

*------------------------------------------------------------------------*/
int near _LoadProg(int cdecl near (*Func)(char *, char *, char *), char *pathP,
                        char *argP[], char *envV[], int UsePath)
{
        char    *cmdP, *envP;
        void    *envSave;
        int     rc;

        /*      First, Check if the program exists      */
        if ((pathP = __searchpath(pathP, UsePath | _PROGRAM)) == NULL)
        {
                errno = ENOENT;
                return -1;
        }

        /* Then, concatenate arguments to make the DOS command line */
        if ((cmdP = __DOScmd(argP)) == NULL)
        {
                errno = ENOMEM;
                return -1;
        }

        /*      Then, concatenate environment strings           */
        if (envV == NULL)
                envV = environ;
        if ((envP = __DOSenv(envV, pathP, &envSave)) == NULL)
        {
                errno = ENOMEM;
                free(cmdP);
                return -1;
        }

        /*      Flush all byte streams          */
        (*_exitbuf)();

        /*      Now, call the low level _exec/_spawn function   */
        rc = (*Func)(pathP, cmdP, envP);

        /*      Release all working buffers     */
        free(envSave);
        free(cmdP);
        return (rc);
}
