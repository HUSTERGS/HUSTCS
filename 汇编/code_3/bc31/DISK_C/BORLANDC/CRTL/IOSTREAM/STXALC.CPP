/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     stxalc.cpp                                               |*/
/*|                                                              |*/
/*|     Class ios                                                |*/
/*|          int ios::xalloc()                                   |*/
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

// supply a new word index for derived class use

int ios::xalloc()
{
    return ++usercount;
}


