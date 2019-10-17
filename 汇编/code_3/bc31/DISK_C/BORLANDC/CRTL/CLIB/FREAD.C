/*-----------------------------------------------------------------------*
 * filename - fread.c
 *
 * function(s)
 *        fread  - reads data from a stream
 *        _fgetn - reads data from a stream
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
#include <io.h>
#include <asmrules.h>

/*---------------------------------------------------------------------*

Name            _fgetn - reads data from a stream

Usage           static unsigned pascal near
                        _fgetn (register void *ptr, size_t n, FILE *fp);

Prototype in    local to this module

Description     _fgetn reads n bytes of data from the named input stream
                into a block pointed to by ptr.

Return value    success : 0
                else    : non-zero

*---------------------------------------------------------------------*/
static unsigned pascal near _fgetn( register void *ptr, size_t n, FILE *fp )
  {
  register int Byte, Temp;

  while( n )
    {
    n++;

    Temp = min( n, fp->bsize );

    if( (fp->flags & _F_BIN) && fp->bsize && (n > fp->bsize) && (fp->level == 0))
      {
      n--;
      Temp = 0;

      while( n >= fp->bsize )
        {
        Temp += fp->bsize;
        n -= fp->bsize;
        }

      Byte = _read(fp->fd, ptr, Temp);

      (char *) ptr += Byte;

      if( Byte != Temp )
        {
        n += (Temp - Byte);
        fp->flags |= _F_EOF;
        break;
        }
      }
    else
      {
      while (--n  && --Temp && ( Byte = getc (fp)) != EOF )
        {
        *((char *) ptr)++ = Byte;
        }

      if( Byte == EOF )
        {
        fp->flags |= _F_EOF;
        break;
        }
      }
    }

  return n;
  }


/*---------------------------------------------------------------------*

Name            fread - reads data from a stream

Usage           #include <stdio.h>
                size_t fread(void *ptr, size_t size, size_t nitems, FILE *stream);

Related
functions usage size_t fwrite(void *ptr, size_t size, size_t nitems, FILE *stream);

Prototype in    stdio.h

Description     fread reads nitems of data, each of length size
                bytes, from the named input stream into a block pointed to by
                ptr.

                fwrite appends nitems of data, each of length size bytes, to
                the named output stream. The data appended begins at ptr.

                For both functions, the total number of bytes read is (nitems
                * size).

                ptr in the declarations is a pointer to any object.
                size is the size of the object ptr points to. The
                expression sizeof *ptr will produce the proper value.

Return value    On successful completion, each function returns the
                number of items (not bytes) actually read or written. fread
                returns a short count (possibly 0) on end-of-file or error.
                fwrite returns a short count on error.

*---------------------------------------------------------------------*/
size_t _FARFUNC fread( void *ptr, register size_t psize, size_t nitems, FILE *fp )
  {
#if (LDATA)
  register size_t n;
#endif
  unsigned long temp;

  if( !psize )  return( 0 );

  if( (temp = (unsigned long)psize * (unsigned long)nitems) < 0x10000L)
        return( ((unsigned)temp - _fgetn( ptr, (unsigned)temp, fp )) / psize );

#if (!LDATA)
  return 0;
#else
  n = nitems+1;

  while( --n && 0 == _fgetn( ptr, psize, fp ))
    {
    ptr = (void *) (((char huge *) ptr) + psize);
    }

  return( nitems - n );
#endif
  }
