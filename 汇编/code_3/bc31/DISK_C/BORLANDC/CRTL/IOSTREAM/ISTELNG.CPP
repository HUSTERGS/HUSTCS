/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     istelng.cpp                                              |*/
/*|                                                              |*/
/*|     Class istream                                            |*/
/*|          istream& istream::operator>> ( long& )              |*/
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
#include <ctype.h>

// extract decimal value from istream, given first character c
// error if c is not a valid character

static unsigned long getdec(istream _FAR & i, int c)
{
    unsigned long l = 0;
    if( ! isdigit(c) )
        {
        if( c == EOF )
            i.clear(i.rdstate() | ios::eofbit | ios::failbit);
        else
            i.clear(i.rdstate() | ios::failbit);
        }
    else
        {
        do  {
            l = 10 * l + c - '0';
            c = i.rdbuf()->snextc();
            } while( isdigit(c) );
        }
    return l;
}


// extract octal value from istream, given first character c
// error if c is not a valid character

static unsigned long getoct(istream _FAR & i, int c)
{
    unsigned long l = 0;
    if( c < '0'  ||  '7' < c )
        {
        if( c == EOF )
            i.clear(i.rdstate() | ios::eofbit | ios::badbit);
        else
            i.clear(i.rdstate() | ios::failbit);
        }
    else
        {
        do  {
            l = 8 * l + c - '0';
            c = i.rdbuf()->snextc();
            } while( '0' <= c  &&  c <= '7' );
        }
    return l;
}


// extract hex value from istream, given first character c
// error if c is not a valid character

static unsigned long gethex(istream _FAR & i, int c)
{
    unsigned long l = 0;
    if( ! isxdigit(c) )
        {
        if( c == EOF )
            i.clear(i.rdstate() | ios::eofbit | ios::badbit);
        else
            i.clear(i.rdstate() | ios::failbit);
        }
    else
        {
        do  {
            if( isupper(c) )
                c -= ('A' - 10);
            else if( islower(c) )
                c -= ('a' - 10);
            else
                c -= '0';
            l = 16 * l + c;
            c = i.rdbuf()->snextc();
            } while( isxdigit(c) );
    }
    return l;
}

istream _FAR & istream::operator>> (long _FAR & l)
{

    if( ipfx0() )
        {
        unsigned long u = 0;    // result
        int c = bp->sgetc();
        int neg = c == '-';
        if( c == '+' || neg )
            c = bp->snextc();
        if( flags() & ios::hex )
            u = gethex(*this, c);
        else if( flags() & ios::oct )
            u = getoct(*this, c);
        else if( (flags() & ios::dec)  ||  c != '0' )
            u = getdec(*this, c);
        else
            {  // c == '0'
            c = bp->snextc();
            if( c == 'x' || c == 'X' )
                {
                c = bp->snextc();
                u = gethex(*this, c);
                }
            else if( '0' <= c && c <= '7' )
                u = getoct(*this, c);
            else // a lone '0'
                u = 0;
            }

        l = neg ? -long(u) : long(u);
        }
    return *this;
}
