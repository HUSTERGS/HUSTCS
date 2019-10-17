/*-----------------------------------------------------------------------*
 * filename - setbuf.c
 *
 * function(s)
 *        setbuf - assigns buffering to a stream
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <stdio.h>

/*-----------------------------------------------------------------------*

Name            setbuf - assigns buffering to a stream

Usage           #include <stdio.h>
                void setbuf(FILE *stream, char *buf);

Related
functions usage int setvbuf(FILE *stream, char *buf, int type,
                            size_t size);

Prototype in    stdio.h

Description     setbuf and setvbuf cause the buffer buf to be used
                for I/O buffering instead of an automatically allocated buffer.
                They are used after the given stream is opened.

                In setbuf, if buf is NULL, I/O will be unbuffered; otherwise,
                it will be fully buffered. The buffer must be BUFSIZ bytes
                long (specified in stdio.h). In setvbuf, if buf is NULL, a
                buffer will be allocated using malloc; the buffer will use
                size as the amount allocated. The size parameter specifies
                the buffer size and must be greater than zero.

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
void setbuf(FILE *fp, char *buf)
{
        setvbuf (fp, buf, (buf != NULL) ? _IOFBF : _IONBF, BUFSIZ);
}
