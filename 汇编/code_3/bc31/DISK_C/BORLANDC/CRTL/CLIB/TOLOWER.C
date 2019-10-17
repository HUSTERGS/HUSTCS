/*-----------------------------------------------------------------------*
 * filename - tolower.c
 *
 * function(s)
 *        tolower - translates characters to lower-case
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <ctype.h>

/*---------------------------------------------------------------------*

Name            tolower - translates characters to lower-case

Usage           int tolower(int c);

Prototype in    ctype.h

Description     tolower is a function that converts an integer c (in the range
                EOF to 255) to its lower-case value (if it was upper-case): all
                others are left unchanged.

Return value    returns the converted value of c, on success, and nothing
                on failure.

*---------------------------------------------------------------------*/
#if defined(__FARFUNCS__)
#include <_farfunc.h>
#endif

int _CType tolower( int ch )
  {
  if( ch == -1 )  return( -1 );

  if( isupper( (unsigned char)ch) )
    {
    return( _tolower((unsigned char)ch) );
    }
  else
    {
    return( (unsigned char)ch );
    }
  }
