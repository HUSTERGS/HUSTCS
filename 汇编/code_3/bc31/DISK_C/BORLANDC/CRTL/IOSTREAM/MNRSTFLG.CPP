/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     mnrstflg.cpp                                             |*/
/*|                                                              |*/
/*|     Predefined manipulators                                  |*/
/*|         smanip_long resetiosflags( long )                    |*/
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

// clear the flags bitvector according to the bits set in b

static ios _FAR & rsios(ios _FAR & i, long b)
{
    i.unsetf(b);
    return i;
}

smanip_long resetiosflags(long b)
{
    return smanip_long(rsios, b);
}


