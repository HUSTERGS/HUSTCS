// ObjectWindows - (C) Copyright 1992 by Borland International

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
  HDC DragDC;
  BOOL ButtonDown;

  TMyWindow(PTWindowsObject AParent, LPSTR ATitle);
  virtual BOOL CanClose();
  virtual void WMLButtonDown(RTMessage Msg)
    = [WM_FIRST + WM_LBUTTONDOWN];
  virtual void WMLButtonUp(RTMessage Msg)
    = [WM_FIRST + WM_LBUTTONUP];
  virtual void WMMouseMove(RTMessage Msg)
    = [WM_FIRST + WM_MOUSEMOVE];
  virtual void WMRButtonDown(RTMessage Msg)
    = [WM_FIRST + WM_RBUTTONDOWN];
};

TMyWindow::TMyWindow(PTWindowsObject AParent, LPSTR ATitle)
  : TWindow(AParent, ATitle)
{
  ButtonDown = FALSE;
}

BOOL TMyWindow::CanClose()
{
  return MessageBox(HWindow, "Do you want to save?",
    "Drawing has changed", MB_YESNO | MB_ICONQUESTION) == IDNO;
}

void TMyWindow::WMLButtonDown(RTMessage Msg)
{
  InvalidateRect(HWindow, NULL, TRUE);
  if ( !ButtonDown )
  {
    ButtonDown = TRUE;
    SetCapture(HWindow);
    DragDC = GetDC(HWindow);
    MoveTo(DragDC, Msg.LP.Lo, Msg.LP.Hi);
  }
}

void TMyWindow::WMMouseMove(RTMessage Msg)
{
  if ( ButtonDown )
    LineTo(DragDC, Msg.LP.Lo, Msg.LP.Hi);
}

void TMyWindow::WMLButtonUp(RTMessage)
{
  if ( ButtonDown )
  {
    ButtonDown = FALSE;
    ReleaseCapture();
    ReleaseDC(HWindow, DragDC);
  }
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
