/*-----------------------------------------------------------------------*
 * filename - doskeep.c
 *
 * function(s)
 *        _dos_keep - exits and remains resident
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1991, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <dos.h>
#include <process.h>

/*---------------------------------------------------------------------*

Name            _dos_keep - exits and remains resident

Usage           void _dos_keep(unsigned status, unsigned size);

Prototype in    dos.h

Description     _dos_keep returns to MS-DOS with the exit status in
                status. The current program remains resident, however. The
                program is set to size paragraphs in length, and the
                remainder of the memory of the program is freed.

                _dos_keep does the same cleanup as _cexit.  It flushes
                files, calls atexit and #pragma exit routines, and
                restores interrupt vectors taken by the library.
                It does not close files; the caller must explicitly
                close any open files, if necessary.

                _dos_keep can be used when installing a TSR program.
                _dos_keep uses DOS function 0x31.

Return value    None

*---------------------------------------------------------------------*/
void _dos_keep(unsigned char status, unsigned size)
{
        _cexit();
        _DX = size;
        _AL = status;
        _AH = 0x31;
        geninterrupt(0x21);
}
