// ObjectWindows - (C) Copyright 1992 by Borland International

// Printing program example using Application Framework Libraries (OWL)
// This application displays and prints a RULER using OWL and printer classes.


#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
}
#endif


#include <owl.h>

#include "printer.h"
#include "ids.h"

class TRulerApp : public TApplication
{
public:
        TRulerApp(LPSTR AName, HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
    : TApplication(AName, hInstance, hPrevInstance, lpCmdLine, nCmdShow)
    {}
  virtual void InitMainWindow(void);
};

  _CLASSDEF(TRulerWin)
  class TRulerWin : public TWindow
  {
                PTPrinter Printer;    // Pointer to a TPrinter object
  public:
    TRulerWin(PTWindowsObject AParent, LPSTR ATitle,
        PTModule AModule = NULL);
    ~TRulerWin( void );
    virtual void CMFilePrint(RTMessage Msg)
        = [CM_FIRST + CM_FILEPRINT];
    virtual void CMFilePrinterSetup(RTMessage Msg)
        = [CM_FIRST + CM_FILEPRINTERSETUP];
    virtual void CMFileExit(RTMessage Msg)
        = [CM_FIRST + CM_FILEEXIT];
    virtual void Paint(HDC PaintDC, PAINTSTRUCT& PaintInfo);
  };

  _CLASSDEF(TRulerOut)
  class TRulerOut : public TPrintout
  {
  public:
    TRulerOut(Pchar ATitle) : TPrintout(ATitle) {}
    virtual void PrintPage(HDC DC, WORD Page, POINT Size, LPRECT Rect,
        WORD Flags);
    void SetBanding( BOOL b ) { Banding = b; }
  };


// Display or print a ruler

void ShowRuler( HDC DC )
{
const UnitsPerInch = 100;      // Display scale 0.01 inches per unit
const NumInches = 6;           // Size of ruler in inches
const MarksPerInch = 4;        // Number of markers for each inch
const LargeMarkerSize = (0.50 * UnitsPerInch);  // Size of labeled markers
const SmallMarkerSize = (0.25 * UnitsPerInch);  // Size of small markers

int I;                         // For-loop control variable
int X, X1, Y1, X2, Y2;         // Coordinates for displaying ruler
char S[2];                     // Holds ruler digits in text form

  SaveDC(DC);
  SetMapMode(DC, MM_LOENGLISH);
  X1 = (0.50 * UnitsPerInch);
  Y1 = X1;
  X2 = X1 + (NumInches * UnitsPerInch);
  Y2 = Y1 + (1 * UnitsPerInch);
  Rectangle(DC, X1, -Y1, X2, -Y2);
  Y2 = Y1 + LargeMarkerSize;
  for (I = 1;  I <= NumInches - 1; I++ )
  {
    X = X1 + (I * UnitsPerInch);
    MoveTo(DC, X, -Y1);
    LineTo(DC, X, -Y2);
    itoa(I, S, 10);
    TextOut(DC, X, -Y2, S, strlen(S));
  }
  Y2 = Y1 + SmallMarkerSize;
  for ( I = 0; I <= ((NumInches * MarksPerInch) - 1); I++ )
  {
    X = X1 + ((I * UnitsPerInch) / MarksPerInch);
    MoveTo(DC, X, -Y1);
    LineTo(DC, X, -Y2);
  }
  RestoreDC(DC, -1);
}


// TRulerApp


// Initialize TRulerApp's main window

void TRulerApp::InitMainWindow(void)
{
  MainWindow = new TRulerWin(NULL, "Ruler Demonstration");
}



// TRulerWin


// Construct a TRulerWin object

TRulerWin::TRulerWin(PTWindowsObject AParent, LPSTR ATitle, PTModule AModule)
        : TWindow( AParent, ATitle, AModule )
{
    AssignMenu(ID_MENU);
    Attr.X = GetSystemMetrics(SM_CXSCREEN) / 8;
    Attr.Y = GetSystemMetrics(SM_CYSCREEN) / 8;
    Attr.H = Attr.Y * 6;
    Attr.W = Attr.X * 6;
    Printer = new TPrinter;
}


// Destroy a TRulerWin object

TRulerWin::~TRulerWin( void )
{
    delete Printer;
}


// Execute File:Print command

void TRulerWin::CMFilePrint(RTMessage)
{
  PTRulerOut Printout = 0;

  if ( Printer )
  {
    Printout = new TRulerOut("Ruler Test");
    if ( Printout )
    {
      Printout->SetBanding( TRUE );
      Printer->Print(this, Printout);
      delete Printout;
    }
  }
}


// Execute File:Printer-setup command

void TRulerWin::CMFilePrinterSetup(RTMessage)
{
  if ( Printer )
        Printer->Setup(this);
}


// Execute File:Exit command

void TRulerWin::CMFileExit(RTMessage)
{
  CloseWindow();
}


// Paint window's contents on screen

void TRulerWin::Paint(HDC PaintDC, PAINTSTRUCT&)
{
  ShowRuler(PaintDC);
}


// TRulerOut


// Print page (or pages)

void TRulerOut::PrintPage(HDC DC, WORD, POINT, LPRECT, WORD)
{
  ShowRuler(DC);
}


int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
  LPSTR lpCmdLine, int nCmdShow)
{
  TRulerApp RulerApp("Ruler", hInstance, hPrevInstance,
    lpCmdLine, nCmdShow);
  RulerApp.Run();
  return ( RulerApp.Status );
}
