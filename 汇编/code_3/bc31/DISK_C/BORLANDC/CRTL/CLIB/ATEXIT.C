/*------------------------------------------------------------------------
 * filename - atexit.c
 *
 * function(s)
 *        atexit - registers termination function
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <stdlib.h>

#define MAX_ATEXIT      32

int             _atexitcnt = 0;         /* count of atexit functions */
atexit_t        _atexittbl[MAX_ATEXIT]; /* array of atexit function pointers */


/*-------------------------------------------------------------------------*

Name            atexit - registers termination function

Usage           #include <stdlib.h>
                int atexit(atexit_t func);

Prototype in    stdlib.h

Description     atexit registers provided to by func as an "exit function".
                Upon normal  termination of the  program, exit calls  *func
                (without  args)  just  before  returning  to  the operating
                system.

                Each call to atexit registers  another exit function; up to
                32  functions can  be registered  and they  are executed on
                last in, first out basis.

Return value    atexit returns 0 on success and non-zero on failure(no space
                left to register the function)

*---------------------------------------------------------------------------*/
int atexit(atexit_t func)
{
        if (_atexitcnt == MAX_ATEXIT)
                return(1);
        _atexittbl[_atexitcnt++] = func;
        return(0);
}

