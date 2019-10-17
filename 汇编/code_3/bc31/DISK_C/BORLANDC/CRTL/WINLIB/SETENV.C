/*------------------------------------------------------------------------
 * filename - setenv.c
 *
 * function(s)
 *        _setenv - initializes global RTL environment variables
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */

#include <windows.h>
#include <dos.h>

#pragma warn -use

unsigned _envseg = 0;   /* Environment length               */
unsigned _envLng = 0;   /* Environment segment              */
unsigned _envSize= 0;   /* # of strings in Environment * sizeof(char *) */

/*----------------------------------------------------------------------*

Name            _setenv - Initializes global RTL environment variables.

Usage           Is executed when any reference to these variables causes
                this module to be linked in.

Description     Initializes the global variables _envseg, _envLng,
                and _envSize.

*-----------------------------------------------------------------------*/
static void _setenv(void)
{
    char far *envptr;
    int count;

    envptr = GetDOSEnvironment();

    count = 0;
    while (1)
        {
        _envSize++;
        while(envptr[count++])
            ;
        if (!envptr[count])
            break;
        }
    _envSize*= sizeof(char *);
    _envLng = count+1;   /* length includes both NULL bytes */
    _envseg = FP_SEG(envptr);
}

#pragma startup _setenv 8
