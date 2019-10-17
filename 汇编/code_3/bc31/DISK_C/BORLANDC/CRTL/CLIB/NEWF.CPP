/*-----------------------------------------------------------------------*
 * filename - newf.cpp
 * C++ NEW
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

typedef void (*pvf)();

extern pvf _new_handler;

void far * operator new( unsigned long size )
{
    void far * p;
    size = size ? size : 1;
    while ( (p = farmalloc(size)) == NULL && _new_handler != NULL)
        _new_handler();
    return p;
}
