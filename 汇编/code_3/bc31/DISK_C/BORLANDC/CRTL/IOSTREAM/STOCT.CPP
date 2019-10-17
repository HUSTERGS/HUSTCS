/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     stoct.cpp                                                |*/
/*|                                                              |*/
/*|     Class ios                                                |*/
/*|          ios& oct( ios& )                                    |*/
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

ios _FAR & oct(ios _FAR & s)
{
    s.setf(ios::oct, ios::basefield);
    return s;
}


