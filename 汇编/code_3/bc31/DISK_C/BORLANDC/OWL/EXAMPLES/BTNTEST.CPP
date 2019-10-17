// ObjectWindows - (C) Copyright 1992 by Borland International

#include <owl.h>
#include <button.h>
#include <checkbox.h>
#include <radiobut.h>
#include <groupbox.h>

const WORD ID_BUTTON = 101;
const WORD ID_RBUTTON1 = 102;
const WORD ID_RBUTTON2 = 103;
const WORD ID_CHECKBOX = 104;
const WORD ID_GROUPBOX = 105;

class TTestApp : public TApplication
{
public:
  TTestApp(LPSTR AName, HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
    : TApplication(AName, hInstance, hPrevInstance, lpCmdLine, nCmdShow) {};
  virtual void InitMainWindow();
};

class TTestWindow : public TWindow
{
public:
  TRadioButton *RTButton1, *RTButton2;
  TCheckBox *CheckBox;
  TGroupBox *GroupBox;
  TTestWindow(PTWindowsObject AParent, LPSTR ATitle);
  virtual void HandleButtonMsg(RTMessage Msg)
    = [ID_FIRST + ID_BUTTON];
  virtual void HandleCheckBoxMsg(RTMessage Msg)
    = [ID_FIRST + ID_CHECKBOX];
  virtual void HandleGroupBoxMsg(RTMessage Msg)
    = [ID_FIRST + ID_GROUPBOX];
};

TTestWindow::TTestWindow(PTWindowsObject AParent, LPSTR ATitle) :
  TWindow(AParent, ATitle)
{
  new TButton(this, ID_BUTTON, "State of Check Box",
    88, 48, 296, 24, FALSE);
  CheckBox = new TCheckBox(this, ID_CHECKBOX, "Check Box Text",
    158, 12, 150, 26, NULL);
  GroupBox = new TGroupBox(this, ID_GROUPBOX, "Group Box",
    158, 102, 176, 108);
  RTButton1 = new TRadioButton(this, ID_RBUTTON1, "Radio Button 1",
    174, 128, 138, 24, GroupBox);
  RTButton2 = new TRadioButton(this, ID_RBUTTON2, "Radio Button 2",
    174, 162, 138, 24, GroupBox);
}

void TTestWindow::HandleButtonMsg(RTMessage)
{
  if ( CheckBox->GetCheck() == BF_CHECKED )
    MessageBox(HWindow, "Checked", "The check box is:", MB_OK);
  else
    MessageBox(HWindow, "Unchecked", "The check box is:", MB_OK);
}

void TTestWindow::HandleCheckBoxMsg(RTMessage)
{
  MessageBox(HWindow, "Toggled", "The check box has been:", MB_OK);
}

void TTestWindow::HandleGroupBoxMsg(RTMessage)
{
  char TextBuff[20];

  if ( RTButton1->GetCheck() == BF_CHECKED )
    GetWindowText(RTButton1->HWindow, TextBuff, sizeof(TextBuff));
  else
    GetWindowText(RTButton2->HWindow, TextBuff, sizeof(TextBuff));
  MessageBox(HWindow, TextBuff, "You have selected:", MB_OK);
}

void TTestApp::InitMainWindow()
{
  MainWindow = new TTestWindow(NULL, Name);
}

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
  LPSTR lpCmdLine, int nCmdShow)
{
  TTestApp TestApp("Button Tester", hInstance, hPrevInstance,
    lpCmdLine, nCmdShow);
  TestApp.Run();
  return TestApp.Status;
}
