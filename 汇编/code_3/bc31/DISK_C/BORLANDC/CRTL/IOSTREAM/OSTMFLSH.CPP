/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     ostmflush.cpp                                            |*/
/*|                                                              |*/
/*|     Class ostream                                            |*/
/*|          ostream& flush( ostream& )                          |*/
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

// flush the ostream
ostream _FAR & flush(ostream _FAR & os)
{
    os.flush();
    return os;
}
