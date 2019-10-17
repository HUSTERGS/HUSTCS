/*-----------------------------------------------------------------------*
 * filename - write.c
 *
 * function(s)
 *    write - writes to a file
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
#include <stdio.h>

#define  SIZE 128

/*---------------------------------------------------------------------*

Name            write - writes to a file

Usage           int write(int handle, const void *buf, unsigned nbyte);

Related
functions usage int _write(int handle, const void *buf, unsigned nbyte);

Prototype in    io.h

Description     Both write and _write are functions that write a
                buffer of data to the file or device named by the given
                handle.

                handle is a file handle obtained from a creat, open, dup,
                dup2, or fcntl call.

                These functions attempt to write nbyte bytes from the buffer
                pointed to by buf to the file associated with handle. Except
                when write is used to write to a text file, the number of
                bytes written to the file will be no more than the number
                requested.

                On text files, when write sees a linefeed (LF) character, it
                outputs a CR-LF pair. _write does no such translation, since
                all of its files are binary files.

                If the number of bytes actually written is less than that
                requested, the condition should be considered an error and
                probably indicates a full disk.

                For disk or diskette files, writing always proceeds from the
                current file pointer (see lseek). For devices, bytes are
                directly sent to the device.

                For files opened with the O_APPEND option, the file pointer is
                positioned to EOF by write (but not by _write) before writing
                the data.

Return value    The number of bytes written are returned by both
                functions. A write to a text file does not count generated
                carriage returns. In case of error, each function returns -1
                and sets the global variable errno to one of the following:

                    EACCES  Permission denied
                    EBADF   Bad file number

*---------------------------------------------------------------------*/

/* NOTE: This function is named __write for internal library use.
 * The user entry point is in writeu.asm.
 */

#pragma warn -sig
int _CType _FARFUNC __write(int fd, const void *buf, unsigned int len)
{
    register unsigned chunk;
    unsigned    res;
    register char   *tbuf;
    unsigned    remainder;
    char        c;
    const char  *sbuf;
    char        crbuf [1 + SIZE];
    _QRTLDataBlock;

    if ((unsigned)fd >= _QRTLInstanceData(_nfile))
        return __IOerror(e_badHandle);

    if ((len +1) < 2)
        return (0);              /* can't write 0 or 65535 bytes */

    if (_QRTLInstanceData(_openfd)[fd] & O_APPEND)
        lseek (fd, 0L, SEEK_END);

    if ((_QRTLInstanceData(_openfd)[fd] & O_TEXT) == 0)
        return (_write (fd, buf, len));

    _QRTLInstanceData(_openfd)[fd] &= ~_O_EOF;  /* assume we go beyond ^Z EOF   */

    sbuf = buf;
    remainder = len;
    tbuf = crbuf;
    while (remainder)
    {
        remainder--;
        if ((c = *sbuf++) == '\n')
            *tbuf++ = '\r';

        *tbuf++ = c;
        if ((tbuf - crbuf) >= SIZE)
        {
            chunk = tbuf - crbuf;
            if ((res = _write (fd, crbuf, chunk)) != chunk)
                                return( (res == ~0U) ? -1 : (len - remainder + res - chunk));
            tbuf = crbuf;
        }
    }

    if ((chunk = (tbuf - crbuf)) > 0)
        if ((res = _write (fd, crbuf, chunk)) != chunk)
                        return ((res == ~0U) ? -1 : (len + res - chunk));

        return( len );
}

#pragma warn .sig
