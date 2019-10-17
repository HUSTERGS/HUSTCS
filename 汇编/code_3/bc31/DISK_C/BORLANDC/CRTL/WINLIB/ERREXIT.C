/*------------------------------------------------------------------------
 * filename - errexit.c
 *
 * function(s)
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */

#if !defined( __STDLIB_H )
#include <stdlib.h>
#endif  // __STDLIB_H

#if !defined( ___WIN_H )
#include <_win.h>
#endif  // ___WIN_H

#if !defined( __WINDOWS_H )
#include <windows.h>
#endif  // __WINDOWS_H

#if !defined( __STRING_H )
#include <string.h>
#endif  // __STRING_H

extern char *_Cdecl _argv0;
extern HWND _hInstance;

void _errorBox(char *msg)
{
    char _FAR *progName = strrchr(_argv0, '\\');
    if (progName == NULL)
        progName = _argv0;
    else
        progName++;     // skip backslash in front of name

    MessageBox(GetDesktopWindow(), msg, progName,
                MB_ICONHAND | MB_SYSTEMMODAL);
}

void _errorExitBox(char *msg, int code)
{
    _errorBox(msg);
    _exit(code);
}
