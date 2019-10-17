/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     ostosfx.cpp                                              |*/
/*|                                                              |*/
/*|     Class ostream                                            |*/
/*|          void ostream::do_osfx()                             |*/
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

// implementation of osfx -- output suffix operations
void ostream::do_osfx()
{
    if( ! fail()  && (x_flags & ios::unitbuf) )
        flush();
#if !defined( _RTLDLL )
    if( x_flags & ios::stdio )
        {
        cout.flush();
        clog.flush();
        }
#endif
}


