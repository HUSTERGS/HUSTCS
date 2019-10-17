/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     mnsetw.cpp                                               |*/
/*|                                                              |*/
/*|     Predefined manipulators                                  |*/
/*|         smanip_int setw( int )                               |*/
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

// set the field width to n

static ios _FAR & swidth(ios _FAR & i, int n)
{
    i.width(n);
    return i;
}

smanip_int setw(int n)
{
    return smanip_int(swidth, n);
}
