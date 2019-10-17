/*-----------------------------------------------------------------------*
 * filename - scanf.c
 *
 * function(s)
 *        scanf - gets formatted input from stdin
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

Name            scanf - gets formatted input from stdin

Usage           int scanf(const char *format[, argument ...])

Prototype in    stdio.h

Description     gets formatted input from stdin

Return value    number of fields scanned and stored.  scanf returns EOF
                if an attempt is made to read at end-of-file

*---------------------------------------------------------------------*/
int cdecl _FARFUNC scanf(const char *fmt, ...)
  {
  return( _scanner( (int near (*)(void *))_Nfgetc,
                    (void near (*)(int, void *))_Nungetc,
                    stdin,
                    fmt,
                   _va_ptr ) );
  }
