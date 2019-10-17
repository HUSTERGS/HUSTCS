/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     isrctr1.cpp                                              |*/
/*|                                                              |*/
/*|     Class istrstream                                          |*/
/*|          istrstream::istrstream( char * )                    |*/
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

istrstream::istrstream(signed char* str) :
        strstreambase(str, 0, 0),
        istream(strstreambase::rdbuf())
{
}

istrstream::istrstream(unsigned char* str) :
        strstreambase((signed char *)str, 0, 0),
        istream(strstreambase::rdbuf())
{
}


