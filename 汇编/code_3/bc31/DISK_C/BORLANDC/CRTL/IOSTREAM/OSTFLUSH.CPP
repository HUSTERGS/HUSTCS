/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     ostflush.cpp                                             |*/
/*|                                                              |*/
/*|     Class ostream                                            |*/
/*|          ostream& ostream::flush()                           |*/
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

ostream _FAR & ostream::flush()
{
    if( bp->sync() == EOF )
        setstate(ios::badbit);
    return *this;
}
