// ObjectWindows - (C) Copyright 1992 by Borland International

// TBitBltWindow demo window object for GDIDEMO program

#include <owl.h>
#include <stdlib.h>
#include <math.h>
#include "demobase.h"
#include "bitblt.h"

const int test = OS2_MODE + 10;

/* TBitBltWindow ---------------------------------------------------- */

/* Initialize the bitblt demo window and allocate bitmaps */
TBitBltWindow::TBitBltWindow( PTWindowsObject AParent, LPSTR ATitle ) :
                  TBaseDemoWindow( AParent, ATitle )
{
  Background = LoadBitmap(GetApplication()->hInstance, MAKEINTRESOURCE(BackgroundID));
  Ship = LoadBitmap(GetApplication()->hInstance, MAKEINTRESOURCE(ShipID));
  MonoShip = LoadBitmap(GetApplication()->hInstance, MAKEINTRESOURCE(MonoShipID));
  ScratchBitmap = 0;
  StretchedBkgnd = 0;
  OldX = 0;
  OldY = 0;
  X = 0;
  Y = 0;
  Delta = 5;
  CurClick = 1;
};

/* Dispose of all used resources */
TBitBltWindow::~TBitBltWindow()
{
  DeleteObject(Background);
  DeleteObject(Ship);
  DeleteObject(MonoShip);
  if (ScratchBitmap)
    DeleteObject(ScratchBitmap);
  if (StretchedBkgnd)
    DeleteObject(StretchedBkgnd);
};

void TBitBltWindow::GetWindowClass( WNDCLASS& WndClass )
{
  TBaseDemoWindow::GetWindowClass( WndClass );
  WndClass.hIcon = 0;  // we'll paint on our icon when minimized
};

/* Allocate scratch bitmaps */
void TBitBltWindow::SetupWindow()
{
  HDC HandleDC;

  TBaseDemoWindow::SetupWindow();
  HandleDC = GetDC(HWindow);
  ScratchBitmap = CreateCompatibleBitmap(HandleDC, 80, 80);
  StretchedBkgnd = CreateCompatibleBitmap(HandleDC, 1000, 1000);
  ReleaseDC(HWindow, HandleDC);
};

/* Record the new size and stretch the background to it */
void TBitBltWindow::WMSize( TMessage& Message )
{
  HDC HandleDC, MemDC, StretchedDC;
  HANDLE StretchObject, MemObject;
  HCURSOR OldCur;

  TBaseDemoWindow::WMSize(Message);
  WindowSize.x = Message.LP.Lo;
  WindowSize.y = Message.LP.Hi;

  HandleDC = GetDC(HWindow);

  /* Create a stretched to fit background */
  StretchedDC = CreateCompatibleDC(HandleDC);
  MemDC = CreateCompatibleDC(HandleDC);
  StretchObject = SelectObject(StretchedDC, StretchedBkgnd);
  MemObject = SelectObject(MemDC, Background);
  OldCur = SetCursor(LoadCursor(0, IDC_WAIT));   // set the cursor to an hourglass - this might take awhile
  StretchBlt(StretchedDC, 0, 0, WindowSize.x, WindowSize.y, MemDC, 0, 0, 100, 100, SRCCOPY);
  SetCursor(OldCur);
  SelectObject(StretchedDC, StretchObject);
  SelectObject(MemDC, MemObject);
  DeleteDC(MemDC);
  DeleteDC(StretchedDC);
  ReleaseDC(HWindow, HandleDC);
};

/* Need to ensure that the Old copy of the ship gets redrawn with
  any paint messages. */
void TBitBltWindow::WMPaint( TMessage& Message )
{
  RECT Rect;

  Rect.top = OldY;
  Rect.left = OldX;
  Rect.bottom = OldY + BitmapSize;
  Rect.right = OldX + BitmapSize;
  InvalidateRect(HWindow, &Rect, FALSE);
  TBaseDemoWindow::WMPaint(Message);
};

void TBitBltWindow::Paint( HDC PaintDC, PAINTSTRUCT& )
{
  HDC MemDC;
  HANDLE MemObject;

  MemDC = CreateCompatibleDC(PaintDC);
  MemObject = SelectObject(MemDC, StretchedBkgnd);
  BitBlt(PaintDC, 0, 0, WindowSize.x, WindowSize.y, MemDC, 0, 0, SRCCOPY);
  SelectObject(MemDC, MemObject);
  DeleteDC(MemDC);
};

/* TimerTick deletes the old position of the saucer and blt's a new one */
void TBitBltWindow::TimerTick()
{
  const int ClicksToSkip = 4;

  HDC Bits, BackingStore, WindowDC;
  HANDLE SavedBitsObject, SavedStoreObject;
  int BX, BY, OX, OY, BH, BW;

  /* Make the saucer go slower then everyone else - only move on every 4th tick */
  if (CurClick < ClicksToSkip) {
    CurClick++;
    return;
  } else {
    CurClick = 1;
  };

  /* Setup the DC's */
  WindowDC = GetDC(HWindow);
  Bits = CreateCompatibleDC(WindowDC);
  BackingStore = CreateCompatibleDC(WindowDC);

  CalculateNewXY();

  /* Calculate the offsets into and dimentions of the backing store */
  BX = min(X, OldX);
  BY = min(Y, OldY);
  OX = abs(X - BX);
  OY = abs(Y - BY);
  BW = BitmapSize + abs(OldX - X);
  BH = BitmapSize + abs(OldY - Y);

  /* Create an image into the backing store the will that, when blt into
    the window will both erase the old image and draw the new one.
    ( to minimize screen flicker ) */

  SavedStoreObject = SelectObject(BackingStore, ScratchBitmap);
  SavedBitsObject = SelectObject(Bits, StretchedBkgnd);
  BitBlt(BackingStore, 0, 0, BW, BH, Bits, BX, BY, SRCCOPY);
  SelectObject(Bits, MonoShip);
  BitBlt(BackingStore, OX, OY, BitmapSize, BitmapSize, Bits, 0, 0, SRCAND);
  SelectObject(Bits, Ship);
  BitBlt(BackingStore, OX, OY, BitmapSize, BitmapSize, Bits, 0, 0, SRCPAINT);

  /* Blt the backing store to the window */
  BitBlt(WindowDC, BX, BY, BW, BH, BackingStore, 0, 0, SRCCOPY);

  /* Clean up the DC's */
  SelectObject(Bits, SavedBitsObject);
  SelectObject(BackingStore, SavedStoreObject);
  DeleteDC(Bits);
  DeleteDC(BackingStore);
  ReleaseDC(HWindow, WindowDC);

  OldX = X;
  OldY = Y;
};

void TBitBltWindow::CalculateNewXY()
{
  if (WindowSize.x < BitmapSize)
    return;  /* Don't move if too small */
  if ((X > WindowSize.x - BitmapSize) || (X < 0)) {
    Delta = -Delta;
    if (X > (WindowSize.x - BitmapSize))
      X = WindowSize.x - BitmapSize - 5;
  };
  X += Delta;
  Y += random(10) - 5;  // range from -5 to +5
  if (Y > (WindowSize.y - BitmapSize)) {
    Y = WindowSize.y - BitmapSize;
  } else {
    if (Y < 0)
      Y = 0;
  }
};

