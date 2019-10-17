/*-----------------------------------------------------------------------*
 * filename - putc.c
 *
 * function(s)
 *      fputc    - puts a character on a stream
 *      _fputc   - puts a character on a stream
 *      fputchar - puts a character to stdout
 *      __fputn  - writes bytes on a stream
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <stdio.h>
#include <_stdio.h>
#include <_io.h>
#include <io.h>
#include <mem.h>
#include <fcntl.h>

/*---------------------------------------------------------------------*

Name            _fputc - puts a character on a stream

Usage           int _fputc(int ch, FILE *stream);

Prototype in    stdio.h

Description     this function is only called by the putc() macro. The
                only purpose for this is to decrement the level
                indicator before calling fputc().

Return value    On success it returns the character ch

                On error, it returns EOF.

*---------------------------------------------------------------------*/


int _FARFUNC _fputc( char ch,  FILE *fp )
  {
  --fp->level;

  return( fputc( ch, fp ) );
  }


/*---------------------------------------------------------------------*

Name            fputc - puts a character on a stream

Usage           #include <stdio.h>
                int fputc(int ch, FILE *stream);

Related
functions usage int fputc(int ch, FILE *stream);
                int fputchar(int ch);
                int putch(int ch);

                int putchar(int ch);
                int putw(int w, FILE *stream);

Prototype in    stdio.h

Description     fputc is like putc but it is a true function that outputs ch to
                the named stream.

Return value    On success putc, fputc, fputchar, and putchar return the
                character ch, while putw returns the word w, and putch returns
                nothing.

                On error, all the functions except putch return EOF.

*---------------------------------------------------------------------*/

int _FARFUNC fputc( int ch,  register FILE *fp )
  {
  static char cr = '\r';
  static unsigned char c;             /*--- SS!=DS ---*/

  c = ch;  /* this assignment *MUST* be done *AFTER* the semaphore lock */

  if( fp->level < -1 )
    {
    ++fp->level;

    *fp->curp++ = c;

    if( (fp->flags & _F_LBUF) && ((c == '\n') || (c == '\r')) )
      {
      if( fflush( fp ) )  return( EOF );
      }

    return( c );
    }

  if( fp->flags & (_F_IN | _F_ERR) || !(fp->flags & _F_WRIT) )
    {
    fp->flags |= _F_ERR;
    return( EOF );
    }

  fp->flags |= _F_OUT;

  if( fp->bsize != 0 )     /* is the stream buffered ? */
    {
    /*  The level is zero only at initialization or after a rewind
        or seek, when _F_OUT is not yet decided and the buffer empty.
    */
    if( fp->level )
      {
      if( fflush( fp ) )  return( EOF );
      }

    fp->level = -fp->bsize;

    *fp->curp++ = c;

    if( (fp->flags & _F_LBUF) && ((c == '\n') || (c == '\r')) )
      {
      if( fflush( fp ) )  return( EOF );
      }

    return( c );
    }
  else                     /* the stream is not buffered */
    {
    if (_openfd[fp->fd] & O_APPEND)
      lseek (fp->fd, 0L, SEEK_END);

    if( (('\n' == c) && ! (fp->flags & _F_BIN) &&
        (_write( fp->fd, & cr, 1 ) != 1) )  ||
        (_write( fp->fd, & c , 1 ) != 1) )
      {
      if( (fp->flags & _F_TERM) == 0 )
        {
        fp->flags |= _F_ERR;
        return( EOF );
        }
      }

    return( c );
    }
  }


/*---------------------------------------------------------------------*

Name            fputchar - puts a character to stdout


Usage           int fputchar (register int c);

Prototype in    stdio.h

Description     fputchar simply calls fputc to output its argument to
                stdout.

Return value    see fgetc.

*---------------------------------------------------------------------*/

int _FARFUNC fputchar( register int c )
  {
  return( fputc( c, stdout ) );
  }


/*---------------------------------------------------------------------*

Name            __fputn - writes bytes on a stream

Usage           size_t  pascal __fputn (const void *ptr, register size_t n, FILE *fp)

Prototype in    stdio.h

Description     __fputn writes n bytes whose address is referenced by ptr to
                an open stream fp.

Return value    The number of bytes written is returned on success;
                zero is returned on failure.

*---------------------------------------------------------------------*/
size_t pascal near __fputn( const void *ptr, size_t n, register FILE *fp )
  {
  int len = n;

  if( fp->flags & _F_LBUF )         /* if it's line buffered, */
    {                               /* handle it in the traditional way */
    while( n-- )
      {
      if( fputc( *((char *)ptr)++, fp ) == EOF )  return( 0 );
      }

    return( len );
    }
  else                              /* yipee, it isn't line buffered */
    {
    if( fp->flags & _F_BIN )        /* binary mode? */
      {

      if( fp->bsize )               /* is it buffered? */
        {
        if( n > fp->bsize )         /* too big to fit in buffer? */
          {
          if( fp->level )
            {
            if( fflush( fp ) )  return( 0 );
            }

          if (_openfd[fp->fd] & O_APPEND)
            lseek (fp->fd, 0L, SEEK_END);
          if( _write( fp->fd, (void *)ptr, n ) != n )  return( 0 );
          else                                return( len );
          }
        else                        /* it is small enough to fit */
          {
          if( fp->level + (int)n >= 0 )  /* must we flush it to make room? */
            {
            if( fp->level == 0 )
              {
              fp->level = -1 - fp->bsize;
              }
            else
              {
              if( fflush( fp ) )  return( 0 );
              }
            }

          /* stuff it into the file buffer all at once! */
          memcpy( fp->curp, ptr, n );
          fp->level += n;
          fp->curp += n;

          return( len );
          }
        }
      else                          /* it is unbuffered */
        {
        /* write it all at once! */
        if (_openfd[fp->fd] & O_APPEND)
          lseek (fp->fd, 0L, SEEK_END);
        if( _write( fp->fd, (void *)ptr, n ) != n )  return( 0 );
        else                                return( len );
        }
      }
    else                            /* oh no, the cursed text mode! */
      {
      if( fp->bsize )               /* is it buffered? */
        {
        while( n-- )
          {
          if( putc( *((char *)ptr)++, fp ) == EOF )  return( 0 );
          }

        return( len );
        }
      else                          /* it is unbuffered */
        {
        /* write it all at once! */
        if( __write( fp->fd, (void *)ptr, n ) != n )  return( 0 );
        else                               return( len );
        }
      }
    }
  }


