// ObjectWindows - (C) Copyright 1992 by Borland International

#include <owl.h>
#include "dllhello.h"
#include "calldll.h"

class TCallDLLApp : public TApplication {
public:
  TCallDLLApp(LPSTR Name, HINSTANCE hInstance,
		  HINSTANCE hPrevInstance, LPSTR lpCmd,
		  int nCmdShow)
	        : TApplication(Name, hInstance,
			       hPrevInstance, lpCmd, nCmdShow) {};
  virtual void InitMainWindow();
};

class TTestWindow : public TWindow {
public:
  TTestWindow(PTWindowsObject AParent, LPSTR ATitle);
  virtual void CMCreate(TMessage& Msg) = [CM_FIRST + CM_CREATE];
};

TTestWindow::TTestWindow(PTWindowsObject AParent, LPSTR ATitle)
  : TWindow(AParent, ATitle)
{
  AssignMenu("COMMANDS");
}

void TTestWindow::CMCreate(TMessage&)
{
  CreateDLLWindow(HWindow);
}

void TCallDLLApp::InitMainWindow()
{
  MainWindow = new TTestWindow(NULL, "Create a DLL Window");
}

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
		   LPSTR lpCmd, int nCmdShow)
{
  TCallDLLApp CallDLLApp("CallDLL", hInstance, hPrevInstance,
		lpCmd, nCmdShow);
  CallDLLApp.Run();
  return(CallDLLApp.Status);
}
