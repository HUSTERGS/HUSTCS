/*---------------------------------------------------------*/
/*                                                         */
/*   Turbo Vision 1.0                                      */
/*   TVGUID19.CPP Demo Source File                         */
/*   Copyright (c) 1991 by Borland International           */
/*                                                         */
/*---------------------------------------------------------*/

/*
   Read a line and add each unique word to a sorted
   string collection. Use the forEach iterator to
   traverse the collection and print out each word.
*/

#include <stdio.h>              // temp for gets
#include <stdlib.h>             // for exit()
#include <iostream.h>           // for << etc
#include <string.h>             // for strlen etc
#include <ctype.h>              // for ispunct

#define Uses_TStringCollection
#include <tv.h>

const int maxLine = 81;
char line[maxLine];

class TWordCollection : public TStringCollection
{

public:

    TWordCollection( short aLimit, short aDelta ) :
       TStringCollection( aLimit, aDelta) {}
    virtual void print();
};

/* Iterator */
static void printWord( void *w, void * )
{
    char *s = (char *)w;
    cout << s << endl;
}

void TWordCollection::print()
{
    forEach( &printWord, 0 );
}

// Enter a line of text, extract words and insert them in coll
static void insertWord( char *line, TStringCollection *sc )
{
    char *curr;
    char *first;

    char wstr[maxLine];
    char ch = EOS;
    Boolean inword;

    curr = first = line;
    inword = False;

    while( (ch = *curr) != EOS )
        {
        if( !isalnum( ch ) && inword )
            {
            inword = False;
            strncpy( wstr, first, size_t(curr - first) );
            wstr[size_t(curr-first)]=EOS;
            sc->insert( newStr( wstr ) );
            }
        else if( isalnum( ch ) && !inword )
            {
            inword = True;
            first = curr;
            }
        curr++;
        }

    if( inword )
        // grab last word if final char before null is alfa-num
        {
        strncpy( wstr, first, size_t(curr - first) );
        wstr[size_t(curr-first)]=EOS;
        sc->insert( newStr( wstr ));
        }
}

int main()
{
    TWordCollection *wordCollection = new TWordCollection( 20, 5 );
    // in production code, check lowMemory here

    cout << "Enter a line of text: " << endl;
    cin.get( line, maxLine, '\n' );

    // parse line, insert unique words into sorted collection
    insertWord( line, wordCollection );
    if( wordCollection->getCount() > 0 )
        {
        wordCollection->print();
        cout << "Total word count = " << wordCollection->getCount() << endl;
        }
    else
        cout << "No words in WordCollection!" << endl;

    return 0;
}

