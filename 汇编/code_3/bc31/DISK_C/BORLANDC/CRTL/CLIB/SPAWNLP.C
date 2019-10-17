/*-----------------------------------------------------------------------*
 * filename - spawnlp.c
 *
 * function(s)
 *        spawnlp - creates and runs child processes
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
#include <errno.h>
#include <stddef.h>

/*--------------------------------------------------------------------------*

Name            spawnlp - creates and runs child processes

Usage           #include <process.h>
                int spawnlp(int modeF, char *pathP, char *arg0, char *arg1,
                            ..., char *argn, NULL);

Prototype in    process.h

Description     The  functions  in  the  spawn...  family  create  and  run
                (execute) other files, known as child processes. There must
                be  sufficient memory  available for  loading and executing
                the child process.

                The  value  of  modeP  determines  what  action the calling
                function  (the parent  process) will  take after  the spawn
                call. The possible values of modeP are:

                        P_WAIT          Puts parent process "on hold" until
                                        child process completes execution.

                        P_NOWAIT        Continues  to  run  parent  process
                                        while child process runs.

                        P_OVERLAY       Overlays  child  process  in memory
                                        location   formerly   occupied   by
                                        parent. Same as exec... call.

                Note: P_NOWAIT  is currently not  available; using it  will
                generate an error value.

                pathP is  the file name   of the called  child process. The
                spawn... functions  search for pathname using  the standard
                MS-DOS search algorithm:

                        . no  extension or no period-search  for exact file
                          name;  if  not  successful,  add  .EXE and search
                          again

                        . extension given-search only for exact file name

                        . period  given-search only for  file name with  no
                          extension

                The suffixes l, v, p and e added to  spawn... "family name"
                specify that  the named function will  operate with certain
                capabilities.

                        p specifies  that the function will  search for the
                          child in  those directories specified by  the DOS
                          PATH environment variable.  Without the p suffix,
                          the  function only  searches the root and current
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

                The spawn... functions  must have at least one  argument to
                the child process. This argument  is, by convention, a copy
                of pathname.  Under MS-DOS 3.x,  pathname is available  for
                the child process; under earlier versions, the child cannot
                use the passed value of arg0 (or argv[0]).

                When  an spawn...  function call   is made,  any open  files
                remain open in the child process.

Return value    On a  successful execution, the  return value is  the child
                process's exit  status (0 for  normal termination). If  the
                child specifically calls exit with a non-zero argument, its
                exit status can be set to a non-zero value.
                On error, the spawn...  functions return -1, and errno  is set
                to  one of  the following:
                        E2BIG   Argument list too long
                        EINVAL  Invalid argument
                        ENOENT  Path or file name not found
                        ENOEXEC Exec format  error
                        ENOMEM  Not enough core

*---------------------------------------------------------------------------*/
int spawnlp(int modeF, char *pathP, char *arg0, ...)
{
        switch(modeF)
        {
        case P_WAIT :
                return _LoadProg(_spawn, pathP, &arg0, NULL, 1);
        case P_OVERLAY :
                return _LoadProg(_exec, pathP, &arg0, NULL, 1);
        default :
                errno = EINVAL;
                return (-1);
        }
}

