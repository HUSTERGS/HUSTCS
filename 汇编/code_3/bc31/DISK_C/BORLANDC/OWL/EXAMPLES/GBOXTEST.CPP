// ObjectWindows - (C) Copyright 1992 by Borland International

#include <stdio.h>
#include <string.h>
#include <owl.h>
#include <radiobut.h>
#include <groupbox.h>
#include <static.h>

const int ID_BCCGROUP = 100;
const int ID_BCC1 = 101;
const int ID_BCC5  = 102;
const int ID_BCC10 = 103;
const int ID_BCCX  = 104;
const int ID_CPPGROUP = 110;
const int ID_CPP1 = 111;
const int ID_CPP5  = 112;
const int ID_CPP10 = 113;
const int ID_CPPX  = 114;
const int ID_PLACEBUTTON = 131;
const int ID_CANCELBUTTON = 132;

class TOrderApp : public TApplication
{
public:
  TOrderApp(LPSTR Name, HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
    : TApplication(Name, hInstance, hPrevInstance, lpCmdLine, nCmdShow) {};
  virtual void InitMainWindow();
};

class TOrderWindow : public TWindow
{
public:
  PTGroupBox BCCGroup;
  PTGroupBox CPPGroup;

  TOrderWindow(PTWindowsObject AParent, LPSTR ATitle);
  virtual void HandleBCCGroupMsg(TMessage& Msg) =
    [ID_FIRST + ID_BCCGROUP];
  virtual void HandleCPPGroupMsg(TMessage& Msg) =
    [ID_FIRST + ID_CPPGROUP];
 };

TOrderWindow::TOrderWindow(PTWindowsObject AParent, LPSTR ATitle)
  : TWindow(AParent, ATitle)
{
  PTRadioButton TmpRB;
  Attr.X = 20;
  Attr.Y = 5;
  Attr.W = 380;
  Attr.H = 260;
  new TStatic(this, -1, "Borland C++ now includes an extensive Windows",
    20, 10, 380, 15, 55);
  new TStatic(this, -1, "class library and a complete toolkit for Windows",
    20, 27, 380, 15, 45);
  new TStatic(this, -1, "resource editing.", 20, 44, 380, 15, 55);
  new TStatic(this, -1, "              How many copies would you like?",
    10, 61, 380, 15, 35);
  BCCGroup = new TGroupBox(this, ID_BCCGROUP, "BCC Compiler",
    20, 80, 150, 105);
  TmpRB = new TRadioButton(this, ID_BCC1, "1", 30, 100, 40, 17, BCCGroup);
  TmpRB->Attr.Style |= WS_TABSTOP;
  new TRadioButton(this, ID_BCC5, "5", 30, 120, 40, 17, BCCGroup);
  new TRadioButton(this, ID_BCC10, "10", 30, 140, 40, 17, BCCGroup);
  new TRadioButton(this, ID_BCCX, "X", 30, 160, 40, 17, BCCGroup);
  CPPGroup = new TGroupBox(this, ID_CPPGROUP, "Professional Packs",
    189, 80, 150, 105);
  TmpRB = new TRadioButton(this, ID_CPP1, "1", 200, 100, 40, 17, CPPGroup);
  TmpRB->Attr.Style |= WS_TABSTOP;
  new TRadioButton(this, ID_CPP5, "5", 200, 120, 40, 17, CPPGroup);
  new TRadioButton(this, ID_CPP10, "10", 200, 140, 40, 17, CPPGroup);
  new TRadioButton(this, ID_CPPX, "X", 200, 160, 40, 17, CPPGroup);
  new TButton(this, ID_PLACEBUTTON, "PLACE ORDER", 20, 195, 157, 25, FALSE);
  new TButton(this, ID_CANCELBUTTON, "CANCEL ORDER", 181, 195, 157, 25, FALSE);
  EnableKBHandler();
}

void TOrderWindow::HandleBCCGroupMsg(TMessage&)
{
  MessageBox(HWindow, "Delivery will take 1 week", Title, MB_OK);
}

void TOrderWindow::HandleCPPGroupMsg(TMessage&)
{
  MessageBox(HWindow, "Delivery will take 2 weeks", Title, MB_OK);
}

void TOrderApp::InitMainWindow()
{
  MainWindow = new TOrderWindow(NULL, Name);
}

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
  LPSTR lpCmdLine, int nCmdShow)
{
  TOrderApp OrderApp("BCC Order Form", hInstance, hPrevInstance,
    lpCmdLine, nCmdShow);
  OrderApp.Run();
  return OrderApp.Status;
}
