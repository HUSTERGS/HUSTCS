/*------------------------------------------------------------------------*/
/*                                                                        */
/*  LDATE.CPP                                                             */
/*                                                                        */
/*  Copyright Borland International 1991, 1992                            */
/*  All Rights Reserved                                                   */
/*                                                                        */
/*------------------------------------------------------------------------*/

#if !defined( __LDATE_H )
#include <LDate.h>
#endif  // __LDATE_H

#ifndef __STRSTREAM_H
#include <strstrea.h>
#endif

#ifndef __STDIO_H
#include <stdio.h>
#endif

const BufSize = 20;

static char *MonthNames[] =
    {
    "",
    "January",
    "February",
    "March",
    "April",
    "May",
    "June",
    "July",
    "August",
    "September",
    "October",
    "November",
    "December"
    };

int BaseDate::isEqual( const Object& testDate ) const
{
    return MM == ((BaseDate&)testDate).MM &&
           DD == ((BaseDate&)testDate).DD &&
           YY == ((BaseDate&)testDate).YY;
}

int BaseDate::isLessThan( const Object& testDate ) const
{
    if( YY != ((BaseDate&)testDate).YY )
        return YY < ((BaseDate&)testDate).YY;
    if( MM != ((BaseDate&)testDate).MM )
        return MM < ((BaseDate&)testDate).MM;
    return DD < ((BaseDate&)testDate).DD;
}

hashValueType BaseDate::hashValue() const
{
    return hashValueType( YY + MM + DD );
}

void Date::printOn( ostream& outputStream ) const
{
    char temp[BufSize];
    ostrstream os( temp, BufSize );
    os << MonthNames[ Month() ] << " "
       << Day() << ", " << Year() << ends;
    outputStream << temp;
}

