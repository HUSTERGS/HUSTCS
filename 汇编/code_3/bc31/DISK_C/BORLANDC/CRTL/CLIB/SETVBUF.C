/*-----------------------------------------------------------------------*
 * filename - setvbuf.c
 *
 * function(s)
 *        setvbuf - assigns buffering to a stream
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <stdio.h>
#include <stdlib.h>

extern  void    (*_exitbuf)();
extern  void      _xfflush();

static int _stdinStarted  = 0;
static int _stdoutStarted = 0;

/*-----------------------------------------------------------------------*

Name            setvbuf - assigns buffering to a stream

Usage           #include <stdio.h>
                int setvbuf(FILE *stream, char *buf, int type,
                            size_t size);

Prototype in    stdio.h

Description     setbuf and setvbuf cause the buffer buf to be used
                for I/O buffering instead of an automatically allocated buffer.
                They are used after the given stream is opened.

                In setbuf, if buf is NULL, I/O will be unbuffered; otherwise,
                it will be fully buffered. The buffer must be BUFSIZ bytes long
                (specified in stdio.h). In setvbuf, if buf is NULL, a buffer
                will be allocated using malloc; the buffer will use size as the
                amount allocated. The size parameter specifies the buffer size
                and must be greater than zero.

                stdin and stdout are unbuffered if they are not redirected;
                otherwise, they are fully buffered. setbuf may be used to
                change the buffering style being used.

                Unbuffered means that characters written to a stream are
                immediately output to the file or device, while buffered
                means that the characters are accumulated and written as
                a block.

                In setvbuf, the type parameter is one of the following:

                        _IOFBF  The file is fully buffered. When a buffer
                                is empty, the next input operation will
                                attempt to fill the entire buffer.

                                On output the buffer will be completely
                                filled before any data is written to the file.

                        _IOLBF  The file is line buffered. When a buffer
                                is empty, the next input operation will still
                                attempt to fill the entire buffer. On output,
                                however, the buffer will be flushed whenever
                                a newline character is written to the file.

                        _IONBF  The file is unbuffered. The buf and size
                                parameters are ignored. Each input operation
                                will read directly from the file, and each
                                output operation will immediately write the
                                data to the file.

                setbuf will produce unpredictable results if it is called for a
                stream, except immediately after opening the stream or any call
                to fseek. Calling setbuf after a stream has been unbuffered is
                legal and will not cause problems.

                A common cause for error is to allocate the buffer as an
                automatic (local) variable and then fail to close the file
                before returning from the function where the buffer was
                declared.

Return value    setbuf returns nothing.

                setvbuf returns 0 on success. It returns non-zero if an
                invalid value is given for type or size, if buf is NULL,
                or if there is not enough space to allocate a buffer.

                setvbuf returns 0 on success.

*-----------------------------------------------------------------------*/
int _FARFUNC setvbuf(register FILE *fp, char *buf, int type, size_t size)
{
    if (fp->token != (short) fp || _IONBF < type || 0x7fff < size)
                return(EOF);

    if (! _stdoutStarted  && ((short) fp == (short) stdout))
        _stdoutStarted = 1;
    else
        if (! _stdinStarted  && ((short) fp == (short) stdin))
        _stdinStarted = 1;

/*  Ensure the change in buffering causes no loss of characters.
    fseek() will fflush and reposition safely.
*/
    if (fp->level)
        fseek (fp, 0L, SEEK_CUR);

    if (fp->flags & _F_BUF)
        free (fp->buffer);

    fp->flags &= ~(_F_BUF | _F_LBUF);
    fp->bsize = 0;
    fp->curp = fp->buffer = & fp->hold;

    if (_IONBF != type && size > 0)
    {
        _exitbuf = _xfflush;

        if (NULL == buf)
        {
            if ((buf = malloc (size)) != NULL)
                fp->flags |= _F_BUF;
            else
                                return(EOF);
        }
                fp->buffer = fp->curp = (unsigned char *)buf;
        fp->bsize = size;
        if (_IOLBF == type)
            fp->flags |= _F_LBUF;
    }

        return 0;

}
