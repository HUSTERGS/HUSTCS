/*-----------------------------------------------------------------------*
 * filename - getswit.c
 *
 * function(s)
 *        getswitchar - gets the MS-DOS switch character
 *        setswitchar - sets the MS-DOS switch character
 * note : these functions are undocumented in the Reference Guide
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <dos.h>

/*---------------------------------------------------------------------*

Name            getswitchar - gets the MS-DOS switch character

Usage           char getswitchar(void);

Prototype in    dos.h

Description     getswitchar returns the current MS-DOS switch character
                value.

Return value    the current MS-DOS switch character value.

*---------------------------------------------------------------------*/
int getswitchar(void)
{
        _AX = 0x3700;
        geninterrupt(0x21);
        return(_DL);
}

/*---------------------------------------------------------------------*

Name            setswitchar - sets the MS-DOS switch character

Usage           void setswitch(char byte);

Prototype in    dos.h

Description     setswitchar set the current MS-DOS switch character
                value to the value of byte.  This call uses the
                undocumented MS-DOS system call 0x37, and works for
                MS-DOS versions 2.0 to 3.0 (Future versions of MS-DOS
                may alter or discontinue this call.)

Return value    Nothing

*---------------------------------------------------------------------*/
void setswitchar(char ch)
{
        _AX = 0x3701;
        _DL = ch;
        geninterrupt(0x21);
}
