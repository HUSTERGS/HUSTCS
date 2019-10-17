// ObjectWindows - (C) Copyright 1992 by Borland International

#include <stdio.h>
#include <owl.h>
#include <button.h>
#include "dctltest.h"

class TTestApp : public TApplication
{
public:
  TTestApp(LPSTR AName, HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
    : TApplication(AName, hInstance, hPrevInstance, lpCmdLine, nCmdShow) {};
  virtual void InitMainWindow();
};

_CLASSDEF(TDrawableButton)

class TDrawableButton : public TButton
{
public:
  TDrawableButton(PTWindowsObject AParent, int ResourceId) :
    TButton(AParent, ResourceId) {}
  void ODADrawEntire(DRAWITEMSTRUCT far & DrawInfo);
  void ODAFocus(DRAWITEMSTRUCT far & DrawInfo);
  void ODASelect(DRAWITEMSTRUCT far & DrawInfo);
};

/* Function called when button needs to be drawn */
void TDrawableButton::ODADrawEntire(DRAWITEMSTRUCT far & DrawInfo)
{
  Rectangle(DrawInfo.hDC, DrawInfo.rcItem.left, DrawInfo.rcItem.top,
    DrawInfo.rcItem.right, DrawInfo.rcItem.bottom);
  if ( IsCurrentDefPB )
      Rectangle(DrawInfo.hDC, DrawInfo.rcItem.left+1,
                DrawInfo.rcItem.top+1, DrawInfo.rcItem.right-1,
                DrawInfo.rcItem.bottom-1);

  DrawInfo.rcItem.top += 6;
  DrawText(DrawInfo.hDC, "DRAWN", -1, &DrawInfo.rcItem,
    DT_CENTER | DT_VCENTER);
  if ( (DrawInfo.itemState & ODS_FOCUS) == ODS_FOCUS )
  {
    DrawInfo.rcItem.left += 4;
    DrawInfo.rcItem.right -= 4; DrawInfo.rcItem.bottom -= 6;
    DrawFocusRect(DrawInfo.hDC, &DrawInfo.rcItem);
  }
}

/* Function called when button gains or loses focus */
void TDrawableButton::ODAFocus(DRAWITEMSTRUCT far & DrawInfo)
{
  DrawInfo.rcItem.top += 6; DrawInfo.rcItem.left += 4;
  DrawInfo.rcItem.right -= 4; DrawInfo.rcItem.bottom -= 6;
  DrawFocusRect(DrawInfo.hDC, &DrawInfo.rcItem);
}

/* Function called when button's selection status changes */
void TDrawableButton::ODASelect(DRAWITEMSTRUCT far & DrawInfo)
{
  Rectangle(DrawInfo.hDC, DrawInfo.rcItem.left, DrawInfo.rcItem.top,
    DrawInfo.rcItem.right, DrawInfo.rcItem.bottom);
  if ( IsCurrentDefPB )
      Rectangle(DrawInfo.hDC, DrawInfo.rcItem.left+1,
                DrawInfo.rcItem.top+1, DrawInfo.rcItem.right-1,
                DrawInfo.rcItem.bottom-1);

  DrawInfo.rcItem.top += 6;
  if ( (DrawInfo.itemState & ODS_SELECTED) == ODS_SELECTED)
    DrawText(DrawInfo.hDC, "SELECTED", -1, &DrawInfo.rcItem,
      DT_CENTER | DT_VCENTER);
  else
    DrawText(DrawInfo.hDC, "DESELECTED", -1, &DrawInfo.rcItem,
      DT_CENTER | DT_VCENTER);
  if ( (DrawInfo.itemState & ODS_FOCUS) == ODS_FOCUS )
  {
    DrawInfo.rcItem.left += 4;
    DrawInfo.rcItem.right -= 4; DrawInfo.rcItem.bottom -= 6;
    DrawFocusRect(DrawInfo.hDC, &DrawInfo.rcItem);
  }
}

class TTestDialog : public TDialog
{
public:
  PTDrawableButton Button1;
  PTDrawableButton Button2;

  TTestDialog(PTWindowsObject AParent);
  virtual void IDButton1(RTMessage) = [ID_FIRST + ID_BUTTON1]
      { MessageBeep(0);}
};

TTestDialog::TTestDialog(PTWindowsObject AParent)
  : TDialog(AParent, "TESTDIALOG")
{
  Button1 = new TDrawableButton(this, ID_BUTTON1);
  Button2 = new TDrawableButton(this, ID_BUTTON2);
}

class TTestWindow : public TWindow
{
public:
  TTestWindow(PTWindowsObject AParent, LPSTR ATitle);
  virtual void Test(RTMessage Msg)
    = [CM_FIRST + CM_TEST];
};

TTestWindow::TTestWindow(PTWindowsObject AParent, LPSTR ATitle)
  : TWindow(AParent, ATitle)
{
  AssignMenu("COMMANDS");
}

void TTestWindow::Test(RTMessage)
{
  GetApplication()->ExecDialog(new TTestDialog(this));
}

void TTestApp::InitMainWindow()
{
  MainWindow = new TTestWindow(NULL, Name);
}

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
  LPSTR lpCmdLine, int nCmdShow)
{
  TTestApp TestApp("Drawable Button Tester", hInstance, hPrevInstance,
    lpCmdLine, nCmdShow);
  TestApp.Run();
  return TestApp.Status;
}
