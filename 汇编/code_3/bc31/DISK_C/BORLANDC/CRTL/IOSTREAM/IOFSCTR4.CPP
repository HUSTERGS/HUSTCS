/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     iofsctr4.cpp                                             |*/
/*|                                                              |*/
/*|     Class fstream                                            |*/
/*|          fstream::fstream( int, char *, int )                |*/
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

fstream::fstream(int f, signed char* b, int len) :
        fstreambase(f, b, len),
        iostream()
{
}

fstream::fstream(int f, unsigned char* b, int len) :
        fstreambase(f, (signed char *)b, len),
        iostream()
{
}


