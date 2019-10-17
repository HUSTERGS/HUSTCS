/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     stbalc.cpp                                               |*/
/*|                                                              |*/
/*|     Class streambuf                                          |*/
/*|          int streambuf::doallocate()                         |*/
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
#include <iostream.h>

int streambuf::doallocate()
{
    char *p = new char[StreambufSize];
    if( ! p )
        return EOF;
    base_ = p;
    ebuf_ = p + StreambufSize;
    alloc_ = 1;
    return 1;
}


