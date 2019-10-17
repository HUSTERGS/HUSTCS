/*------------------------------------------------------------------------
 * filename - easywin.cpp
 *
 * Easy Windows functions
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1991, 1992 by Borland International
 *      All Rights Reserved.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <mem.h>
#include <string.h>
#include <windows.h>

// These are dummy variables that are used because this module is
//   always linked in.

unsigned __hInstance;
unsigned __hPrev;
int      __cmdShow;

extern WORD  (*__ReadBufFPtr)(char *Buffer, WORD Count);
extern void  (*__WriteBufFPtr)(char *Buffer, WORD Count);

extern "C"
{
POINT _WindowOrg  = { CW_USEDEFAULT, CW_USEDEFAULT};
POINT _WindowSize = { CW_USEDEFAULT, CW_USEDEFAULT};

POINT _ScreenSize = { 80, 25 };            // Screen buffer dimensions
POINT _Cursor = { 0, 0 };                  // Cursor location
POINT _Origin = { 0, 0 };                  // Client area origin
char *_InactiveTitle = "(Inactive %s)";    // Inactive window title
BOOL  _AutoTracking = TRUE;                // Track cursor on Write?
BOOL  _CheckEOF = TRUE;                    // Allow Ctrl-Z for EOF?
BOOL  _CheckBreak = TRUE;                  // Allow Ctrl-C for break?

char  _WindowTitle[80];                    // Window title

void  _DoneEasyWin(void);

void  _WriteBuf(char *Buffer, WORD Count);
void  _WriteChar(char Ch);

BOOL  _KeyPressed(void);
int   _ReadKey(void);
WORD  _ReadBuf(char *Buffer, WORD Count);

void   gotoxy(int X, int Y);
int    wherex(void);
int    wherey(void);
void   clrscr(void);
void   clreol(void);

void  _CursorTo(int X, int Y);
void  _ScrollTo(int X, int Y);
void  _TrackCursor(void);
}

void __InitEasyWin(void);

// MinMaxInfo array

typedef POINT TMinMaxInfo[5];

// Scroll key definition record

typedef struct
{
    BYTE Key;
    BOOL Ctrl;
    BYTE SBar;
    BYTE Action;
} TScrollKey;

// Easy window procedure

long FAR PASCAL _export _EasyWinProc(HWND Window, UINT Message,
                                     WPARAM WParam, LONG LParam);

// CRT window class

static WNDCLASS CrtClass =
{
    CS_HREDRAW | CS_VREDRAW, ::_EasyWinProc, 0, 0, 0, 0, 0, 0,
    NULL, "BCEasyWin"
};

static int FirstLine  = 0;                   // First line in circular buffer
static int KeyCount   = 0;                   // Count of keys in KeyBuffer
static BOOL Created = FALSE;                 // Window created?
static BOOL Focused = FALSE;                 // Window focused?
static BOOL Reading = FALSE;                 // Reading from window?
static BOOL Painting = FALSE;                // Handling wm_Paint?

static HWND CrtWindow = 0;                   // CRT window handle
static char *ScreenBuffer;                   // Screen buffer pointer
static POINT ClientSize;                     // Client area dimensions
static POINT Range;                          // Scroll bar ranges
static POINT CharSize;                       // Character cell size
static int CharAscent;                       // Character ascent
static HDC DC;                               // Global device context
static PAINTSTRUCT PS;                       // Global paint structure
static HFONT SaveFont;                       // Saved device context font
static char KeyBuffer[64];                   // Keyboard type-ahead buffer

// Scroll keys table

const
  int ScrollKeyCount = 12;

const
  TScrollKey ScrollKeys[ScrollKeyCount]  =
      {
          { VK_LEFT,  FALSE, SB_HORZ, SB_LINEUP },
          { VK_RIGHT, FALSE, SB_HORZ, SB_LINEDOWN },
          { VK_LEFT,  TRUE,  SB_HORZ, SB_PAGEUP },
          { VK_RIGHT, TRUE,  SB_HORZ, SB_PAGEDOWN },
          { VK_HOME,  FALSE, SB_HORZ, SB_TOP },
          { VK_END,   FALSE, SB_HORZ, SB_BOTTOM },
          { VK_UP,    FALSE, SB_VERT, SB_LINEUP },
          { VK_DOWN,  FALSE, SB_VERT, SB_LINEDOWN },
          { VK_PRIOR, FALSE, SB_VERT, SB_PAGEUP },
          { VK_NEXT,  FALSE, SB_VERT, SB_PAGEDOWN },
          { VK_HOME,  TRUE,  SB_VERT, SB_TOP },
          { VK_END,   TRUE,  SB_VERT, SB_BOTTOM }
      };

// Return the smaller of two integer values

inline int Min(int X, int Y)
{
    return((X < Y)? X : Y);
}

//Return the larger of two integer values

inline int Max(int X, int Y)
{
    return((X > Y)? X: Y);
}

// Allocate device context

static void InitDeviceContext(void)
{
    if (Painting)
        DC = BeginPaint(CrtWindow, &PS);
    else
        DC = GetDC(CrtWindow);
    SaveFont = SelectObject(DC, GetStockObject(SYSTEM_FIXED_FONT));
}

// Release device context

static void DoneDeviceContext(void)
{
    SelectObject(DC, SaveFont);
    if (Painting)
        EndPaint(CrtWindow, &PS);
    else
        ReleaseDC(CrtWindow, DC);
}

// Show caret

static void ShowCursor(void)
{
    CreateCaret(CrtWindow, 0, CharSize.x, 2);
    SetCaretPos((_Cursor.x - _Origin.x) * CharSize.x,
                (_Cursor.y - _Origin.y) * CharSize.y + CharAscent);
    ShowCaret(CrtWindow);
}

// Hide caret

static void HideCursor(void)
{
    DestroyCaret();
}

// Update scroll bars

static void SetScrollBars(void)
{
    SetScrollRange(CrtWindow, SB_HORZ, 0, Max(1, Range.x), FALSE);
    SetScrollPos(CrtWindow, SB_HORZ, _Origin.x, TRUE);
    SetScrollRange(CrtWindow, SB_VERT, 0, Max(1, Range.y), FALSE);
    SetScrollPos(CrtWindow, SB_VERT, _Origin.y, TRUE);
}

// Terminate window

static void Terminate(void)
{
    if (Focused && Reading)
        HideCursor();
    exit(255);
}

// Set cursor position

void _CursorTo(int X, int Y)
{
    _Cursor.x = Max(0, Min(X, _ScreenSize.x - 1));
    _Cursor.y = Max(0, Min(Y, _ScreenSize.y - 1));
}

// Scroll window to given origin

void _ScrollTo(int X, int Y)
{
    if (Created)
        {
        X = Max(0, Min(X, Range.x));
        Y = Max(0, Min(Y, Range.y));
        if ((X != _Origin.x) || (Y != _Origin.y))
            {
            if (X != _Origin.x)
                SetScrollPos(CrtWindow, SB_HORZ, X, TRUE);
            if (Y != _Origin.y)
                SetScrollPos(CrtWindow, SB_VERT, Y, TRUE);
            ScrollWindow(CrtWindow,
                    (_Origin.x - X) * CharSize.x,
                    (_Origin.y - Y) * CharSize.y, NULL, NULL);
            _Origin.x = X;
            _Origin.y = Y;
            UpdateWindow(CrtWindow);
            }
        }
}

// Scroll to make cursor visible

void _TrackCursor(void)
{
    _ScrollTo(Max(_Cursor.x - ClientSize.x + 1,
               Min(_Origin.x, _Cursor.x)),
               Max(_Cursor.y - ClientSize.y + 1,
               Min(_Origin.y, _Cursor.y)));
}

// Return pointer to location in screen buffer

static char *ScreenPtr(int X, int Y)
{
    Y += FirstLine;
    if (Y >= _ScreenSize.y)
        Y -= _ScreenSize.y;
    return (ScreenBuffer+ (Y * _ScreenSize.x + X));
}

// Update text on cursor line

static void ShowText(int L, int R)
{
    if (L < R)
        {
        InitDeviceContext();
        TextOut(DC, (L - _Origin.x) * CharSize.x,
                    (_Cursor.y - _Origin.y) * CharSize.y,
                    ScreenPtr(L, _Cursor.y), R - L);
        DoneDeviceContext();
        }
}

// Write text buffer to window

static void NewLine(int& L, int& R)
{
    ShowText(L, R);
    L = 0;
    R = 0;
    _Cursor.x = 0;
    ++_Cursor.y;
    if (_Cursor.y == _ScreenSize.y)
        {
        --_Cursor.y;
        ++FirstLine;
        if (FirstLine == _ScreenSize.y)
            FirstLine = 0;
        memset(ScreenPtr(0, _Cursor.y), ' ', _ScreenSize.x);
        ScrollWindow(CrtWindow, 0, -CharSize.y, NULL, NULL);
        UpdateWindow(CrtWindow);
        }
}


void _WriteBuf(char *Buffer, WORD Count)
{
    int L, R;

    __InitEasyWin();
    L = _Cursor.x;
    R = _Cursor.x;
    while (Count > 0)
        {
        if (Buffer[0] == -1)
            Buffer[0] = ' ';
        switch (Buffer[0])
            {
            case 13:
            NewLine(L, R);
                break;
            case 10:
                break;
            case  9:
                do
                    {
                    *(ScreenPtr(_Cursor.x, _Cursor.y)) = ' ';
                    ++_Cursor.x;
                    if (_Cursor.x > R)
                        R = _Cursor.x;
                    if (_Cursor.x == _ScreenSize.x)
                        {
                        NewLine(L, R);
                        break;
                        }
                    } while (_Cursor.x % 8);
                break;
            case  8:
            if (_Cursor.x > 0)
                {
                --_Cursor.x;
                *(ScreenPtr(_Cursor.x, _Cursor.y)) = ' ';
                if (_Cursor.x < L )
                        L = _Cursor.x;
                }
                break;
            case  7:
                MessageBeep(0);
                break;
            default:
                *(ScreenPtr(_Cursor.x, _Cursor.y)) = Buffer[0];
                ++_Cursor.x;
                if (_Cursor.x > R)
                    R = _Cursor.x;
                if (_Cursor.x == _ScreenSize.x)
                    NewLine(L, R);
            }

        ++Buffer;
        --Count;
        }
    ShowText(L, R);
    if (_AutoTracking)
        _TrackCursor();
}

// Write character to window

void _WriteChar(char Ch)
{
    _WriteBuf(&Ch, 1);
}

// Return keyboard status

BOOL _KeyPressed(void)
{
    MSG M;

    __InitEasyWin();
    while (PeekMessage(&M, 0, 0, 0, PM_REMOVE))
        {
        if (M.message == WM_QUIT)
            Terminate();
        TranslateMessage(&M);
        DispatchMessage(&M);
        }
    return (BOOL)( KeyCount > 0 );
}

// Read key from window

int _ReadKey(void)
{
    int readkey;

    _TrackCursor();
    if (!_KeyPressed())
        {
        Reading = TRUE;
        if (Focused)
            ShowCursor();
        do
            {
            } while (!_KeyPressed());
        if (Focused)
            HideCursor();
        Reading = FALSE;
        }
    readkey = KeyBuffer[0];
    --KeyCount;
    memmove(KeyBuffer, KeyBuffer+1, KeyCount);
    return readkey;
}

// Read text buffer from window

WORD _ReadBuf(char *Buffer, WORD Count)
{
    unsigned char Ch;
    WORD I;

    I = 0;
    do
        {
        Ch = _ReadKey();
        if (Ch == 8)
            {
            if (I > 0)
                {
                --I;
                _WriteChar(8);
                }
            }
        else
            if (Ch >= 32)
                {
                if (I < Count)
                    {
                    Buffer[I++] = Ch;
                    _WriteChar(Ch);
                    }
                }
        } while (!((Ch == 13) || (_CheckEOF && (Ch == 26))));
    if (I < Count - 2)
        {
        Buffer[I++] = Ch;
        if (Ch == 13)
            {
            Buffer[I++] = 10;
            _WriteChar(13);
            }
        }
    _TrackCursor();
    return I;
}

// Set cursor position }

void gotoxy(int X, int Y)
{
    _CursorTo(X - 1, Y - 1);
}

// Return cursor X position

int wherex(void)
{
    return (_Cursor.x + 1);
}

// Return cursor Y position

int wherey(void)
{
    return(_Cursor.y + 1);
}

// Clear screen

void clrscr(void)
{
    __InitEasyWin();
    memset(ScreenBuffer, ' ', _ScreenSize.x * _ScreenSize.y);
    _Cursor.x = 0;
    _Cursor.y = 0;
    _Origin.x = 0;
    _Origin.y = 0;
    SetScrollBars();
    InvalidateRect(CrtWindow, NULL, TRUE);
    UpdateWindow(CrtWindow);
}

// Clear to end of line

void clreol(void)
{
    __InitEasyWin();
    memset(ScreenPtr(_Cursor.x, _Cursor.y), ' ',_ScreenSize.x - _Cursor.x);
    ShowText(_Cursor.x, _ScreenSize.x);
}

// WM_CREATE message handler

static void WindowCreate(void)
{
    Created = TRUE;
    ScreenBuffer = (char *) malloc(_ScreenSize.x * _ScreenSize.y);
    memset(ScreenBuffer, ' ', _ScreenSize.x * _ScreenSize.y);
    if (!_CheckBreak)
        EnableMenuItem(GetSystemMenu(CrtWindow, FALSE), SC_CLOSE,
                       MF_DISABLED | MF_GRAYED);
}

// WM_PAINT message handler

static void WindowPaint(VOID)
{
    int X1, X2, Y1, Y2;

    Painting = TRUE;
    InitDeviceContext();
    X1 = Max(0, PS.rcPaint.left / CharSize.x + _Origin.x);
    X2 = Min(_ScreenSize.x,
             (PS.rcPaint.right + CharSize.x - 1) / CharSize.x + _Origin.x);
    Y1 = Max(0, PS.rcPaint.top / CharSize.y + _Origin.y);
    Y2 = Min(_ScreenSize.y,
             (PS.rcPaint.bottom + CharSize.y - 1) / CharSize.y + _Origin.y);
    while (Y1 < Y2)
        {
        TextOut(DC, (X1 - _Origin.x) * CharSize.x, (Y1 - _Origin.y) * CharSize.y,
                    ScreenPtr(X1, Y1), X2 - X1);
        ++Y1;
        }
    DoneDeviceContext();
    Painting = FALSE;
}

// WM_VSCROLL and WM_HSCROLL message handler }

static int GetNewPos(int Pos, int Page, int Range, int Action, int Thumb)
{
    switch (Action)
        {
        case SB_LINEUP:
            return(Pos - 1);
        case SB_LINEDOWN:
            return(Pos + 1);
        case SB_PAGEUP:
            return(Pos - Page);
        case SB_PAGEDOWN:
            return(Pos + Page);
        case SB_TOP:
            return(0);
        case SB_BOTTOM:
            return(Range);
        case SB_THUMBPOSITION:
            return(Thumb);
        default:
            return(Pos);
        }
}

static void WindowScroll(int Which, int Action, int Thumb)
{
    int X, Y;

    X = _Origin.x;
    Y = _Origin.y;
    switch (Which)
        {
        case SB_HORZ:
            X = GetNewPos(X, ClientSize.x / 2, Range.x, Action, Thumb);
            break;
        case SB_VERT:
            Y = GetNewPos(Y, ClientSize.y, Range.y, Action, Thumb);
        }
    _ScrollTo(X, Y);
}

// WM_SIZE message handler

static void WindowResize(int X, int Y)
{
    if (Focused && Reading)
        HideCursor();
    ClientSize.x = X / CharSize.x;
    ClientSize.y = Y / CharSize.y;
    Range.x = Max(0, _ScreenSize.x - ClientSize.x);
    Range.y = Max(0, _ScreenSize.y - ClientSize.y);
    _Origin.x = Min(_Origin.x, Range.x);
    _Origin.y = Min(_Origin.y, Range.y);
    SetScrollBars();
    if (Focused && Reading)
        ShowCursor();
}

// WM_GETMINMAXINFO message handler

static void WindowMinMaxInfo(TMinMaxInfo far * MinMaxInfo)
{
    int X, Y;
    TEXTMETRIC Metrics;

    InitDeviceContext();
    GetTextMetrics(DC, &Metrics);
    CharSize.x = Metrics.tmMaxCharWidth;
    CharSize.y = Metrics.tmHeight + Metrics.tmExternalLeading;
    CharAscent = Metrics.tmAscent;
    X = Min(_ScreenSize.x * CharSize.x + GetSystemMetrics(SM_CXVSCROLL),
    GetSystemMetrics(SM_CXSCREEN)) + GetSystemMetrics(SM_CXFRAME) * 2;
    Y = Min(_ScreenSize.y * CharSize.y + GetSystemMetrics(SM_CYHSCROLL) +
    GetSystemMetrics(SM_CYCAPTION), GetSystemMetrics(SM_CYSCREEN)) +
    GetSystemMetrics(SM_CYFRAME) * 2;
    (*MinMaxInfo)[1].x = X;
    (*MinMaxInfo)[1].y = Y;
    (*MinMaxInfo)[3].x = CharSize.x * 16 + GetSystemMetrics(SM_CXVSCROLL) +
    GetSystemMetrics(SM_CXFRAME) * 2;
    (*MinMaxInfo)[3].y = CharSize.y * 4 + GetSystemMetrics(SM_CYHSCROLL) +
    GetSystemMetrics(SM_CYFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION);
    (*MinMaxInfo)[4].x = X;
    (*MinMaxInfo)[4].y = Y;
    DoneDeviceContext();
}

// WM_CHAR message handler

static void WindowChar(char Ch)
{
    if (_CheckBreak  && (Ch == 3))
        Terminate();
    if (KeyCount < sizeof(KeyBuffer))
        {
        KeyBuffer[KeyCount] = Ch;
        ++KeyCount;
        }
}

// WM_KEYDOWN message handler

static void WindowKeyDown(BYTE KeyDown)
{
    BOOL CtrlDown;
    int I;

    if (_CheckBreak && (KeyDown == VK_CANCEL))
        Terminate();
    CtrlDown = (BOOL) (GetKeyState(VK_CONTROL < 0));
    for (I = 0; I < ScrollKeyCount; ++I)
        {
        if (ScrollKeys[I].Key == KeyDown && ScrollKeys[I].Ctrl == CtrlDown)
            {
        WindowScroll(ScrollKeys[I].SBar, ScrollKeys[I].Action, 0);
        return;
            }
        }
}

// WM_SETFOCUS message handler

static void WindowSetFocus(void)
{
    Focused = TRUE;
    if (Reading)
        ShowCursor();
}

// WM_KILLFOCUS message handler

static void WindowKillFocus(void)
{
    if (Reading)
        HideCursor();
    Focused = FALSE;
}

// WM_DESTROY message handler

static void WindowDestroy(void)
{
    free(ScreenBuffer);
    _Cursor.x = 0;
    _Cursor.y = 0;
    _Origin.x = 0;
    _Origin.y = 0;
    PostQuitMessage(0);
    Created = FALSE;
}

inline int LoVal(LONG LVal)
{
    return (((unsigned *)&LVal)[0]);
}

inline int HiVal(LONG LVal)
{
    return (((unsigned *)&LVal)[1]);
}

// Easy window procedure

long FAR PASCAL _export _EasyWinProc(HWND Window, UINT Message,
                                   WPARAM WParam, LONG LParam)
{
    CrtWindow = Window;
    switch (Message)
        {
        case WM_CREATE:
            WindowCreate();
            break;
        case WM_PAINT:
            WindowPaint();
            break;
        case WM_VSCROLL:
            WindowScroll(SB_VERT, WParam, LoVal(LParam));
            break;
        case WM_HSCROLL:
            WindowScroll(SB_HORZ, WParam, LoVal(LParam));
            break;
        case WM_SIZE:
            WindowResize(LoVal(LParam), HiVal(LParam));
            break;
        case WM_GETMINMAXINFO:
            WindowMinMaxInfo((TMinMaxInfo far *) LParam);
            break;
        case WM_CHAR:
            WindowChar((char)WParam);
            break;
        case WM_KEYDOWN:
            WindowKeyDown((BYTE)WParam);
            break;
        case WM_SETFOCUS:
            WindowSetFocus();
            break;

        case WM_KILLFOCUS:
            WindowKillFocus();
            break;
        case WM_DESTROY:
            WindowDestroy();
            break;
        default:
            return DefWindowProc(Window, Message, WParam, LParam);
        }
    return NULL;
}


// Create window if required

void __InitEasyWin(void)
{
   if (!Created)
       {
       CrtWindow = CreateWindow(
                       CrtClass.lpszClassName,
                       _WindowTitle,
                       WS_OVERLAPPEDWINDOW | WS_HSCROLL | WS_VSCROLL,
                       _WindowOrg.x, _WindowOrg.y,
                       _WindowSize.x, _WindowSize.y,
                       0,
                       0,
                       __hInstance,
                       NULL);
       ShowWindow(CrtWindow, __cmdShow);
       UpdateWindow(CrtWindow);
       }
}

// Destroy window if required

void _DoneEasyWin(void)
{
    if (Created)
        DestroyWindow(CrtWindow);
    exit(0);
}

// EasyWin unit exit procedure

void far __ExitEasyWin(void)
{
    char *P;
    MSG Message;
    char Title[128];

    if (Created) // && (ErrorAddr = NULL))
        {
        P = _WindowTitle;
        wsprintf(Title, _InactiveTitle, (char far *) P);
        SetWindowText(CrtWindow, Title);
        GetSystemMenu(CrtWindow, TRUE);
        _CheckBreak = FALSE;
        while (GetMessage(&Message, 0, 0, 0))
            {
            TranslateMessage(&Message);
            DispatchMessage(&Message);
            }
        }
}

void __CreateEasyWin(void)
{
    if (__hPrev == 0)
        {
        CrtClass.hInstance = __hInstance;
        CrtClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
        CrtClass.hCursor = LoadCursor(NULL, IDC_ARROW);
        CrtClass.hbrBackground = GetStockObject(WHITE_BRUSH);
        RegisterClass(&CrtClass);
        }
    GetModuleFileName(__hInstance, _WindowTitle, sizeof(_WindowTitle));
    OemToAnsi(_WindowTitle, _WindowTitle);
    __ReadBufFPtr  = _ReadBuf;
    __WriteBufFPtr = _WriteBuf;
}
