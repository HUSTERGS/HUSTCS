// ObjectWindows - (C) Copyright 1992 by Borland International

#include <owl.h>
#include <window.h>
#include <static.h>
#include <combobox.h>
#include <array.h>
#include <string.h>

const WORD ID_COMBOBOX = 102;
const int TheTextLen = 21;

class TTestApp : public TApplication
{
public:
  TTestApp(LPSTR AName, HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow) :
    TApplication(AName, hInstance, hPrevInstance, lpCmdLine, nCmdShow) {};
  virtual void InitMainWindow();
};


class TCBoxWindow : public TWindow
{
public:
  PTComboBox ComboBox;
  PTComboBoxData ComboBoxData;

  TCBoxWindow(PTWindowsObject AParent, LPSTR ATitle);
  ~TCBoxWindow();
};

TCBoxWindow::TCBoxWindow(PTWindowsObject AParent, LPSTR ATitle) :
  TWindow(AParent, ATitle)
{
  ComboBox = new TComboBox(this, ID_COMBOBOX, 190, 30, 150, 100,
    CBS_SIMPLE, TheTextLen);
  ComboBox->EnableTransfer();
  ComboBoxData = new TComboBoxData();
  ComboBoxData->AddString("a");
  ComboBoxData->AddString("b");
  ComboBoxData->AddString("c", TRUE);
  ComboBoxData->AddString("d");
  ComboBoxData->AddString("e");
  ComboBoxData->AddString("f");
  TransferBuffer = &ComboBoxData;
  EnableKBHandler();
}

TCBoxWindow::~TCBoxWindow()
{
  delete ComboBoxData;
}

void TTestApp::InitMainWindow()
{
  MainWindow = new TCBoxWindow(NULL, Name);
}

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
  LPSTR lpCmdLine, int nCmdShow)
{
  TTestApp TestApp("Combo Box Transfer Tester", hInstance, hPrevInstance,
    lpCmdLine, nCmdShow);
  TestApp.Run();
  return(TestApp.Status);
}
