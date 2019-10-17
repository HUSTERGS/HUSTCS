/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     isrctr2.cpp                                              |*/
/*|                                                              |*/
/*|     Class itrstream                                          |*/
/*|          istrstream::istrstream( char *, int )               |*/
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

istrstream::istrstream(signed char* str, int len) :
        strstreambase(str, len, 0),
        istream(strstreambase::rdbuf())
{
}

istrstream::istrstream(unsigned char* str, int len) :
        strstreambase((signed char *)str, len, 0),
        istream(strstreambase::rdbuf())
{
}


