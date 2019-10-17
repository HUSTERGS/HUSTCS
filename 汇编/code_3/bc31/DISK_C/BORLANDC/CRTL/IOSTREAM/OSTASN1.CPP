/*[]-----------------------------------------------------------------[]*/
/*|                                                                   |*/
/*|     ostasn1.cpp                                                   |*/
/*|                                                                   |*/
/*|     Class ostream_withassign                                      |*/
/*|     ostream_withassign& ostream_withassign::operator= ( ostream& )|*/
/*|                                                                   |*/
/*[]-----------------------------------------------------------------[]*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1990, 1992 by Borland International
 *      All Rights Reserved.
 *
 */

#include <ioconfig.h>
#include <iostream.h>

// gets buffer from ostream and does entire initialization

ostream_withassign _FAR & ostream_withassign::operator= (ostream _FAR & os)
{
    ios::init(os.rdbuf());
    return *this;
}


