/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     ostx.cpp                                                 |*/
/*|                                                              |*/
/*|     Obsolete class ostream constructors                      |*/
/*|          ostream::ostream(int fd)                            |*/
/*|          ostream::ostream(int sz, char* b)                   |*/
/*|                                                              |*/
/*[]------------------------------------------------------------[]*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1990, 1992 by Borland International
 *      All Rights Reserved.
 *
 */

#include <strstrea.h>
#include <fstream.h>


// Obsolete constructor, for streams 1.2 compatibility
ostream::ostream(int fd)
{
    ios::init(new filebuf(fd));
}


// Obsolete constructor, for streams 1.2 compatibility
ostream::ostream(int sz, char* b)
{
    ios::init(new strstreambuf(b, sz, b));
}
