// ObjectWindows - (C) Copyright 1992 by Borland International

#include <owl.h>
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
  TListBox *ListBox;
  PTListBoxData ListBoxData;

  TLBoxWindow();
  ~TLBoxWindow();
  virtual void HandleListBoxMsg(RTMessage Msg) =
    [ID_FIRST + ID_LISTBOX];
};

TLBoxWindow::TLBoxWindow() : TWindow(NULL, "List Box Transfer Tester")
{
  ListBox = new TListBox(this, ID_LISTBOX, 20, 20, 340, 100);
  ListBoxData = new TListBoxData();
  ListBox->EnableTransfer();
  ListBoxData->AddString("Item 1");
  ListBoxData->AddString("Item 1.5");
  ListBoxData->AddString("Item 2");
  ListBoxData->AddString("Item 3", TRUE);
  ListBoxData->AddString("Item 4");
  ListBoxData->AddString("Item 5");
  ListBoxData->AddString("Item 6");
  TransferBuffer = &ListBoxData;
  EnableKBHandler(); // so focus goes to ListBox, see also lboxtest.cpp
}

TLBoxWindow::~TLBoxWindow()
{
  delete ListBoxData;
}

void TLBoxWindow::HandleListBoxMsg(RTMessage Msg)
{
  char TheStr[10];

  if ( Msg.LP.Hi == LBN_SELCHANGE )
  {
    ListBox->Transfer(&ListBoxData, TF_GETDATA);
    if ( ListBoxData->GetSelStringLength() < 10 )
    {
      ListBoxData->GetSelString(TheStr, 10);
      MessageBox(HWindow, TheStr, "You selected:", MB_OK);
    }
    else  // This should never happen, strings are all small enough
      MessageBox(HWindow, "Selection too large for output buffer",
          "Error", MB_OK);
  }
}

void TTestApp::InitMainWindow()
{
  MainWindow = new TLBoxWindow();
}

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
  LPSTR lpCmdLine, int nCmdShow)
{
  TTestApp TestApp("List Box Transfer Tester", hInstance, hPrevInstance,
    lpCmdLine, nCmdShow);
  TestApp.Run();
  return TestApp.Status;
}
