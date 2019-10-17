/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     ifsctr4.cpp                                              |*/
/*|                                                              |*/
/*|     Class ifstream                                           |*/
/*|          ifstream::ifstream( int, char *, int )              |*/
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
#include "filesys.h"
#include <fstream.h>

ifstream::ifstream(int f, signed char* b, int len) :
        fstreambase(f, b, len),
        istream()
{
}

ifstream::ifstream(int f, unsigned char* b, int len) :
        fstreambase(f, (signed char *)b, len),
        istream()
{
}

