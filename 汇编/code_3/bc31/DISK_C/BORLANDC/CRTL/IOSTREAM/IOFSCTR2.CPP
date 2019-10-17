/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     iofsctr2.cpp                                             |*/
/*|                                                              |*/
/*|     Class fstream                                            |*/
/*|          fstream::fstream( const char *, int, int )          |*/
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

fstream::fstream(const signed char* name, int omode, int prot) :
        fstreambase(name, omode, prot),
        iostream()
{
}

fstream::fstream(const unsigned char* name, int omode, int prot) :
        fstreambase((const signed char *)name, omode, prot),
        iostream()
{
}

