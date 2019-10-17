/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     filename - istmanip.cpp                                  |*/
/*|                                                              |*/
/*|     Class istream                                            |*/
/*|          istream& istream::operator>> (ios& (*f)(ios&) )     |*/
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

istream _FAR & istream::operator>> (ios _FAR & (*f)(ios _FAR &) )
{
    (*f)(*((ios*)this));
    return *this;
}


