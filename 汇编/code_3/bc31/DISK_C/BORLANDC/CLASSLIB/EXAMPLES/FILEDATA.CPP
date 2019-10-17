#ifndef __IOSTREAM_H
#include <iostream.h>
#endif

#ifndef __IOMANIP_H
#include <iomanip.h>
#endif

#ifndef __DIR_H
#include <dir.h>
#define __DIR_H
#endif

#ifndef __FILEDATA_H
#include "filedata.h"
#endif

FileData::FileData( ffblk& blk ) :
    fileName( blk.ff_name ),
    fileDate( (blk.ff_fdate >> 5) & 0x000F,
              blk.ff_fdate & 0x0001F,
              (blk.ff_fdate >> 9) + 1980 ),
    fileSize( blk.ff_fsize ),
    fileTime( blk.ff_ftime >> 11,
              (blk.ff_ftime >> 5) & 0x3F,
              blk.ff_ftime & 0x1F )
{
}

void FileData::printOn( ostream& outputStream ) const
{
    outputStream << setw( 14 ) << setiosflags( ios::left )   << fileName
                 << setw( 18 ) << fileDate
                 << setw( 17 ) << resetiosflags( ios::left ) << fileTime
                 << setw( 10 ) << fileSize << " bytes";
}

int FilesByName::isEqual( const Object& testFile ) const
{
    return fileName == ( (FilesByName&)testFile ).fileName;
}

int FilesByName::isLessThan( const Object& testFile ) const
{
    return fileName < ( (FilesByName&)testFile ).fileName;
}

int FilesByDate::isEqual( const Object& testFile ) const
{
    return fileDate == ( (FilesByDate&)testFile ).fileDate &&
           fileTime == ( (FilesByDate&)testFile ).fileTime;
}

int FilesByDate::isLessThan( const Object& testFile ) const
{
    if( fileDate == ( (FilesByDate&)testFile ).fileDate )
        return fileTime < ( (FilesByDate&)testFile ).fileTime;
    else
        return fileDate < ( (FilesByDate&)testFile ).fileDate;
}

int FilesBySize::isEqual( const Object& testFile ) const
{
    return fileSize == ( (FilesBySize&)testFile ).fileSize;
}

int FilesBySize::isLessThan( const Object& testFile ) const
{
    return fileSize < ( (FilesBySize&)testFile ).fileSize;
}
