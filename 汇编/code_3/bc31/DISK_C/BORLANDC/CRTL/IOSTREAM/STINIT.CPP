/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     stinit.cpp                                               |*/
/*|                                                              |*/
/*|     Class ios                                                |*/
/*|          void ios::init( streambuf * )                       |*/
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

void ios::init(streambuf* sbp)
{
    nwords = 0;
    state = ospecial = 0;
    ispecial = skipping;
    x_flags = skipws;
    x_precision = x_width = 0;
    x_fill = ' ';
    x_tie = 0;
    bp = sbp;
}


