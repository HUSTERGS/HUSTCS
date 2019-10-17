/*---------------------------------------------------------------------------
 * filename - doslock.c
 *
 * function(s)
 *        _dos_lock   - sets file sharing locks
 *        _dos_unlock - resets file sharing locks
 *--------------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1991, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <_io.h>
#include <dos.h>

/*-----------------------------------------------------------------------*

Name            _dos_lock - sets file sharing locks

Usage           unsigned _dos_lock(int handle, long offset, long length);

Related
functions usage unsigned _dos_unlock(int handle, long offset, long length);

Prototype in    none

Description     _dos_lock and _dos_unlock provide an interface to the MS-DOS
                3.x file-sharing mechanism.

                lock can be placed on arbitrary, non-overlapping regions of
                any file. A program attempting to read or write into a
                locked region will retry the operation three times. If all
                three retries fail, the call fails with an error.

                _dos_unlock removes lock; to avoid error, lock must be removed
                before a file is closed. A program must release all lock(s)
                before completing.

Return value    Both functions return 0 on success.  Otherwise, they return
                the DOS error code and set errno as follows:

                EBADF           Invalid file handle
                EACCESS         Locking violation (file already locked
                                or unlocked)

Portability     Unique to MS-DOS 3.x. Older versions of MS-DOS do
                not support these calls.

*------------------------------------------------------------------------*/

unsigned _dos_lock(int handle, long offset, long length)
{
    _BX = handle;
    _CX = FP_SEG(offset);
    _DX = FP_OFF(offset);
    _SI = FP_SEG(length);
    _DI = FP_OFF(length);
    _AX = 0x5c00;
    geninterrupt(0x21);
    if (_FLAGS & 1)                     /* if carry set, error */
        return (__DOSerror(_AX));       /* set errno */
    else
        return (0);
}


/*-----------------------------------------------------------------------*

Name            _dos_unlock - resets file sharing locks

Usage           int _dos_unlock(int handle, long offset, long length);

Related
functions usage unsigned _dos_lock(int handle, long offset, long length);

Prototype in    none

Description     see _dos_lock above

Return value    see _dos_lock above

*------------------------------------------------------------------------*/
unsigned _dos_unlock(int handle, long offset, long length)
{
    _BX = handle;
    _CX = FP_SEG(offset);
    _DX = FP_OFF(offset);
    _SI = FP_SEG(length);
    _DI = FP_OFF(length);
    _AX = 0x5c01;
    geninterrupt(0x21);
    if (_FLAGS & 1)                     /* if carry set, error */
        return (__DOSerror(_AX));       /* set errno */
    else
        return (0);
}
