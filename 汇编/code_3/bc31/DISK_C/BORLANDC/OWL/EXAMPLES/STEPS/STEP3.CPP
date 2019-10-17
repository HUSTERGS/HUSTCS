// ObjectWindows - (C) Copyright 1992 by Borland International

#include <stdio.h>
#include <string.h>
#include <owl.h>

class TMyApp : public TApplication
{
public:
  TMyApp(LPSTR AName, HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
    : TApplication(AName, hInstance, hPrevInstance, lpCmdLine, nCmdShow) {};
  virtual void InitMainWindow();
};

_CLASSDEF(TMyWindow)
class TMyWindow : public TWindow
{
public:
  TMyWindow(PTWindowsObject AParent, LPSTR ATitle)
    : TWindow(AParent, ATitle) {};
  virtual BOOL CanClose();
  virtual void WMLButtonDown(RTMessage Msg)
    = [WM_FIRST + WM_LBUTTONDOWN];
  virtual void WMRButtonDown(RTMessage Msg)
    = [WM_FIRST + WM_RBUTTONDOWN];
};

BOOL TMyWindow::CanClose()
{
  return MessageBox(HWindow, "Do you want to save?",
    "Drawing has changed", MB_YESNO | MB_ICONQUESTION) == IDNO;
}

void TMyWindow::WMLButtonDown(RTMessage Msg)
{
  HDC DC;
  char S[16];

  sprintf(S, "(%d,%d)", Msg.LP.Lo, Msg.LP.Hi);
  DC = GetDC(HWindow);
  TextOut(DC, Msg.LP.Lo, Msg.LP.Hi, S, strlen(S));
  ReleaseDC(HWindow, DC);
}

void TMyWindow::WMRButtonDown(RTMessage)
{
  InvalidateRect(HWindow, NULL, TRUE);
}

void TMyApp::InitMainWindow()
{
  MainWindow = new TMyWindow(NULL, Name);
}

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
  LPSTR lpCmdLine, int nCmdShow)
{
  TMyApp MyApp("Sample ObjectWindows Program", hInstance, hPrevInstance,
               lpCmdLine, nCmdShow);
  MyApp.Run();
  return MyApp.Status;
}
