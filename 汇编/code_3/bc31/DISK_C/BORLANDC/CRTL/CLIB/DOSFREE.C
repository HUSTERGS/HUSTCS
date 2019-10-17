/*---------------------------------------------------------------------------
 * filename - dosfree.c
 *
 * function(s)
 *        _dos_freemem - frees a previously allocated DOS memory block
 *                       (MSC compatible)
 *--------------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1991, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <dos.h>
#include <_io.h>

/*--------------------------------------------------------------------------*

Name            _dos_freemem - frees a previously allocated DOS memory block

Usage           int _dos_freemem(unsigned seg);

Prototype in    dos.h

Description     frees a memory block allocated by a previous call to
                allocmem.  seg is the segment address of that block.

Return value    success : 0
                else    : DOS error number, and errno is set to

                        ENOMEM  Insufficient memory

Note            Compatible with Microsoft C.  Not the same as freemem().

*---------------------------------------------------------------------------*/


unsigned _dos_freemem(unsigned segx)
{
    _ES = segx;
    _AH = 0x49;
    geninterrupt(0x21);
    if (_FLAGS & 1)                     /* if carry set, error */
        return (__DOSerror(_AX));       /* set errno */
    else
        return (0);
}
