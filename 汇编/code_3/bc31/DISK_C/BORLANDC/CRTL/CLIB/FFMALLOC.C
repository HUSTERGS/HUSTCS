/*-----------------------------------------------------------------------*
 * filename - ffmalloc.c
 *
 * function(s)
 *        __ffarmalloc  - helper function for _fstrdup
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1991, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <alloc.h>

/*
   Helper function for _fstrdup.  It's a far function that makes a near or
   far call to farmalloc depending on the memory model.
*/

void far * far _ffarmalloc(unsigned long __nbytes)
{
        return farmalloc(__nbytes);
}
