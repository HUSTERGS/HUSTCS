/*---------------------------------------------------------------------------
 * filename - dosalloc.c
 *
 * function(s)
 *        _dos_allocmem - allocates DOS memory segment (MSC compatible)
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

Name            _dos_allocmem - allocates DOS memory segment

Usage           int allocmem(unsigned size, unsigned *seg);

Prototype in    dos.h

Description     uses the MS-DOS system call 0x48 to allocate a block of free
                memory and returns the segment address of the allocated block.

Return value    returns 0 on success.  In the event of an error,
                the size of the largest available block) is stored at *seg,
                errno is set to ENOMEM, and the DOS error code is returned.

Note            Compatible with Microsoft C.  Not the same as allocmem().

*---------------------------------------------------------------------------*/

unsigned _dos_allocmem(unsigned size, unsigned *segp)
{
    _BX = size;
    _AH = 0x48;
    geninterrupt(0x21);
    if (_FLAGS & 1)                     /* if carry set, error */
    {
        *segp = _BX;                    /* return max. block size */
        return (__DOSerror(_AX));       /* set errno */
    }
    else
    {
        *segp = _AX;                    /* return block address */
        return (0);
    }
}
