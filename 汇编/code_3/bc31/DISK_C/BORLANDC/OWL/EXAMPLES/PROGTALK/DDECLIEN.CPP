#include "ddeclien.h"

/*
	Initiate a DDE conversation. Bring up a
	message box if the server does not respond to the
	WM_DDE_INITIATE message.
*/

void TDDEClient::InitiateDDE( char* AppName, char* TopicName )
{
	ATOM AppAtom, TopicAtom;

	PendingMessage = WM_DDE_INITIATE;
	AppAtom = GlobalAddAtom( AppName );
	TopicAtom = GlobalAddAtom( TopicName );
	SendMessage( HWND( 0xFFFF ), WM_DDE_INITIATE, (WPARAM)HWindow,
		MAKELONG( AppAtom, TopicAtom ) );
	GlobalDeleteAtom( AppAtom );
	GlobalDeleteAtom( TopicAtom );
	PendingMessage = 0;
	if ( ServerWindow == 0 )
		MessageBox( HWindow,
			"Cannot establish DDE link to DDE Server.",
			"Error",
			MB_ICONEXCLAMATION | MB_OK );
}

/*
	Terminate the DDE conversation. Send the WM_DDE_TERMINATE message
	only if the server window still exists.
*/

void TDDEClient::TerminateDDE( void )
{
	HWND W = ServerWindow;
	ServerWindow = 0;
	if ( IsWindow( W ) )
		PostMessage( W, WM_DDE_TERMINATE, (WPARAM)HWindow, 0 );
}

/*
	WM_DDE_ACK message response method. If the current DDE message
	is a WM_DDE_INITIATE, store off the window handle of the window
	that responded. If more than one window responds, terminate all
	conversations but the first. If the current DDE message is a
	WM_DDE_EXECUTE, free the command string memory block, and focus our
	window.
*/

void TDDEClient::WMDDEAck( TMessage& Msg )
{
	switch( PendingMessage )
	{
		case WM_DDE_INITIATE:

			if ( ServerWindow == 0 )
				ServerWindow = (HWND)Msg.WParam;
			else
				PostMessage( (HWND)Msg.WParam,
					WM_DDE_TERMINATE,
					(WPARAM)HWindow,
					0L );
			GlobalDeleteAtom( Msg.LP.Lo );
			GlobalDeleteAtom( Msg.LP.Hi );
			break;

		case WM_DDE_EXECUTE:

			GlobalFree( (HGLOBAL)Msg.LP.Hi );
			PendingMessage = 0;
			SetFocus( HWindow );
			break;
	}
}

/*
	WM_DDE_TERMINATE message response method. If the window signaling
	termination is our server window, terminate
	the DDE conversation. Otherwise ignore the WM_DDE_TERMINATE.
*/

void TDDEClient::WMDDETerminate( TMessage& Msg )
{
	if ( (HWND)Msg.WParam == ServerWindow )
		TerminateDDE();
}

/*
	WM_CLOSE message response method. Terminate the DDE link and
	call the inherited WMClose.
*/

void TDDEClient::WMClose( TMessage& Msg )
{
	TerminateDDE();

	DWORD dwTime = GetCurrentTime();
	const DWORD DDE_TIMEOUT = 3000;
	MSG msg;
	while( GetCurrentTime() - dwTime < DDE_TIMEOUT )
	{
		if( PeekMessage( &msg, HWindow, WM_DDE_TERMINATE,
				WM_DDE_TERMINATE, PM_REMOVE ) )
			break;
	}

	TWindowsObject::WMClose( Msg );
}
