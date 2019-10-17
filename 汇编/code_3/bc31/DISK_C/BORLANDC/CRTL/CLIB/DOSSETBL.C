/*---------------------------------------------------------------------------
 * filename - dossetbl.c
 *
 * function(s)
 *        _dos_setblock - modifies the size of a previously allocated
 *                   DOS memory segment (MSC compatible)
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

Name            _dos_setblock - modifies the size of a previously allocated
                           DOS memory segment

Usage           unsigned setblock(unsigned size, unsigned segx,
                        unsigned *maxp);

Prototype in    dos.h

Description     modifies the size of a memory segment.  segx is the
                segment address returned by a previous call to
                _dos_allocmem.  size is the new, requested size in
                paragraphs.  If the request can't be satisfied, the
                maximum possible segment size is stored at *maxp.

Return value    success : 0
                else    : DOS error number, and errno is set to

                        ENOMEM  Insufficient memory

Note            Compatible with Microsoft C.  Not the same as setblock().

*---------------------------------------------------------------------------*/

unsigned _dos_setblock(unsigned size, unsigned segx, unsigned *maxp)
{
    _ES = segx;
    _BX = size;
    _AH = 0x4a;
    geninterrupt(0x21);
    if (_FLAGS & 1)                     /* if carry set, error */
    {
        *maxp = _BX;                    /* return max. block size */
        return (__DOSerror(_AX));       /* set errno */
    }
    else
        return (0);
}
