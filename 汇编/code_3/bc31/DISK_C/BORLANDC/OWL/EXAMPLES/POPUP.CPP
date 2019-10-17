// ObjectWindows - (C) Copyright 1992 by Borland International

#include <owl.h>
#include <window.h>

#include <string.h>

const int CM_WINDOW = 100;

enum TSubWinType { SW_CHILD, SW_POPPARENT, SW_POPNOPARENT };

class TSubWindow : public TWindow
{
private:
	TSubWinType SubWinType;
public:
	TSubWindow( PTWindowsObject AParent, TSubWinType ASubWinType );
	virtual ~TSubWindow( void );
	virtual void Paint( HDC PaintDC, PAINTSTRUCT& PaintStruct );
};

typedef TSubWindow* PSubWindow;

class TMainWindow : public TWindow
{
public:
	TMainWindow( LPSTR ATitle );
	void ShowSubWindow( PTWindowsObject AParent, TSubWinType ASubWinType );
	virtual void WMInitMenu( TMessage& Msg ) = [ WM_FIRST + WM_INITMENU ];
	virtual void CMChild( TMessage& Msg ) = [ CM_FIRST + CM_WINDOW + SW_CHILD ];
	virtual void CMPopParent( TMessage& Msg ) = [ CM_FIRST + CM_WINDOW + SW_POPPARENT ];
	virtual void CMPopNoParent( TMessage& Msg ) = [ CM_FIRST + CM_WINDOW + SW_POPNOPARENT ];
};

typedef TMainWindow* PMainWindow;

class TPopupApp : public TApplication
{
public:
	TPopupApp(LPSTR name, HINSTANCE hInstance, HINSTANCE hPrevInstance,
		  LPSTR lpCmd, int nCmdShow)
		  : TApplication(name, hInstance, hPrevInstance,
			         lpCmd, nCmdShow) {};
	virtual void InitMainWindow( void );
   virtual BOOL CanClose();
};

PSubWindow SubWinPtr[] = { NULL, NULL, NULL };

LPSTR SubWinTitle[] = { "Child Window", "Popup with Parent",
	"Popup without Parent" };

long SubWinStyle[] = {
    WS_CHILD | WS_OVERLAPPEDWINDOW | WS_VISIBLE,
    WS_POPUP | WS_OVERLAPPEDWINDOW | WS_VISIBLE,
    WS_POPUP | WS_OVERLAPPEDWINDOW | WS_VISIBLE };

POINT SubWinPos[] = { { 10, 10 }, { 34, 72 }, { 54, 92 } };

LPSTR SubWinText[] = {
    "Child windows cannot be moved outside their parent window.  When " \
      "minimized, a child window's icon resides within the parent " \
      "window.",
    "Popup windows can be moved outside their parent window.  A popup " \
      "with a parent is always displayed in front of the parent, " \
      "even when the parent is focused.  To test this, click on the " \
      "parent window.  When minimized, popup icons reside on the desktop.",
    "Popup windows can be moved outside their parent window.  A popup " \
      "without a parent allows the parent to be brought to the front " \
      "when focused. To test this, click on the parent window.  When " \
      "minimized, popup icons reside on the desktop." };

TSubWindow::TSubWindow( PTWindowsObject AParent, TSubWinType ASubWinType ) :
	TWindow( AParent, SubWinTitle[ ASubWinType ] )
{
	Attr.Style = SubWinStyle[ ASubWinType ];
	Attr.X = SubWinPos[ ASubWinType ].x;
	Attr.Y = SubWinPos[ ASubWinType ].y;
	Attr.W = 300;
	Attr.H = 150;
	SubWinType = ASubWinType;
}

TSubWindow::~TSubWindow( void )
{
	SubWinPtr[ SubWinType ] = NULL;
}

void TSubWindow::Paint( HDC PaintDC, PAINTSTRUCT& )
{
	LPSTR s;
	RECT rect;

	GetClientRect( HWindow, &rect );
	InflateRect( &rect, -2, 0 );
	s = SubWinText[ SubWinType ];
	DrawText( PaintDC, s, _fstrlen( s ), &rect, DT_WORDBREAK );
}

TMainWindow::TMainWindow( LPSTR ATitle ) : TWindow( NULL, ATitle )
{
	Attr.X = 0;
	Attr.Y = 0;
	Attr.W = 400;
	Attr.H = 215;
	AssignMenu( "COMMANDS" );
}

void TMainWindow::ShowSubWindow( PTWindowsObject AParent,
	TSubWinType ASubWinType )
{
	if ( SubWinPtr[ ASubWinType ] == NULL )
		SubWinPtr[ ASubWinType ] = PSubWindow(
			GetApplication()->MakeWindow(
				new TSubWindow( AParent, ASubWinType) ) );
	else
		SetFocus( SubWinPtr[ ASubWinType ]->HWindow );
}

void TMainWindow::WMInitMenu( TMessage& )
{
	WORD MenuState;

	for ( int i = SW_CHILD; i <= SW_POPNOPARENT; i++ )
	{
		if ( SubWinPtr[i] == NULL )
			MenuState = MF_UNCHECKED;
		else
			MenuState = MF_CHECKED;
		CheckMenuItem( GetMenu(HWindow), CM_WINDOW + i, MenuState );
	}
}

void TMainWindow::CMChild( TMessage& )
{
	ShowSubWindow( this, SW_CHILD );
}

void TMainWindow::CMPopParent( TMessage& )
{
	ShowSubWindow( this, SW_POPPARENT );
}

void TMainWindow::CMPopNoParent( TMessage& )
{
	ShowSubWindow( NULL, SW_POPNOPARENT );
}

void TPopupApp::InitMainWindow( void )
{
	MainWindow = new TMainWindow( "Parent Window" );
}

BOOL TPopupApp::CanClose(void)
{
   // In order to avoid debugging kernel warning messages, ensure that
   // the parentless popup window is destroyed before exiting the
   // application.
   if (SubWinPtr[SW_POPNOPARENT] != NULL )
      SubWinPtr[SW_POPNOPARENT]->CloseWindow();
   return(TRUE);
}

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
		   LPSTR lpCmd, int nCmdShow)
{
	TPopupApp PopupApp("Popup", hInstance, hPrevInstance,
			   lpCmd, nCmdShow);
	PopupApp.Run();
	return ( PopupApp.Status );
}
