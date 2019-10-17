// ObjectWindows - (C) Copyright 1992 by Borland International

#include <owl.h>
#include <radiobut.h>
#include <edit.h>
#include <string.h>
#include "trantest.h"

const MAXNAMELEN	= 26;
const MAXADDRLEN        = 47;
const MAXCITYSTLEN      = 27;
const MAXCOUNTRYLEN 	= 27;

struct TTransferStruct {
  BOOL MrTitle;
  BOOL MsTitle;
  BOOL DrTitle;
  char NameEdit[MAXNAMELEN];
  char Addr1Edit[MAXADDRLEN];
  char Addr2Edit[MAXADDRLEN];
  char CityStEdit[MAXCITYSTLEN];
  char CountryEdit[MAXCOUNTRYLEN];
};

class TTransferApp : public TApplication {
public:
  TTransferApp(LPSTR AName, HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
    : TApplication(AName, hInstance, hPrevInstance, lpCmdLine, nCmdShow) {};
  virtual void InitMainWindow();
};


class TTransferWindow : public TWindow {
public:
  TTransferStruct TransferStruct;

  TTransferWindow(PTWindowsObject AParent, LPSTR ATitle);
  virtual void CMTest(TMessage& Msg) = [CM_FIRST + CM_TEST];
};

class TTransferDialog : public TDialog {
public:
  TTransferDialog(PTWindowsObject AParent, int ResourceId);
};

TTransferWindow::TTransferWindow(PTWindowsObject AParent, LPSTR ATitle) :
  TWindow(AParent, ATitle)
{
  AssignMenu(ID_MENU);
  memset(&TransferStruct, 0x0, sizeof TransferStruct);
  TransferStruct.MrTitle = TRUE;
  TransferStruct.MsTitle = FALSE;
  TransferStruct.DrTitle = FALSE;
}

void TTransferWindow::CMTest(TMessage&)
{
  char ALabel[255];

  if ( GetModule()->ExecDialog(new TTransferDialog(this, ID_DIALOG)) == IDOK )
  {
    strcpy(ALabel, "Mailing Label Entered:\n\n");
    if ( TransferStruct.MrTitle )
      strcat(ALabel, "Mr. ");
    else
      if ( TransferStruct.MsTitle )
        strcat(ALabel, "Ms. ");
      else
        strcat(ALabel, "Dr. ");
    strcat(ALabel, TransferStruct.NameEdit);
    strcat(ALabel, "\n");
    strcat(ALabel, TransferStruct.Addr1Edit);
    strcat(ALabel, "\n");
    if ( strcmp(TransferStruct.Addr2Edit, "") != NULL )
    {
      strcat(ALabel, TransferStruct.Addr2Edit);
      strcat(ALabel, "\n");
    }
    strcat(ALabel, TransferStruct.CityStEdit);
    strcat(ALabel, "\n");
    strcat(ALabel, TransferStruct.CountryEdit);
    MessageBox(HWindow, ALabel, "Test Dialog Transfer", MB_OK);
  }
}

TTransferDialog::TTransferDialog(PTWindowsObject AParent, int ResourceId)
                 : TDialog(AParent, ResourceId)
{
  new TRadioButton(this, ID_MRBUTTON, NULL);
  new TRadioButton(this, ID_MSBUTTON, NULL);
  new TRadioButton(this, ID_DRBUTTON, NULL);
  new TEdit(this, ID_NAMEEDIT,
            sizeof(((TTransferWindow *)Parent)->TransferStruct.NameEdit));
  new TEdit(this, ID_ADDR1EDIT,
            sizeof(((TTransferWindow *)Parent)->TransferStruct.Addr1Edit));
  new TEdit(this, ID_ADDR2EDIT,
            sizeof(((TTransferWindow *)Parent)->TransferStruct.Addr2Edit));
  new TEdit(this, ID_CITYSTEDIT,
            sizeof(((TTransferWindow *)Parent)->TransferStruct.CityStEdit));
  new TEdit(this, ID_COUNTRYEDIT,
            sizeof(((TTransferWindow *)Parent)->TransferStruct.CountryEdit));
  TransferBuffer = (void far*)&(((TTransferWindow *)Parent)->TransferStruct);
}

void TTransferApp::InitMainWindow()
{
  MainWindow = new TTransferWindow(NULL, "Test Dialog Transfer");
}

// Main program
int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
  LPSTR lpCmdLine, int nCmdShow)
{
  TTransferApp TransferApp("TransferTest", hInstance, hPrevInstance,
    lpCmdLine, nCmdShow);
  TransferApp.Run();
  return TransferApp.Status;
}
