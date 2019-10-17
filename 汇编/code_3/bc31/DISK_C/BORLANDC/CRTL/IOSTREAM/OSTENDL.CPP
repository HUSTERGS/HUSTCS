/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     ostendl.cpp                                              |*/
/*|                                                              |*/
/*|     Class ostream                                            |*/
/*|          ostream& endl( ostream& )                           |*/
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

// insert newline and flush

ostream _FAR & endl(ostream _FAR & os)
{
    os << '\n';
    os.flush();
    return os;
}


