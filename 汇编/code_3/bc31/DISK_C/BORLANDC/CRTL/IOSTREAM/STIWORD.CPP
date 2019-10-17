/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     stiword.cpp                                              |*/
/*|                                                              |*/
/*|     Class ios                                                |*/
/*|          long& ios::iword( i )                               |*/
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
#include "user.h"

// return user word as an integer

long _FAR & ios::iword(int i)
{
    static long l = 0;      // for error return
    if( i < 1  ||  usercount < i )
        return l;       // no such entry
    if( i > nwords )
        usersize(i);
    return (i > nwords) ? l : userwords[i-1].lword;
}


