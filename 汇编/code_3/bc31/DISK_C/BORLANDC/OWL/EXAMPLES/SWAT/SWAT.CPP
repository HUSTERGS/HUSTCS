// ObjectWindows - (C) Copyright 1992 by Borland International
//
// swat.cpp

#include <owl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "swat.h"

const int MissedPoints	= -2;
const int HitPoints	= 5;
const int MissedCritter	= -1;
const int CritterSize	= 72;
const int MaxPop	= 35;
const int MaxLiveTime	= 30;

POINT Holes[ 5 ] = { { 10, 10 }, { 200, 10 },
    { 100, 100 }, { 10, 200 }, { 200, 200 } };

class TApp : public TApplication
{
public:
	TApp( LPSTR name, HINSTANCE hInstance,
		  HINSTANCE hPrevInstance, LPSTR lpCmd,
		  int nCmdShow)
	        : TApplication(name, hInstance,
			       hPrevInstance, lpCmd, nCmdShow) {};
	virtual void InitMainWindow( void );
};


struct THole {
	WORD Time;
	BOOL Dead;
};

class TGameWindow;
typedef TGameWindow* PGameWindow;

class TGameWindow : public TWindow
{
private:
	HBITMAP Live, Dead, GameOver, ScoreBoard;
	HCURSOR CursorDown, CursorUp;
	int Counter, Score, LiveTime, Frequence, GameTime;
	int Hits, Miss, Escaped;
	BOOL IsGameOver, IsPause;
	THole HoleInfo[ 5 ];
public:
	TGameWindow( PTWindowsObject AParent, LPSTR Title );
	virtual void About( TMessage& Message ) = [ CM_FIRST + IDM_ABOUT ];
	void DrawBMP( HDC DC, int X, int Y, HBITMAP BitMap );
	void DrawGameOver( HDC DC );
	void DrawCritter( HDC DC, int CritterNumber );
	void DrawScoreBoard( HDC DC );
	virtual void GetWindowClass( WNDCLASS& WndClass );
	virtual void Options( TMessage& Message ) = [ CM_FIRST + IDM_OPTION ];
	virtual void Paint( HDC PaintDC, PAINTSTRUCT& PaintInfo );
	virtual void Pause( TMessage& Message ) = [ CM_FIRST + IDM_PAUSE ];
	virtual void ResetGame( TMessage& Message ) =  [ CM_FIRST + IDM_RESET ];
	virtual void SetupWindow( void );
	virtual void Stop( TMessage& Message ) = [ CM_FIRST + IDM_STOP ];
	void StopGame( void );
	virtual void WMDestroy( TMessage& Message ) = [ WM_FIRST + WM_DESTROY ];
	virtual void WMLButtonDown( TMessage& Message ) = [ WM_FIRST + WM_LBUTTONDOWN ];
	virtual void WMLButtonUp( TMessage& Message ) = [ WM_FIRST + WM_LBUTTONUP ];
	virtual void WMTimer( TMessage& Message ) = [ WM_FIRST + WM_TIMER ];
	virtual void WMSize( TMessage& Message ) = [ WM_FIRST + WM_SIZE ];
	void WriteScore( HDC DC );

	friend class TOptionDialog;
};

class TOptionDialog : public TDialog
{
public:
	TOptionDialog( PTWindowsObject AParent, LPSTR AName ) :
		TDialog( AParent, AName ) {}
	virtual BOOL CanClose(void);
	virtual void SetupWindow( void );
	virtual void WMHScroll( TMessage& Message ) = [ WM_FIRST + WM_HSCROLL ];
};

// --------------- TOptionDialog ---------------

void TOptionDialog::SetupWindow( void )
{
	char str[ 10 ];

	TWindowsObject::SetupWindow();
	SetScrollRange( GetDlgItem( HWindow, IDD_LIVETIMESB ), SB_CTL, 1,
		MaxLiveTime, FALSE );
	SetScrollRange( GetDlgItem( HWindow, IDD_POPSB ), SB_CTL, 1,
		MaxPop, FALSE );
	SetScrollPos( GetDlgItem( HWindow, IDD_LIVETIMESB ), SB_CTL,
		MaxLiveTime + 1 - PGameWindow( Parent )->LiveTime, TRUE );
	SetScrollPos( GetDlgItem( HWindow, IDD_POPSB ), SB_CTL,
		MaxPop + 6 - PGameWindow( Parent )->Frequence, TRUE );
	itoa( PGameWindow( Parent )->GameTime / 10, str, 10 );
	SetDlgItemText( HWindow, IDD_INPUTEDITBOX, str );
}

void TOptionDialog::WMHScroll( TMessage& Message )
{
	int Pos;
	HWND Scroll;
	const int PageStep = 10;

	Scroll = (HWND)Message.LP.Hi;
	Pos = GetScrollPos( Scroll, SB_CTL );
	switch ( Message.WParam )
	{
		case SB_LINEUP:
			Pos--;
			break;
		case SB_LINEDOWN:
			Pos++;
			break;
		case SB_PAGEUP:
			Pos -= PageStep;
			break;
		case SB_PAGEDOWN:
			Pos += PageStep;
			break;
		case SB_THUMBPOSITION:
		case SB_THUMBTRACK:
			Pos = Message.LP.Lo;
			break;
	}
	SetScrollPos( Scroll, SB_CTL, Pos, TRUE );
}

BOOL TOptionDialog::CanClose()
{
    BOOL NoError;
    int Time;

    PGameWindow( Parent )->LiveTime = MaxLiveTime + 1 -
	    GetScrollPos( GetDlgItem( HWindow, IDD_LIVETIMESB ), SB_CTL );
    PGameWindow( Parent )->Frequence = MaxPop + 1 -
	    GetScrollPos( GetDlgItem( HWindow, IDD_POPSB ), SB_CTL ) + 5;

    Time = GetDlgItemInt( HWindow, IDD_INPUTEDITBOX, &NoError, FALSE ) * 10;
    if ( ( NoError ) && ( Time > 0 ) )
    {
	    PGameWindow( Parent )->GameTime = Time;
	    return TRUE;
    }
    else
    {
	    MessageBox( HWindow,
		    "Game Time must be a number greater than 0!",
		    "Error",
		    MB_OK );
	    return FALSE;
    }
}

// --------------- TGameWindow -----------------

TGameWindow::TGameWindow( PTWindowsObject AParent, LPSTR Title ) :
	TWindow( AParent, Title )
{
	Attr.W = 282;
	Attr.H = 400;
	Attr.Style = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
	randomize();
};

void TGameWindow::About( TMessage& )
{
        GetApplication()->ExecDialog(new TDialog(this, "About"));
}

void TGameWindow::DrawBMP( HDC DC, int X, int Y, HBITMAP BitMap )
{
	HDC MemDC;
	BITMAP bm;
	BOOL MadeDC;

	if ( DC == 0 )
	{
		DC = GetDC( HWindow );
		MadeDC = TRUE;
	}
	else
		MadeDC = FALSE;
	MemDC = CreateCompatibleDC( DC );
	SelectObject( MemDC, BitMap );
	GetObject( GameOver, sizeof( bm ), ( LPSTR ) &bm );
	BitBlt( DC, X, Y, bm.bmWidth, bm.bmHeight, MemDC, 0, 0, SRCCOPY );
	DeleteDC( MemDC );
	if ( MadeDC )
		ReleaseDC( HWindow, DC );
}

void TGameWindow::DrawGameOver( HDC DC )
{
	DrawBMP( DC, 10, 70, GameOver );
}

void TGameWindow::DrawCritter( HDC DC, int CritterNumber )
{
	BOOL MadeDC;
	HDC MemDC;

	if ( DC == 0 )
	{
		DC = GetDC( HWindow );
		MadeDC = TRUE;
	}
	else
		MadeDC = FALSE;

	if ( HoleInfo[ CritterNumber ].Time != 0 )
	{
		MemDC = CreateCompatibleDC( DC );
		if ( HoleInfo[ CritterNumber ].Dead )
			SelectObject( MemDC, Dead );
		else
			SelectObject( MemDC, Live );
		BitBlt( DC, Holes[ CritterNumber ].x,
			Holes[ CritterNumber ].y,
			CritterSize, CritterSize, MemDC, 0, 0, SRCCOPY );
		DeleteDC( MemDC );
	}
	else
	{
		SelectObject( DC, GetStockObject( GRAY_BRUSH ) );
		SelectObject( DC, GetStockObject( NULL_PEN ) );
		Rectangle( DC, Holes[ CritterNumber ].x,
			Holes[ CritterNumber ].y,
			Holes[ CritterNumber ].x + CritterSize + 1,
			Holes[ CritterNumber ].y + CritterSize + 1 );
	}
	if ( MadeDC )
		ReleaseDC( HWindow, DC );
}

void TGameWindow::DrawScoreBoard( HDC DC )
{
	DrawBMP( DC, 11, 214, ScoreBoard );
}

void TGameWindow::GetWindowClass( WNDCLASS& WndClass )
{
	TWindow::GetWindowClass( WndClass );
	CursorUp = LoadCursor( GetApplication()->hInstance, "Malet" );
	WndClass.style = 0;
	WndClass.hCursor = CursorUp;
	WndClass.hbrBackground = (HBRUSH)GetStockObject( GRAY_BRUSH );
	WndClass.lpszMenuName = "SWATMENU";
	WndClass.hIcon = LoadIcon( GetApplication()->hInstance, "Critter" );
}

void TGameWindow::Options( TMessage& )
{
        GetApplication()->ExecDialog(new TOptionDialog(this, "OptionDlg"));
}

void TGameWindow::Paint( HDC PaintDC, PAINTSTRUCT& )
{
	DrawScoreBoard( PaintDC );
	WriteScore( PaintDC );
	if ( IsGameOver )
		DrawGameOver( PaintDC );
	else {
		for( int i = 0; i < 5; i++ )
			DrawCritter( PaintDC, i );
	}
}

void TGameWindow::Pause( TMessage& )
{
	if ( IsGameOver )
		return;
	if ( IsPause )
	{
		IsPause = FALSE;
		ModifyMenu( GetMenu( HWindow ), IDM_PAUSE, MF_BYCOMMAND,
			IDM_PAUSE, "&Pause" );
		DrawMenuBar( HWindow );
		if ( SetTimer( HWindow, 1, 100, NULL ) == 0 )
		{
			MessageBox( HWindow, "No Timers Left", "Error", MB_OK );
			exit( 1 );
		}
	}
	else
	{
		IsPause = TRUE;
		KillTimer( HWindow, 1 );
		ModifyMenu( GetMenu( HWindow ), IDM_PAUSE, MF_BYCOMMAND,
			IDM_PAUSE, "&Continue" );
		DrawMenuBar( HWindow );
	}
}

void TGameWindow::ResetGame( TMessage& )
{
	ModifyMenu( GetMenu( HWindow ), IDM_OPTION, MF_BYCOMMAND | MF_GRAYED,
		IDM_OPTION, "&Options" );
	ModifyMenu( GetMenu( HWindow ), IDM_PAUSE, MF_BYCOMMAND,
		IDM_PAUSE, "&Pause" );
	ModifyMenu( GetMenu( HWindow ), IDM_STOP, MF_BYCOMMAND,
		IDM_STOP, "&Stop" );
	DrawMenuBar( HWindow );
	InvalidateRect( HWindow, FALSE, TRUE );
	if ( SetTimer( HWindow, 1, 100, NULL ) == 0 )
	{
		MessageBox( HWindow, "No Timers Left", "Error", MB_OK );
		exit( 1 );
	}
	memset( HoleInfo, 0, sizeof( HoleInfo ) );
	Counter = 0;
	Score = 0;
	Hits = 0;
	Miss = 0;
	Escaped = 0;
	IsGameOver = FALSE;
	if ( IsPause )
	{
		IsPause = FALSE;
		ModifyMenu( GetMenu( HWindow ), IDM_PAUSE, MF_BYCOMMAND,
			IDM_PAUSE, "&Pause" );
		DrawMenuBar( HWindow );
	}
}

void TGameWindow::SetupWindow( void )
{
	CursorDown = LoadCursor( GetApplication()->hInstance, "MaletDown" );
	Live = LoadBitmap( GetApplication()->hInstance, "Live" );
	Dead = LoadBitmap( GetApplication()->hInstance, "Dead" );
	GameOver = LoadBitmap( GetApplication()->hInstance, "GameOver" );
	ScoreBoard = LoadBitmap( GetApplication()->hInstance, "Board" );
	IsGameOver = TRUE;
	IsPause = FALSE;
	LiveTime = 10;
	Frequence = 20;
	Counter = 0;
	Score = 0;
	Hits = 0;
	Miss = 0;
	Escaped = 0;
	GameTime = 150;		// fifteen seconds
}

void TGameWindow::Stop( TMessage& )
{
	StopGame();
}

void TGameWindow::StopGame( void )
{
	KillTimer( HWindow, 1 );
	ModifyMenu( GetMenu( HWindow ), IDM_OPTION, MF_BYCOMMAND,
		IDM_OPTION, "&Options" );
	ModifyMenu( GetMenu( HWindow ), IDM_PAUSE, MF_BYCOMMAND | MF_GRAYED,
		IDM_PAUSE, "&Pause" );
	ModifyMenu( GetMenu( HWindow ), IDM_STOP, MF_BYCOMMAND | MF_GRAYED,
		IDM_STOP, "&Stop" );
	IsPause = FALSE;
	DrawMenuBar( HWindow );
	IsGameOver = TRUE;
	InvalidateRect( HWindow, FALSE, TRUE );
	Counter = GameTime;
}

void TGameWindow::WMDestroy( TMessage& Message )
{
	DeleteObject( Live );
	DeleteObject( Dead );
	DeleteObject( GameOver );
	DeleteObject( ScoreBoard );
	KillTimer( HWindow, 1 );
	TWindow::WMDestroy( Message );
}

void TGameWindow::WMLButtonDown( TMessage& Message )
{
	POINT Point;
	RECT R;
	BOOL Hit;

	SetClassWord( HWindow, GCW_HCURSOR, (WORD)CursorDown );
	GetCursorPos( &Point );
	SetCursorPos( Point.x, Point.y );
	if ( IsGameOver || IsPause )
		return;
	Hit = FALSE;
	for( int i = 0; i < 5; i++ )
	{
		if (!( ( HoleInfo[ i ].Dead ) || ( HoleInfo[ i ].Time == 0 ) ) )
		{
			R.top = Holes[ i ].x;
			R.left = Holes[ i ].y;
			R.bottom = R.top + CritterSize;
			R.right = R.left + CritterSize;
			Point.x = Message.LP.Hi;
			Point.y = Message.LP.Lo;
#pragma warn -stv
			if ( PtInRect( &R, Point ) )
#pragma warn +stv
			{
				Score += HitPoints;
				HoleInfo[ i ].Dead = TRUE;
				HoleInfo[ i ].Time = Counter + 2 * LiveTime;
				Hits++;
				Hit = TRUE;
				DrawCritter( 0, i );
			}
		}
	}
	if ( !Hit )
	{
		Score += MissedPoints;
		Miss++;
	}
	WriteScore( 0 );
}

void TGameWindow::WMLButtonUp( TMessage& )
{
	POINT Point;

	SetClassWord( HWindow, GCW_HCURSOR, (WORD)CursorUp );
	GetCursorPos( &Point );
	SetCursorPos( Point.x, Point.y );
}

void TGameWindow::WMTimer( TMessage& )
{
	int i;

	Counter++;
	i = random( Frequence );
	if ( i < 5 )
	{
		if ( HoleInfo[ i ].Time == 0 )
		{
			HoleInfo[ i ].Time = Counter + LiveTime;
			HoleInfo[ i ].Dead = FALSE;
			DrawCritter( 0, i );
		}
	}
	for ( i = 0; i < 5; i++ )
	{
		if ( ( Counter > HoleInfo[ i ].Time ) &&
			( HoleInfo[ i ].Time != 0 ) )
		{
			HoleInfo[ i ].Time = 0;
			if ( ! HoleInfo[ i ].Dead )
			{
				Score += MissedCritter;
				Escaped++;
			}
			DrawCritter( 0, i );
		}
	}
	WriteScore( 0 );
	if ( Counter >= GameTime )
		StopGame();
}

void TGameWindow::WMSize( TMessage& )
{
	if ( IsGameOver )
		return;
	if ( IsIconic( HWindow ) )
		KillTimer( HWindow, 1 );
	else
		if ( ! IsPause )
			if ( SetTimer( HWindow, 1, 100, NULL ) == 0 )
			{
				MessageBox( HWindow, "No Timers Left",
					"Error", MB_OK );
				exit( 1 );
			}
}

void TGameWindow::WriteScore( HDC DC )
{
	char s[ 21 ];
	BOOL MadeDC;

	if ( DC == 0 )
	{
		MadeDC = TRUE;
		DC = GetDC( HWindow );
	}
	else
		MadeDC = FALSE;
	SelectObject( DC, CreateSolidBrush( 0x8080 ) );
	SelectObject( DC, GetStockObject( NULL_PEN ) );
	SetBkMode( DC, TRANSPARENT );

	// Timer
	Rectangle( DC, 130, 252, 163, 275 );
	sprintf( s, "%3.3d", GameTime - Counter );
	s[ 3 ] = s[ 2 ];
	s[ 2 ]= '.';
	TextOut( DC, 130, 252, s, 4 );

	// Hits
	Rectangle( DC, 40, 310, 71, 329 );
	sprintf( s, "%3.3d", Hits );
	TextOut( DC, 40, 310, s, strlen( s ) );

	// Misses
	Rectangle( DC, 77, 310, 117, 329 );
	sprintf( s, "%3.3d", Miss );
	TextOut( DC, 77, 310, s, strlen( s ) );

	// Escaped
	Rectangle( DC, 133, 310, 174, 329 );
	sprintf( s, "%3.3d", Escaped );
	TextOut( DC, 133, 310, s, strlen( s ) );

	// Total
	Rectangle( DC, 203, 310, 239, 328 );
	sprintf( s, "%3.3d", Score );
	TextOut( DC, 203, 310, s, strlen( s ) );

	DeleteObject( SelectObject( DC, GetStockObject( GRAY_BRUSH ) ) );
	SelectObject( DC, GetStockObject( NULL_PEN ) );
	if ( MadeDC )
		ReleaseDC( HWindow, DC );
}

// --------------- TApp ------------------------

void TApp::InitMainWindow( void )
{
	MainWindow = new TGameWindow( NULL, "Swat!" );
}

// -------------Main Program--------------------

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
		   LPSTR lpCmd, int nCmdShow)
{
	TApp App( "SwatGame", hInstance, hPrevInstance,
		lpCmd, nCmdShow);
	App.Run();
	return ( App.Status );
}
