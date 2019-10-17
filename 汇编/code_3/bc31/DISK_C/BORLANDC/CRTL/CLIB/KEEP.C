/*-----------------------------------------------------------------------*
 * filename - keep.c
 *
 * function(s)
 *        keep - exits and remains resident
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <dos.h>

extern void _restorezero(void);

/*---------------------------------------------------------------------*

Name            keep - exits and remains resident

Usage           void keep(unsigned char status, unsigned size);

Prototype in    dos.h

Description     keep returns to MS-DOS with the exit status in
                status. The current program remains resident, however. The
                program is set to size paragraphs in length, and the
                remainder of the memory of the program is freed.

                keep can be used when installing a TSR program. keep uses DOS
                function 0x31.

Return value    None

*---------------------------------------------------------------------*/
void keep(unsigned char status, unsigned size)
{
        _restorezero();
        _DX = size;
        _AL = status;
        _AH = 0x31;
        geninterrupt(0x21);
}
