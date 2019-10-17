// ObjectWindows - (C) Copyright 1992 by Borland International

#ifndef __DDECLIEN_H
#define __DDECLIEN_H

// OWL headers
#include <owl.h>
#include <dialog.h>

// Windows header
#include <dde.h>

/*
	TDDEClient is an interface object for a DDE client.
	This was made a dialog window for the 'ProgTalk' demo because
	that is	a convenient type for a window with several controls.
*/

class TDDEClient : public TDialog
{
	protected:
		HWND ServerWindow;
		WORD PendingMessage;

	public:

		/*
			DDE window constructor.
			Clear the DDE server window handle and the
			pending DDE message ID.
		*/
		TDDEClient( PTWindowsObject Parent, LPSTR AName )
			: TDialog( Parent, AName ),
			ServerWindow( 0 ),
			PendingMessage( 0 )
		{}

		/*
			SetupWindow is called right after the DDE window
			is created to initiate the DDE conversation.
			This must be defined in a derived class in order
			to correctly determine the DDE server and topic.
		*/
		virtual void SetupWindow( void ) = 0;
		/*
			Return window class name. This name corresponds
			to the class name specified for the DDE dialog
			in the resource file.
		*/
		virtual LPSTR GetClassName( void )
		{
			return "DDEClient";
		}
		void InitiateDDE( char* AppName, char* TopicName );
		void TerminateDDE( void );

		virtual void WMDDEAck( TMessage& Msg )
			= [ WM_FIRST + WM_DDE_ACK ];
		virtual void WMDDETerminate( TMessage& Msg )
			= [ WM_FIRST + WM_DDE_TERMINATE ];
		virtual void WMClose( TMessage& Msg )
			= [ WM_FIRST + WM_CLOSE ];
		virtual void Cancel( TMessage& Msg )
			= [ ID_FIRST + IDCANCEL ];
};

inline void TDDEClient::Cancel( TMessage& Msg )
{
	TDDEClient::WMClose( Msg );
}

#endif
