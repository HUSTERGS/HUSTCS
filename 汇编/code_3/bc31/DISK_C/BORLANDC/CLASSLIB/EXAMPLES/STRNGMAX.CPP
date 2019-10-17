#if !defined( __STRNG_H )
#include <strng.h>
#endif  // __STRNG_H

#ifndef __IOSTREAM_H
#include <iostream.h>
#endif

//
// Determines the maximum string using the ASCII collating sequence to 
// define rank.  A string is defined to be greater than another if the
// ASCII values of its characters are greater than the values of the other
// string.  For example,
//
// strngmax Alpha Beta Charlie
//
// would print Charlie to stdout and return 3.
//
int main( int argc, char *argv[] )
{
    if( argc < 2 )
        {
        cerr << "Usage:  strngmax string1 [string2 ...]\n";
        return 1;
        }

    String theGreatestString( argv[1] );
    int positionOfTheGreatestString = 1;
    int nextArg = 2;

    while( nextArg < argc )
        {
        String argListString ( argv[nextArg++] );
        if ( argListString > theGreatestString )
            {
            theGreatestString = argListString;
            positionOfTheGreatestString = nextArg - 1;
            }
        }

    cout << theGreatestString << endl;
    return positionOfTheGreatestString;
}
