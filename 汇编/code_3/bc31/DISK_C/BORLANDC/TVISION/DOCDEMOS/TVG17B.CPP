/*---------------------------------------------------------*/
/*                                                         */
/*   Turbo Vision 1.0                                      */
/*   TVGUID17 Demo Source File                             */
/*   Copyright (c) 1991 by Borland International           */
/*                                                         */
/*---------------------------------------------------------*/

#include <iostream.h>           // for cout, <<
#include <iomanip.h>            // for setw
#include <string.h>             // for strncmp

#define Uses_TNSCollection
#include <tv.h>

struct TClient : public TObject
{
    // all members public by default
    char account[7], name[35], phone[14];

    TClient( char *newAccount, char *newName, char *newPhone)
        {
        strcpy( account, newAccount );
        strcpy( name, newName );
        strcpy( phone, newPhone );
        };
};

class TClientCollection : public TNSCollection
{

public:

    TClientCollection (ccIndex aLimit, ccIndex aDelta ) :
        TNSCollection( aLimit, aDelta ) {}
    virtual ccIndex insert( TClient *tc )
	    { return TNSCollection::insert( tc ); }
        // overrides TNSCollection::insert( void *item )
        // In a more complete application, you would also override
        // at, indexOf, remove, free,... so that they all
        // handle TClient pointers

    void printAll();
    void searchArea( char *areaToFind );

};

static void print( void *c, void * )
{
    TClient *tc = (TClient *)c;
    cout << setiosflags( ios::left )
         << setw(10) << tc->account
         << setw(20) << tc->name
         << setw(16) << tc->phone
         << endl;
}

void TClientCollection::printAll()  // print info for all clients
{
    cout << endl << "Client List:" << endl;
    forEach( &print, 0 ); // call print for each client
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

void TClientCollection::searchArea( char *areaToFind )
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

    TClientCollection clientList( 50, 10 );    // limit is 50, delta is 10

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
    return 0;

};


