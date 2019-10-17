/*[]--------------------------------------------------------------[]*/
/*|                                                                |*/
/*|     iostasn1.cpp                                               |*/
/*|                                                                |*/
/*|     Class iostream_withassign                                  |*/
/*|     iostream_withassign& iostream_withassign::operator=( ios& )|*/
/*|                                                                |*/
/*[]--------------------------------------------------------------[]*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1990, 1992 by Borland International
 *      All Rights Reserved.
 *
 */

#include <ioconfig.h>
#include <iostream.h>

// gets buffer from iostream and does entire initialization
iostream_withassign _FAR & iostream_withassign::operator= (ios _FAR & s)
{
    ios::init(s.rdbuf());
    return *this;
}


