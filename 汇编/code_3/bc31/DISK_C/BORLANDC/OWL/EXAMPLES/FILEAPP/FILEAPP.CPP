// ObjectWindows - (C) Copyright 1992 by Borland International

#include "owl.h"
#include "filewnd.h"

// Declare TFileApp, a TApplication descendant
class TFileApp : public TApplication {
public:
    TFileApp(LPSTR AName, HINSTANCE hInstance, HINSTANCE hPrevInstance,
      LPSTR lpCmdLine, int nCmdShow)
      : TApplication(AName, hInstance, hPrevInstance, lpCmdLine, nCmdShow) {};
    virtual void InitMainWindow();
    virtual void InitInstance();
};

// Declare TMyFileWindow, a TFileWindow descendant
class TMyFileWindow : public TFileWindow {
public:
    TMyFileWindow(PTWindowsObject, LPSTR, LPSTR);
};

// Construct a TMyFileWindow, loading its menu
TMyFileWindow::TMyFileWindow(PTWindowsObject AParent, LPSTR ATitle,
  LPSTR AFileName)
  : TFileWindow(AParent, ATitle, AFileName)
{
  AssignMenu("FileCommands");
}

// Construct the TFileApp's MainWindow of type TMyFileWindow
void TFileApp::InitMainWindow()
{
  MainWindow = new TMyFileWindow(NULL, "File Window", "");
}

/* Initialize each MS-Windows application instance, loading an
  accelerator table */
void TFileApp::InitInstance()
{
  TApplication::InitInstance();
  if ( Status == 0 )
    HAccTable = LoadAccelerators(hInstance, "FileCommands");
}

// Run the FileApp
int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
  LPSTR lpCmdLine, int nCmdShow)
{
    TFileApp FileApp ("FileApp", hInstance, hPrevInstance,
      lpCmdLine, nCmdShow);
    FileApp.Run();
    return FileApp.Status;
}
