// ObjectWindows - (C) Copyright 1992 by Borland International

#include <stdio.h>
#include <string.h>
#include <owl.h>
#include <scrollba.h>
#include <groupbox.h>
#include "cctltest.h"
#include "colordlg.h"

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
  virtual void CMColor(RTMessage Msg)
    = [CM_FIRST + CM_COLOR];
};

TTestWindow::TTestWindow(PTWindowsObject AParent, LPSTR ATitle)
  : TWindow(AParent, ATitle)
{
  AssignMenu("COMMANDS");
}

void TTestWindow::CMColor(RTMessage)
{
  COLORREF TheColor;
  char MsgStr[128];

  TheColor = RGB(0x00, 0x00, 0x00);
  if ( GetApplication()->ExecDialog(
    new TColorDialog(this, TheColor)) == IDOK )
      sprintf(MsgStr,
        "RGB intensities: \r\n\r\n Red - %d \r\n Green - %d \r\n Blue - %d",
        GetRValue(TheColor), GetGValue(TheColor), GetBValue(TheColor));
  else
    strcpy(MsgStr, "Cancelled");
  MessageBox(HWindow, MsgStr, GetApplication()->Name, MB_OK);
}

void TTestApp::InitMainWindow()
{
  MainWindow = new TTestWindow(NULL, Name);
}


int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
  LPSTR lpCmdLine, int nCmdShow)
{
  TTestApp TestApp("Custom Control Test", hInstance, hPrevInstance,
    lpCmdLine, nCmdShow);
  TestApp.Run();
  return TestApp.Status;
}
