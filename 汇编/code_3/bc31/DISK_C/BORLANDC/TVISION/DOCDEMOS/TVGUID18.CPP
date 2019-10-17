/*---------------------------------------------------------*/
/*                                                         */
/*   Turbo Vision 1.0                                      */
/*   TVGUID18 Demo Source File                             */
/*   Copyright (c) 1991 by Borland International           */
/*                                                         */
/*---------------------------------------------------------*/

#include <iostream.h>           // for cout, <<
#include <iomanip.h>            // for setw
#include <string.h>             // for strncmp

#define Uses_TNSSortedCollection
#include <tv.h>

struct TClient : public TObject
{
    // all members public by default

    const char *account;
    const char *name;
    const char *phone;

    TClient( char *newAccount, char *newName, char *newPhone);
    ~TClient();

};

TClient::TClient( char *newAccount, char *newName, char *newPhone)
{
    account = newStr( newAccount );
    name = newStr( newName );
    phone = newStr( newPhone );
};

TClient::~TClient()
{
    delete (char *)account;
    delete (char *)name;
    delete (char *)phone;
}

class TSortedClientCollection : public TNSSortedCollection
{

public:

    TSortedClientCollection (ccIndex aLimit, ccIndex aDelta ) :
        TNSSortedCollection( aLimit, aDelta ) {}
    virtual ccIndex insert( TClient *tc )
	    { return TNSSortedCollection::insert( tc ); }
        // overrides TNSCollection::insert( void *item )
        // In a more complete application, you would also override
        // at, indexOf, remove, free,... so that they all
        // handle TClient pointers

    virtual void *keyOf(void *item);

    void printAll();
    void searchArea( char *areaToFind );

private:

    virtual int compare( void *key1, void *key2);
    virtual void freeItem( void *item );

};

void *TSortedClientCollection::keyOf(void *item)
{

    return (void *)((TClient*)item)->name;
}

int TSortedClientCollection::compare(void *key1, void *key2)
{
   return strcmp ( (char *)(key1), (char *)(key2) );
}

static void print( void *c, void * )
{
    TClient *tc = (TClient *)c;
    cout << setiosflags( ios::left )
         << setw(10) << tc->account
         << setw(20) << tc->name
         << setw(16) << tc->phone
         << endl;
}

void TSortedClientCollection::printAll()  // print info for all clients
{
    cout << endl << "Client List:" << endl;
    forEach( &print, 0 ); // call print for each client
}

void TSortedClientCollection::freeItem( void *item )
{
    delete ( TClient * ) item;
}

Boolean areaMatch( void *c, void *ph )
{
    char *areaToFind = (char *)ph;
    TClient *tc = (TClient *)c;
    if( strncmp( areaToFind, tc->phone, 5 ) == 0 )
        return True;
    else
        return False;
}

void TSortedClientCollection::searchArea( char *areaToFind )
{
    TClient *foundClient =
        (TClient *)firstThat( &areaMatch, areaToFind );
    if( !foundClient )
        cout << "No client met the search requirement" << endl;
    else
        {
	    cout << "Found client:" << endl;
	    print( foundClient, 0 );
        }
}

int main()
{

    TSortedClientCollection clientList( 50, 10 );
    // limit is 50, delta is 10

    clientList.insert( new TClient("90-167", "Smith, Zelda",
			   "(800) 555-1212" ));
    clientList.insert( new TClient("90-160", "Johnson, Agatha",
			   "(302) 139-8913" ));
    clientList.insert( new TClient("90-177", "Smitty, John",
			   "(406) 987-4321"));
    clientList.insert( new TClient("91-100", "Anders, Smitty",
			   "(406) 111-2222"));

    clientList.printAll();
    clientList.searchArea( "(406)" );
    clientList.freeAll();
    return 0;

};


