/*------------------------------------------------------------------------
 * filename - execlpe.c
 *
 * function(s)
 *        execlpe - load and execute a program
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <process.h>
#include <_process.h>
#include <stddef.h>

/*---------------------------------------------------------------------------*

Name            exec... - functions that load and run other programs

Usage           int  execlpe(char *pathname, char *arg0, char *arg1, ...,
                           char *argn, NULL, char *envp[]);

Prototype in    process.h

Description     The functions in the exec...  family load and run (execute)
                other programs,  known as child processes.  When an exec...
                call is  successful, the child process  overlays the parent
                process.  There  must  be  sufficient  memory available for
                loading and executing the child process.

                pathname is the file name  of the called child process. The
                exec...  functions search  for pathname  using the standard
                MS-DOS search algorithm:

                        . If no explicit extension is given, the function
                          will search for the file as given. If that one is
                          not found, the function will add .COM and search
                          again. If that's not found, it will add .EXE and
                          search one last time.

                        . If an explicit extension or period is given, the
                          function will search for the file as given.

                The suffixes l,  v, p and e added to  exec... "family name"
                specify that  the named function will  operate with certain
                capabilities.

                        p specifies  that the function will  search for the
                          child in  those directories specified by  the DOS
                          PATH environment variable. If pathname does not
                          contain an explicit directory the function will
                          search first the current directory then in the
                          directory specified by the path. Without the p
                          suffix, the  function only  searches the current
                          working directory.

                        l specifies that the argument pointers (arg0, arg1,
                          ...,  argn)  are  passed  as  separate arguments.
                          Typically, the l suffix is  used when you know in
                          advance the  number of arguments to  be passed. A
                          mandatory  NULL following  argn marks  the end of
                          the list.

                        v specifies  that  the argument  pointers (argv[0],
                          argv[1], ..., argv[n]) are  passed as an array of
                          pointers.  Typically,  the  v  suffix  is  used a
                          variable number of arguments is to be passed.

                        e specifies that the  argument envp maybe passed to
                          the  child  process,  allowing  you  to alter the
                          environment for the child  process. Without the e
                          suffix, child process inherits the environment of
                          the parent process.  This environment argument is
                          an  array of  char *.  Each element  points to  a
                          null-terminated character string of the form:

                                envar=value

                          where  envar  is  the   name  of  an  environment
                          variable, and value is  the string value to which
                          envar is set. The last element of envp[] is NULL.
                          When  envp[0]  is  NULL,  the  child inherits the
                          parent's environment settings.

                The  exec... functions  must at  least one  argument to the
                child process. This  argument is, by convention, a  copy of
                pathname.  Under MS-DOS  3.x, pathname is available for the
                child process; under earlier versions, the child cannot use
                the passed value of arg0 (or argv[0]).

                When  an exec...  function call   is made,  any open  files
                remain open in the child process.

Return value    If  successful, the  exec...  functions  do not  return. On
                error, the exec... functions return -1, and errno is set to
                one of the following:
                        E2BIG   Argument list too long
                        EACCES  Permission denied
                        EMFILE  Too many open files
                        ENOENT  Path or file name not found
                        ENOEXEC Exec format error
                        ENOMEM  Not enough core

*----------------------------------------------------------------------------*/
int execlpe(char *pathP, char *arg0,...)
{
        register char   **p;

        /* Find the end of the argument list */

        for (p = &arg0; *p++ != NULL; );
        return(_LoadProg(_exec, pathP, &arg0, (char **)*p, 1));
}

