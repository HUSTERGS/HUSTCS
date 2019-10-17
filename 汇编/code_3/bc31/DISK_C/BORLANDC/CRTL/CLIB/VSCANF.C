/*-----------------------------------------------------------------------*
 * filename - vscanf.c
 *
 * function(s)
 *        vscanf - performs formatted input from stdin
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

Name            vscanf - performs formatted input from stdin

Usage           int vscanf(const char *format, va_list param);

Prototype in    stdio.h

Description     see ...scanf

*---------------------------------------------------------------------*/
int cdecl _FARFUNC vscanf (const char *fmt, va_list ap)
  {
  return( _scanner( (int near (*)(void *))_Nfgetc,
                    (void near (*)(int, void *))_Nungetc,
                    stdin,
                    fmt,
                    ap ) );
  }
