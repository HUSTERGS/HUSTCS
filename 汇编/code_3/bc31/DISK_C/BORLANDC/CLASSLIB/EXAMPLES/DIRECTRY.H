#ifndef __DIRECTRY_H
#define __DIRECTRY_H

#if !defined( __SORTARRY_H )
#include <SortArry.h>
#endif	// __SORTARRY_H

#ifndef __DIR_H
#include <dir.h>
#endif

#ifndef __FILEDATA_H
#include "filedata.h"
#endif

const directoryClass = filesBySizeClass+1;

class Directory:  public SortedArray
{

public:

    enum sortOrder { byName, byDate, bySize };

    Directory( char *, sortOrder );
    virtual ~Directory() {}

    virtual classType isA() const { return directoryClass; }
    virtual char *nameOf() const { return "Directory"; }
    virtual hashValueType hashValue() const { return 0; }
    virtual void printHeader( ostream& ) const;
    virtual void printSeparator( ostream& ) const;
    virtual void printTrailer( ostream& ) const;

private:

    void addFile( ffblk&, sortOrder );
    String mask;

};

#endif    
