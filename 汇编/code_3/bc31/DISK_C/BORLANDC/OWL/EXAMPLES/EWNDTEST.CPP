// ObjectWindows - (C) Copyright 1992 by Borland International

#include <owl.h>
#include <stdio.h>
#include <editwnd.h>
#include "ewndtest.h"

class TTestApp : public TApplication
{
public:
  TTestApp(LPSTR AName, HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
    : TApplication(AName, hInstance, hPrevInstance, lpCmdLine, nCmdShow) {};
  virtual void InitMainWindow();
  virtual void InitInstance();
};

class TTestWindow : public TEditWindow
{
public:
  TTestWindow(PTWindowsObject AParent, LPSTR ATitle);
  virtual void CMSendText(RTMessage Msg)
    = [CM_FIRST + CM_SENDTEXT];
};

TTestWindow::TTestWindow(PTWindowsObject AParent, LPSTR ATitle)
  : TEditWindow(AParent, ATitle)
{
  AssignMenu("COMMANDS");
}

void TTestWindow::CMSendText(RTMessage)
{
  int Lines;
  char Text[20];

  Lines = Editor->GetNumLines();
  sprintf(Text, "%d lines sent", Lines);
  MessageBox(HWindow, Text, "Message Sent", MB_OK);
}

void TTestApp::InitMainWindow()
{
  MainWindow = new TTestWindow(NULL, Name);
}

void TTestApp::InitInstance()
{
  TApplication::InitInstance();
  HAccTable = LoadAccelerators(hInstance, "EDITCOMMANDS");
}

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
  LPSTR lpCmdLine, int nCmdShow)
{
  TTestApp TestApp("Edit Window Tester", hInstance, hPrevInstance,
    lpCmdLine, nCmdShow);
  TestApp.Run();
  return TestApp.Status;
}
