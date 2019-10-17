/*---------------------------------------------------------------------------
 * filename - dossftim.c
 *
 * function(s)
 *        _dos_setftime - changes file date and time (MSC compatible)
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

Name            _dos_setftime - gets file date and time

Usage           #include <dos.h>
                unsigned _dos_setftime(int handle, unsigned date,
                                        unsigned time);

Related
functions       _dos_getftime

Prototype in    dos.h

Description     _dos_setftime changes the file time and date for the
                disk file associated with the open handle to values in
                time and date.

                Time bits       Meaning
                ---------       -------
                0-4             Number of 2-second increment (0-99)
                5-10            Minutes (0-59)
                11-15           Hours (0-23)

                Date bits       Meaning
                ---------       -------
                0-4             Day (1-31)
                5-8             Month (1-12)
                9-15            Year (1980-2099)


Return value    On success, 0 is returned.

                In the event of an error return, the DOS error code
                is returned and the global variable errno is set to:

                        EBADF           Bad file number

*---------------------------------------------------------------------------*/

unsigned _dos_setftime(int fd, unsigned date, unsigned time)
{
    _AX = 0x5701;
    _BX = fd;
    _CX = time;
    _DX = date;
    geninterrupt(0x21);
    if (_FLAGS & 1)                     /* if carry flag set, error */
        return (__DOSerror(_AX));       /* set errno */
    else
        return (0);
}
