/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     stbctr1.cpp                                              |*/
/*|                                                              |*/
/*|     Class streambuf                                          |*/
/*|          streambuf::streambuf()                              |*/
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

streambuf::streambuf()
{
    alloc_ = 0;
    unbuf_ = 0;
    base_ = 0;
    pbase_ = 0;
    pptr_ = 0;
    epptr_ = 0;
    gptr_ = 0;
    egptr_ = 0;
    eback_ = 0;
    ebuf_ = 0;
}


