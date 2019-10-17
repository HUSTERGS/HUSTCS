/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     fsopen.cpp                                               |*/
/*|                                                              |*/
/*|     Class fstreambase                                        |*/
/*|          void fstreambase::open( const char *, int, int )    |*/
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

void fstreambase::open(const char* b, int m, int prot)
{
    if( m & ios::app )
        m |= ios::out;  // append implies output
    else if( (m & (ios::out | ios::ate | ios::app | ios::in)) == ios::out )
        m |= ios::trunc; // output implies truncate unless in, app, or ate

    if( buf.is_open() )
        clear(ios::failbit);        // fail - already open
    else if( buf.open(b, m, prot) )
        clear(ios::goodbit);        // successful open
    else
        clear(ios::badbit);     // open failed
}


