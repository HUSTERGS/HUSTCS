// ObjectWindows - (C) Copyright 1992 by Borland International

#include "owl.h"
#include "dialog.h"
#include "edit.h"
#include "string.h"	// for strcpy and strcat
#include "stdlib.h"	// for atoi
#include "ctype.h" 	// for isdigit and isalpha


#define CM_EMPINPUT 201
#define ID_NAMEEDIT 101
#define ID_SSEDIT 105
#define ID_IDEDIT 107

#define MAXNAMELEN 35
#define MAXSSLEN 12
#define MAXIDLEN 6

struct TTransferStruct {
    char NameEdit[MAXNAMELEN];
    char SSEdit[MAXSSLEN];
    char IDEdit[MAXIDLEN];
};

/* Declare TEmployeeDlg, a TDialog descendant */
class TEmployeeDlg : public TDialog {
public:
    char EmpName[MAXNAMELEN] ;
    char EmpSSNum[MAXSSLEN] ;
    char EmpID[MAXIDLEN] ;
    TEmployeeDlg(PTWindowsObject AParent, LPSTR name);
    virtual BOOL CanClose();

private:
    void FillBuffers();
    BOOL ValidName();
    BOOL ValidSSNum();
    BOOL ValidID();
};

/* Declare TTestWindow, a TWindow descendant */
class TTestWindow : public TWindow {
public:
    TTransferStruct TransferStruct;

    TTestWindow(PTWindowsObject AParent, LPSTR ATitle);
    virtual void EmpInput(RTMessage Msg) = [CM_FIRST + CM_EMPINPUT];
};

/* Declare TValidateApp, a TApplication descendant */
class TValidateApp : public TApplication {
public:
  TValidateApp(LPSTR name, HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
    : TApplication(name, hInstance, hPrevInstance, lpCmdLine, nCmdShow) {};
    virtual void InitMainWindow();
};

/*--------------------------------------------------*/
/* TEmployeeDlg implementations:              	    */
/*--------------------------------------------------*/

TEmployeeDlg::TEmployeeDlg(PTWindowsObject AParent, LPSTR name)
                 :TDialog(AParent, name)
{
  new TEdit(this, ID_NAMEEDIT,
      sizeof(((TTestWindow *)Parent)->TransferStruct.NameEdit));
  new TEdit(this, ID_SSEDIT,
      sizeof(((TTestWindow *)Parent)->TransferStruct.SSEdit));
  new TEdit(this, ID_IDEDIT,
      sizeof(((TTestWindow *)Parent)->TransferStruct.IDEdit));
  TransferBuffer = (void far*)
                     &(((TTestWindow *)Parent)->TransferStruct);
}

/*--------------------------------------------------*/
/* When OK button is pressed and CanClose called,   */
/* respond by validating the employee data which    */
/* was input.  The dialog is not ended until valid  */
/* entries have been made in all fields.            */
/*--------------------------------------------------*/
BOOL TEmployeeDlg::CanClose()
{
  FillBuffers();

  /* Make sure all input fields have been filled in.*/
  if ((EmpName[0]) && (EmpSSNum[0]) && (EmpID[0]))
  {
    /* Make sure all input fields have valid data */
    if ( ValidName() && ValidSSNum() && ValidID() )
      return TRUE;
  }
  else
    MessageBox(HWindow,
		   "All fields must be filled in","Input Error", MB_OK);
  return FALSE;
}

/*--------------------------------------------------*/
/* Retrieve data.                                   */
/*--------------------------------------------------*/
void TEmployeeDlg::FillBuffers()
{
   GetDlgItemText(HWindow, ID_NAMEEDIT, EmpName, MAXNAMELEN);
   GetDlgItemText(HWindow, ID_SSEDIT, EmpSSNum, MAXSSLEN);
   GetDlgItemText(HWindow, ID_IDEDIT, EmpID, MAXIDLEN);
}

/*--------------------------------------------------*/
/* Validate employee name.                          */
/*--------------------------------------------------*/
BOOL TEmployeeDlg::ValidName()
{
  for (int i=0; i < strlen(EmpName); i++)
    if ( !isalpha(EmpName[i]) && EmpName[i] != ' ' && EmpName[i] != '.' )
    {
      MessageBox(HWindow,
                 "Employee Name Entry is incorrect","Input Error", MB_OK);
      return FALSE;
    }
  return TRUE;
}

/*--------------------------------------------------*/
/* Validate employee social security number.        */
/*--------------------------------------------------*/
BOOL TEmployeeDlg::ValidSSNum()
{
  int i , Len;
  BOOL Valid;

  Valid = TRUE;
  Len = strlen(EmpSSNum);
  if ( (Len != 11) || (EmpSSNum[3] != '-') || (EmpSSNum[6] != '-') )
     Valid = FALSE;
  else
     for (i=0; i < Len; i++)
     {
        if ( (i != 3) && (i != 6) && !(isdigit(EmpSSNum[i]) ) )
        {
	      Valid = FALSE;
	      break;
        }
     }
  if ( !Valid )
     MessageBox(HWindow, "Employee Social Security number is incorrect",
                "Input Error", MB_OK);
  return Valid;
}

/*--------------------------------------------------*/
/* Validate employee ID, must be between 1 and 10000*/
/*--------------------------------------------------*/
BOOL TEmployeeDlg::ValidID()
{
  long IDValue;

  IDValue = atoi(EmpID) ;    /* returns 0 if can't be converted */
  if ( IDValue < 1 || IDValue > 10000)
  {
    MessageBox(HWindow, "Employee ID number is incorrect","Input Error", MB_OK);
    return FALSE;
  }
  return TRUE;
}

/*--------------------------------------------------*/
/* TTestWindow implementations:                      */
/*--------------------------------------------------*/

TTestWindow::TTestWindow(PTWindowsObject Parent,LPSTR ATitle)
                         : TWindow(Parent, ATitle)
{
  AssignMenu(200);
  memset(&TransferStruct, 0x0, sizeof TransferStruct);
}

void TTestWindow::EmpInput(RTMessage)
{
  char EmpInfo[MAXNAMELEN + MAXSSLEN + MAXIDLEN + 3] ;

  if ( GetModule()->ExecDialog(
               new TEmployeeDlg(this,"EMPLOYEEINFO")) == IDOK )
  {
    strcpy(EmpInfo, TransferStruct.NameEdit);	
    strcat(EmpInfo, "\n");
    strcat(EmpInfo, TransferStruct.SSEdit);	
    strcat(EmpInfo, "\n");
    strcat(EmpInfo, TransferStruct.IDEdit);	
    MessageBox(HWindow, EmpInfo,"information stored", MB_OK);
  }
}

/*--------------------------------------------------*/
/* TValidateApp method implementations:             */
/*--------------------------------------------------*/

/* Construct the TValidateApp's MainWindow of type TTestWindow */
void TValidateApp::InitMainWindow()
{
  MainWindow = new TTestWindow(NULL, "Validate Dialog Input");
}

// Main program
int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
  LPSTR lpCmdLine, int nCmdShow)
{
  TValidateApp ValidateApp ("ValidateApp", hInstance, hPrevInstance,
    lpCmdLine, nCmdShow);
  ValidateApp.Run();
  return ValidateApp.Status;
}
