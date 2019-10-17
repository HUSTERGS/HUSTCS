/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     istctr3.cpp                                              |*/
/*|                                                              |*/
/*|     Class istream                                            |*/
/*|          istream::istream( streambuf *, int, ostream * )     |*/
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

// obsolete: set skip via format, tie via tie() function

istream::istream(streambuf* s, int sk, ostream* t)
{
    ios::init(s);
    gcount_ = 0;
    skip(sk);
    tie(t);
}


