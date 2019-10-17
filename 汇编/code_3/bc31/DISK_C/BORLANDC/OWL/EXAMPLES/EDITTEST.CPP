// ObjectWindows - (C) Copyright 1992 by Borland International

#include <stdio.h>
#include <owl.h>
#include <window.h>
#include <edit.h>
#include <static.h>
#include <button.h>

const WORD ID_EDIT1 = 101;
const WORD ID_EDIT2 = 102;
const WORD ID_BUTTON = 103;
const WORD MAX_TEXTLEN = 20;

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
  TEdit *Edit1, *Edit2;
  TTestWindow::TTestWindow(PTWindowsObject AParent, LPSTR ATitle);
  virtual void HandleButtonMsg(RTMessage Msg)
    = [ID_FIRST + ID_BUTTON];
};

TTestWindow::TTestWindow(PTWindowsObject AParent, LPSTR ATitle)
  : TWindow(AParent, ATitle)
{
  new TStatic(this, -1, "&Original:", 20, 30, 150, 20, 0);
  Edit1 = new TEdit(this, ID_EDIT1, "Default Text", 20, 50, 150, 30,
    MAX_TEXTLEN, FALSE);
  new TButton(this, ID_BUTTON, "-->", 190, 50, 50, 30, FALSE);
  new TStatic(this, -1, "&Copy:", 260, 30, 150, 20, 0);
  Edit2 = new TEdit(this, ID_EDIT2, "", 260, 50, 150, 30, MAX_TEXTLEN, FALSE);
  Edit2->Attr.Style |= ES_UPPERCASE;
  AssignMenu("COMMANDS");
  EnableKBHandler();
}

void TTestWindow::HandleButtonMsg(RTMessage)
{
  int StartPos, EndPos;
  char TheText[MAX_TEXTLEN];

  // Handle notification messages from button
  Edit1->GetSelection(StartPos, EndPos);
  if ( StartPos == EndPos )
    Edit1->GetText(TheText, sizeof(TheText));
  else Edit1->GetSubText(TheText, StartPos, EndPos);
  Edit2->SetText(TheText);
  Edit1->SetSelection(0, 0);
}

void TTestApp::InitMainWindow()
{
  MainWindow = new TTestWindow(NULL, Name);
}

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
  LPSTR lpCmdLine, int nCmdShow)
{
  TTestApp TestApp("Edit Control Tester", hInstance, hPrevInstance,
    lpCmdLine, nCmdShow);
  TestApp.Run();
  return TestApp.Status;
}
