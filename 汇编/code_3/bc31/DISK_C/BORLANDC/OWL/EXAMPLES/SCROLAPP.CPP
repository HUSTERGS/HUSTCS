// ObjectWindows - (C) Copyright 1992 by Borland International

#include <owl.h>

// Declare TScrollApp, a TApplication descendant
class TScrollApp : public TApplication {
public:
  TScrollApp(LPSTR AName, HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
    : TApplication(AName, hInstance, hPrevInstance, lpCmdLine, nCmdShow) {};
  virtual void InitMainWindow();
};

// Declare TScrollWindow, a TWindow descendant
class TScrollWindow : public TWindow
{
public:
  TScrollWindow(LPSTR ATitle);
  virtual void Paint(HDC PaintDC, PAINTSTRUCT& PaintInfo);
};

/* Constructor for a TScrollWindow, sets scroll styles and
   constructs the Scroller object. */
TScrollWindow::TScrollWindow(LPSTR ATitle) : TWindow(NULL, ATitle)
{
  Attr.Style |= WS_VSCROLL | WS_HSCROLL;
  Scroller = new TScroller(this, 8, 15, 80, 60);
}

/* Responds to an incoming "paint" message by redrawing boxes. Note
   that the Scroller's BeginView method, which sets the viewport origin
   relative to the present scroll position, has already been called. */
void TScrollWindow::Paint(HDC PaintDC,PAINTSTRUCT&)
{
  int X1, Y1, I;

  for (I = 0; I <= 49; ++I)
  {
    X1 = 10 + I*8;
    Y1 = 30 + I*5;
    Rectangle(PaintDC, X1, Y1, X1 + X1, X1 + Y1 * 2);
  }
}

// Construct the TScrollApp's MainWindow of type TScrollWindow
void TScrollApp::InitMainWindow()
{
  MainWindow = new TScrollWindow("Boxes");
}

// Run the ScrollApp
int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
  LPSTR lpCmdLine, int nCmdShow)
{
  TScrollApp ScrollApp("ScrollApp", hInstance, hPrevInstance,
    lpCmdLine, nCmdShow);
  ScrollApp.Run();
  return ScrollApp.Status;
}
