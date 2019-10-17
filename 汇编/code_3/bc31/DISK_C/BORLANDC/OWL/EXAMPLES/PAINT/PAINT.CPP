// ObjectWindows - (C) Copyright 1992 by Borland International

#include <owl.h>
#include <windobj.h>
#include <string.h>

const int BitMapWidth  = 640;
const int BitMapHeight = 480;

const COLORREF Colors[3][16] = {
    {0x00FFFFFFl,0x00E0E0E0l,0x00C0C0FFl,0x00C0E0FFl,0x00E0FFFFl,0x00C0FFC0l,0x00FFFFC0l,0x00FFC0C0l,
     0x00FFC0FFl,0x000000C0l,0x000040C0l,0x0000C0C0l,0x0000C000l,0x00C0C000l,0x00C00000l,0x00C000C0l},
    {0x00C0C0C0l,0x00404040l,0x008080FFl,0x0080C0FFl,0x0080FFFFl,0x0080FF80l,0x00FFFF80l,0x00FF8080l,
     0x00FF80FFl,0x00000080l,0x00004080l,0x00008080l,0x00008000l,0x00808000l,0x00800000l,0x00800080l},
    {0x00808080l,0x00000000l,0x000000FFl,0x000080FFl,0x0000FFFFl,0x0000FF00l,0x00FFFF00l,0x00FF0000l,
     0x00FF00FFl,0x00000040l,0x00404080l,0x00004040l,0x00004000l,0x00404000l,0x00400000l,0x00400040l}};

const int ToolCount = 6;

const int LineCount = 8;
const int LineBarWidth = LineCount * 4 + 6 + (1 + 2 + 3 + 4 + 5 + 7 + 9 + 12);
const int LineWidth[ LineCount ] = { 1, 2, 3, 4, 5, 7, 9, 12 };

_CLASSDEF(TDrawTool)
_CLASSDEF(TCanvas)

struct TState {
	 PTDrawTool DrawTool;
         HBITMAP   BitMap;
         int       PenSize;
         COLORREF  PenColor;
         COLORREF  BrushColor;
};
typedef TState* PTState;

class TDrawTool
{
protected:
         HCURSOR Cursor;
         HICON Icon;
         PTState State;
         HWND Window;
         HPEN Pen;
         HBRUSH Brush;
         HDC DC;
         HPEN OrigPen;
         HBRUSH OrigBrush;
public:
         TDrawTool( LPSTR IconName);
         void MouseDown( HWND AWindow, int X, int Y, PTState AState);
         void MouseMove( int X, int Y);
         void MouseUp();
         virtual void DrawBegin( int, int) {};       // Abstract draw methods will be implemented
         virtual void DrawTo( int, int) {};          // in derrived classes
	 virtual void DrawEnd() {};
	 HCURSOR GetCursor() { return Cursor; };     // Classes other than derrived may want
	 HICON GetIcon() { return Icon; };           // access to these member fields
};

_CLASSDEF(TPenTool)

class TPenTool : public TDrawTool
{
protected:
	 HPEN BrushPen;
    HPEN OrigBrushPen;
public:
	 TPenTool( LPSTR IconName ) : TDrawTool( IconName ) {};
	 virtual void DrawBegin( int X, int Y);
	 virtual void DrawTo( int X, int Y);
	 virtual void DrawEnd();
};

_CLASSDEF(TFillTool)

class TFillTool : public TDrawTool
{
public:
	 TFillTool( LPSTR IconName ) : TDrawTool( IconName ) {};
         virtual void DrawBegin( int X, int Y);
};

_CLASSDEF(TBoxTool)

class TBoxTool : public TDrawTool
{
protected:
         BOOL Filled;
         int X1, Y1, X2, Y2;
public:
         TBoxTool( LPSTR IconName, BOOL AFilled )
          : TDrawTool( IconName ) { Filled = AFilled; };
         virtual void DrawBegin( int X, int Y);
         virtual void DrawTo( int X, int Y);
         virtual void DrawEnd();
         virtual void DrawObject() {};
};

_CLASSDEF(TRectTool)

class TRectTool : public TBoxTool
{
public:  TRectTool( LPSTR IconName, BOOL AFilled )
          : TBoxTool( IconName, AFilled ) {};
         virtual void DrawObject();
};

_CLASSDEF(TEllipseTool)

class TEllipseTool : public TBoxTool
{
public:  TEllipseTool( LPSTR IconName, BOOL AFilled )
              : TBoxTool( IconName, AFilled ) {};
         virtual void DrawObject();
};

_CLASSDEF(TPalette)

class TPalette : public TWindow
{
private:
         PTState State;
public:
	 TPalette( PTWindowsObject AParent, PTState AState );
         virtual void Paint( HDC PaintDC, PAINTSTRUCT& PaintInfo );
         void SelectColor( TMessage& Message, COLORREF& Color );
         virtual void WMLButtonDown( TMessage& Message ) = [ WM_FIRST + WM_LBUTTONDOWN ];
         virtual void WMRButtonDown( TMessage& Message ) = [ WM_FIRST + WM_RBUTTONDOWN ];
};

_CLASSDEF(TToolBar)

class TToolBar : public TWindow
{
private:
         PTState State;
         PTDrawTool Tools[ ToolCount ];
public:
         TToolBar( PTWindowsObject AParent, PTState AState );
         virtual ~TToolBar();
         virtual void Paint( HDC PaintDC, PAINTSTRUCT& PaintInfo );
         virtual void WMLButtonDown( TMessage& Message ) = [ WM_FIRST + WM_LBUTTONDOWN ];
};

_CLASSDEF(TLineBar)

class TLineBar : public TWindow
{
public:
         TLineBar( PTWindowsObject AParent, PTState AState );
         virtual void Paint( HDC PaintDC, PAINTSTRUCT& PaintInfo );
         virtual void WMLButtonDown( TMessage& Message ) = [ WM_FIRST + WM_LBUTTONDOWN ];
private:
         PTState State;
         void Notch( HDC PaintDC, int X, int W, int Y, int DY );
};

// TCanvas has already been _CLASSDEF'd

class TCanvas : public TWindow
{
private:
         PTState State;
         BOOL Drawing;
public:
         TCanvas( PTWindowsObject AParent, PTState AState );
         virtual ~TCanvas();
         virtual LPSTR GetClassName() { return "TCanvas"; };
	 virtual void Paint( HDC PaintDC, PAINTSTRUCT& PaintInfo );
         virtual void WMLButtonDown( TMessage& Message ) = [ WM_FIRST + WM_LBUTTONDOWN ];
         virtual void WMLButtonUp( TMessage& Message ) = [ WM_FIRST + WM_LBUTTONUP ];
         virtual void WMMouseMove( TMessage& Message ) = [ WM_FIRST + WM_MOUSEMOVE ];
         virtual void WMSetCursor( TMessage& Message ) = [ WM_FIRST + WM_SETCURSOR ];
};

_CLASSDEF(TPaintWin)

class TPaintWin : public TWindow
{
private:
         TState State;
         PTPalette Palette;
         PTToolBar ToolBar;
         PTLineBar LineBar;
         PTCanvas Canvas;
public:
         TPaintWin( PTWindowsObject AParent, LPSTR ATitle);
         virtual LPSTR GetClassName() { return "TPaintWin"; };
         virtual void GetWindowClass( WNDCLASS& WndClass );
         virtual void WMSize( TMessage& Message ) = [ WM_FIRST + WM_SIZE ];
};


class TPaintApp : public TApplication
{
public:
	TPaintApp( LPSTR name, HINSTANCE hInstance,
		  HINSTANCE hPrevInstance, LPSTR lpCmd,
		  int nCmdShow)
	        : TApplication(name, hInstance,
			       hPrevInstance, lpCmd, nCmdShow) {};
	virtual void InitMainWindow( void );
};


// --------------- TDrawTool ------------------------

TDrawTool::TDrawTool( LPSTR IconName )
{
  char Temp[30];

  _fstrcpy(Temp, IconName);
  strncat(Temp, "Tool", sizeof(Temp)-1);
  Icon = LoadIcon(GetApplicationObject()->hInstance, Temp);

  _fstrcpy(Temp, IconName);
  strncat(Temp, "Cursor", sizeof(Temp)-1);
  Cursor = LoadCursor(GetApplicationObject()->hInstance, Temp);
};

void TDrawTool::MouseDown( HWND AWindow, int X, int Y, PTState AState )
{
  Window = AWindow;
  State = AState;
  SetCapture(Window);
  Pen = CreatePen(PS_SOLID, State->PenSize, State->PenColor);
  Brush = CreateSolidBrush(State->BrushColor);
  DC = GetDC(Window);
  OrigPen = (HPEN)SelectObject(DC, Pen);
  OrigBrush = (HBRUSH)SelectObject(DC, Brush);
  DrawBegin(X, Y);
};

void TDrawTool::MouseMove( int X, int Y )
{
  DrawTo(X, Y);
};

void TDrawTool::MouseUp()
{
  DrawEnd();
  ReleaseCapture();
  SelectObject(DC, OrigPen);
  SelectObject(DC, OrigBrush);
  DeleteObject(Brush);
  DeleteObject(Pen);
  ReleaseDC(Window, DC);
};


// --------------- TPenTool ------------------------

void TPenTool::DrawBegin( int X, int Y )
{
  BrushPen = CreatePen(PS_SOLID, State->PenSize, State->BrushColor);
  OrigBrushPen = (HPEN)SelectObject(DC, BrushPen);
  MoveTo(DC, X, Y);
};

void TPenTool::DrawTo( int X, int Y )
{
  LineTo(DC, X, Y);
};

void TPenTool::DrawEnd()
{
  SelectObject(DC, OrigBrushPen);
  DeleteObject(BrushPen);
};

// --------------- TFillTool ------------------------

void TFillTool::DrawBegin( int X, int Y )
{
  DWORD SurfaceColor;
  SurfaceColor = GetPixel(DC, X, Y);
  ExtFloodFill(DC, X, Y, SurfaceColor, FLOODFILLSURFACE);
};


// --------------- TBoxTool ------------------------

void TBoxTool::DrawBegin( int X, int Y )
{
  X1 = X;
  Y1 = Y;
  X2 = X;
  Y2 = Y;
  SelectObject(DC, GetStockObject(BLACK_PEN));
  SelectObject(DC, GetStockObject(NULL_BRUSH));
  SetROP2(DC, R2_NOT);
  DrawObject();
};

void TBoxTool::DrawTo( int X, int Y )
{
  DrawObject();
  X2 = X;
  Y2 = Y;
  DrawObject();
};

void TBoxTool::DrawEnd()
{
  DrawObject();
  SetROP2(DC, R2_COPYPEN);
  SelectObject(DC, Pen);
  if (!Filled) DrawObject();
  SelectObject(DC, Brush);
  if (Filled) DrawObject();
};

// --------------- TRectTool ------------------------

void TRectTool::DrawObject()
{
  Rectangle(DC, X1, Y1, X2, Y2);
};

// --------------- TEllipseTool ------------------------

void TEllipseTool::DrawObject()
{
  Ellipse(DC, X1, Y1, X2, Y2);
};

// --------------- TPalette ------------------------

TPalette::TPalette( PTWindowsObject AParent, PTState AState) :
                  TWindow(AParent, NULL)
{
  Attr.Style = WS_CHILD | WS_VISIBLE;
  State = AState;
};

void TPalette::Paint( HDC PaintDC, PAINTSTRUCT& )
{
  int X, Y, S;
  HPEN OldPen;
  HBRUSH OldBrush;
  RECT R;

  GetClientRect(HWindow, &R);
  S = R.bottom / 17;
  for( Y = 0; Y < 16; Y++ )
    for( X = 0; X < 3; X++ ) {
      OldBrush = (HBRUSH)SelectObject(PaintDC, CreateSolidBrush(Colors[X][Y]));
      Rectangle(PaintDC, X * S, Y * S, (X + 1) * S + 1, (Y + 1) * S + 1);
      DeleteObject(SelectObject(PaintDC, OldBrush));
    };

  SelectObject(PaintDC, GetStockObject(NULL_BRUSH));
  Rectangle(PaintDC, 0, S * 16, R.right, R.bottom);

  OldPen = (HPEN)SelectObject(PaintDC, CreatePen(PS_SOLID, 5, State->PenColor));
  OldBrush = (HBRUSH)SelectObject(PaintDC, CreateSolidBrush(State->BrushColor));
  Rectangle(PaintDC, 3, S * 16 + 3, R.right - 3, R.bottom - 3);
  DeleteObject(SelectObject(PaintDC, OldBrush));
  DeleteObject(SelectObject(PaintDC, OldPen));
};

void TPalette::SelectColor( TMessage& Message, COLORREF& Color )
{
  int X, Y, S;
  RECT R;

  GetClientRect(HWindow, &R);
  S = R.bottom / 17;
  X = Message.LP.Lo / S;
  Y = Message.LP.Hi / S;
  if ((X < 3) && (Y < 16)) {
    Color = Colors[X][Y];
    InvalidateRect(HWindow, NULL, FALSE);
  }
};

void TPalette::WMLButtonDown( TMessage& Message )
{
  SelectColor(Message, State->BrushColor);
};

void TPalette::WMRButtonDown( TMessage& Message )
{
  SelectColor(Message, State->PenColor);
};


// --------------- TToolBar ------------------------

TToolBar::TToolBar( PTWindowsObject AParent, PTState AState) :
                   TWindow(AParent, NULL)
{
  Attr.Style = WS_CHILD | WS_VISIBLE;
  State = AState;
  Tools[0] = new TPenTool("Pen");
  Tools[1] = new TFillTool("Fill");
  Tools[2] = new TRectTool("Rect", FALSE);
  Tools[3] = new TRectTool("FillRect", TRUE);
  Tools[4] = new TEllipseTool("Ellipse", FALSE);
  Tools[5] = new TEllipseTool("FillEllipse", TRUE);
  State->DrawTool = Tools[0];
};

TToolBar::~TToolBar()
{
  for( int i = 0; i < ToolCount; i++)
    delete Tools[i];
};

void TToolBar::Paint( HDC PaintDC, PAINTSTRUCT& )
{
  int I;
  RECT R;

  for ( I = 0; I < ToolCount; I++) {
    DrawIcon(PaintDC, I * 31, 0, Tools[I]->GetIcon());
    if (Tools[I] == State->DrawTool) {
      R.top = 1;
      R.left = I * 31 + 1;
      R.bottom = R.top + 30;
      R.right = R.left + 30;
      InvertRect(PaintDC, &R);
    }
  }
};

void TToolBar::WMLButtonDown( TMessage& Message )
{
  int I;

  I = Message.LP.Lo / 31;
  if ( I < ToolCount ) {
    State->DrawTool = Tools[I];
    InvalidateRect(HWindow, NULL, FALSE);
  }
};


// --------------- TLineBar ------------------------

TLineBar::TLineBar( PTWindowsObject AParent, PTState AState) :
                   TWindow(AParent, NULL)
{
  Attr.Style = WS_BORDER | WS_CHILD | WS_VISIBLE;
  State = AState;
};

void TLineBar::Notch( HDC PaintDC, int X, int W, int Y, int DY )
{
  for( int L = 3; L >= 0; L-- ) {
    MoveTo(PaintDC, X + W / 2 - L, Y);
    LineTo(PaintDC, X + W / 2 + L + 1, Y);
    Y += DY;
  }
};

void TLineBar::Paint( HDC PaintDC, PAINTSTRUCT& )
{
  int I, X, W;
  RECT R;

  X = 4;
  for ( I = 0; I < LineCount; I++) {
    W = LineWidth[I];
    SetRect(&R, X, 5, X + W, 25);
    FillRect(PaintDC, &R, (HBRUSH)GetStockObject(BLACK_BRUSH));
    if (W == State->PenSize) {
      Notch(PaintDC, X, W, 0, 1);
      Notch(PaintDC, X, W, 29, -1);
    };
    X += W + 4;
  }
};

void TLineBar::WMLButtonDown( TMessage& Message )
{
  int I, X, W;

  X = 2;
  for( I = 0; I < LineCount; I++) {
    W = LineWidth[I];
    if ((Message.LP.Lo >= X) && (Message.LP.Lo < (X + W + 4))) {
      State->PenSize = W;
      InvalidateRect(HWindow, NULL, TRUE);
      return;
    }
    X += W + 4;
  }
};


// --------------- TCanvas ------------------------

TCanvas::TCanvas( PTWindowsObject AParent, PTState AState) :
                   TWindow(AParent, NULL)
{
  HDC DC, MemDC;

  Attr.Style = WS_BORDER | WS_CHILD | WS_VISIBLE;
  State = AState;
  Drawing = FALSE;
  DC = GetDC(0);
  State->BitMap = CreateCompatibleBitmap(DC, BitMapWidth, BitMapHeight);
  MemDC = CreateCompatibleDC(DC);
  SelectObject(MemDC, State->BitMap);
  PatBlt(MemDC, 0, 0, BitMapWidth, BitMapHeight, WHITENESS);
  DeleteDC(MemDC);
  ReleaseDC(0, DC);
};

TCanvas::~TCanvas()
{
  DeleteObject(State->BitMap);
};

void TCanvas::Paint( HDC PaintDC, PAINTSTRUCT& )
{
  HDC MemDC;
  RECT R;

  MemDC = CreateCompatibleDC(PaintDC);
  SelectObject(MemDC, State->BitMap);
  GetClientRect(HWindow, &R);
  BitBlt(PaintDC, 0, 0, R.right, R.bottom, MemDC, 0, 0, SRCCOPY);
  DeleteDC(MemDC);
};

void TCanvas::WMLButtonDown( TMessage& Message )
{
  if (!Drawing) {
    Drawing = TRUE;
    State->DrawTool->MouseDown(HWindow, Message.LP.Lo, Message.LP.Hi, State);
  }
};

void TCanvas::WMMouseMove( TMessage& Message )
{
  if (Drawing)
    State->DrawTool->MouseMove(Message.LP.Lo, Message.LP.Hi);
};

void TCanvas::WMLButtonUp( TMessage& )
{
  HDC DC, MemDC;
  RECT R;

  if (Drawing) {
    State->DrawTool->MouseUp();
    Drawing = FALSE;
    DC = GetDC(HWindow);
    MemDC = CreateCompatibleDC(DC);
    SelectObject(MemDC, State->BitMap);
    GetClientRect(HWindow, &R);
    BitBlt(MemDC, 0, 0, R.right, R.bottom, DC, 0, 0, SRCCOPY);
    DeleteDC(MemDC);
    ReleaseDC(HWindow, DC);
  }
};

void TCanvas::WMSetCursor( TMessage& )
{
  SetCursor(State->DrawTool->GetCursor());
};


// --------------- TPaintWin ------------------------

TPaintWin::TPaintWin( PTWindowsObject AParent, LPSTR ATitle) :
              TWindow(AParent, ATitle)
{
  State.DrawTool = NULL;
  State.BitMap = 0;
  State.PenSize = 3;
  State.PenColor = 0x00FFFFFFl;
  State.BrushColor = 0l;
  Palette = new TPalette(this, &State);
  ToolBar = new TToolBar(this, &State);
  LineBar = new TLineBar(this, &State);
  Canvas =  new TCanvas(this, &State);
};

void TPaintWin::GetWindowClass( WNDCLASS& WndClass )
{
  TWindow::GetWindowClass(WndClass);
  WndClass.hbrBackground = (HBRUSH)COLOR_APPWORKSPACE + 1;
  WndClass.hIcon = LoadIcon(GetApplication()->hInstance, "PaintIcon");
};

void TPaintWin::WMSize( TMessage& )
{
  int S;
  RECT R;

  GetClientRect(HWindow, &R);
  S = ((R.bottom - 8) / 17) * 3 + 1;
  MoveWindow(Palette->HWindow, 4, 4, S, R.bottom - 8, TRUE);
  MoveWindow(ToolBar->HWindow, S + 8, 4, ToolCount * 31 + 1, 32, TRUE);
  MoveWindow(LineBar->HWindow, S + ToolCount * 31 + 13, 4, LineBarWidth, 32, TRUE);
  MoveWindow(Canvas->HWindow, S + 8, 40, R.right - S - 12, R.bottom - 44, TRUE);
};


// --------------- TPaintApp ------------------------

void TPaintApp::InitMainWindow()
{
	MainWindow = new TPaintWin(NULL, "OWL Paint");
}

// -------------Main Program--------------------

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
		   LPSTR lpCmd, int nCmdShow)
{
	TPaintApp App( "OwlPaint", hInstance, hPrevInstance,
		lpCmd, nCmdShow);
	App.Run();
	return ( App.Status );
}
