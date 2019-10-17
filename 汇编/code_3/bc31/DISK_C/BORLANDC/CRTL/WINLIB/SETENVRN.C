/*------------------------------------------------------------------------
 * filename - setenvrn.c
 *
 * function(s)
 *     _setenviron (init proc)
 *
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */

#include <stdlib.h>
#include <string.h>
#include <dos.h>
#include <mem.h>

#pragma warn -use

extern int _envLng;             /* environment length           */
extern int _envseg;             /* environment segment          */
extern int _envSize;    /* # of strings in environment * sizeof(char *) */

extern unsigned _WinAllocFlag;

#define EXTRA   4               /* # of extra envp slots to include*/

char **environ = NULL;

/*----------------------------------------------------------------------*

Name    _setenviron - initializes the global variable environ

Usage   Is executed when any reference to environ causes this module
        to be linked in.

Desc.   Allocates and initializes the global variable environ.

Notes   Must be executed after _setenv init proc so that _envLng, _envseg,
        and _envSize are already setup.

*-----------------------------------------------------------------------*/
static void _setenviron(void)
{
        int     i;
        char    *evBlock;
    unsigned Old_WinAllocFlag = _WinAllocFlag;

        /*
          Get block to hold strings, copy the strings to the local block.
          Get a block to hold the envp array pointers.  We'll get a
          block large enough to hold 4 more pointers than there currently
          are.  This way minor additions can be made to the environment
          without having to realloc the pointer array each time.
          Fill in array of pointers with the addresses of the strings.
          Make _envSize reflect how many slots there are now.
        */

    _WinAllocFlag |= 0x2000;
        if ((evBlock = malloc(_envLng)) == NULL)
                abort();
        movedata(_envseg, 0, FP_SEG((char far *)evBlock),
             FP_OFF((char far *)evBlock), _envLng);
        if ((environ = (char **)calloc((_envSize/sizeof(char *))+EXTRA,
        sizeof(char *))) == NULL)
                abort();
        for (i=0; i<(_envSize/sizeof(char*)); i++, evBlock+=(strlen(evBlock)+1))
                environ[i] = evBlock;
        _envSize += EXTRA*sizeof(char*);
    _WinAllocFlag = Old_WinAllocFlag;
}

#pragma startup _setenviron 9  /* Must be executed after _setenv (8) */
