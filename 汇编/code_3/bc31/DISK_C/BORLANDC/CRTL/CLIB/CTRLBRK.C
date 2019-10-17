/*------------------------------------------------------------------------
 * filename - ctrlbrk.c
 *
 * function(s)
 *        hentry  - hook to call user's control break handler
 *        ctrlbrk - sets control-break handler
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <dos.h>
#include <process.h>

#ifdef __TINY__
#define FARINT(f) ((void interrupt far (*)())MK_FP(_CS,f))
#else
#define FARINT(f) f
#endif

static  int     (*Hfunc)(void);

/*---------------------------------------------------------------------*

Name            hentry - hook to call user's control break handler

Usage           static  void interrupt far hentry();

Prototype in    local to this module

Description     interprets the return value from the ctrl break
                handler

Return value    nothing

*---------------------------------------------------------------------*/

static  void interrupt far hentry()
{
        if      (!(*Hfunc)())
                _exit(0);
}


/*--------------------------------------------------------------------------*

Name            ctrlbrk - sets control-break handler

Usage           void ctrlbrk(int (*fptr)(void));

Prototype in    dos.h

Description     ctrlbrk sets  a new control-break handler  function pointed
                to by fptr.  The interrupt vector 0x23 is  modified to call
                the named function.

                The  named   function  is  not  called   directly.  ctrlbrk
                establishes a  DOS interrupt handler  that calls the  named
                function.

Return value    ctrlbrk returns nothing. The  handler function returns 0 to
                abort the current  program; any other value will  cause the
                program to resume execution.

*---------------------------------------------------------------------------*/
void    ctrlbrk(int (*fptr)())
{
        Hfunc = fptr;

        setvect(0x23, FARINT(hentry));
}
