/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     ostends.cpp                                              |*/
/*|                                                              |*/
/*|     Class ostream                                            |*/
/*|          ostream& ends( ostream& )                           |*/
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

// insert null to terminate string

ostream _FAR & ends(ostream _FAR & os)
{
    os << char(0);
    return os;
}


