/*------------------------------------------------------------------------
 * filename - setargv0.c
 *
 * function(s)
 *        _setargv0 - set argv[0] to program name
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1991, 1992 by Borland International
 *      All Rights Reserved.
 *
 */

#include <windows.h>
#include <alloc.h>
#include <_win.h>

#pragma warn -use

#define MAXFNAMELEN 80

extern unsigned _hInstance;

char _FAR *_argv0 = NULL;

static void _setargv0(void)
{
    _argv0 = malloc(MAXFNAMELEN+1);
    if (_argv0 == NULL)
        _errorExitBox("Out of memory in _setargv0", 3);
    GetModuleFileName(_hInstance, _argv0, MAXFNAMELEN);
}

#pragma startup _setargv0 9
