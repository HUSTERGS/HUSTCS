/*-----------------------------------------------------------------------*
 * filename - vfprintf.c
 *
 * function(s)
 *        vfprintf - sends formatted output to a stream
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <stdio.h>
#include <_printf.h>
#include <_stdio.h>

/*---------------------------------------------------------------------*

Name            vfprintf - sends formatted output to a stream

Usage           #include <stdio.h>
                #include <stdarg.h>
                int vfprintf(FILE *stream, const char *format, va_list param);

Prototype in    stdio.h
                stdarg.h

Description     see printf

*---------------------------------------------------------------------*/
int cdecl _FARFUNC vfprintf( FILE *F, const char *fmt, va_list ap )
  {
  return( __vprinter( (putnF *)__fputn, F, fmt, (void _ss *) ap ) );
  }

