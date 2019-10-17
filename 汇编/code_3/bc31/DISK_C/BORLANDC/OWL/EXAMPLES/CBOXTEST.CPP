// ObjectWindows - (C) Copyright 1992 by Borland International

#include <owl.h>
#include <window.h>
#include <static.h>
#include <button.h>
#include <listbox.h>
#include <combobox.h>

const ID_LISTBOX = 101;
const ID_COMBO1 = 102;
const ID_COMBO2 = 103;
const ID_COMBO3 = 104;
const ID_BUTTON1 = 105;
const ID_BUTTON2 = 106;

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
  TListBox *ListBox;
  TComboBox *Combo1, *Combo2, *Combo3;
  TTestWindow(PTWindowsObject AParent, LPSTR ATitle);
  virtual void SetupWindow();
  virtual void HandleButton1Msg(RTMessage Msg)
    = [ID_FIRST + ID_BUTTON1];
  virtual void HandleButton2Msg(RTMessage Msg)
    = [ID_FIRST + ID_BUTTON2];
};

TTestWindow::TTestWindow(PTWindowsObject AParent, LPSTR ATitle) :
  TWindow(AParent, ATitle)
{
  ListBox = new TListBox(this, ID_LISTBOX, 20, 30, 150, 100);
  Combo1 = new TComboBox(this, ID_COMBO1, 190, 30, 150, 100, CBS_SIMPLE, 0);
  Combo1->Attr.Style &= ~WS_VSCROLL;
  Combo2 = new TComboBox(this, ID_COMBO2, 20, 160, 150, 100, CBS_DROPDOWN, 0);
  Combo3 = new TComboBox(this, ID_COMBO3, 190, 160, 150, 100, CBS_DROPDOWNLIST, 0);
  new TButton(this, ID_BUTTON1, "Show", 190, 270, 65, 20, FALSE);
  new TButton(this, ID_BUTTON2, "Hide", 275, 270, 65, 20, FALSE);
  new TStatic(this, -1, "List Box", 20, 8, 150, 20, 0);
  new TStatic(this, -1, "Simple Combo", 190, 8, 150, 20, 0);
  new TStatic(this, -1, "Drop Down Combo", 20, 138, 150, 20, 0);
  new TStatic(this, -1, "Drop Down List", 190, 138, 150, 20, 0);
}

void TTestWindow::SetupWindow()
{
  TWindow::SetupWindow();
  ListBox->AddString("a");
  ListBox->AddString("b");
  ListBox->AddString("c");
  ListBox->AddString("d");
  ListBox->AddString("e");
  ListBox->AddString("f");

  Combo1->AddString("a");
  Combo1->AddString("b");
  Combo1->AddString("c");
  Combo1->AddString("d");
  Combo1->AddString("e");
  Combo1->AddString("f");

  Combo2->AddString("a");
  Combo2->AddString("b");
  Combo2->AddString("c");
  Combo2->AddString("d");
  Combo2->AddString("e");
  Combo2->AddString("f");

  Combo3->AddString("a");
  Combo3->AddString("b");
  Combo3->AddString("c");
  Combo3->AddString("d");
  Combo3->AddString("e");
  Combo3->AddString("f");
}

void TTestWindow::HandleButton1Msg(RTMessage)
{
  // Respond to the "Show" button being pressed.
  Combo3->ShowList();
}

void TTestWindow::HandleButton2Msg(RTMessage)
{
  // Respond to the "Hide" button being pressed.
  Combo3->HideList();
}

void TTestApp::InitMainWindow()
{
  MainWindow = new TTestWindow(NULL, Name);
}

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
  LPSTR lpCmdLine, int nCmdShow)
{
  TTestApp TestApp("Combo Box Tester", hInstance, hPrevInstance,
    lpCmdLine, nCmdShow);
  TestApp.Run();
  return TestApp.Status;
}
