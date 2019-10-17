/*------------------------------------------------------------------------*
 * filename - fflush.c
 *
 * function(s)
 *        fflush - flushes a stream
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <stdio.h>
#include <io.h>
#include <_io.h>

/*------------------------------------------------------------------------*

Name            fflush - flushes a stream

Usage           #include <stdio.h>
                int fflush(FILE *stream);

Prototype in    stdio.h

Description     fflush causes the contents of the buffer associated with
                an open output stream to be written to stream, and clears
                the buffer contents if stream is an open input stream.
                stream remains open.

Return value    success : 0
                failure : EOF

*------------------------------------------------------------------------*/

int _FARFUNC fflush( register FILE *fp )
  {
  register count;

  if( !fp )
    {
    flushall();
    }
  else
    {
    if( fp->token != (short)fp )  return( EOF );      /* validity check */

    if( fp->level >= 0 )                    /* no output data in buffer */
      {
      if( fp->flags & _F_LBUF || fp->curp == &fp->hold )
        {
        fp->level = 0;                          /* ensure no unget char */
        if( fp->curp == &fp->hold )  fp->curp = fp->buffer;
        }

      return( 0 );
      }

    count = fp->bsize + 1 + fp->level;
    fp->level -= count;

    if( (__write( fp->fd, (fp->curp = fp->buffer), count ) != count) &&
      ((fp->flags & _F_TERM) == 0) )
      {
      fp->flags |= _F_ERR;
      return( EOF );
      }
    }

  return( 0 );
  }
