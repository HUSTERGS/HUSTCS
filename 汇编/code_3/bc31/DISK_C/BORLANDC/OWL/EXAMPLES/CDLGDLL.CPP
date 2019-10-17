// ObjectWindows - (C) Copyright 1992 by Borland International

#include <owl.h>
#include "colordlg.h"
#include "cdlgdll.h"

PTModule TheModule;

BOOL far _export GetColor(HWND ParentHandle, COLORREF _FAR & ColorBuffer)
{
  PTWindowsObject AParentAlias;
  TColorDialog *TheColorDialog;

  AParentAlias = TheModule->GetParentObject(ParentHandle);
  TheColorDialog= new TColorDialog (AParentAlias, ColorBuffer);
  return (TheModule->ExecDialog(TheColorDialog) == IDOK);
}

int FAR PASCAL LibMain(HINSTANCE hInstance, WORD /*wDataSeg*/,
  WORD /* cbHeapSize */, LPSTR lpCmdLine)
{
  int TheStatus;

  // Note that we can't ensure that TheModule is allocated
  // in memory owned by CDLGDLL.DLL.  Hence, it will get owned
  // by the first application that caused CDLGDLL.DLL to be
  // loaded.
  TheModule = new TModule("CDLGDLL", hInstance, lpCmdLine);
  TheStatus = TheModule->Status;
  if ( TheStatus != 0 )
  {
    delete TheModule;
    TheModule = NULL;
  }
  return (TheStatus == 0);
}

int FAR PASCAL WEP ( int /*bSystemExit*/ )
{
    // don't delete TheModule here.  We haven't guaranteed that
    // TheModule points to memory owned by CDLGDLL.DLL.  It
    // will belong to the application that first caused CDLGDLL.DLL
    // to be loaded.  At the time WEP is called, that application,
    // and all of its memory, has been deleted.
    return 1;
}
