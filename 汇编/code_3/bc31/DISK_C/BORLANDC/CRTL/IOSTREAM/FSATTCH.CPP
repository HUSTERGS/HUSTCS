/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     fsattch.cpp                                              |*/
/*|                                                              |*/
/*|     Class fstreambase                                        |*/
/*|          void fstreambase::attach( int )                     |*/
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

void fstreambase::attach(int f)
{
    if( buf.is_open() )
        setstate(ios::failbit);
    else if( buf.attach(f) )
        clear(ios::goodbit);
    else
        clear(ios::badbit);
}


