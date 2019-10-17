/*-----------------------------------------------------------------------*
 * filename - vfscanf.c
 *
 * function(s)
 *        vfscanf - performs formatted input from a stream
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <stdarg.h>
#include <stdio.h>
#include <_stdio.h>
#include <_scanf.h>

#undef   ungetc         /* remove the macro version */

/*---------------------------------------------------------------------*

Name            vfscanf - performs formatted input from a stream

Usage           #include <stdio.h>
                int vfscanf(FILE *stream, char *format, va_list param);

Prototype in    stdio.h

Description     see ...scanf

*---------------------------------------------------------------------*/
int cdecl _FARFUNC vfscanf( FILE *fp, const char *fmt, va_list ap )
  {
  return( _scanner( (int near (*)(void *))_Nfgetc,
                    (void near (*)(int, void *))_Nungetc,
                    fp,
                    fmt,
                    ap ) );
  }
