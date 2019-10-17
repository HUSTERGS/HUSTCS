/*-----------------------------------------------------------------------*
 * filename - fscanf.c
 *
 * function(s)
 *        fscanf - performs formatted input from a stream
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

Name            fscanf - performs formatted input from a stream

Usage           #include <stdio.h>
                int fscanf(FILE *stream, const char *format[, argument,...]);

Prototype in    stdio.h

Description     reads data from the named input stream into the locations
                given by the address arguments

Return value    the number of input fields successfully scanned, converted
                and stored; the return value does not include scanned
                fields that were not stored.

                If an attempt is made to read at end-of-file, the return
                value is EOF.

                If no fields were stored, the return value is 0

*---------------------------------------------------------------------*/
int cdecl _FARFUNC fscanf (FILE *fp, const char *fmt, ...)
  {
  return( _scanner ( (int near (*)(void *))_Nfgetc,
                     (void near (*)(int, void *))_Nungetc,
                     fp,
                     fmt,
                     _va_ptr ) );
  }
