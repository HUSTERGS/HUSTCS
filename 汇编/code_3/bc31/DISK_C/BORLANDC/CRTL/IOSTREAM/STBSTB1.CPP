/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     stbstb1.cpp                                              |*/
/*|                                                              |*/
/*|     Class streambuf                                          |*/
/*|          streambuf *streambuf::setbuf( char *, int, int )    |*/
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

// obsolete.  included for compatibility with version 1.2 streams

streambuf* streambuf::setbuf(char* p, int len, int offset)
{
    setb(p, p + len, 0);
    setp(p + offset, p + len);
    return this;
}


