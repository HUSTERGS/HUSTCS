// ObjectWindows - (C) Copyright 1992 by Borland International

#include "owl.h"

  /* Declare TScribbleApp, a TApplication descendant */
class TScribbleApp : public TApplication
{
public:
  TScribbleApp(LPSTR name, HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
    : TApplication(name, hInstance, hPrevInstance, lpCmdLine, nCmdShow) {};
  virtual void InitMainWindow();
};

  /* Declare TScribbleWindow, a TWindow descendant */
class TScribbleWindow : public TWindow
{
public:
  HDC HoldDC;
  BOOL ButtonDown ;
  TScribbleWindow(PTWindowsObject Parent,LPSTR name);
  virtual void WMLButtonDown(RTMessage Msg) = [WM_FIRST + WM_LBUTTONDOWN];
  virtual void WMLButtonUp(RTMessage Msg) = [WM_FIRST + WM_LBUTTONUP];
  virtual void WMMouseMove(RTMessage Msg) = [WM_FIRST + WM_MOUSEMOVE];
  virtual void WMRButtonDown(RTMessage Msg) = [WM_FIRST + WM_RBUTTONDOWN];
};

TScribbleWindow::TScribbleWindow(PTWindowsObject AParent, LPSTR AName)
                : TWindow(AParent, AName)
{
  ButtonDown = FALSE;
}

/* Define a TScribbleWindow's response to an incoming "left-button-down"
  message.  In response, TScribbleWindows prepare to draw a line,
  setting the current position in client area, retrieving a display
  context from MS-Windows, and capturing mouse input. */
void TScribbleWindow::WMLButtonDown(RTMessage Msg)
{
  if (!ButtonDown)
  {
    ButtonDown = TRUE;
    // Direct all subsequent mouse input to this window
    SetCapture(HWindow); //MS-Windows function
    HoldDC = GetDC(HWindow);
    MoveTo (HoldDC, Msg.LP.Lo, Msg.LP.Hi);
  }
}

/* Define a TScribbleWindow's response to an incoming "mouse-move"
  message.  In response, TScribbleWindows draw a line using the new
  position of the mouse. */
void TScribbleWindow::WMMouseMove(RTMessage Msg)
{
  if (ButtonDown)
    LineTo(HoldDC, Msg.LP.Lo, Msg.LP.Hi);   // draw the line
}


/* Define a TScribbleWindow's response to an incoming "left-button-up"
  message.  In response, TScribbleWindows "cleanup" required after a
  line is drawn, releasing the display context to MS-Windows, and
  releasing mouse input. */
void TScribbleWindow::WMLButtonUp(RTMessage)
{
  if (ButtonDown)
  {
    ReleaseCapture();
    ReleaseDC(HWindow, HoldDC);
    ButtonDown = FALSE;
  }
}

/* Define a TScribbleWindow's response to an incoming
   "right-button-down" message.  In response, TScribbleWindows "clear"
   their client area. */
void TScribbleWindow::WMRButtonDown(RTMessage)
{
  // Invalidate the entire window
  InvalidateRect(HWindow, LPRECT(NULL), TRUE);  // MS-Windows function
  // MS-Windows will send WM_PAINT message to the window
}

void TScribbleApp::InitMainWindow()
{
  MainWindow = new TScribbleWindow(NULL, "Scribble Away!");
}

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
  LPSTR lpCmdLine, int nCmdShow)
{
  TScribbleApp ScribbleApp ("Scribble", hInstance, hPrevInstance,
    lpCmdLine, nCmdShow);
  ScribbleApp.Run();
  return ScribbleApp.Status;
}
