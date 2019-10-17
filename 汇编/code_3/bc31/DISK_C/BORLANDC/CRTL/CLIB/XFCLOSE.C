/*-----------------------------------------------------------------------*
 * filename - xfclose.c
 *
 * function(s)
 *        _xfclose - closes streams
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

/*---------------------------------------------------------------------*

Name            _xfclose - closes streams

Usage           void _xfclose(void)

Description     called at exit to close open streams

*---------------------------------------------------------------------*/
void _FARFUNC _xfclose( void )
  {
  register FILE *fp;
  register int  i;
  _QRTLDataBlock;

  for( i = 0, fp = _QRTLInstanceData(_streams);
       i < _QRTLInstanceData(_nfile);
       fp++, i++ )
    {
    if( fp->flags & _F_RDWR )
        fclose( fp );
    }
  }
