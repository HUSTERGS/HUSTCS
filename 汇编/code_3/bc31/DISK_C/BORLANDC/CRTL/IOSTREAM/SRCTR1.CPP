/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     srctr1.cpp                                               |*/
/*|                                                              |*/
/*|     Class strstreambase                                      |*/
/*|          strstreambase::strstreambase( char *, int, char* )  |*/
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
#include <strstrea.h>

strstreambase::strstreambase(char* ptr, int n, char* pstart) :
        buf(ptr, n, pstart)
{
    ios::init(&this->buf);
}


