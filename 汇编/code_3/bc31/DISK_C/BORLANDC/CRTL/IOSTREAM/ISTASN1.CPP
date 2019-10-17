/*[]-----------------------------------------------------------------[]*/
/*|                                                                   |*/
/*|     istasn1.cpp                                                   |*/
/*|                                                                   |*/
/*|     Class istream_withassign                                      |*/
/*|     istream_withassign& istream_withassign::operator= ( istream& )|*/
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

// gets buffer from istream and does entire initialization

istream_withassign _FAR & istream_withassign::operator= (istream _FAR & is)
{
    ios::init(is.rdbuf());
    return *this;
}


