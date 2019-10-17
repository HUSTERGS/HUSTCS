/*-----------------------------------------------------------------------*
 * filename - delf.cpp
 * C++ DELETE
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1990, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <stddef.h>
#include <alloc.h>
#include <dos.h>

#if defined(__TINY__) || defined(__SMALL__) || defined(__MEDIUM__)
void operator delete( void far *ptr )
{
    if (FP_SEG(ptr) == _DS)
        free((void *) ptr);
    else
        farfree(ptr);
}
#endif
