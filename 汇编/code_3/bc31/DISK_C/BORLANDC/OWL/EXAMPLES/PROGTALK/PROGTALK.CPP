// ObjectWindows - (C) Copyright 1992 by Borland International

// OWL headers
#include <owl.h>
#include <dialog.h>
#include <listbox.h>
#include <inputdia.h>

// Standard headers
#include <string.h>

// Dialog item IDs
#include "progtalk.h"

// Class definition of TDDEClient
#include "ddeclien.h"

/*
	TDDEProgTalk is the main window of the application.
	It engages in a DDE conversation with the Program Manager
	to create program groups with a
	user specified list of program items.
*/
class TDDEProgTalk : public TDDEClient
{
	private:
		PTListBox ListBox;

	public:

		/*
			TDDEProgTalk window constructor.
			Create a TListBox object to represent the
			dialog's list box.
		*/
		TDDEProgTalk( PTWindowsObject Parent, LPSTR AName )
			: TDDEClient( Parent, AName )
		{
			ListBox = new TListBox( this, ID_LISTBOX );
		}
		/*
			SetupWindow is called right after the DDE window
			is created.  Initiate the DDE conversation.
		*/
		virtual void SetupWindow( void )
		{
                        TDialog::SetupWindow();
			InitiateDDE( "PROGMAN", "PROGMAN" );
		}
		virtual void AddItem( TMessage& Msg )
			= [ ID_FIRST + ID_ADDITEM ];
		virtual void DeleteItem( TMessage& Msg )
			= [ ID_FIRST + ID_DELETEITEM ];
		virtual void ClearItems( TMessage& Msg )
			= [ ID_FIRST + ID_CLEARITEMS ];
		virtual void CreateGroup( TMessage& Msg )
			= [ ID_FIRST + ID_CREATEGROUP ];
		virtual void WMDDEAck( TMessage& Msg )
			= [ WM_FIRST + WM_DDE_ACK ];
};

/*
	Add item button response method. Bring up the Add item dialog to
	input a program item string, and add that item to the list box.
*/

void TDDEProgTalk::AddItem( TMessage& )
{
	char Name[ 64 ] = "";

	if (GetApplication()->ExecDialog( new TInputDialog( this,
		"Add an Item to the Group",
		"Item &name:",
		Name,
		sizeof( Name ) ) ) != IDCANCEL )
			ListBox->AddString( Name );
}

/*
	Delete item button response method. Delete the currently selected
	item in the list box.
*/

void TDDEProgTalk::DeleteItem( TMessage& )
{
	ListBox->DeleteString( ListBox->GetSelIndex() );
}

// Clear items button response method. Clear the list box.

void TDDEProgTalk::ClearItems( TMessage& )
{
	ListBox->ClearList();
}

/*
	Create group button response method. Bring up the Create Group
	dialog to input the program group name. Then, if a DDE link has
	been established (ServerWindow != 0) and there is no DDE message
	currently pending (PendingMessage == 0), build a list of Program
	Manager commands, and submit the commands using a WM_DDE_EXECUTE
	message. To build the command list, first calculate the total
	length of the list, then allocate a global memory block of that
	size, and finally store the command list as a null-terminated
	string in the memory block.
*/

void TDDEProgTalk::CreateGroup( TMessage& )
{
	LPSTR lpCreateGroup = "[CreateGroup(%s)]";
	LPSTR lpAddItem = "[AddItem(%s)]";

	BOOL Executed;
	int i, len;
	HANDLE HCommands;
	LPSTR lpName, lpCommands;
	char Name[ 64 ] = "";

	if (GetApplication()->ExecDialog( new TInputDialog( this,
		"Create a new group",
		"&Name of new group:",
		Name,
		sizeof( Name ) ) ) != IDCANCEL )
	{
		Executed = False;
		if ( ( ServerWindow != 0 ) && ( PendingMessage == 0 ) )
		{
			// Subtract 2 for the '%s' in 'lpCreateGroup'
			// plus 1 for null terminator.
			len = strlen( Name ) + _fstrlen( lpCreateGroup ) - 2 + 1;
			int count = ListBox->GetCount();
			for ( i = 0; i < count; i++ )
				// Subtract 2 for the '%s' in 'lpAddItem'.
				len += ListBox->GetStringLen( i ) +
					_fstrlen( lpAddItem ) - 2;
			HCommands = (HANDLE)GlobalAlloc( GHND | GMEM_DDESHARE, len );
			if ( HCommands != 0 )
			{
				lpName = Name;
				lpCommands = (LPSTR)GlobalLock( HCommands );
				wsprintf( lpCommands, lpCreateGroup,
					lpName );
				int count = ListBox->GetCount();
				for ( i = 0; i < count; i++ )
				{
					ListBox->GetString( Name, i );
					lpCommands += _fstrlen( lpCommands );
					wsprintf( lpCommands, lpAddItem,
						lpName );
				}
				GlobalUnlock( HCommands );
				if ( PostMessage( ServerWindow,
					WM_DDE_EXECUTE,
					(WPARAM)HWindow,
					MAKELONG( 0, HCommands ) ) )
				{
					PendingMessage = WM_DDE_EXECUTE;
					Executed = True;
				}
				else
					GlobalFree( HCommands );
			}
		}
		if ( ! Executed )
			MessageBox( HWindow,
				"Program Manager DDE execute failed.",
				"Error",
				MB_ICONEXCLAMATION | MB_OK );
	}
}

/*
	WM_DDE_ACK message response method.
	If the current DDE message is a	WM_DDE_EXECUTE,
	free the command string memory block and focus our
	window (as usual), and then clear the list box.
*/

void TDDEProgTalk::WMDDEAck( TMessage& Msg )
{
	TDDEClient::WMDDEAck( Msg );
	if ( PendingMessage == WM_DDE_EXECUTE )
		ListBox->ClearList();
}


/*
	TDDEApp is the application object. It creates a main window of type
	TDDEProgTalk.
*/

class TDDEApp : public TApplication
{
	public:
		TDDEApp(LPSTR AName, HINSTANCE hInstance,
			HINSTANCE hPrevInstance, LPSTR lpCmd,
			int nCmdShow)
	        : TApplication(AName, hInstance,
			       hPrevInstance, lpCmd, nCmdShow) {};
		virtual void InitMainWindow( void );
};

// Create a DDE window as the application's main window.
void TDDEApp::InitMainWindow( void )
{
	MainWindow = new TDDEProgTalk( 0, "ProgTalk" );
}

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
		   LPSTR lpCmd, int nCmdShow)
{
	TDDEApp DDEApp ( "ProgTalk", hInstance, hPrevInstance,
		lpCmd, nCmdShow);
	DDEApp.Run();
	return ( DDEApp.Status );
}
