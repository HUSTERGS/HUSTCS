/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     fsctr3.cpp                                               |*/
/*|                                                              |*/
/*|     Class fstreambase                                        |*/
/*|          fstreambase::fstreambase( int )                     |*/
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

fstreambase::fstreambase(int f)
        : buf(f)
{
    ios::init(&buf);
}


