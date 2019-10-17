// (C) Copyright 1991, 1992 by Borland International

#define STRICT

#include <windows.h>
#include <custcntl.h>
#include "bitbtnco.h"

// "local" variable offsets into the window structure
#define OF_RESERVED		0		// Used by the dialog manager
#define OF_STATE		2
#define OF_DOWNBITS		4
#define OF_UPBITS		6
#define OF_FOCUPBITS	        8
#define OF_SIZE			10

// Width of the line bordering the bitmap of the button
#define BD_BORDERWIDTH	1

// State masks for the state of the button
#define BS_DISABLED		0x0001
#define BS_FOCUS		0x0002
#define BS_KEYDOWN		0x0004
#define BS_MOUSEDOWN	0x0008
#define BS_MOUSEUPDOWN	0x0010
#define BS_DEFAULT		0x0020

// Color definitions
#define CO_GRAY			0x00C0C0C0L

static HINSTANCE hInstance;

/* GetAppInstance ----------------------------------------------- *
 *	 Returns a handle to the current client application.      *
 * -------------------------------------------------------------- */
HINSTANCE GetAppInstance(void)
{
  return (HINSTANCE) GlobalHandle(_SS);
}

/* IsWorkshopWindow --------------------------------------------- *
 *	Returns true if the window belongs to Resource Workshop.      *
 *	Used to determine if the control is being edited; allowing    *
 *	the LoadResRW function to be called.                          *
 * -------------------------------------------------------------- */
static BOOL IsWorkshopWindow(HWND hWnd)
{
	HWND	hParent;
	char	szClassName[81];

	hParent = hWnd;
	do
	{
		hWnd = hParent;
		hParent = GetParent(hWnd);
	}
	while ( hParent );
	GetClassName(hWnd, szClassName, sizeof(szClassName));
	return ( lstrcmpi(szClassName, "rwswnd") == 0);
}

/* LoadResRW ---------------------------------------------------- *
 *   Load a resource from Resource Workshop. Initialized by       *
 *   ListClasses below.                                           *
 * -------------------------------------------------------------- */
static LPFNLOADRES LoadResRW;

/* GetDInColors ------------------------------------------------- *
 *   Return the number of colors in the given number of bits.	  *
 * -------------------------------------------------------------- */
static int GetDInColors(int BitCount)
{
	switch( BitCount )
	{
		case 1:
		case 3:
		case 4:
		case 8:
			return	1 << BitCount;
		default:
			return 	0;
	}
}

/* LoadBitmapRW ------------------------------------------------- *
 *   Load a bitmap from Resource Workshop.  *MUST* be called from *
 *   inside resource workshop (IsWorkshopWindow must be true).    *
 * -------------------------------------------------------------- */
static HBITMAP LoadBitmapRW(LPSTR szTitle)
{
	HBITMAP hRet = NULL;
        HGLOBAL  hRes = LoadResRW((LPCSTR)RT_BITMAP, (LPCSTR)szTitle);

	if ( hRes )
	{
		LPBITMAPINFOHEADER pBits = (LPBITMAPINFOHEADER) GlobalLock(hRes);

                // only Windows format bitmaps

		if ( pBits->biSize == sizeof(BITMAPINFOHEADER) )
		{
			int nColors = GetDInColors(pBits->biBitCount);
			HDC hDC = GetDC(NULL);

                        // number of colors can be less than returned above

                        if ( pBits->biClrUsed)
                          nColors = (int)pBits->biClrUsed;

			if ( hDC )
			{
				hRet = CreateDIBitmap(hDC, pBits, CBM_INIT,
					((LPSTR) (pBits + 1)) + (nColors * sizeof(RGBQUAD)),
					(LPBITMAPINFO) pBits, DIB_RGB_COLORS);
				ReleaseDC(NULL, hDC);
			}
			GlobalUnlock(hRes);
			GlobalFree(hRes);
		}
	}

	return hRet;
}

/* Get, SetWord, State, DownBits, UpBits, FocBits, GetState ----- *
 *   Utility macros to implement pseudo button local variables.	  *
 * -------------------------------------------------------------- */
#define Get(Ofs)				GetWindowWord(hWnd, Ofs)
#define SetWord(Ofs, Val)		SetWindowWord(hWnd, Ofs, Val)
#define State					Get(OF_STATE)
#define DownBits				Get(OF_DOWNBITS)
#define UpBits					Get(OF_UPBITS)
#define FocUpBits				Get(OF_FOCUPBITS)
#define GetState(AState)		((State & (AState)) == (AState))

/* Paint -------------------------------------------------------- *
 *	Paint the button.  Called in response to a WM_PAINT message   *
 *	and whenever the button changes state (called by Repaint).    *
 * -------------------------------------------------------------- */
static void Paint(HWND hWnd, HDC hDC)
{
	HBITMAP hBits;

	// Get the appropriate bitmap for the button state
	if ( (State & (BS_MOUSEDOWN | BS_KEYDOWN)) && !GetState(BS_MOUSEUPDOWN) )
                hBits = (HBITMAP)DownBits;
	else
		if ( GetState(BS_FOCUS) )
                        hBits = (HBITMAP)FocUpBits;
		else
                        hBits = (HBITMAP)UpBits;

	// Draw the button border
	{
		RECT	Frame;
		int		Height, Width;
		HBRUSH	hBorderBrush, hOldBrush;

		// Get window extent
		GetClientRect(hWnd, &Frame);
		Height = Frame.bottom - Frame.top;
		Width = Frame.right - Frame.left;

		// Select brush
		if ( GetState(BS_DEFAULT) )
			hBorderBrush = GetStockObject(BLACK_BRUSH);
		else
			hBorderBrush = GetStockObject(WHITE_BRUSH);
		hOldBrush = SelectObject(hDC, hBorderBrush);

		// Blt the brush
		PatBlt(hDC, Frame.left, Frame.top, Width, BD_BORDERWIDTH, PATCOPY);
		PatBlt(hDC, Frame.left, Frame.top, BD_BORDERWIDTH, Height, PATCOPY);
		PatBlt(hDC, Frame.left, Frame.bottom - BD_BORDERWIDTH, Width,
			BD_BORDERWIDTH, PATCOPY);
		PatBlt(hDC, Frame.right - BD_BORDERWIDTH, Frame.top, BD_BORDERWIDTH,
			Height, PATCOPY);

		// Clean up scope
		SelectObject(hDC, hOldBrush);
	}

	// Draw the bitmap
	{
                HDC     hMemDC          =       CreateCompatibleDC(hDC);
		HBITMAP	hOldBitmap	=	SelectObject(hMemDC, hBits);
		BITMAP	Bitmap;

		// Blt the image
		GetObject(hBits, sizeof(Bitmap), (LPSTR) &Bitmap);
		if ( GetState(BS_DISABLED) )
		{
			// Blt disabled
			HBITMAP hOldBrush = SelectObject(hDC, CreateSolidBrush(CO_GRAY));
			LOGBRUSH lbLogBrush;

			PatBlt(hDC, BD_BORDERWIDTH, BD_BORDERWIDTH, Bitmap.bmWidth,
				Bitmap.bmHeight, PATCOPY);
			DeleteObject(SelectObject(hDC, hOldBrush));

			lbLogBrush.lbStyle = BS_PATTERN;
                        lbLogBrush.lbHatch = (int)LoadBitmap(hInstance,
				MAKEINTRESOURCE(BT_DISABLEBITS));;
			hOldBrush = SelectObject(hDC, CreateBrushIndirect(&lbLogBrush));

			BitBlt(hDC, BD_BORDERWIDTH, BD_BORDERWIDTH, Bitmap.bmWidth,
			  Bitmap.bmHeight, hMemDC, 0, 0, 0x00A803A9UL); // DPSoa
			DeleteObject(SelectObject(hDC, hOldBrush));
                        DeleteObject((HGDIOBJ)lbLogBrush.lbHatch);
		}
		else
			// Blt enabled
			BitBlt(hDC, BD_BORDERWIDTH, BD_BORDERWIDTH, Bitmap.bmWidth,
				Bitmap.bmHeight, hMemDC, 0, 0, SRCCOPY);

		// Clean up
		SelectObject(hDC, hOldBitmap);
		DeleteDC(hMemDC);
	}
}

/* Repaint ------------------------------------------------------ *
 *   Repaint the button. Called whenever the button changes       *
 *   state.                                                       *
 * -------------------------------------------------------------- */
static void Repaint(HWND hWnd)
{
	HDC		hDC		= 	GetDC(hWnd);

	Paint(hWnd, hDC);
	ReleaseDC(hWnd, hDC);
}

/* SetState ----------------------------------------------------- *
 *   Sets the value of a state bit.  If the word changes value    *
 *   the button is repainted.                                     *
 * -------------------------------------------------------------- */
// Make it look like GetState
#define SetState(AState, Enable) Set_State(hWnd, AState, Enable)

static void Set_State(HWND hWnd, int AState, BOOL Enable)
{
	WORD	OldState	= 	State;
	WORD	NewState	=	Enable ? OldState | AState : OldState & ~AState;

	if (NewState != OldState)
	{
		SetWord(OF_STATE, NewState);
		Repaint(hWnd);
	}
}

/* InMe --------------------------------------------------------- *
 *	Returns true if the given point is within the border of       *
 *	the button.                                                   *
 * -------------------------------------------------------------- */
static BOOL InMe(HWND hWnd, POINT Point)
{
	RECT	R;

	GetClientRect(hWnd, &R);
	InflateRect(&R, -BD_BORDERWIDTH, -BD_BORDERWIDTH);
	return PtInRect(&R, Point);
}

/* ButtonPressed ------------------------------------------------ *
 *	Called when the button is pressed by either the keyboard or   *
 *	by the mouse.                                                 *
 * -------------------------------------------------------------- */
static void ButtonPressed(HWND hWnd)
{
	SetState(BS_MOUSEDOWN | BS_MOUSEUPDOWN | BS_KEYDOWN, FALSE);
	SendMessage(GetParent(hWnd), WM_COMMAND, (WPARAM) GetDlgCtrlID(hWnd),
	  (LPARAM) MAKELONG(hWnd, BN_CLICKED));
}

/* LoadBits ----------------------------------------------------- *
 *	 Load the bitmap for the button or the "NO BITMAP" version    *
 *	 if it does not exist.                                        *
 * -------------------------------------------------------------- */
static void LoadBits(HWND hWnd, WORD Wrd, WORD MapNumber)
{
	HBITMAP	hMapBits = LoadBitmap(hInstance, MAKEINTRESOURCE(MapNumber));

	if ( !hMapBits )
		if ( IsWorkshopWindow(hWnd) )
                        hMapBits = LoadBitmapRW((LPSTR)MAKEINTRESOURCE(MapNumber));
		else
                        hMapBits = LoadBitmap(GetAppInstance(), MAKEINTRESOURCE(MapNumber));

	if ( !hMapBits )
		hMapBits = LoadBitmap(hInstance, MAKEINTRESOURCE(MapNumber -
		  Get(GWW_ID)));

        SetWord((int)Wrd, (WORD)hMapBits);
}

/* BitButtonWinFn ----------------------------------------------- *
 *	 Button window procedure.                                     *
 * -------------------------------------------------------------- */
LRESULT CALLBACK BitButtonWinFn(HWND hWnd, UINT wMessage,
        WPARAM wParam, LPARAM lParam)
{
	DWORD	result = 0;

	switch( wMessage )
	{
		case WM_CREATE:
		{
			HDC 	hDC 		= GetDC(NULL);
			int		BitsNumber;
			BITMAP	Bitmap;
			RECT	Rect;
			POINT	Pt;
			DWORD	style;

			// Detect EGA vs. VGA monitor
			if ( GetSystemMetrics(SM_CYSCREEN) < 480 ||
					GetDeviceCaps(hDC, NUMCOLORS) < 16 )
				BitsNumber = 2000 + Get(GWW_ID);
			else
				BitsNumber = 1000 + Get(GWW_ID);
			ReleaseDC(NULL, hDC);

			// Load bitmaps from resource
			LoadBits(hWnd, OF_UPBITS, BitsNumber);
			LoadBits(hWnd, OF_DOWNBITS, BitsNumber + 2000);
			LoadBits(hWnd, OF_FOCUPBITS, BitsNumber + 4000);

			// Adjust size of buttons to size of bitmap
                        GetObject((HBITMAP)DownBits, sizeof(Bitmap), (LPSTR) &Bitmap);
			GetWindowRect(hWnd, &Rect);
			Pt.x = Rect.left;
			Pt.y = Rect.top;
			ScreenToClient(((LPCREATESTRUCT) lParam)->hwndParent, &Pt);
			MoveWindow(hWnd, Pt.x, Pt.y, Bitmap.bmWidth + BD_BORDERWIDTH * 2,
			  Bitmap.bmHeight + BD_BORDERWIDTH * 2, FALSE);

			// Initialize button state flags
			style = ((LPCREATESTRUCT) lParam)->style;
			if ( (style & 0x1F) == BS_DEFPUSHBUTTON )
				SetState(BS_DEFAULT, TRUE);
			if ( style & WS_DISABLED )
				SetState(BS_DISABLED, TRUE);

			break;
		}

		case WM_NCDESTROY:
		{
			// Destroy all saved bitmaps before the button is destroyed.

			result = DefWindowProc(hWnd, wMessage, wParam, lParam);
                        DeleteObject((HGDIOBJ)UpBits);
                        DeleteObject((HGDIOBJ)DownBits);
                        DeleteObject((HGDIOBJ)FocUpBits);

			break;
		}

		case WM_PAINT:
		{
			PAINTSTRUCT PS;

			BeginPaint(hWnd, &PS);
			Paint(hWnd, PS.hdc);
			EndPaint(hWnd, &PS);

			break;
		}

		case WM_ERASEBKGND:
		{
			// Squelch the painting of the background to eliminate flicker
			break;
		}

		case WM_ENABLE:
		{
			SetState(BS_DISABLED, wParam == 0);

			break;
		}

		case WM_SETFOCUS:
		{
			SetState(BS_FOCUS, TRUE);

			break;
		}

		case WM_KILLFOCUS:
		{
			SetState(BS_FOCUS, FALSE);

			break;
		}

		case WM_KEYDOWN:
		{
			if ( wParam == ' '  && ! GetState(BS_MOUSEDOWN) &&
					!GetState(BS_KEYDOWN) )
				SetState(BS_KEYDOWN, TRUE);

			break;
		}

		case WM_KEYUP:
		{
			if ( wParam == ' ' && GetState(BS_KEYDOWN) )
				ButtonPressed(hWnd);

			break;
		}

		case WM_LBUTTONDBLCLK:
		case WM_LBUTTONDOWN:
		{
			if ( InMe(hWnd, *((LPPOINT) &lParam)) && !GetState(BS_KEYDOWN) )
			{
				if ( GetFocus() != hWnd )
					SetFocus(hWnd);
				SetState(BS_MOUSEDOWN, TRUE);
				SetCapture(hWnd);
			}

			break;
		}

		case WM_MOUSEMOVE:
		{
			if ( GetState(BS_MOUSEDOWN) )
				SetState(BS_MOUSEUPDOWN, !InMe(hWnd, *((LPPOINT) &lParam)));

			break;
		}

		case WM_LBUTTONUP:
		{
			if ( GetState(BS_MOUSEDOWN) )
			{
				ReleaseCapture();
				if ( !GetState(BS_MOUSEUPDOWN) )
					ButtonPressed(hWnd);
				else
					SetState(BS_MOUSEDOWN | BS_MOUSEUPDOWN, FALSE);
			}

			break;
		}

		/**** Handling the next four messages is what, at least for the dialog
		  manager, makes a push button a push button. ****/
		case WM_GETDLGCODE:
		{
			/* Sent by the dialog manager to determine the control kind of
			a child window.  Returning DLGC_DEFPUSHBUTTON or
			DLGC_UNDEFPUSHBUTTON causes the dialog manager to treat the
			control like a button, sending the BM_SETSTYLE message to
			move the default button style to the currently focused button.

			The DLGC_BUTTON constant is not documented by Microsoft
			(however, it is documented for OS/2 PM, and appears to work
			the same). If this constant is or'd in, the Windows dialog
			manager will take care of all accelerator key processing,
			sending BM_GETSTATE and BM_SETSTATE messages when an
			accelerator key is pressed. There is a side effect to using
			the message, however, the dialog manager messes with the word
			at offset 0 from the user window words. */

			result = GetState(BS_DEFAULT) ?
				DLGC_DEFPUSHBUTTON | DLGC_BUTTON:
				DLGC_UNDEFPUSHBUTTON | DLGC_BUTTON;

			break;
		}

		case BM_GETSTATE:
		{
			result = GetState(BS_KEYDOWN);

			break;
		}

		case BM_SETSTATE:
		{
			SetState(BS_KEYDOWN, wParam);

			break;
		}

		case BM_SETSTYLE:
		{
			SetState(BS_DEFAULT, wParam == BS_DEFPUSHBUTTON);

			break;
		}

		default:
		{
			result = DefWindowProc(hWnd, wMessage, wParam, lParam);

			break;
		}
	}

	return result;
}

/* ============================================================== *
 * Custom control interface routines.							  *
 * ============================================================== */

/* BitBtnInfo --------------------------------------------------- *
 *	 Return the information about the capabilities of the         *
 *	 bit button class.                                            *
 * -------------------------------------------------------------- */
HGLOBAL CALLBACK BitBtnInfo(void)
{
	HGLOBAL hInfo =		GlobalAlloc(GHND,
		sizeof(RWCTLINFO));

	if ( hInfo )
	{
		LPRWCTLINFO	Info =	(LPRWCTLINFO) GlobalLock(hInfo);

		Info->wVersion	=	0x0100;		// Version 1.00
		Info->wCtlTypes = 	2;			// 2 types
		lstrcpy(Info->szClass, "BitButton");
		lstrcpy(Info->szTitle, "Button");

		// Normal (un-default) push button type
		Info->Type[0].wWidth  = 63 | 0x8000;
		Info->Type[0].wHeight = 39 | 0x8000;
		lstrcpy(Info->Type[0].szDescr, "Push Button");
		Info->Type[0].dwStyle = BS_PUSHBUTTON | WS_TABSTOP;
		Info->Type[0].hToolBit = LoadBitmap(hInstance,
			MAKEINTRESOURCE(BT_UNDEFBITS));
		Info->Type[0].hDropCurs = LoadCursor(hInstance,
			MAKEINTRESOURCE(CR_UNDEFCURS));

		// Default push button type
		Info->Type[1].wWidth  = 63 | 0x8000;
		Info->Type[1].wHeight = 39 | 0x8000;
		lstrcpy(Info->Type[1].szDescr, "Default Push Button");
		Info->Type[1].dwStyle = BS_DEFPUSHBUTTON | WS_TABSTOP;
		Info->Type[1].hToolBit = LoadBitmap(hInstance,
			MAKEINTRESOURCE(BT_DEFBITS));
		Info->Type[1].hDropCurs = LoadCursor(hInstance,
			MAKEINTRESOURCE(CR_DEFCURS));


		GlobalUnlock(hInfo);
	}

	return hInfo;
}

typedef struct
{
       	HGLOBAL 	CtlStyle;
	LPFNSTRTOID     StrToId;
	LPFNIDTOSTR	IdToStr;
} PARAMREC, FAR * LPPARAMREC;

/* BitBtnStyleDlg ----------------------------------------------- *
 *	 Style dialog's dialog hook.  Used by the dialog and called   *
 *	 when the control is double-clicked inside the dialog         *
 *	 editor.                                                      *
 * -------------------------------------------------------------- */
BOOL FAR PASCAL BitBtnStyleDlg(HWND hWnd, UINT wMessage,
	WPARAM wParam, LPARAM lParam)
{
	BOOL result = TRUE;

	switch( wMessage )
	{
		case WM_INITDIALOG:
		{
                        HGLOBAL         hRec    =       (HGLOBAL)LOWORD(lParam);
			LPPARAMREC  Rec		=	(LPPARAMREC) GlobalLock(hRec);
			LPCTLSTYLE	Style	=	(LPCTLSTYLE) GlobalLock(Rec->CtlStyle);
			char		S[81];

			// Save hRec for future use in other messages.
			SetProp(hWnd, "Prop", hRec);

			// SetCaption
			SetDlgItemText(hWnd, ID_CAPTION, Style->szTitle);

			// Set control id
			(*Rec->IdToStr)(Style->wId, S, sizeof(S));
			SetDlgItemText(hWnd, ID_CONTROLID, S);

			// Set type radio buttons
			CheckRadioButton(hWnd, ID_DEFAULTBUTTON, ID_PUSHBUTTON,
			  (Style->dwStyle & 0xF) == BS_DEFPUSHBUTTON ? ID_DEFAULTBUTTON :
			  ID_PUSHBUTTON);

			// Initialize Tab Stop check box
			CheckDlgButton(hWnd, ID_TABSTOP,
				(Style->dwStyle & WS_TABSTOP) != 0);

			// Initialize Disabled check box
			CheckDlgButton(hWnd, ID_DISABLED,
				(Style->dwStyle & WS_DISABLED) != 0);

			// Initialize Group check box
			CheckDlgButton(hWnd, ID_GROUP,
				(Style->dwStyle & WS_GROUP) != 0);

			// Clean-up scope
			GlobalUnlock(Rec->CtlStyle);
			GlobalUnlock(hRec);

			break;
		}

		case WM_COMMAND:
		{
			switch( wParam )
			{
				case IDCANCEL:
				{
					EndDialog(hWnd, FALSE);

					break;
				}

				case IDOK:
				{
					HGLOBAL		hRec	=	GetProp(hWnd, "Prop");
					LPPARAMREC      Rec		=	(LPPARAMREC) GlobalLock(hRec);
					LPCTLSTYLE	Style	=	(LPCTLSTYLE) GlobalLock(Rec->CtlStyle);
					char		S[81];

					// Get caption
					GetDlgItemText(hWnd, ID_CAPTION, Style->szTitle,
						sizeof(Style->szTitle));

					// Get control id
					GetDlgItemText(hWnd, ID_CONTROLID, S, sizeof(S));
					Style->wId = HIWORD( (*Rec->StrToId)(S));

					// Get button type
					Style->dwStyle = IsDlgButtonChecked(hWnd,
						ID_DEFAULTBUTTON) ? BS_DEFPUSHBUTTON : BS_PUSHBUTTON;

					// Get tab stop
					if ( IsDlgButtonChecked(hWnd, ID_TABSTOP) )
						Style->dwStyle |= WS_TABSTOP;

					// Get disabled
					if ( IsDlgButtonChecked(hWnd, ID_DISABLED) )
						Style->dwStyle |= WS_DISABLED;

					// Get group
					if ( IsDlgButtonChecked(hWnd, ID_GROUP) )
						Style->dwStyle |= WS_GROUP;

					// Clean-up scope
					GlobalUnlock(Rec->CtlStyle);
					GlobalUnlock(hRec);
					EndDialog(hWnd, TRUE);

					break;
				}

				default:
				{
					result = 0;

					break;
				}
			}

			break;
		}

		case WM_DESTROY:
		{
			RemoveProp(hWnd, "Prop");

			break;
		}

		default:
		{
			result = 0;

			break;
		}
	}

	return result;
}

/* BitBtnStyle -------------------------------------------------- *
 *	 The function will bring up a dialog box to modify the style  *
 *	 of the button.  Called when the button is double-clicked in  *
 *	 the dialog editor.                                           *
 * -------------------------------------------------------------- */
BOOL CALLBACK BitBtnStyle(HWND hWnd, HGLOBAL hCtlStyle,
	LPFNSTRTOID StrToId, LPFNIDTOSTR IdToStr)
{
	BOOL	result 	= 	FALSE;
	HGLOBAL	hRec    =       GlobalAlloc(GHND, sizeof(PARAMREC));

	if ( hRec )
	{
		LPPARAMREC	Rec 	= (LPPARAMREC) GlobalLock(hRec);
		HWND		hFocus  = GetFocus();

		// Setup the parameter record
		Rec->IdToStr = IdToStr;
		Rec->StrToId = StrToId;
		Rec->CtlStyle = hCtlStyle;
		GlobalUnlock(hRec);

		// Invoke the dialog box
		result = DialogBoxParam(hInstance, MAKEINTRESOURCE(ID_BUTTONSTYLE),
                        hWnd, (DLGPROC) BitBtnStyleDlg, (DWORD) hRec);

		// Restore focused window since Windows does not do it
		if ( hFocus )
			SetFocus(hFocus);

		GlobalFree(hRec);
	}

	return result;
}

/* BitBtnFlags -------------------------------------------------- *
 *	 Called to decompose the style double word into the .RC       *
 *	 script expression that it represents.  This only needs to    *
 *	 decompose the style bits added to the style double word,     *
 *	 it need not decompose, for example, the ws_XXX bits.         *
 *	 The expression returned must be a valid .RC expression       *
 *	 (i.e. C syntax, case sensitive).                             *
 * -------------------------------------------------------------- */
#pragma warn -par
UINT CALLBACK BitBtnFlag(DWORD Style, LPSTR Buff,
	UINT BuffLength)
{
	lstrcpy(Buff, (Style & 0xF) == BS_DEFPUSHBUTTON ? "BS_DEFPUSHBUTTON" :
		"BS_PUSHBUTTON");

	return 0;
}
#pragma warn .par

/* ListClasses ------------------------------------------------------ *
 *	 Called by Resource Workshop to retrieve the information      *
 *	 necessary to edit the custom controls contained in this DLL. *
 *	 This is an alternative to the Microsoft xxxStyle convention. *
 * ------------------------------------------------------------------ */
#pragma argsused       // szAppName, wVersion, and fnEdit intentionally unused
HGLOBAL CALLBACK ListClasses(LPSTR szAppName,
	UINT wVersion, LPFNLOADRES fnLoad, LPFNEDITRES fnEdit)
{
	HGLOBAL hClasses = GlobalAlloc(GHND,
		sizeof(int) + sizeof(RWCTLCLASS));

	LoadResRW = fnLoad;

	if ( hClasses )
	{
		LPCTLCLASSLIST	Classes	= (LPCTLCLASSLIST) GlobalLock(hClasses);

		Classes->nClasses = 1;
		Classes->Classes[0].fnRWInfo  = BitBtnInfo;
		Classes->Classes[0].fnRWStyle = BitBtnStyle;
		Classes->Classes[0].fnFlags   = BitBtnFlag;
		lstrcpy(Classes->Classes[0].szClass, "BitButton");
		GlobalUnlock(hClasses);
	}

	return hClasses;
}


/* LibMain --------------------------------------------------------*
 *    Called by Windows when the library is loaded.  Registers the *
 *	  Custom control class.					   *					  *
 * ----------------------------------------------------------------*/

static WNDCLASS Class = {
/* Style */			CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS | CS_GLOBALCLASS,
/* lpfnWndProc */       BitButtonWinFn,
/* cbClsExtra */	0,
/* cbWndExtra */	OF_SIZE,
/* hInstance */		0, 				// Initialized in LibMain
/* hIcon */			NULL,			// No icon
/* hCursor */		NULL,			// No cursor
/* hbrBackground */	NULL,			// Default background brush
/* lpszMenuName */	NULL,			// No menu
/* lpszClassName */	"BitButton"
};

#pragma argsused // wDataSeg, cbHeapSize, lpszCmdLine not used
int FAR PASCAL LibMain(HINSTANCE hInst, WORD wDataSeg, WORD cbHeapSize,
                        LPSTR lpszCmdLine)
{
	hInstance = hInst;

	// Register the "BitButton" class
	Class.hInstance = hInstance;
	RegisterClass(&Class);

	return 1;
}
