/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     srbdalc.cpp                                              |*/
/*|                                                              |*/
/*|     Class strstreambuf                                       |*/
/*|          int strstreambuf::doallocate()                      |*/
/*|                                                              |*/
/*[]------------------------------------------------------------[]*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1990, 1992 by Borland International
 *      All Rights Reserved.
 *
 */

#include <ioconfig.h>
#include <strstrea.h>

int strstreambuf::doallocate()
{
    int size = next_alloc ? next_alloc : MinStrstreamAlloc;
    char *p;
    if( allocf )
        p = (char*)(*allocf)((long)size);
    else
        p = new char[size];
    if( ! p )
        return EOF;

    next_alloc = 0; // assume next_alloc increment is one time only
    setb(p, p + size, 0);
    *p = 0;
    return 1;
}


