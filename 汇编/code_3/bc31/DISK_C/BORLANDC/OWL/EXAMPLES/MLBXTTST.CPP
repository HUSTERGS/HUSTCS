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

TLBoxWindow::TLBoxWindow() : TWindow(NULL, "Multiple-Selection List Box Transfer Tester")
{
  ListBox = new TListBox(this, ID_LISTBOX, 20, 20, 340, 300);
  ListBox->Attr.Style |= LBS_MULTIPLESEL;
  ListBoxData = new TListBoxData();
  ListBox->EnableTransfer();

  ListBoxData->AddString("Nancy");
  ListBoxData->AddString("Kathy");
  ListBoxData->AddString("Robert");
  ListBoxData->AddString("Carol");
  ListBoxData->AddString("Marina");
  ListBoxData->AddString("Stanley");
  ListBoxData->AddString("Lynn");
  ListBoxData->AddString("Laura");
  ListBoxData->AddString("Dan");
  ListBoxData->AddString("Mike");
  ListBoxData->AddString("Latesh");
  ListBoxData->AddString("Craig", TRUE);
  ListBoxData->AddString("Danny");
  ListBoxData->AddString("Spencer");
  ListBoxData->AddString("Liang-Jye");
  ListBoxData->AddString("Bradford", TRUE);
  ListBoxData->AddString("Tayloe");
  ListBoxData->AddString("Daniel");
  ListBoxData->AddString("Cecile");
  ListBoxData->AddString("Ken");
  ListBoxData->AddString("Keimpe", TRUE);
  ListBoxData->AddString("Julie");
  ListBoxData->AddString("Scott");
  ListBoxData->AddString("Mike");
  ListBoxData->AddString("Rick");
  ListBoxData->AddString("Pete");
  ListBoxData->AddString("Eric");
  ListBoxData->AddString("Lee");
  ListBoxData->AddString("Chopin");
  ListBoxData->AddString("Eli");
  ListBoxData->AddString("Pat");
  ListBoxData->AddString("Charles");

  // could be done by AddString instead.
  ListBoxData->SelectString("Eric");

  TransferBuffer = &ListBoxData;
  EnableKBHandler(); // so focus goes to ListBox, see also lboxtest.cpp
}

TLBoxWindow::~TLBoxWindow()
{
  delete ListBoxData;
}

void TLBoxWindow::HandleListBoxMsg(RTMessage Msg)
{
  Pchar TheStr;
  WORD Pos = 0, Length, NumSelected;

  if ( Msg.LP.Hi == LBN_SELCHANGE )
  {
    ListBox->Transfer(&ListBoxData, TF_GETDATA);
    NumSelected = ListBoxData->SelCount;
    if ( NumSelected )
    {
      TheStr = new char[NumSelected * 10];
      for ( int I = 0; I < NumSelected; I++ )
      {
        Length = ListBoxData->GetSelStringLength(I);
        ListBoxData->GetSelString((LPSTR)&TheStr[Pos], Length + 1, I);
        Pos += Length;
        if ( I < NumSelected - 1 )
          TheStr[Pos++] = '\n';
      }
      MessageBox(HWindow, TheStr, "You have selected:", MB_OK);
      delete TheStr;
    }
    else
      MessageBox(HWindow, "<No items are selected>",
                 "You have selected:", MB_OK);
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
