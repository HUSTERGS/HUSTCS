/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     iostctr1.cpp                                             |*/
/*|                                                              |*/
/*|     Class iostream                                           |*/
/*|          iostream::iostream( streambuf * )                   |*/
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

iostream::iostream(streambuf* s) :
        istream(),
        ostream()
{
    ios::init(s);
}


