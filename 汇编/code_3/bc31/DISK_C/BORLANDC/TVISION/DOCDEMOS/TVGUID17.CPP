/*---------------------------------------------------------*/
/*                                                         */
/*   Turbo Vision 1.0                                      */
/*   TVGUID17.CPP Demo Source File                         */
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

static void print( void *c, void * )
{
    TClient *tc = (TClient *)c;
    cout << setiosflags( ios::left )
         << setw(10) << tc->account
         << setw(20) << tc->name
         << setw(16) << tc->phone
         << endl;
}

void printAll( TNSCollection *c )  // print info for all clients
{
    cout << endl << "Client List:" << endl;
    c->forEach( &print, 0 ); // call print for each client
}

Boolean areaMatch( void *c, void *ph )
{
    char *areaToFind = (char *)ph;
    TClient *tc = (TClient *)c;

    // seek match in first 5 chars: "(xxx)"
    if( strncmp( areaToFind, tc->phone, 5 ) == 0 )
        return True;
    else
        return False;
}

void searchArea( TNSCollection *c, char *areaToFind )
{
    TClient *foundClient =
        (TClient *)(c->firstThat( &areaMatch, areaToFind ));
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
    TNSCollection clientList( 50, 10 );    // limit is 50, delta is 10

    clientList.insert( new TClient("90-167", "Smith, Zelda",
               "(800) 555-1212" ));
    clientList.insert( new TClient("90-160", "Johnson, Agatha",
               "(302) 139-8913" ));
    clientList.insert( new TClient("90-177", "Smitty, John",
               "(406) 987-4321"));
    clientList.insert( new TClient("91-100", "Anders, Smitty",
               "(406) 111-2222"));

    printAll( &clientList );
    searchArea( &clientList, "(406)" );
    return 0;
};


