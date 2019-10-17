/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     ofsctr4.cpp                                              |*/
/*|                                                              |*/
/*|     Class ofstream                                           |*/
/*|          ofstream::ofstream( int, char *, int )              |*/
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

ofstream::ofstream(int f, signed char* b, int len) :
        fstreambase(f, b, len),
        ostream()
{
}

ofstream::ofstream(int f, unsigned char* b, int len) :
        fstreambase(f, (signed char*)b, len),
        ostream()
{
}

