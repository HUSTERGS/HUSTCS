#ifndef __STDLIB_H
#include <stdlib.h>
#endif

#ifndef __IOSTREAM_H
#include <iostream.h>
#endif

#ifndef __DIRECTRY_H
#include "directry.h"
#endif

int main( int argc, char *argv[] )
{
    if( argc < 2 || argc > 3 )
        {
        cerr << "Usage:  directry [options] filespec" << endl << endl;
        cerr << "Options:" << endl;
        cerr << "\t-sd\tsort by date" << endl;
        cerr << "\t-sn\tsort by name" << endl;
        cerr << "\t-ss\tsort by size" << endl;
        exit(1);
        }

    int path;                       
    Directory::sortOrder sorting = Directory::byName;

    if( argc != 3 )
        path = 1;
    else 
        {
        path = 2;
        if( strcmp( argv[1], "-sn" ) == 0 )
            sorting = Directory::byName;
        else if( strcmp( argv[1], "-sd" ) == 0 )
            sorting = Directory::byDate;
        else if( strcmp( argv[1], "-ss" ) == 0 )
            sorting = Directory::bySize;
        }

    Directory sortedDirectory( argv[path], sorting );
    cout << sortedDirectory;
    return 0;
}
