// ObjectWindows - (C) Copyright 1992 by Borland International
//
// paltest.cpp

#include <alloc.h>
#include <owl.h>
#include <window.h>
#include "paltest.h"

const NumColors = 8;
const BYTE RedVals[NumColors] =   {0, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF};
const BYTE GreenVals[NumColors] = {0, 0, 0xFF, 0xFF, 0, 0, 0xFF, 0xFF};
const BYTE BlueVals[NumColors] =  {0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF};

class TTestApp : public TApplication
{
public:
  TTestApp(LPSTR AName, HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
    : TApplication(AName, hInstance, hPrevInstance, lpCmdLine, nCmdShow) {};
  virtual void InitMainWindow();
};

class TTestWindow : public TWindow
{
public:
  LPLOGPALETTE MyLogPalette;
  TTestWindow(PTWindowsObject AParent, LPSTR ATitle);
  ~TTestWindow();
  virtual void WMLButtonDown(RTMessage Msg) =
    [WM_FIRST + WM_LBUTTONDOWN];
  virtual void WMRButtonDown(RTMessage Msg) =
    [WM_FIRST + WM_RBUTTONDOWN];
  virtual void CMAbout(RTMessage  Msg) =
    [CM_FIRST + CM_ABOUT];
};

TTestWindow::TTestWindow(PTWindowsObject AParent, LPSTR ATitle) :
  TWindow(AParent, ATitle)
{
  AssignMenu("PALTEST_MENU");
  MyLogPalette = (LPLOGPALETTE)
    farmalloc(sizeof(LOGPALETTE) + sizeof(PALETTEENTRY) * NumColors);
  MyLogPalette->palVersion = 0x300;
  MyLogPalette->palNumEntries = NumColors;
  for (int i = 0; i < NumColors; ++i)
  {
    MyLogPalette->palPalEntry[i].peRed = RedVals[i];
    MyLogPalette->palPalEntry[i].peGreen = GreenVals[i];
    MyLogPalette->palPalEntry[i].peBlue = BlueVals[i];
    MyLogPalette->palPalEntry[i].peFlags = PC_RESERVED;
  }
}

TTestWindow::~TTestWindow()
{
  farfree(MyLogPalette);
}

void TTestWindow::WMLButtonDown(RTMessage)
{
  HBRUSH ABrush, OldBrush;
  HPALETTE ThePalette, OldPalette;
  HDC TheDC;

  ThePalette = CreatePalette(MyLogPalette);
  TheDC = GetDC(HWindow);
  OldPalette = SelectPalette(TheDC, ThePalette, FALSE);
  RealizePalette(TheDC);
  for (int i = 0; i < NumColors; ++i)
  {
    ABrush = CreateSolidBrush(PALETTEINDEX(i));
    OldBrush = (HBRUSH)SelectObject(TheDC, ABrush);
    Rectangle(TheDC, i * 25, i * 25, i * 25 + 20, i * 25 + 20);
    SelectObject(TheDC, OldBrush);
    DeleteObject(ABrush);
  }
  SelectPalette(TheDC, OldPalette, FALSE);
  ReleaseDC(HWindow, TheDC);
  DeleteObject(ThePalette);
}

void TTestWindow::WMRButtonDown(RTMessage)
{
  PALETTEENTRY APaletteEntry;

  APaletteEntry = MyLogPalette->palPalEntry[0];
  for (int i = 0; i < NumColors-1; i++)
  {
    MyLogPalette->palPalEntry[i] = MyLogPalette->palPalEntry[i + 1] ;
  }
  MyLogPalette->palPalEntry[i] = APaletteEntry;
}

void TTestWindow::CMAbout(RTMessage)
{
  GetApplication()->ExecDialog(new TDialog(this, "ABOUT"));
}

void TTestApp::InitMainWindow()
{
  MainWindow = new TTestWindow(NULL, "Palette Tester");
}

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
  LPSTR lpCmdLine, int nCmdShow)
{
  TTestApp TestApp("Palette Tester", hInstance, hPrevInstance,
    lpCmdLine, nCmdShow);
  TestApp.Run();
  return TestApp.Status;
}
