/*[]-------------------------------------------------------------------[]*/
/*|                                                                     |*/
/*|     iostasn2.cpp                                                    |*/
/*|                                                                     |*/
/*|     Class iostream_withassign                                       |*/
/*|  iostream_withassign& iostream_withassign::operator= ( streambuf * )|*/
/*|                                                                     |*/
/*[]-------------------------------------------------------------------[]*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1990, 1992 by Borland International
 *      All Rights Reserved.
 *
 */

#include <ioconfig.h>
#include <iostream.h>

// associates streambuf with stream and does entire initialization
iostream_withassign _FAR & iostream_withassign::operator= (streambuf* s)
{
    ios::init(s);
    return *this;
}

