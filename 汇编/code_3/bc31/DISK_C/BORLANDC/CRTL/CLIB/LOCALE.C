/*-----------------------------------------------------------------------*
 * filename - locale.c
 *
 * function(s)
 *        setlocale  - set the locale specific info
 *        localeconv - gets the locale specific info
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <locale.h>
#include <limits.h>
#include <string.h>
#include <stdio.h>

static struct lconv locale =
  {
  ".",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  CHAR_MAX,
  CHAR_MAX,
  CHAR_MAX,
  CHAR_MAX,
  CHAR_MAX,
  CHAR_MAX,
  CHAR_MAX,
  CHAR_MAX
  };

/* At the present time we support only the C locale */
#pragma argsused
char * _FARFUNC setlocale( int category, const char *locale )
  {
  if( locale == NULL )
    {
    return( "C" );
    }
  else
    {
    return( *locale && strcmp( locale, "C" ) ? NULL : (char *) locale );
    }
  }


struct lconv * _FARFUNC localeconv( void )
  {
  return( &locale );
  }

