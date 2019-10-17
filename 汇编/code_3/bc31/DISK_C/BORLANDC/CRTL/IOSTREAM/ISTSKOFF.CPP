/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     filename - istskoff.cpp                                  |*/
/*|                                                              |*/
/*|     Class istream                                            |*/
/*|          istream& istream::seekg( streamoff, ios::seek_dir ) |*/
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

istream _FAR & istream::seekg(streamoff off, ios::seek_dir dir)
{
    if( bad()  ||  bp->seekoff(off, dir, ios::in) == EOF )
        setstate(ios::failbit);
    return *this;
}


