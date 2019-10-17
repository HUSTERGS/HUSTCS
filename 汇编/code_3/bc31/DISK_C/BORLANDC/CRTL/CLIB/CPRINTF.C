/*------------------------------------------------------------------------
 * filename - cprintf.c
 *
 * function(s)
 *        __cputn - character output function
 *        cprintf - sends formatted output to the console
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <conio.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <dos.h>
#include <_printf.h>
#include <_video.h>
#define BELL            '\a'
#define BACKSPACE       '\b'
#define LINEFEED        '\n'
#define CR              '\r'


/*---------------------------------------------------------------------*

Name            __cputn - character output function

Description     prints a string of n chars on the screen

Return value    returns last character printed

Note            template must match putnF typedef from _printf.h

*------------------------------------------------------------------------*/
#pragma argsused
unsigned pascal near __cputn(const void *s, unsigned n, void *dontCare)
{
        int col, row;
        unsigned char c = 0;
        unsigned int videochar;

        col = _wherex();
        row = _wherey();

  while (n--) {
    switch (c = *(((char*)s)++)) {
    case BELL :
      _AH = V_WR_TTY;
      _AL = BELL;
      _VideoInt();
      break;
    case BACKSPACE :
      if (col > _video.windowx1)
        col--;
      break;
    case CR :
      col = _video.windowx1;
      break;
    case LINEFEED :
      ++row;
      break;
    default :
      if (!_video.graphicsmode && directvideo) {
        _AH = _video.attribute;
        _AL = c;
        videochar = _AX;
        __vram(__vptr(col+1,row+1), &videochar, 1);
      }
      else {
        _DL = col;
        _DH = row;
        _AH = V_SET_CURSOR_POS;
        _BH = 0;
        _VideoInt();
        _BL = _video.attribute;
        _AL = c;
        _AH = V_WR_CHAR_ATTR;
        _BH = 0;
        _CX = 1;
        _VideoInt();
      }
      col++;
      break;
    } /* end switch */

    if (col > _video.windowx2) {    /* line wrap? */
      col = _video.windowx1;
      row += _wscroll;
    }
    if (row > _video.windowy2) { /* screen wrap? */
        __scroll(UP, _video.windowx1, _video.windowy1,
        _video.windowx2, _video.windowy2, 1);
        row--;
    }
  } /* end while */

  _DL = col;
  _DH = row;
  _AH = V_SET_CURSOR_POS;
  _BH = 0;
  _VideoInt();
  return c;
} /* cputn */


/*---------------------------------------------------------------------*

Name            cprintf - sends formatted output to the console

Usage           int cprintf(char *format [,argument, ...]);

Prototype in    conio.h

Description     member of the printf family.  cprintf send its output
                directly to the console.  It does not translate linefeed
                characters into CR/LF combinations.

Return value    success : the number of bytes output.
                error : EOF

*------------------------------------------------------------------------*/
int     cdecl cprintf(const char *fmt, ...)
{
  return  __vprinter (__cputn, 0, fmt, (void _ss *) _va_ptr);
}

