/*---------------------------------------------------------------------------
 * filename - dosgdriv.c
 *
 * function(s)
 *        _dos_getdrive - gets current drive (MSC compatible)
 *        _dos_setdrive - sets current drive (MSC compatible)
 *--------------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1991, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <dos.h>

/*--------------------------------------------------------------------------*

Name            _dos_getdrive - gets current drive

Usage           void _dos_getdrive(unsigned *drive);

Prototype in    dos.h

Description     gets the current drive, stores it at *drive (1=A, 2=B, etc.)

Return value    None.

*---------------------------------------------------------------------------*/
void _dos_getdrive(unsigned *drive)
{
    _AH = 0x19;
    geninterrupt(0x21);
    *drive = _AL + 1;   /* convert (A=0,B=1,etc.) to (A=1,B=2,etc.) */
}

/*--------------------------------------------------------------------------*

Name            _dos_setdrive - sets current drive

Usage           void _dos_setdrive(unsigned drive, unsigned *ndrives);

Prototype in    dir.h

Description     sets the current drive, where drive is:
                1 = A:, 2 = B:, 3 = C:; etc.  Stores the total
                number of drives in the system at *ndrives.

Return value    none

*---------------------------------------------------------------------------*/
void _dos_setdrive(unsigned drive, unsigned *ndrives)
{
    _DL = drive - 1;    /* convert (A=1,B=2,etc.) to (A=0,B=1,etc.) */
    _AH = 0x0e;
    geninterrupt(0x21);
    *ndrives = _AL;
}
