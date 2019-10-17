/*------------------------------------------------------------------------
 * filename - fcorelft.c
 *
 * function(s)
 *        farcoreleft - returns measure of unused memory in far heap
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <alloc.h>
#include <_fheap.h>

/*---------------------------------------------------------------------*

Name            farcoreleft - returns measure of unused memory in
                              far heap

Usage           long farcoreleft(void);

Prototype in    alloc.h

Description     returns measure of unused memory in far heap beyond the
                highest allocated block.

Return value    see description.

*---------------------------------------------------------------------*/

/*----------------------------------------------------------------------
  In protected mode we'll do a DosMemAvail, in real mode we'll ask for
  an outrageous amount of memory via INT 21 and look at the BX register
  on return.
----------------------------------------------------------------------*/

unsigned long farcoreleft(void)
  {
  unsigned long value = 0L;
  value = _heaptop - _brklvl;

  if( value > 16 )  value -= 16;

  value &= 0xfffffff0L;
  return( value );
  }
