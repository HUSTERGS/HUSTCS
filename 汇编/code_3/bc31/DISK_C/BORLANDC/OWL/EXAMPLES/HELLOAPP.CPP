// ObjectWindows - (C) Copyright 1992 by Borland International

#include <owl.h>

// Define a class derived from TApplication
class THelloApp :public TApplication
{
public:
  THelloApp(LPSTR AName, HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
    : TApplication(AName, hInstance, hPrevInstance, lpCmdLine, nCmdShow) {};
  virtual void InitMainWindow();
};

// Construct the THelloApp's MainWindow data member
void THelloApp::InitMainWindow()
{
  MainWindow = new TWindow(NULL, "Hello World!");
}

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
  LPSTR lpCmdLine, int nCmdShow)
{
  THelloApp HelloApp ("HelloApp", hInstance, hPrevInstance,
    lpCmdLine, nCmdShow);
  HelloApp.Run();
  return HelloApp.Status;
}
