/*-----------------------------------------------------------------------*
 * filename - dosseek.c
 *
 * function(s)
 *        _dos_seek - moves read/write file pointer
 *-----------------------------------------------------------------------*/

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

Name            _dos_seek - moves read/write file pointer

Usage           #include <io.h>
                unsigned _dos_seek(int handle, long offset, int fromwhere,
                                   long *newoffset);

Prototype in    none

Description     _dos_seek sets the file pointer associated with handle
                to a new position that is offset bytes beyond the file
                location given by fromwhere. fromwhere must be one of the
                values 0, 1 or 2, which represent three symbolic constants
                (defined in stdio.h and io.h) as follows:

                fromwhere       File Location
                SEEK_SET (0)    file beginning
                SEEK_CUR (1)    current file pointer position
                SEEK_END (2)    end-of-file

                The new file position, measured in bytes from the start
                of the file, is stored at *newoffset if the seek is
                successful.

Return value    On success, _dos_seek returns 0.  Otherwise, it returns
                the DOS error code, and errno is set to one of the following:

                        EBADF   Bad file number
                        EINVAL  Invalid argument

                On devices incapable of seeking (such as terminals and
                printers), the return value is undefined.

*------------------------------------------------------------------------*/
unsigned _dos_seek(int fd, long offset, int kind, long *newoffset)
{
    _BX = fd;
    _CX = FP_SEG(offset);
    _DX = FP_OFF(offset);
    _AH = 0x42;
    _AL = kind;
    geninterrupt(0x21);
    if (_FLAGS & 1)                     /* if carry set, error */
        return (__DOSerror(_AX));       /* set errno */
    else
    {
        *newoffset = (long)((void _seg *)(_DX) + (void near *)(_AX));
        return (0);
    }
}
