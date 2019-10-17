// ObjectWindows - (C) Copyright 1992 by Borland International

#include <owl.h>
#include <editwnd.h>

// Declare TEditApp, a TApplication descendant
class TEditApp : public TApplication {
public:
    TEditApp(LPSTR name, HINSTANCE hInstance, HINSTANCE hPrevInstance,
      LPSTR lpCmdLine, int nCmdShow)
      : TApplication(name, hInstance, hPrevInstance, lpCmdLine, nCmdShow) {};
    virtual void InitMainWindow();
    virtual void InitInstance();
};

// Declare TMyEditWindow, a TEditWindow descendant
class TMyEditWindow : public TEditWindow {
public:
    TMyEditWindow(PTWindowsObject AParent, LPSTR ATitle);
};

// Construct a TMyEditWindow, loading its menu
TMyEditWindow::TMyEditWindow(PTWindowsObject AParent, LPSTR ATitle)
              :TEditWindow(AParent, ATitle)
{
  AssignMenu("EditCommands");
}

/* Construct the TEditApp's MainWindow of type TMyEditWindow */
void TEditApp::InitMainWindow()
{
  MainWindow =  new TMyEditWindow(NULL, "EditWindow");
}

/* Initialize each MS-Windows application instance, loading an
  accelerator table */
void TEditApp::InitInstance()
{
  TApplication::InitInstance();
  HAccTable = LoadAccelerators(hInstance, "EditCommands");
}

// Run the EditApp
int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
  LPSTR lpCmdLine, int nCmdShow)
{
  TEditApp EditApp ("EditApp", hInstance, hPrevInstance,
    lpCmdLine, nCmdShow);
  EditApp.Run();
  return EditApp.Status;
}
