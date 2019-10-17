/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     stbdnxtc.cpp                                             |*/
/*|                                                              |*/
/*|     Class streambuf                                          |*/
/*|          int streambuf::do_snextc()                          |*/
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

// called when snextc doesn't have an available character

int streambuf::do_snextc()
{
    return (underflow() == EOF) ? EOF : (unsigned char) *gptr_;
}


