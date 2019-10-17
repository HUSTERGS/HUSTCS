/*-----------------------------------------------------------------------*
 * filename - fwrite.c
 *
 * function(s)
 *        fwrite  - writes data to a stream
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
#include <asmrules.h>

/*---------------------------------------------------------------------*

Name            fwrite - writes data to a stream

Usage           #include <stdio.h>
                size_t fwrite(void *ptr, size_t size, size_t nitems,
                              FILE *stream);

Related
functions usage size_t fread(void *ptr, size_t size, size_t nitems,
                             FILE *stream);

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
size_t _FARFUNC fwrite( const void *ptr, register size_t psize, size_t nitems, FILE *fp )
  {
#if (LDATA)
  register size_t n;
#endif
  unsigned long temp;

  if( !psize )  return( nitems );

  if( (temp = (unsigned long)psize * (unsigned long)nitems) < 0x10000L )
    {
    return( __fputn( ptr, (unsigned)temp, fp ) / psize );
    }
  else
#if (!LDATA)
    return 0;
#else
    for( n = 0; n < nitems; ++n )
      {
      if( (temp = __fputn( ptr, psize, fp )) != psize )
        return( n );
      else
        ptr = (const void *) (((char huge *) ptr) + psize);
      }
  return( nitems );
#endif
  }

