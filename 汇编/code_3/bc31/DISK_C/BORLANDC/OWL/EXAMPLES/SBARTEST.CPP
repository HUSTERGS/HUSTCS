// ObjectWindows - (C) Copyright 1992 by Borland International

#include <stdio.h>
#include <owl.h>
#include <window.h>
#include <scrollba.h>
#include <static.h>

const WORD ID_THERMOMETER = 100;
const WORD ID_STATIC = 101;

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
  TScrollBar *Thermometer;
  TStatic *Static;
  TTestWindow(PTWindowsObject AParent, LPSTR ATitle);
  virtual void SetupWindow();
  virtual void HandleThermMsg(RTMessage Msg)
    = [ID_FIRST + ID_THERMOMETER];
};

TTestWindow::TTestWindow(PTWindowsObject AParent, LPSTR ATitle) :
  TWindow(AParent, ATitle)
{
  Attr.X = 20;  Attr.Y = 20;  Attr.W = 380;  Attr.H = 250;
  Thermometer =
    new TScrollBar(this, ID_THERMOMETER, 20, 170, 340, 0, TRUE);
  Static =
    new TStatic(this, ID_STATIC, "32 degrees", 135, 40, 160, 17, 0);
  EnableKBHandler();
}

void TTestWindow::SetupWindow()
{
  TWindow::SetupWindow();
  Thermometer->SetRange(32, 120);
}

void TTestWindow::HandleThermMsg(RTMessage)
{
  char AString[11];

  sprintf(AString, "%d%s", Thermometer->GetPosition(), " degrees");
  Static->SetText(AString);
}

void TTestApp::InitMainWindow()
{
  MainWindow = new TTestWindow(NULL, Name);
}

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
  LPSTR lpCmdLine, int nCmdShow)
{
  TTestApp TestApp("Thermostat", hInstance, hPrevInstance,
    lpCmdLine, nCmdShow);
  TestApp.Run();
  return TestApp.Status;
}

