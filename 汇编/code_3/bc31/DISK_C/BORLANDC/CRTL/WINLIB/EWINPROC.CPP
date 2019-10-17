/*------------------------------------------------------------------------
 * filename - ewinproc.cpp
 *
 * Startup and exit procedures for EasyWindows
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1991, 1992 by Borland International
 *      All Rights Reserved.
 *
 */

#include <windows.h>

// These are RTL variables

extern unsigned _hInstance;
extern unsigned _hPrev;
extern int      _cmdShow;

// These are dummy ones for linkage purposes

extern unsigned __hInstance;
extern unsigned __hPrev;
extern int      __cmdShow;

void __InitEasyWin(void);
void far __ExitEasyWin(void);
void __CreateEasyWin(void);

// Create CRT window if required

extern "C" void _InitEasyWin(void)
{
    __InitEasyWin();
}


// EasyWin unit exit procedure

static void far ExitEasyWin(void)
{
    __ExitEasyWin();
}

#pragma exit ExitEasyWin 20


static void CreateEasyWin(void)
{
    __hInstance = _hInstance;
    __hPrev = _hPrev;
    __cmdShow = _cmdShow;
    __CreateEasyWin();
}

#pragma startup CreateEasyWin 20
