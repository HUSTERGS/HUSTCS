/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     stdec.cpp                                                |*/
/*|                                                              |*/
/*|     Class ios                                                |*/
/*|          ios& dec( ios& )                                    |*/
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

ios _FAR & dec(ios _FAR & s)
{
    s.setf(ios::dec, ios::basefield);
    return s;
}


