/*------------------------------------------------------------------------
 * filename - closeall.c
 *
 * function(s)
 *        fcloseall - close open streams
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

Name            fcloseall - close open streams

Usage           int fcloseall(void);

Prototype in    stdio.h

Description     fcloseall closes all open  streams except stdin and stdout.
                All buffers  associated to each  stream are flushed  before
                closing. System  allocated buffers are freed  upon closing.
                Buffers   assigned   with   setbuf   or   setvbuf  are  not
                automatically freed.

Return value    fcloseall returns the total number of streams it closed or,
                EOF if any errors were detected.

*-------------------------------------------------------------------------*/
int _FARFUNC fcloseall( void )
  {
  FILE *fp;
  int   i, cnt;
  _QRTLDataBlock;

  for( i = 5, fp = _QRTLInstanceData(_streams) + 5, cnt = 0;
       i < _QRTLInstanceData(_nfile); fp++,
       i++ )
    {
    if( fp->fd >= 0 )
      {
      if( fclose( fp ) )  cnt = -9999;
      else                cnt++;
      }
    }

  return( cnt < 0 ? EOF : cnt );
  }
