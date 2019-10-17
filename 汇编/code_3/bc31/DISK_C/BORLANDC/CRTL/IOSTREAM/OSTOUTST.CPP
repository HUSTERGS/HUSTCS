/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     ostoutst.cpp                                             |*/
/*|                                                              |*/
/*|     Class ostream                                            |*/
/*|          void ostream::oststr( const char *, const char * )  |*/
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
#include <iostream.h>
#include <string.h>

// Perform the prefix routine, output the string with any needed padding,
// and perform the suffix routine.
// 'd' is the data portion, 'p' is the prefix portion.

void ostream::outstr(const char *d, const char *p)
{
    if( opfx() )
        {
        int plen = p ? strlen(p) : 0;
        int dlen = d ? strlen(d) : 0;
        int pad = width(0) - plen - dlen;

        // pad on left (right-adjust) if needed -- the default case
        if( ! (x_flags & (ios::left | ios::internal)) )
            {
            while( --pad >= 0 )
                {
                if( bp->sputc(x_fill) == EOF )
                    {
                    setstate(ios::badbit);
                    break;
                    }
                }
            }

        // output the prefix
        if( ! fail()  &&  plen )
            if( bp->sputn(p, plen) != plen )
                setstate(ios::badbit);

        // internal padding if needed
        if( ! fail()  &&  (x_flags & ios::internal) )
            {
            while( --pad >= 0 )
                {
                if( bp->sputc(x_fill) == EOF )
                    {
                    setstate(ios::badbit);
                    break;
                    }
                }
            }

        // output the data
        if( ! fail()  &&  dlen )
            if( bp->sputn(d, dlen) != dlen )
                setstate(ios::badbit);

        // pad on right (left-adjust) if needed
        if( ! fail()  &&  (x_flags & ios::left) )
            {
            while( --pad >= 0 )
                {
                if( bp->sputc(x_fill) == EOF )
                    {
                    setstate(ios::badbit);
                    break;
                    }
                }
            }
        }
    osfx();
}


