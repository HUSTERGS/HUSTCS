// ObjectWindows - (C) Copyright 1992 by Borland International

#include "owl.h"

class TCursorApplication : public TApplication {
public:
    TCursorApplication (LPSTR name, HINSTANCE hInstance,
	                HINSTANCE hPrevInstance, LPSTR lpCmd,
			int nCmdShow)
		       : TApplication (name, hInstance,
			               hPrevInstance, lpCmd, nCmdShow) {};
    virtual void InitMainWindow();
};

class IBeamWindow : public TWindow {
public:
    IBeamWindow(PTWindowsObject AParent, LPSTR ATitle)
                 : TWindow(AParent, ATitle) {};
    virtual LPSTR GetClassName();
    virtual void GetWindowClass(WNDCLASS& AWndClass);
};

LPSTR IBeamWindow::GetClassName()
{
    return "IBeamWindow";
}

/* Call base class's GetWindowClass and then set IBeamWindow's cursor
   to the predefined cursor IDC_IBEAM */
void IBeamWindow::GetWindowClass(WNDCLASS& AWndClass)
{
  TWindow::GetWindowClass(AWndClass);
  AWndClass.hCursor = LoadCursor(0, IDC_IBEAM);
}

void TCursorApplication::InitMainWindow()
{
  MainWindow = new IBeamWindow (NULL, "Window With An I-Beam Cursor");
}

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
		   LPSTR lpCmd, int nCmdShow)
{
    TCursorApplication CursorApp ("CursorApp", hInstance, hPrevInstance,
		lpCmd, nCmdShow);
    CursorApp.Run();
    return (CursorApp.Status);
}

