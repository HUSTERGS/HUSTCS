/*-----------------------------------------------------------------------*
 * filename - putch.c
 *
 * function(s)
 *        putch - puts character on console
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <conio.h>
#include <_video.h>

/*---------------------------------------------------------------------*

Name            putch - puts character on console

Usage           int putch(int ch);

Prototype in    conio.h

Description     putch outputs the character ch to the console.

Return value    putch returns the character printed.

*---------------------------------------------------------------------*/

int putch(int c)
{
        return __cputn((char*)&c,1,0);
}

