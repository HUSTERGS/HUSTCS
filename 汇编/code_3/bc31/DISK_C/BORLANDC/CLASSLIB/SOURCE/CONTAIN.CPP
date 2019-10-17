/*------------------------------------------------------------------------*/
/*                                                                        */
/*  CONTAIN.CPP                                                           */
/*                                                                        */
/*  Copyright Borland International 1991, 1992                            */
/*  All Rights Reserved                                                   */
/*                                                                        */
/*------------------------------------------------------------------------*/

#if !defined( CHECKS_H )
#include <Checks.h>
#endif  // CHECKS_H

#if !defined( __CONTAIN_H )
#include <Contain.h>
#endif  // __CONTAIN_H

#ifndef __IOSTREAM_H
#include <iostream.h>
#endif

void Container::forEach( iterFuncType actionPtr, void *paramListPtr )
{
    PRECONDITION( actionPtr != 0 );
    ContainerIterator& containerIterator = initIterator();
    while( containerIterator != 0 )
        containerIterator++.forEach( actionPtr, paramListPtr );
    delete &containerIterator;
}

Object& Container::firstThat( condFuncType testFuncPtr,
                              void *paramListPtr
                            ) const
{
    PRECONDITION( testFuncPtr != 0 );
    ContainerIterator &containerIterator = initIterator();
    while( containerIterator != 0 )
        {
        Object& testResult =
                containerIterator++.firstThat( testFuncPtr, paramListPtr );
        if ( testResult != NOOBJECT )
            {
            delete &containerIterator;
            return testResult;
            }
        }
    delete &containerIterator;
    return NOOBJECT;
}

Object& Container::lastThat( condFuncType testFuncPtr,
                             void *paramListPtr
                           ) const
{
    PRECONDITION( testFuncPtr != 0 );
    ContainerIterator& containerIterator = initIterator();
    Object *lastMet = ZERO;
    while( containerIterator != 0 )
        {
        Object& testResult =
                containerIterator++.lastThat( testFuncPtr, paramListPtr );
        if( testResult != NOOBJECT )
            lastMet = &testResult;
        }
    delete &containerIterator;
    return *lastMet;
}

int Container::isEqual( const Object& testContainer ) const
{
    PRECONDITION( isA() == testContainer.isA() );

    int res = 1;

    ContainerIterator& thisIterator = initIterator();
    ContainerIterator& testContainerIterator =
                            ((Container &)(testContainer)).initIterator();
    while( thisIterator != 0 && testContainerIterator != 0 )
        {
        if( thisIterator++ != testContainerIterator++ )
            {
            res = 0;
            break;
            }
        }

    if( thisIterator != 0 || testContainerIterator != 0 )
        res = 0;

    delete &testContainerIterator;
    delete &thisIterator;
    return res;
}

void Container::printOn( ostream& outputStream ) const
{
    ContainerIterator& printIterator = initIterator();
    printHeader( outputStream );
    while( printIterator != 0 )
        {
        printIterator++.printOn( outputStream );
        if ( printIterator != 0 )
            printSeparator( outputStream );
        else
            break;
        }
    printTrailer( outputStream );
    delete &printIterator;
}

static void getHashValue( Object& o, void *valPtr )
{
    hashValueType *val = (hashValueType *)valPtr;
    *val += o.hashValue();
}

#pragma warn -ncf

hashValueType Container::hashValue() const
{
    hashValueType val = 0;
    forEach( getHashValue, &val );
    return val;
}

#pragma warn .ncf

void Container::printHeader( ostream& outputStream ) const
{
    outputStream << nameOf() << " {\n    ";
}

void Container::printSeparator( ostream& outputStream ) const
{
    outputStream << ",\n    ";
}

void Container::printTrailer( ostream& outputStream ) const
{
    outputStream << " }\n";
}

