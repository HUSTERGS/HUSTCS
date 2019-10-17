/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     mnsbase.cpp                                              |*/
/*|                                                              |*/
/*|     Predefined manipulators                                  |*/
/*|         smanip_int setbase( int )                            |*/
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
#include <iomanip.h>

// set the conversion base to 0, 8, 10, or 16

static ios _FAR & sbase(ios _FAR & i, int b)
{
    long l = 0;
    if( b == 16 )
        l = ios::hex;
    else if (b == 10)
        l = ios::dec;
    else if( b == 8 )
        l = ios::oct;
    i.setf(l, ios::basefield);
    return i;
}

smanip_int setbase(int b)
{
    return smanip_int(sbase, b);
}

