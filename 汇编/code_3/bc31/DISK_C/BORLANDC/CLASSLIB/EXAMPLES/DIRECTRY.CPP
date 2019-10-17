#if !defined( __SORTARRY_H )
#include <SortArry.h>
#endif  // __SORTARRY_H

#ifndef __DIR_H
#include <dir.h>
#define __DIR_H
#endif

#ifndef __DIRECTRY_H
#include "directry.h"
#endif

#ifndef __FILEDATA_H
#include "filedata.h"
#endif

#if !defined( __IOSTREAM_H )
#include <iostream.h>
#endif	// __IOSTREAM_H

Directory::Directory( char *pathName, sortOrder sortBy ) :
    SortedArray( 10, 0, 5 ), mask( pathName )
{
    struct ffblk fileBlock;
    int morePathNames = !findfirst( mask, &fileBlock, 0 );
    while( morePathNames )
        {
        addFile( fileBlock, sortBy );
        morePathNames = !findnext( &fileBlock );
        } 
}

void Directory::addFile( ffblk& fileBlock, sortOrder sortBy )
{
    switch( sortBy )
        {
        case byName:
            add( *(new FilesByName( fileBlock )) );
            break;
        case byDate:
            add( *(new FilesByDate( fileBlock )) );
            break;
        case bySize:
            add( *(new FilesBySize( fileBlock )) );
            break;
        }
}

void Directory::printHeader( ostream& outputStream ) const
{
    outputStream << "Directory: " << mask << "\n    ";
}

void Directory::printSeparator( ostream& outputStream ) const
{
    outputStream << "\n    ";
}

void Directory::printTrailer( ostream& outputStream ) const
{
    outputStream << "\n";
}
