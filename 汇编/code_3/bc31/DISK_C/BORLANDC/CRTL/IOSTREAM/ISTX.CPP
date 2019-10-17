/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     filename - istx.cpp                                      |*/
/*|                                                              |*/
/*|     Obsolete class istream constructors                      |*/
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
#include <strstrea.h>
#include <fstream.h>


// Obsolete constructor, for streams 1.2 compatibility
#pragma warn -par
istream::istream(int sz, char* b, int sk)
{
    ios::init(new strstreambuf(b, 0, 0));
    skip(sk);
}
#pragma warn .par


// Obsolete constructor, for streams 1.2 compatibility
istream::istream(int fd, int sk, ostream* t)
{
    ios::init(new filebuf(fd));
    skip(sk);
    tie(t);
}
