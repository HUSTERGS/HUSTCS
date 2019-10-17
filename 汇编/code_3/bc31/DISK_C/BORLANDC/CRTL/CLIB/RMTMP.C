/*------------------------------------------------------------------------
 * filename - rmtmp.c
 *
 * function(s)
 *        rmtmp - close and delete open temporary file streams
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <stdio.h>
#include <RtlData.h>

/*------------------------------------------------------------------------*

Name            rmtmp - close and delete open temporary streams

Usage           int rmtmp(void);

Prototype in    stdio.h

Description     rmtmp closes and deletes all open temporary file streams,
                which were previously created with tmpfil().  The current
                directory must the same as when the files were created, or
                the files will not be deleted.

Return value    rmtmp returns the total number of temporary files
                it closed and deleted.

*-------------------------------------------------------------------------*/
int rmtmp( void )
  {
  FILE *fp;
  int   i, cnt;
  _QRTLDataBlock;

  for( i = 5, fp = _QRTLInstanceData(_streams) + 5, cnt = 0;
       i < _QRTLInstanceData(_nfile);
       fp++, i++
     )
    {
    if( fp->istemp != 0 )
      {
      if( fclose( fp ) == 0 )  cnt++;
      }
    }

  return( cnt );
  }
