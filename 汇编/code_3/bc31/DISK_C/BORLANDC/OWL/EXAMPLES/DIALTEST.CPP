// ObjectWindows - (C) Copyright 1992 by Borland International

#include <owl.h>
#include <dialog.h>
#include "dialtest.h"

class TTestDialog : public TDialog
{
public:
  TTestDialog(PTWindowsObject AParent, LPSTR AName)
    : TDialog(AParent, AName) {};
  virtual void HandleButtonMsg(RTMessage Msg)
    = [ID_FIRST + ID_BUTTON];
  virtual void HandleListBoxMsg(RTMessage Msg)
    = [ID_FIRST + ID_LISTBOX];
};

class TTestWindow : public TWindow
{
public:
  TTestWindow(PTWindowsObject AParent, LPSTR ATitle);
  virtual void CMTest(RTMessage Msg)
    = [CM_FIRST + CM_TEST];
};

class TTestApp : public TApplication
{
public:
  TTestApp(LPSTR AName, HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow) :
    TApplication(AName, hInstance, hPrevInstance, lpCmdLine, nCmdShow) {};
  virtual void InitMainWindow();
};

void TTestDialog::HandleButtonMsg(RTMessage)
{
  SendDlgItemMsg(ID_LISTBOX, LB_ADDSTRING, 0, (LONG)"Item 1");
  SendDlgItemMsg(ID_LISTBOX, LB_ADDSTRING, 0, (LONG)"Item 2");
  SendDlgItemMsg(ID_LISTBOX, LB_ADDSTRING, 0, (LONG)"Item 3");
  SendDlgItemMsg(ID_LISTBOX, LB_ADDSTRING, 0, (LONG)"Item 4");
  SendDlgItemMsg(ID_LISTBOX, LB_ADDSTRING, 0, (LONG)"Item 5");
  SendDlgItemMsg(ID_LISTBOX, LB_ADDSTRING, 0, (LONG)"Item 6");
  SendDlgItemMsg(ID_LISTBOX, LB_ADDSTRING, 0, (LONG)"Item 7");
}

void TTestDialog::HandleListBoxMsg(RTMessage Msg)
{
  DWORD Idx;
  char SelectedText[10];

  if ( Msg.LP.Hi == LBN_SELCHANGE )
  {
    Idx = SendDlgItemMsg(ID_LISTBOX, LB_GETCURSEL, 0, 0L);
    SendDlgItemMsg(ID_LISTBOX, LB_GETTEXT, (WORD)Idx, (DWORD)SelectedText);
    MessageBox(HWindow, SelectedText, "You selected", MB_OK);
  }
}

TTestWindow::TTestWindow(PTWindowsObject AParent, LPSTR ATitle)
  : TWindow(AParent, ATitle)
{
  AssignMenu("COMMANDS");
}

void TTestWindow::CMTest(RTMessage)
{
  GetApplication()->ExecDialog(new TTestDialog(this, "TESTDIALOG"));
}

void TTestApp::InitMainWindow()
{
  MainWindow = new TTestWindow(NULL, Name);
}

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
  LPSTR lpCmdLine, int nCmdShow)
{
  TTestApp TestApp("Dialog Tester", hInstance, hPrevInstance,
    lpCmdLine, nCmdShow);
  TestApp.Run();
  return (TestApp.Status);
}
