/*[]-------------------------------------------------------------------[]*/
/*|                                                                     |*/
/*|     srbskoff.cpp                                                    |*/
/*|                                                                     |*/
/*|   Class strstreambuf                                                |*/
/*|   streampos strstreambuf::seekoff( streamoff, ios::seek_dir, int )  |*/
/*|                                                                     |*/
/*[]-------------------------------------------------------------------[]*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1990, 1992 by Borland International
 *      All Rights Reserved.
 *
 */

#include <ioconfig.h>
#include <strstrea.h>

// we assume streampos and streamoff are type int or long

streampos strstreambuf::seekoff(streamoff off, ios::seek_dir dir, int omode)
{
    streamoff pos = EOF;    // result

    // find position if from beginning or end
    if( dir == ios::end )
        {
        if( (ssbflags & unlimited) || off > 0 )
            pos = -1;   // can't do it
        else
            pos = blen() + off;
        }
    else if( dir == ios::beg )
        pos = off;

    if( omode & ios::in )
        {
        // set up get area
        if( dir == ios::cur )
            {
            // find a reasonable value for current position
            if( gptr() )
                pos = streamoff(gptr() - base()) + off;
            else if( pptr() )
                pos = streamoff(pptr() - base()) + off;
            else
                pos = off;
            }
        if( pos < 0  ||  blen() < pos )
            pos = EOF;  // illegal request
        else
            {
#pragma warn -sig
            char* g = base() + pos;
#pragma warn .sig
            char* eb = (eback() && eback() < g) ? eback() : g;
            char* eg = (egptr() && g < egptr()) ? egptr() : g;
            setg(eb, g, eg);
            }
        }
    if( omode & ios::out )
        {
        // set up put area
        if( dir == ios::cur )
            {
            // find a reasonable value for current position
            if( pptr() )
                pos = streamoff(pptr() - base()) + off;
            else if( gptr() )
                pos = streamoff(gptr() - base()) + off;
            else
                pos = off;
            }
        if( pos < 0  ||  blen() < pos )
            pos = EOF;  // illegal request
        else
            {
#pragma warn -sig
            char* p = base() + pos;
#pragma warn .sig
            char* ep = (epptr() && p < epptr()) ? epptr() : ebuf();
            setp(p, ep);
            }
        }
    return streampos(pos);
}
