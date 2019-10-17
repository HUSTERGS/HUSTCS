/*-----------------------------------------------------------------------*
 * filename - strcoll.c
 *
 * function(s)
 *        strcoll - compares two strings
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <string.h>

int strcoll( const char *s1, const char *s2 )
  {
  return( strcmp( s1, s2 ) );
  }
