/*-----------------------------------------------------------------------*
 * filename - setmode.c
 *
 * function(s)
 *        setmode - sets mode of open file
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <io.h>
#include <_io.h>
#include <fcntl.h>
#include <RtlData.h>

/*--------------------------------------------------------------------------*

Name            setmode - sets mode of open file

Usage           int setmode(int handle, int mode);

Prototype in    io.h

Description     setmode  sets the  mode of  the open  file associated  with
                handle  to either  binary or  text. The  argument mode must
                have a value of either O_BINARY or O_TEXT, never both.

Return value    setmode returns 0 if successful; on error it returns -1 and
                sets errno to
                        EINVAL  Invalid argument

*---------------------------------------------------------------------------*/
int _FARFUNC setmode(int fildes, register int mode)
{
        register int newmode;
    _QRTLDataBlock;

    if ((unsigned)fildes >= _QRTLInstanceData(_nfile))
                return(__IOerror (e_badHandle));
        if ((newmode = mode & (O_TEXT | O_BINARY)) == mode &&
                newmode != (int)(O_TEXT | O_BINARY))
            {
            mode = _QRTLInstanceData(_openfd) [fildes];
            _QRTLInstanceData(_openfd) [fildes] =
                (mode & ~(O_TEXT | O_BINARY)) | newmode;
            return((mode & (O_TEXT | O_BINARY)));
            }
        else
            return __IOerror(e_badFunction);
}
