/*-----------------------------------------------------------------------*
 * filename - cursor.c
 *
 * function(s)
 *        setcursortype - sets the text cursor type.
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <conio.h>
#include <_video.h>


void _setcursortype( int cur_t )
  {
  struct text_info t;
  int start, end;

  gettextinfo( &t );

  switch( cur_t )
    {
    case _NOCURSOR:
      start = 0x20, end = 0;
      break;
    case _SOLIDCURSOR:
      if( t.screenheight == 43 )  start = 0, end = 8;
      else                        start = 0, end = t.currmode == MONO ? 12 : 7;
      break;
    case _NORMALCURSOR:
      if( t.currmode == MONO )  start = 11, end = 12;
      else                      start = 6,  end = t.screenheight == 43 ? 0 : 7;
    }

  _CH = start;
  _CL = end;
  _AH = 1;
  _VideoInt();
  }
