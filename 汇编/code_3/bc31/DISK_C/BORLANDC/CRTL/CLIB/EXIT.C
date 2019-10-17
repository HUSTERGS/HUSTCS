/*------------------------------------------------------------------------
 * filename - exit.c
 *
 * function(s)
 *      ___exit - handle the four flavors of exit
 *      exit    - terminate program
 *      _exit   - quick termination
 *      _cexit  - perform exit cleanup without termination
 *      _c_exit - perform quick exit cleanup without termination
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <stdlib.h>

extern  int             _atexitcnt;    /* count of atexit function pointers */
extern  atexit_t        _atexittbl[];  /* array of atexit function pointers */

void _terminate( int );                 /* terminate program */
void _cleanup( void );                  /* call #pragma exit routines */
void _checknull( void );                /* check for null pointer usage */
void _restorezero( void );              /* restore interrupt vectors */

static  void    dummy(void)
{
}

void    (*_exitbuf)(void)   = dummy;
void    (*_exitfopen)(void) = dummy;
void    (*_exitopen)(void)  = dummy;

/*---------------------------------------------------------------------------*

Name            ___exit - perform cleanup and optionally terminate the program

Usage           void ___exit(int quick, int dontexit, int errcode);

Prototype in    local

Description     ___exit is an internal routine used by the various flavors
                of exit.  If the "quick" flag is false, buffered output
                (waiting to be output) is written to files, any registered
                "exit functions"  (posted with atexit) are called, and
                #pragma exit functions are called.

                In all cases, interrupt vectors taken by the RTL are
                restored, and in small and medium models, stray NULL pointers
                are checked for by seeing if the copyright message
                got zapped.

                Finally, if the "dontexit" flag is false, all files
                are closed, and the program is terminated with the
                error code "errcode".

Return value    If dontexit is false, ___exit never returns; otherwise
                it returns no value.

*----------------------------------------------------------------------------*/
static void pascal near ___exit(int quick, int dontexit, int errcode)
{
    if (!quick)
    {
        /* Execute "atexit" functions
         */
        while (_atexitcnt)
            (*_atexittbl[--_atexitcnt])();

        /* Run #pragma exit routines
         */
        _cleanup();

        /* Flush files.
         */
        (*_exitbuf)();
    }


    /* Restore interrupt vectors.
     */
    _restorezero();

    /* Check for stray NULL pointers zapping the copyright message.
     */
    _checknull();

    if (!dontexit)
    {
        if (!quick)
        {
            (*_exitfopen)();    /* close stream files */
            (*_exitopen)();     /* close handle files */
        }
        _terminate(errcode);    /* terminate program */
    }
}

/*---------------------------------------------------------------------------*

Name            exit - terminates program

Usage           void exit(int status);

Prototype in    process.h and stdlib.h

Related
functions usage void _exit(int status);
                void _cexit(void);
                void _c_exit(void);

Description     exit  terminates the  calling process.  Before exiting, all
                files are closed, buffered output (waiting to be output) is
                written, interrupt vectors taken by the startup code are
                restored, and  any registered "exit functions"  (posted with
                atexit) are called.

                status is provided for the  calling process as the the exit
                status of  the process. Typically a  value of 0 is  used to
                indicate a normal exit, and a non-zero value indicates some
                error.

                _exit is "quick" version of exit.  It does everything
                that exit does, except that it doesn't flush files or
                call atexit or #pragma exit routines.

                _cexit is a non-terminating version of exit().  It does
                everything that exit does, except that it doesn't
                close files or terminate the program.

                _c_exit is a non-terminating version of _exit().  It
                restores interrupt vectors taken by the startup code, but
                does no other cleanup and does not terminate the program.

Return value    exit and _exit never return.  _cexit and _c_exit do
                not return a value.

*----------------------------------------------------------------------------*/
void    exit(int c)
{
    ___exit(0,0,c);
}

void    _exit(int c)
{
    ___exit(1,0,c);
}

void    _cexit(void)
{
    ___exit(0,1,0);
}

void    _c_exit(void)
{
    ___exit(1,1,0);
}
