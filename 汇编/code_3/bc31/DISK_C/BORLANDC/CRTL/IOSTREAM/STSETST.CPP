/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     stsetst.cpp                                              |*/
/*|                                                              |*/
/*|     Class ios                                                |*/
/*|          void ios::setstate( int )                           |*/
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

void ios::setstate(int b)
{
    state |= (b & 0xFF);
    ispecial |= (b & ~(skipping | tied));
    ospecial |= (b & ~tied);
}


