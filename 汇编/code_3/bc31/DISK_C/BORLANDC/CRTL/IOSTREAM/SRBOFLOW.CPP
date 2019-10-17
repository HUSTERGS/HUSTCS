/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     srboflow.cpp                                             |*/
/*|                                                              |*/
/*|     Class strstreambuf                                       |*/
/*|          int strstreambuf::overflow( int )                   |*/
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
#include <strstrea.h>

#define expandable ((ssbflags&(dynamic|frozen))==dynamic)

int strstreambuf::overflow(int c)
{
    if( expandable )
        {
        // allocate put area as needed
        if( ! base() )
            doallocate();
        if( ! pbase() )
            setp(base(), ebuf());
        }

    if( pbase() )
        {
        if( (pptr() >= epptr()) && expandable )
            {
            // expand the reserve area
            char *oldp = base();    // old buf
            int len = blen();       // length of old buf
            char *p = new char[len + MinStrstreamIncr]; // new buf
            if( ! p )
                return EOF;     // out of memory

            memcpy(p, oldp, len);   // copy data to new buf
            // get relative pointer data
            int ebloc, gloc, egloc; // get area pointer data
            int ploc = (int)(pptr() - oldp);    // put area pointer data
            int get_area = (gptr() != 0);
            if( get_area )
                {
                ebloc = (int)(eback() - oldp);  // eback location
                gloc = (int)(gptr() - oldp);    // gptr location
                egloc = (int)(egptr() - oldp);  // egptr location
                }
            // set up new pointers
            setb(p, p + len + MinStrstreamIncr, 0);
            setp(p, ebuf());    // the put area goes to end of buf
            pbump(ploc);
            if( get_area )
                setg(p + ebloc, p + gloc, p + egloc);
            delete oldp;        // free old space
            }
        if( pptr() < epptr() )
            return sputc(c);        // now there is room in the put area
        }

    return EOF;     // could not make more space
}


