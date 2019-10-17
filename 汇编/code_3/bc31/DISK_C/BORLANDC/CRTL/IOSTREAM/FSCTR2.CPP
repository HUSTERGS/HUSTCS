/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     fsctr2.cpp                                               |*/
/*|                                                              |*/
/*|     Class fstreambase                                        |*/
/*|          fstreambase::fstreambase( const char *, int, int )  |*/
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

fstreambase::fstreambase(const char* name, int omode, int prot)
        : buf()
{
    ios::init(&buf);
    open(name, omode, prot);
}


