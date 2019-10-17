// ObjectWindows - (C) Copyright 1992 by Borland International

#include <owl.h>
#include <window.h>
#include <static.h>

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
  TTestWindow(PTWindowsObject AParent, LPSTR ATitle);
};

TTestWindow::TTestWindow(PTWindowsObject AParent, LPSTR ATitle)
  : TWindow(AParent, ATitle)
{
  TStatic *AStatic;

  Attr.X = 100;
  Attr.Y = 100;
  Attr.W = 415;
  Attr.H = 355;
  new TStatic(this, -1, "Default Static", 20, 20, 150, 24, 0);
  new TStatic(this, -1, "SS_SIMPLE", 20, 50, 150, 24, 0);
  new TStatic(this, -1, "SS_LEFT", 20, 80, 150, 24, 0);
  new TStatic(this, -1, "SS_CENTER", 20, 110, 150, 24, 0);
  new TStatic(this, -1, "SS_RIGHT", 20, 140, 150, 24, 0);
  new TStatic(this, -1, "SS_BLACKFRAME", 20, 170, 150, 24, 0);
  new TStatic(this, -1, "SS_BLACKRECT", 20, 200, 150, 24, 0);
  new TStatic(this, -1, "SS_GRAYFRAME", 20, 230, 150, 24, 0);
  new TStatic(this, -1, "SS_GRAYRECT", 20, 260, 150, 24, 0);
  new TStatic(this, -1, "SS_NOPREFIX", 20, 290, 150, 24, 0);
  new TStatic(this, -1, "Sample &Text", 170, 20, 200, 24, 0);
  AStatic = new TStatic(this, -1, "Sample &Text", 170, 50, 200, 24, 14);
  AStatic->Attr.Style = (AStatic->Attr.Style & ~SS_LEFT) | SS_SIMPLE;
  new TStatic(this, -1, "Sample &Text", 170, 80, 200, 24, 0);
  AStatic = new TStatic(this, -1, "Sample &Text", 170, 110, 200, 24, 14);
  AStatic->Attr.Style = (AStatic->Attr.Style & ~SS_LEFT) | SS_CENTER;
  AStatic = new TStatic(this, -1, "Sample &Text", 170, 140, 200, 24, 14);
  AStatic->Attr.Style = (AStatic->Attr.Style & ~SS_LEFT) | SS_RIGHT;
  AStatic = new TStatic(this, -1, "Sample &Text", 170, 170, 200, 24, 0);
  AStatic->Attr.Style = (AStatic->Attr.Style & ~SS_LEFT) | SS_BLACKFRAME;
  AStatic = new TStatic(this, -1, "Sample &Text", 170, 200, 200, 24, 0);
  AStatic->Attr.Style = (AStatic->Attr.Style & ~SS_LEFT) | SS_BLACKRECT;
  AStatic = new TStatic(this, -1, "Sample &Text", 170, 230, 200, 24, 0);
  AStatic->Attr.Style = (AStatic->Attr.Style & ~SS_LEFT) | SS_GRAYFRAME;
  AStatic = new TStatic(this, -1, "Sample &Text", 170, 260, 200, 24, 0);
  AStatic->Attr.Style = (AStatic->Attr.Style & ~SS_LEFT) | SS_GRAYRECT;
  AStatic = new TStatic(this, -1, "Sample &Text", 170, 290, 200, 24, 0);
  AStatic->Attr.Style = (AStatic->Attr.Style & ~SS_LEFT) | SS_RIGHT | SS_NOPREFIX;
}

void TTestApp::InitMainWindow()
{
  MainWindow = new TTestWindow(NULL, Name);
}

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
  LPSTR lpCmdLine, int nCmdShow)
{
  TTestApp TestApp("Static Control Tester", hInstance, hPrevInstance,
    lpCmdLine, nCmdShow);
  TestApp.Run();
  return TestApp.Status;
}
