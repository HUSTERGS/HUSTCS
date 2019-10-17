// ObjectWindows - (C) Copyright 1992 by Borland International

#include <owl.h>
#include <dialog.h>

#include <stdlib.h>

#include "cursor.h"

class TCursorDlg : public TDialog {
	BOOL bUpdateDialog;
public:
	TCursorDlg( PTWindowsObject AParent, LPSTR AName )
		: TDialog( AParent, AName ), bUpdateDialog( FALSE ) {}
	void SetDlgItemText( int nIDDlgItem, LPSTR lpString );
	virtual LPSTR GetClassName( void );
	virtual void GetWindowClass( WNDCLASS& );
	virtual void Ok( TMessage& Msg ) = [ ID_FIRST + IDOK ];
	virtual void Cancel( TMessage& Msg ) = [ ID_FIRST + IDCANCEL ];
	virtual void WMInitDialog( TMessage& Msg )
		= [ WM_FIRST + WM_INITDIALOG ];
   virtual void CloseWindow();
	void UpdateDialog( void );
   BOOL ShouldUpdate() { return bUpdateDialog; }
};

/*
	This function sets the caption or text of a control in the dialog
	box. The control whose text is to be set is specified by
	nIDDlgItem.
*/
void TCursorDlg::SetDlgItemText( int nDlgItemID, LPSTR lpString )
{
	::SetDlgItemText( HWindow, nDlgItemID, lpString );
}

void TCursorDlg::WMInitDialog( TMessage& )
{
	SetupWindow();
	bUpdateDialog = TRUE;
}

// Override the meaning of 'OK' to do nothing.
void TCursorDlg::Ok( TMessage& ) {}
void TCursorDlg::Cancel( TMessage& ) {}

void TCursorDlg::CloseWindow()
{
	bUpdateDialog = FALSE;       // disable updating
	TWindowsObject::CloseWindow();
}

LPSTR TCursorDlg::GetClassName( void )
{
	return( "CursorDlg" );
}

void TCursorDlg::GetWindowClass( WNDCLASS& AWndClass )
{
	TDialog::GetWindowClass( AWndClass );
	AWndClass.hIcon = LoadIcon( GetApplication()->hInstance, "CursorDlg" );
}

inline BOOL operator != ( POINT& p1, POINT& p2 )
{
	if ( ( p1.x != p2.x ) || ( p1.y != p2.y ) )
		return TRUE;
	else
		return FALSE;
}

inline BOOL operator != ( RECT& r1, RECT& r2 )
{
	if ( ( r1.left != r2.left ) || ( r1.top != r2.top ) ||
	     ( r1.right != r2.right ) || ( r1.bottom != r2.bottom ) )
		return TRUE;
	else
		return FALSE;
}


void TCursorDlg::UpdateDialog( void )
{
	POINT Point;
	static POINT prevPoint = { -1, -1 };
	static HWND hPrevWnd = (HWND)-1, hPrevParent = (HWND)-1;
	HWND hWndFromPt, hParent = hPrevParent;
	HWND hFocus;
	static HWND hPrevFocus = (HWND)-1;
	static RECT Rect, prevRect = { -1, -1, -1, -1 };
	char szBuffer[26];

	if ( bUpdateDialog )
	{
		GetCursorPos( &Point );

		// If the cursor position has changed...
		if ( Point != prevPoint )
		{
			prevPoint = Point;
			SetDlgItemText( IDD_SX,	ltoa( Point.x, szBuffer, 10 ) );
			SetDlgItemText( IDD_SY,	ltoa( Point.y, szBuffer, 10 ) );
// Turn off warning that struct is passed by value in call to WindowFromPoint.
#pragma warn -stv
			if ( ( hWndFromPt = WindowFromPoint( Point ) ) != 0 )
#pragma warn +stv
			{
				// Set the x and y coordinates in terms
				// of the client area of the underlying window.
				ScreenToClient( hWndFromPt, &Point );
				SetDlgItemText( IDD_WX,
					ltoa( Point.x, szBuffer, 10 ) );
				SetDlgItemText( IDD_WY,
					ltoa( Point.y, szBuffer, 10 ) );

				if ( ( hParent = GetParent( hWndFromPt ) ) != 0 )
				{
					// Set the x and y coordinates in
					// terms of the client area of
					// the parent of the window.
					Point = prevPoint;
					ScreenToClient( hParent, &Point );
					SetDlgItemText( IDD_PX,
						ltoa( Point.x, szBuffer, 10 ) );
					SetDlgItemText( IDD_PY,
						ltoa( Point.y, szBuffer, 10 ) );
				}
				else
				{
					// If the window has no parent,
					// leave the x and y fields blank.
					SetDlgItemText( IDD_PX, "" );
					SetDlgItemText( IDD_PY, "" );
				}
			}
			// If there is no window at the current point,
			// the x and y coordinates should be blank
			// in the dialog box.
			else
			{
				SetDlgItemText( IDD_WX, "" );
				SetDlgItemText( IDD_WY, "" );
			}
			// Update the display of the handle of the
			// underlying window if necessary.
			if ( hWndFromPt != hPrevWnd )
				SetDlgItemText( IDD_HW,
					ltoa( (LONG)hWndFromPt, szBuffer, 10 ) );
			// If the parent window has changed,
			// update the display of its handle.
			if ( hParent != hPrevParent )
			{
				if( ( hWndFromPt == 0 ) || ( hParent == 0 ) )
					SetDlgItemText( IDD_HP, "" );
				else
					SetDlgItemText( IDD_HP,
						ltoa( (LONG)hParent, szBuffer, 10 ) );
			}
			else
			{
				// If there is no underlying window,
				// do not display a handle for a parent.
				if ( hWndFromPt == 0 )
					SetDlgItemText( IDD_HP, "" );
			}
			hPrevWnd = hWndFromPt;
			hPrevParent = hParent;
		}

		// Update the focus display fields if necessary.
		hFocus = GetFocus();
		if ( hFocus == 0 )
		{
			if( hFocus != hPrevFocus )
			{
				SetDlgItemText( IDD_HF, "" );
				SetDlgItemText( IDD_LEFT, "" );
				SetDlgItemText( IDD_TOP, "" );
				SetDlgItemText( IDD_RIGHT, "" );
				SetDlgItemText( IDD_BOTTOM, "" );
			}
		}
		else
		{
			if( hFocus != hPrevFocus )
			{
				SetDlgItemText( IDD_HF,
					ltoa( (LONG)hFocus, szBuffer, 10 ) );
			}
			GetWindowRect( hFocus, &Rect );
			if ( Rect != prevRect )
			{
				prevRect = Rect;
				SetDlgItemText( IDD_LEFT,
					ltoa( Rect.left, szBuffer, 10 ) );
				SetDlgItemText( IDD_TOP,
					ltoa( Rect.top, szBuffer, 10 ) );
				SetDlgItemText( IDD_RIGHT,
					ltoa( Rect.right, szBuffer, 10 ) );
				SetDlgItemText( IDD_BOTTOM,
					ltoa( Rect.bottom, szBuffer, 10 ) );
			}
		}
		hPrevFocus = hFocus;
	}
}

class CursorApplication : public TApplication {
public:
	CursorApplication(LPSTR name, HINSTANCE hInstance,
			  HINSTANCE hPrevInstance, LPSTR lpCmd,
		          int nCmdShow)
	        : TApplication(name, hInstance,
			       hPrevInstance, lpCmd, nCmdShow) {};
	virtual void InitMainWindow( void );
        virtual void IdleAction(void);
};

void CursorApplication::InitMainWindow()
{
	MainWindow = new TCursorDlg( NULL, "CursorDlg" );
}

void CursorApplication::IdleAction( void )
{
  if ( MainWindow && ((TCursorDlg *)MainWindow)->ShouldUpdate() )
          ((TCursorDlg*)MainWindow)->UpdateDialog();
}

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
		   LPSTR lpCmd, int nCmdShow)
{
	CursorApplication CursorApp ("Cursor Location", hInstance,
				     hPrevInstance, lpCmd, nCmdShow);
	CursorApp.Run();
	return ( CursorApp.Status );
}
