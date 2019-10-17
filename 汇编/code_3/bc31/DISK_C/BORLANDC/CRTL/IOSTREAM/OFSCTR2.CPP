/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     ofsctr2.cpp                                              |*/
/*|                                                              |*/
/*|     Class ofstream                                           |*/
/*|          ofstream::ofstream( const char *, int, int )        |*/
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

ofstream::ofstream(const signed char* name, int omode, int prot) :
        fstreambase(name, omode | ios::out, prot),
        ostream()
{
}

ofstream::ofstream(const unsigned char* name, int omode, int prot) :
        fstreambase((const signed char *)name, omode | ios::out, prot),
        ostream()
{
}

