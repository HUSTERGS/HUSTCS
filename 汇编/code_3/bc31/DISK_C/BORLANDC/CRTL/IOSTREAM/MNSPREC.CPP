/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     mnsprec.cpp                                              |*/
/*|                                                              |*/
/*|     Predefined manipulators                                  |*/
/*|         smanip_int setprecision( int )                       |*/
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

// set the floating-point precision to n digits

static ios _FAR & sprec(ios _FAR & i, int n)
{
    i.precision(n);
    return i;
}

smanip_int setprecision(int n)
{
    return smanip_int(sprec, n);
}


