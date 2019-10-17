// ObjectWindows - (C) Copyright 1992 by Borland International

#include <owl.h>
#include <window.h>
#include <listbox.h>

const WORD ID_LISTBOX = 101;

class TTestApp : public TApplication
{
public:
  TTestApp(LPSTR AName, HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
    : TApplication(AName, hInstance, hPrevInstance, lpCmdLine, nCmdShow) {};
  virtual void InitMainWindow();
};

class TLBoxWindow : public TWindow
{
public:
  PTListBox ListBox;
  TLBoxWindow(PTWindowsObject AParent, LPSTR ATitle);
  virtual void SetupWindow();
  virtual void HandleListBoxMsg(RTMessage Msg)
    = [ID_FIRST + ID_LISTBOX];
  virtual void WMSetFocus(RTMessage Msg) =
    [WM_FIRST + WM_SETFOCUS];
};

TLBoxWindow::TLBoxWindow(PTWindowsObject AParent, LPSTR ATitle) :
  TWindow(AParent, ATitle)
{
  ListBox = new TListBox(this, ID_LISTBOX, 20, 20, 340, 100);
}

void TLBoxWindow::SetupWindow()
{
  TWindow::SetupWindow();
  ListBox->AddString("Item 1");
  ListBox->AddString("Item 2");
  ListBox->AddString("Item 3");
  ListBox->InsertString("Item 1.5", 1);
  ListBox->AddString("Item 4");
  ListBox->AddString("Item 5");
  ListBox->AddString("Item 6");
}

void TLBoxWindow::HandleListBoxMsg(RTMessage Msg)
{
  int Idx;
  char Str[10];

  if ( Msg.LP.Hi == LBN_SELCHANGE )
  {
    Idx = ListBox->GetSelIndex();
    if ( ListBox->GetStringLen(Idx) <= sizeof(Str))
    {
      ListBox->GetSelString(Str, sizeof(Str));
      MessageBox(HWindow, Str, "You selected:", MB_OK);
    }
  }
}

/* When the TLBoxWindow gets focus, pass it on to the list box.
   This could also be done by calling EnableKBHandler in the
   TLBoxWindow constructor (see lbxttest.cpp). */
void TLBoxWindow::WMSetFocus(RTMessage)
{
  SetFocus(ListBox->HWindow);
}

void TTestApp::InitMainWindow()
{
  MainWindow = new TLBoxWindow(NULL, Name);
}

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
  LPSTR lpCmdLine, int nCmdShow)
{
  TTestApp TestApp("List Box Tester", hInstance, hPrevInstance,
    lpCmdLine, nCmdShow);
  TestApp.Run();
  return TestApp.Status;
}
