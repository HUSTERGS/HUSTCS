/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     ostptr.cpp                                               |*/
/*|                                                              |*/
/*|     Class ostream                                            |*/
/*|          ostream& ostream::operator<< (void* p)              |*/
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

// insert character representation of the value of the pointer
ostream _FAR & ostream::operator<< (void* p)
{
    long f = flags();
    setf((ios::hex | ios::showbase | ios::internal),
         (ios::basefield | ios::showbase | ios::adjustfield));
    fill('0');

#ifndef SHOW_COLON
    /* Output without a separator */
#if defined(__COMPACT__) || defined(__LARGE__) || defined(__HUGE__)
    width(10);
    *this << (unsigned long) p;
#else
    width(6);
    *this << (unsigned) p;
#endif

#else
    /* Output with ':' separator */
    width(6);
#if defined(__LARGE__) || defined(__HUGE__) || defined(__COMPACT__)
    *this << (unsigned)((unsigned long)p >> 16);
    *this << ':';
#ifndef SHOWBASE_ON_OFFSET
    /* Don't show 0x on offset */
    unsetf(ios::showbase);
    width(4);
#else
    width(6);
#endif  /* SHOWBASE_ON_OFFSET */
#endif
    *this << (unsigned)p;
#endif  /* SHOW_COLON */

    flags(f);
    return *this;
}


