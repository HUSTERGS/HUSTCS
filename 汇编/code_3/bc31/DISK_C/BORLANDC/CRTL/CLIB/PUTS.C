/*-----------------------------------------------------------------------*
 * filename - puts.c
 *
 * function(s)
 *        puts - puts a string on a stream
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <stdio.h>
#include <string.h>
#include <_stdio.h>

/*---------------------------------------------------------------------*

Name            puts - outputs a string to stdout

Usage           int puts(const char *string);

Prototype in    stdio.h

Description     puts copies the null-terminated string string to the
                standard output stream stdout and appends a newline character.

Return value    On successful completion, puts returns the
                last character written. Otherwise, a value of EOF is
                returned.

*---------------------------------------------------------------------*/
int _FARFUNC puts( const register char *s )
  {
  int len;

  if (s == NULL)
    return (0);

  len = strlen( s );

  if( __fputn( s, len, stdout) != len )  return( EOF );

  return( ((fputc ('\n', stdout) != '\n')  ? EOF : '\n') );
  }
