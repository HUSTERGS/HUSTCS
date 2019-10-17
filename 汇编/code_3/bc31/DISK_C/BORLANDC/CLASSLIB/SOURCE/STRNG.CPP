/*------------------------------------------------------------------------*/
/*                                                                        */
/*  STRNG.CPP                                                             */
/*                                                                        */
/*  Copyright Borland International 1991, 1992                            */
/*  All Rights Reserved                                                   */
/*                                                                        */
/*------------------------------------------------------------------------*/

#if !defined( __CHECKS_H )
#include <Checks.h>
#endif	// __CHECKS_H

#if !defined( __STRNG_H )
#include <Strng.h>
#endif  // __STRNG_H

#ifndef __STDLIB_H
#include <stdlib.h>
#endif

#ifndef __STRING_H
#include <string.h>
#endif

#if !defined( __IOSTREAM_H )
#include <iostream.h>
#endif  // __IOSTREAM_H

String::String( const char *aPtr )
{
    if ( aPtr == 0 )
        aPtr = "";

    len = strlen( aPtr ) + 1;
    theString = new char[ len ];
    CHECK( theString != 0 );
    strcpy( theString, aPtr );
}

String::String( const String& sourceString )
{
    len = sourceString.len;
    theString = new char[ len ];
    CHECK( theString != 0 );
    strcpy( theString, sourceString.theString );
}

String::isEqual( const Object& testString ) const
{
    return ( len == ((String &)testString).len &&
             !strcmp( theString, ((String &)testString).theString ) );
}

int String::isLessThan( const Object& testString ) const
{
    return ( strcmp ( theString, ((String &)testString).theString ) < 0 );
}

hashValueType String::hashValue() const
{
    hashValueType   value = hashValueType(0);
    for( int i = 0; i < len; i++ )
        {
        value ^= theString[i];
        value = _rotl( value, 1 );
        }
    return value;
}

void String::printOn( ostream& outputStream ) const
{
    outputStream << theString;
}

String& String::operator =( const String& sourceString )
{
    if ( *this != sourceString )
        {
        if ( len != sourceString.len )
            {
            delete theString;
            len = sourceString.len;
            theString = new char[ len ];
            CHECK( theString != 0 );
            }
        strcpy( theString, sourceString.theString );
        }
    return *this;
}
