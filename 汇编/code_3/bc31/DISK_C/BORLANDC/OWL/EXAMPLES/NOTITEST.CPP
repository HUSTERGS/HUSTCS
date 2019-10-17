// ObjectWindows - (C) Copyright 1992 by Borland International

#include <stdio.h>
#include <owl.h>
#include <button.h>
#include "notitest.h"

class TBeepButton : public TButton
{
public:
  TBeepButton(PTWindowsObject AParent, int ResourceId)
    : TButton(AParent, ResourceId) {};
  virtual void BNClicked(RTMessage Msg) =
    [NF_FIRST + BN_CLICKED];
};

class TBeepDialog : public TDialog
{
public:
  int NumClicks;
  TBeepButton *BeepButton;
  TBeepDialog(PTWindowsObject AParent, LPSTR AName);
  virtual void HandleButtonMsg(RTMessage Msg) =
    [ID_FIRST + ID_BUTTON];
};

class TTestWindow : public TWindow
{
public:
  TTestWindow(PTWindowsObject AParent, LPSTR ATitle);
  virtual void CMTest(RTMessage Msg) =
    [CM_FIRST + CM_TEST];
};

class TTestApp : public TApplication
{
public:
  TTestApp(LPSTR AName, HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
    : TApplication(AName, hInstance, hPrevInstance, lpCmdLine, nCmdShow) {};
  virtual void InitMainWindow();
};

TBeepDialog::TBeepDialog(PTWindowsObject AParent, LPSTR AName)
  : TDialog(AParent, AName)
{
  NumClicks = 0;
  BeepButton = new TBeepButton(this, ID_BUTTON);
}

void TBeepDialog::HandleButtonMsg(RTMessage)
{
  char Text[4];

  sprintf(Text, "%d", ++NumClicks);
  SetWindowText(GetItemHandle(ID_STATIC), Text);
}

TTestWindow::TTestWindow(PTWindowsObject AParent, LPSTR ATitle)
  : TWindow(AParent, ATitle)
{
  AssignMenu("COMMANDS");
}

void TTestWindow::CMTest(RTMessage)
{
  TBeepDialog *TheDialog;

  TheDialog = new TBeepDialog(this, "TESTDIALOG");
  GetModule()->ExecDialog(TheDialog);
}

void TBeepButton::BNClicked(RTMessage Msg)
{
  MessageBeep(0);
  DefNotificationProc(Msg);
}

void TTestApp::InitMainWindow()
{
  MainWindow = new TTestWindow(NULL, "Subclass Tester");
}

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
  LPSTR lpCmdLine, int nCmdShow)
{
  TTestApp TestApp("Subclass Tester", hInstance, hPrevInstance,
    lpCmdLine, nCmdShow);
  TestApp.Run();
  return TestApp.Status;
}
