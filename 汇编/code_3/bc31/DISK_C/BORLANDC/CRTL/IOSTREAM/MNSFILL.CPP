/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     mnsfill.cpp                                              |*/
/*|                                                              |*/
/*|     Predefined manipulators                                  |*/
/*|         smanip_int setfill( int )                            |*/
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

// set fill character for padding a field

static ios _FAR & sfill(ios _FAR & i, int f)
{
    i.fill(f);
    return i;
}

smanip_int setfill(int f)
{
    return smanip_int(sfill, f);
}


