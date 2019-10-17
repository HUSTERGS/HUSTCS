// ObjectWindows - (C) Copyright 1992 by Borland International

#include <stdlib.h>
#include <owl.h>
#include "windows.h"
#include "dllhello.h"

PTModule DLLHelloLib;

BOOL far _export CreateDLLWindow(HWND ParentHWnd)
{
  PTWindowsObject AParentAlias;
  PTWindow TheWindow;

  AParentAlias = DLLHelloLib->GetParentObject(ParentHWnd);
  TheWindow = new TWindow(AParentAlias, "Hello from a DLL!", DLLHelloLib);
  TheWindow->Attr.Style |= WS_POPUPWINDOW | WS_CAPTION | WS_THICKFRAME
    | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
  TheWindow->Attr.X = 100; TheWindow->Attr.Y = 100;
  TheWindow->Attr.W = 300; TheWindow->Attr.H = 300;
  return (DLLHelloLib->MakeWindow(TheWindow) == TheWindow);
}

int FAR PASCAL LibMain(HINSTANCE hInstance, WORD /*wDataSeg*/,
  WORD /* cbHeapSize */, LPSTR lpCmdLine)
{
    int TheStatus;

    // Note that we can't ensure that DLLHelloLib is allocated
    // in memory owned by DLLHELLO.DLL.  Hence, it will get owned
    // by the first application that caused DLLHELLO.DLL to be
    // loaded.
    DLLHelloLib = new TModule("DLLHello", hInstance, lpCmdLine);
    TheStatus = DLLHelloLib->Status;
    if ( TheStatus != 0 )
    {
      delete DLLHelloLib;
      DLLHelloLib = NULL;
    }
    return (TheStatus == 0);
}

int FAR PASCAL WEP ( int /*bSystemExit*/ )
{
    // don't delete DLLHelloLib here.  We haven't guaranteed that
    // DLLHelloLib points to memory owned by DLLHELLO.DLL.  It
    // will belong to the application that first caused DLLHELLO.DLL
    // to be loaded.  At the time WEP is called, that application,
    // and all of its memory, has been deleted.
    return 1;
}
