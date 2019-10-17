/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     stbctr2.cpp                                              |*/
/*|                                                              |*/
/*|     Class streambuf                                          |*/
/*|          streambuf::streambuf( char *, int )                 |*/
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

streambuf::streambuf(char* b, int len)
{
    alloc_ = 0;
    unbuf_ = 0;
    base_ = b;
    ebuf_ = (len > 0) ? b + len : b;
    pbase_ = 0;
    pptr_ = 0;
    epptr_ = 0;
    gptr_ = 0;
    egptr_ = 0;
    eback_ = 0;
}


