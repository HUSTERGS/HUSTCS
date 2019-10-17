/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     fsbuflow.cpp                                             |*/
/*|                                                              |*/
/*|     Class filebuf                                            |*/
/*|          int filebuf::underflow()                            |*/
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

// return the next available character, reading in a buffer if needed

int filebuf::underflow()
{
    if( ! opened  ||  (mode & (ios::in | ios::out)) == ios::out )
        return EOF;

    if( in_avail() )    // no action needed
        return (unsigned char) *gptr();

    int c;  // the return value
    int count;  // input character count

    if ( ! unbuffered()  &&  base() )
        {     // this is buffered

        if (sync() != 0)
                return EOF;

        // find buffer data
        int pb = (blen() > 8) ? 4 : 1;  // putback area size
        char *b = base();

        // read in a new buffer
        count = ::read(xfd, b+pb, blen()-pb);
        if( count == OS_err )
            return EOF;

        // set up get and put areas
        setg(b, b+pb, b+pb+count);
        setp(b+pb, b+pb);

        if( count )
            c = (unsigned char) *gptr();
        }
    else
        {     // this is not buffered
        count = ::read(xfd, lahead, 1);
        if( count == OS_err)
            {
            c = EOF;
            setg(0, 0, 0);
            }
        else
            {
            c = (unsigned char)lahead[0];
            setg(lahead, lahead, lahead+1);
            }
        }

    if( ! count )
        c = EOF;    // end of file

    return c;
}


