/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     stsetf1.cpp                                              |*/
/*|                                                              |*/
/*|     Class ios                                                |*/
/*|          long ios::setf( long )                              |*/
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

long ios::setf(long l)
{
    long x = x_flags;

    if (l & ios::adjustfield)       // If padding requested, reset flags
            x_flags &= ~ios::adjustfield;
    if (l & ios::basefield)         // same for base
            x_flags &= ~ios::basefield;
    if (l & ios::floatfield)        // same for float conversion
            x_flags &= ~ios::floatfield;

    x_flags |= l;

    if( x_flags & ios::skipws )
        ispecial |= skipping;
    else
        ispecial &= ~skipping;
    return x;
}


