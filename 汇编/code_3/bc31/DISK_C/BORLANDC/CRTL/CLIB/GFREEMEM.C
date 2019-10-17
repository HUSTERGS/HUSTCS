/*-----------------------------------------------------------------------*
 * filename - gfreemem.c
 *
 * function(s)
 *   _graphfreemem - free memory for graphics library
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <graphics.h>
#include <alloc.h>

/*-----------------------------------------------------------------------*

Name            _graphfreemem - free memory for graphics library

Usage           void far _graphfreemem(void far *ptr, unsigned size)

Prototype in    graphics.h

Description     frees memory previously allocated by _graphgetmem.

*------------------------------------------------------------------------*/
#pragma argsused
#pragma warn -sus  /* This will be removed with call to farxxxx() */
void far _graphfreemem(void far *ptr, unsigned size)
{
        free(ptr);
}
#pragma warn .sus

