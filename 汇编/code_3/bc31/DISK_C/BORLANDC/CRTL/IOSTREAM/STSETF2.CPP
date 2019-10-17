/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     stsetf2.cpp                                              |*/
/*|                                                              |*/
/*|     Class ios                                                |*/
/*|          long ios::setf( long, long )                        |*/
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


long ios::setf(long _setbits, long _field)
{
    long x = x_flags;
    x_flags &= ~_field;
    x_flags |= (_setbits & _field);
    if( x_flags & ios::skipws )
        ispecial |= skipping;
    else
        ispecial &= ~skipping;
    return x;
}


