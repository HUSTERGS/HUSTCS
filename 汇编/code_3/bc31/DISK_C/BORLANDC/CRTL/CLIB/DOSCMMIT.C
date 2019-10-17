/*---------------------------------------------------------------------------
 * filename - doscommit.c
 *
 * function(s)
 *        _dos_commit - commit a file handle
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

/*--------------------------------------------------------------------------*

Name            _dos_commit - commit a file handle

Usage           unsigned _dos_commit(int handle);

Prototype in    io.h

Description     _dos_commit commits the  file handle indicated by handle which is
                obtained  from a  _dos_creat, _dos_creatnew, or _dos_open call.

Return value    Upon successful completion, _dos_commit returns 0.
                Otherwise, the DOS error code is returned, and errno is set to
                        EBADF   Bad file number

*---------------------------------------------------------------------------*/
unsigned _dos_commit( int fd )
{
    _AH = 0x68;
    _BX = fd;
    geninterrupt(0x21);
    if (_FLAGS & 1)                     /* if carry set, error */
        return (__DOSerror(_AX));       /* set errno */
    else
        return (0);
}
