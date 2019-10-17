/*------------------------------------------------------------------------*/
/*                                                                        */
/*  LTIME.CPP                                                             */
/*                                                                        */
/*  Copyright Borland International 1991, 1992                            */
/*  All Rights Reserved                                                   */
/*                                                                        */
/*------------------------------------------------------------------------*/

#if !defined( __LTIME_H )
#include <LTime.h>
#endif  // __LTIME_H

#ifndef __IOMANIP_H
#include <iomanip.h>
#endif

#ifndef __STRSTREAM_H
#include <strstrea.h>
#endif

#ifndef __STDIO_H
#include <stdio.h>
#endif

const BufSize = 20;

BaseTime::isEqual( const Object& testTime ) const
{
    return HH == ((BaseTime&)testTime).HH &&
           MM == ((BaseTime&)testTime).MM &&
           SS == ((BaseTime&)testTime).SS &&
           HD == ((BaseTime&)testTime).HD;
}

BaseTime::isLessThan( const Object& testTime ) const
{
    if( HH != ((BaseTime&)testTime).HH )
        return HH < ((BaseTime&)testTime).HH;
    if( MM != ((BaseTime&)testTime).MM )
        return MM < ((BaseTime&)testTime).MM;
    if( SS != ((BaseTime&)testTime).SS )
        return SS < ((BaseTime&)testTime).SS;
    if( HD != ((BaseTime&)testTime).HD )
        return HD < ((BaseTime&)testTime).HD;
    return 0;
}

hashValueType BaseTime::hashValue() const
{
    return hashValueType( HH + MM + SS + HD );
}

void Time::printOn( ostream& outputStream ) const
{
    char temp[BufSize];
    ostrstream os( temp, BufSize );
    os << ((hour()%12 == 0) ? 12 : hour()%12) << ":"
       << setfill( '0' )
       << setw( 2 ) << minute() << ":"
       << setw( 2 ) << second() << "."
       << setw( 2 ) << hundredths() << " "
       << ((hour() > 11) ? "p" : "a") << "m" << ends;
    outputStream << temp;
}

