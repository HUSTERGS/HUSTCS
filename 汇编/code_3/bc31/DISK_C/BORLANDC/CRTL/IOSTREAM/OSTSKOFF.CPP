/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     ostskoff.cpp                                             |*/
/*|                                                              |*/
/*|     Class ostream                                            |*/
/*|          ostream& ostream::seekp( streamoff, ios::seek_dir ) |*/
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

// set the put pointer's position
ostream _FAR & ostream::seekp(streamoff off, ios::seek_dir dir)
{
    if( bad()  ||  bp->seekoff(off, dir, ios::out) == EOF )
        setstate(ios::failbit);
    return *this;
}


