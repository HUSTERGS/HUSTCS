// ObjectWindows - (C) Copyright 1992 by Borland International

// Arty demo window object

#include <owl.h>
#include <stdlib.h>
#include "demobase.h"
#include "arty.h"           // class definition for TArtyWindow
#include "artypriv.h"       // internal component classes of TArtyWindow


//---------- TList ----------------------------------------------

/* Initialize the list-of-lines object */
TList::TList( int Max )
{
  MaxLines = min( Max, MaxLineCount );
  CurrentLine = 1;
  Xmax = 0;
  Ymax = 0;
  ColorDuration = MaxColorDuration;
  IncrementCount = 0;
  MaxDelta = 10;
  PenColor = RGB(random(256), random(256), random(256));
};

/* Keep X within range, and reverse Delta if necessary to do so */
void TList::AdjustX( int &X, int &DeltaX )
{
  int TestX = X + DeltaX;
  if ((TestX < 1) || (TestX > Xmax)) {
    TestX = X;
    DeltaX = -DeltaX;
  };
  X = TestX;
};

/* Keep Y within range, and reverse Delta if necessary to do so */
void TList::AdjustY( int &Y, int &DeltaY )
{
  int TestY = Y + DeltaY;
  if ((TestY < 1) || (TestY > Ymax)) {
    TestY = Y;
    DeltaY = -DeltaY;
  };
  Y = TestY;
};

/* Clear the array of lines */
void TList::ResetLines()
{
  int StartX, StartY, I;

  StartX = Xmax / 2;
  StartY = Ymax / 2;
  for( I = 0; I < MaxLines; I++) {
    Line[I].LX1 = StartX;
    Line[I].LX2 = StartX;
    Line[I].LY1 = StartY;
    Line[I].LY2 = StartY;
    Line[I].Color = 0;
  };
  X1 = StartX;
  X2 = StartX;
  Y1 = StartY;
  Y2 = StartY;
};

/* Scale the old line coordinates to the new Xmax and Ymax coordinates.
  The new Xmax and new Ymax are passed in as parameters so we can
  calculate the scaling ratios. */
void TList::ScaleTo( int NewXmax, int NewYmax )
{
  int I;
  float RatioX, RatioY;

  if ((!Xmax) || (!Ymax)) { /* at startup, Xmax and Ymax are zero */
    Xmax = NewXmax;
    Ymax = NewYmax;
    ResetLines();
  } else {
    RatioX = NewXmax / Xmax;
    RatioY = NewYmax / Ymax;
    X1 = X1 * RatioX;
    X2 = X2 * RatioX;
    Y1 = Y1 * RatioY;
    Y2 = Y2 * RatioY;
    for( I = 0; I < MaxLines; I++) {
      Line[I].LX1 = Line[I].LX1 * RatioX;
      Line[I].LX2 = Line[I].LX2 * RatioX;
      Line[I].LY1 = Line[I].LY1 * RatioY;
      Line[I].LY2 = Line[I].LY2 * RatioY;
    };
  };
  Xmax = NewXmax;
  Ymax = NewYmax;
};

/* The low-level Draw method of the object. */
void TList::Draw( HDC DC, int a1, int b1, int a2, int b2, long lPenColor )
{
  HPEN OldPen;

  OldPen = (HPEN)SelectObject(DC, CreatePen(PS_SOLID, 1, lPenColor));
  MoveTo(DC, a1, b1);
  LineTo(DC, a2, b2);
  DeleteObject(SelectObject(DC, OldPen));
};

/* The high-level Draw method of the object. */
void TList::DrawLine( HDC DC, int Index )
{
  Draw(DC, Line[Index].LX1,
           Line[Index].LY1,
           Line[Index].LX2,
           Line[Index].LY2,
           Line[Index].Color);
};

/* The high-level draw which erases a line. */
void TList::EraseLine( HDC DC, int Index )
{
  Draw(DC, Line[Index].LX1,
           Line[Index].LY1,
           Line[Index].LX2,
           Line[Index].LY2,
           RGB(0,0,0));
};

/* Redraw all the lines in the array. */
void TList::Redraw( HDC DC )
{
  for( int I = 0; I < MaxLines; I++ )
    DrawLine(DC, I);
};

/* Reset the color counter and pick a random color. */
void TList::SelectNewColor()
{
  ColorDuration = MaxColorDuration;
  PenColor = RGB(random(256), random(256), random(256));
};

/* Pick random directional deltas and reset the delta counter. */
void TList::SelectNewDeltaValues()
{
  DeltaX1 = random(MaxDelta)-(MaxDelta / 2);
  DeltaX2 = random(MaxDelta)-(MaxDelta / 2);
  DeltaY1 = random(MaxDelta)-(MaxDelta / 2);
  DeltaY2 = random(MaxDelta)-(MaxDelta / 2);
  IncrementCount = 2 * (1 + random(10));
};

/* Process the movement of one line. */
void TList::LineTick( HDC DC )
{
  EraseLine(DC, CurrentLine);
  if (ColorDuration < 0)   SelectNewColor();
  if (!IncrementCount)     SelectNewDeltaValues();
  AdjustX(X1,DeltaX1);  AdjustX(X2,DeltaX2);
  AdjustY(Y1,DeltaY1);  AdjustY(Y2,DeltaY2);

  Line[CurrentLine].LX1 = X1;
  Line[CurrentLine].LX2 = X2;
  Line[CurrentLine].LY1 = Y1;
  Line[CurrentLine].LY2 = Y2;
  Line[CurrentLine].Color = PenColor;

  DrawLine(DC, CurrentLine);
  CurrentLine++;
  if (CurrentLine >= MaxLines)  CurrentLine = 1;
  ColorDuration--;
  IncrementCount--;
};


//------------ TQuadList ----------------------------------------

/* Draw the line and 3 reflections of it. */
void TQuadList::DrawLine( HDC DC, int Index )
{
  Draw(DC, Line[Index].LX1,
           Line[Index].LY1,
           Line[Index].LX2,
           Line[Index].LY2,
           Line[Index].Color);
  Draw(DC, Xmax - Line[Index].LX1,
           Line[Index].LY1,
           Xmax - Line[Index].LX2,
           Line[Index].LY2,
           Line[Index].Color);
  Draw(DC, Line[Index].LX1,
           Ymax - Line[Index].LY1,
           Line[Index].LX2,
           Ymax - Line[Index].LY2,
           Line[Index].Color);
  Draw(DC, Xmax - Line[Index].LX1,
           Ymax - Line[Index].LY1,
           Xmax - Line[Index].LX2,
           Ymax - Line[Index].LY2,
           Line[Index].Color);
};

/* Erase the line and 3 reflections of it. */
void TQuadList::EraseLine( HDC DC, int Index )
{
  Draw(DC, Line[Index].LX1,
           Line[Index].LY1,
           Line[Index].LX2,
           Line[Index].LY2,
           RGB(0,0,0));
  Draw(DC, Xmax - Line[Index].LX1,
           Line[Index].LY1,
           Xmax - Line[Index].LX2,
           Line[Index].LY2,
           RGB(0,0,0));
  Draw(DC, Line[Index].LX1,
           Ymax - Line[Index].LY1,
           Line[Index].LX2,
           Ymax - Line[Index].LY2,
           RGB(0,0,0));
  Draw(DC, Xmax - Line[Index].LX1,
           Ymax - Line[Index].LY1,
           Xmax - Line[Index].LX2,
           Ymax - Line[Index].LY2,
           RGB(0,0,0));
};

//----------- TArtyWindow ------------------------------------------

TArtyWindow::TArtyWindow( PTWindowsObject AParent, LPSTR ATitle ) :
                TBaseDemoWindow( AParent, ATitle )
{
  StaticControl = new TStatic(this, 100,
    "Press Left Button to pause, Right Button to Clear",10,10,10,10,0);
  Iconized = False;
  TextHeight = 20;
  Paused = FALSE;

  /* Initialize two line list objects:
      BigLineList is the 4-reflection artwork that is displayed in
      a full sized window.  Mouse clicks will pause or clear
      the display, and the line list will be scaled to the
      new window coordinates when the window is resized.

      IconicLineList is a smaller list implementing a single-line
      quark to display in the iconized window region.  Since
      mouse clicks are not sent to iconized windows, the icon
      cannot be paused or cleared, and since there is only one
      icon window size, scaling the lines to new coordinates
      has no visual effect.

    The List pointer will be toggled between the two line list
    objects: when the window is iconized, List will point to the
    IconicLineList object.  When the window is restored to full
    size, List will be made to point to the BigLineList object.
    This is so the window routines don't have to know which kind
    of list they're dealing with.  Keyword: polymorphism.   */

  BigLineList = new TQuadList(MaxLineCount);
  IconicLineList = new TList(MaxIconicLineCount);
  List = BigLineList;
};

/* Dispose of the objects that this window object created.  There's
  no need to dispose the List pointer, since it will only point to
  one of these two objects which are being disposed by their
  primary pointers */
TArtyWindow::~TArtyWindow()
{
  delete BigLineList;
  delete IconicLineList;
};

void TArtyWindow::GetWindowClass( WNDCLASS& WndClass )
{
  TBaseDemoWindow::GetWindowClass( WndClass );
  WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
  WndClass.hIcon = 0;  // we'll paint our own icon when minimized, thank you.
};

/* When the window is resized, scale the line list to fit the new
  window extent, or switch between full size and iconized window
  states.  */
void TArtyWindow::WMSize( TMessage& Message )
{
  int NewXmax, NewYmax;

  TBaseDemoWindow::WMSize(Message);

  /* Force Windows to repaint the entire window region */
  InvalidateRect(HWindow, NULL, TRUE);

  NewXmax = Message.LP.Lo;
  NewYmax = Message.LP.Hi;
  if (IsIconic(HWindow)) {
    if (!Iconized) {
      Iconized = TRUE;
      List = IconicLineList;
    }
  } else {
    if (Iconized) {
      Iconized = FALSE;
      List = BigLineList;
    };
    NewYmax -= TextHeight;  /* allow room for the text at the bottom */
  };

  List->ScaleTo(NewXmax, NewYmax);  /* scale the lines in the list */
  if (StaticControl)
    MoveWindow(StaticControl->HWindow, 0, NewYmax, NewXmax, TextHeight, True);
};

/* Toggle the window's Paused status.  Since the window will
  not receive mouse clicks when iconized, this will not pause the
  iconized lines display.  */
void TArtyWindow::WMLButtonDown( TMessage& )
{
  Paused = !Paused;
};

/* Clear the line list when the user presses the right mouse
  button.  Same comments as above on iconized windows.  */
void TArtyWindow::WMRButtonDown( TMessage& )
{
  InvalidateRect(HWindow, NULL, TRUE);
  List->ResetLines();
};

/* When the window is resized, or some other window blots out part
  of our client area, redraw the entire line list.  The PaintDC
  is fetched before Paint is called and is released for us after
  Paint is finished. */
void TArtyWindow::Paint( HDC PaintDC, PAINTSTRUCT& PaintInfo)
{
  TBaseDemoWindow::Paint(PaintDC, PaintInfo);
  List->Redraw(PaintDC);
};

/* Fetch a device context, pass it to the line list object, then
  release the device context back to Windows.  */
void TArtyWindow::TimerTick()
{
  HDC DC;

  if (!Paused) {
    DC = GetDC(HWindow);
    List->LineTick(DC);
    ReleaseDC(HWindow, DC);
  }
};

