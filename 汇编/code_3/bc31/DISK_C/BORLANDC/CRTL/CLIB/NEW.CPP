/*-----------------------------------------------------------------------*
 * filename - new.cpp
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
#include <stdlib.h>

typedef void (* pvf)();

pvf _new_handler;

pvf set_new_handler(pvf p)
{
    pvf t = _new_handler;
    _new_handler = p;
    return t;
}

void *operator new( size_t size )
{
    void * p;
        size = size ? size : 1;
    while ( (p = malloc(size)) == NULL && _new_handler != NULL)
        _new_handler();
    return p;
}
