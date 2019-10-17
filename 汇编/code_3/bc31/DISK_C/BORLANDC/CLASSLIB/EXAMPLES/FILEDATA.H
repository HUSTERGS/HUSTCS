#ifndef __FILEDATA_H
#define __FILEDATA_H

#if !defined( __SORTABLE_H )
#include <Sortable.h>
#endif	// __SORTABLE_H

#if !defined( __STRNG_H )
#include <Strng.h>
#endif	// __STRNG_H

#if !defined( __LDATE_H )
#include <LDate.h>
#endif	// __LDATE_H

#if !defined( __LTIME_H )
#include <LTime.h>
#endif	// __LTIME_H

#ifndef __DIR_H
#include <dir.h>
#endif

const fileDataClass = __firstUserClass;
const filesByNameClass = fileDataClass+1;
const filesByDateClass = filesByNameClass+1;
const filesBySizeClass = filesByDateClass+1;

class FileData: public Sortable
{

public:

    FileData( ffblk& );

    virtual classType isA() const { return fileDataClass; }
    virtual char *nameOf() const { return "FileData"; }
	virtual int isEqual( const Object& ) const = 0;
	virtual int isLessThan( const Object& ) const = 0;
    virtual hashValueType hashValue() const { return 0; }
    virtual void printOn( ostream& ) const;

protected:

    String fileName;
    Date fileDate;
    Time fileTime;
    long fileSize;

};

class FilesByName:  public FileData
{

public:

    FilesByName( ffblk& blk ) : FileData( blk ) {}

    virtual classType isA() const { return filesByNameClass; }
    virtual char *nameOf() const { return "FilesByName"; }
	virtual int isEqual( const Object& ) const;
	virtual int isLessThan( const Object& ) const;

};

class FilesByDate:  public FileData
{

public:

    FilesByDate( ffblk& blk ) : FileData( blk ) {}

    virtual classType isA() const { return filesByDateClass; }
    virtual char *nameOf() const { return "FilesByDate"; }
	virtual isEqual( const Object& ) const;
	virtual isLessThan( const Object& ) const;

};

class FilesBySize:  public FileData
{

public:

    FilesBySize( ffblk& blk ) : FileData( blk ) {}

    virtual classType isA() const { return filesBySizeClass; }
    virtual char *nameOf() const { return "FilesBySize"; }
	virtual isEqual( const Object& ) const;
	virtual isLessThan( const Object& ) const;

};

#endif    
