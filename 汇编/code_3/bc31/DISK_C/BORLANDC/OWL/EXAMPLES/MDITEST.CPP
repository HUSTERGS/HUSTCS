// ObjectWindows - (C) Copyright 1992 by Borland International

#include <stdio.h>
#include <string.h>
#include <owl.h>
#include <mdi.h>
#include <checkbox.h>
#include "mditest.h"

class TTestApp : public TApplication
{
public:
  TTestApp(LPSTR AName, HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
    : TApplication(AName, hInstance, hPrevInstance, lpCmdLine, nCmdShow) {};
  virtual void InitMainWindow();
};

class TMyMDIChild : public TWindow
{
public:
  TCheckBox *CloseBox;
  TMyMDIChild(PTWindowsObject AParent, int ChildNum);
  virtual BOOL CanClose();
};

class TMyMDIFrame : public TMDIFrame
{
public:
  TMyMDIFrame(LPSTR ATitle) : TMDIFrame(ATitle, "COMMANDS") {};
  void SetupWindow();
  virtual PTWindowsObject CreateChild();
  int GetChildCount();
  virtual void CMCountChildren(RTMessage Msg)
    = [CM_FIRST + CM_COUNTCHILDREN];
};

// TMyMDIChild's constructor instantiates a checkbox
TMyMDIChild::TMyMDIChild(PTWindowsObject AParent, int ChildNum)
  : TWindow(AParent, "")
{
  char TitleStr[12];

  sprintf(TitleStr, "%s%i", "Child #", ChildNum);
  Title = _fstrdup(TitleStr);
  CloseBox =
    new TCheckBox(this, ID_CLOSEBOX, "Cannot Close", 10, 10, 200, 20, NULL);
}

//  CanClose is dependent upon the state of the checkbox
BOOL TMyMDIChild::CanClose()
{
  BOOL BoxChecked;

  BoxChecked = ( CloseBox->GetCheck() == BF_CHECKED );
  return !BoxChecked;
}

// set up the TMDIFrame, creating its first child
void TMyMDIFrame::SetupWindow()
{
  TMDIFrame::SetupWindow();
  CreateChild();
}

//  create a new MDI child
PTWindowsObject TMyMDIFrame::CreateChild()
{
  return GetApplication()->MakeWindow(
    new TMyMDIChild(this, GetChildCount()+1));
}

void CountChild(void *, void *CountPtr)
{
 ++*(int *)CountPtr;	
}

//  return a count of the MDI children
int TMyMDIFrame::GetChildCount()
{
  int Count = 0;

  ForEach(CountChild, &Count);
  return Count;
}

//  display a message box which shows the number of children
void TMyMDIFrame::CMCountChildren(RTMessage)
{
  char CountStr[5];

  sprintf(CountStr, "%i", GetChildCount());
  MessageBox(HWindow, (LPSTR)CountStr, "Total Children", MB_OK);
}

void TTestApp::InitMainWindow()
{
  MainWindow = new TMyMDIFrame(Name);
}

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
  LPSTR lpCmdLine, int nCmdShow)
{
  TTestApp TestApp("MDI Conformist", hInstance, hPrevInstance,
    lpCmdLine, nCmdShow);
  TestApp.Run();
  return TestApp.Status;
}
