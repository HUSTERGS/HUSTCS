// ObjectWindows - (C) Copyright 1992 by Borland International

#include <owl.h>
#include <filewnd.h>
#include <mdi.h>
#include <string.h>
#include <io.h>
#include "mfileapp.h"

const char DskFile[] = "MFILEAPP.SAV";

_CLASSDEF(TMDIFileApp)
_CLASSDEF(TMDIFileWindow)

// Declare TMDIFileApp, a TApplication descendant
class _CLASSTYPE TMDIFileApp : public TApplication {
public:
    TMDIFileApp(LPSTR name, HINSTANCE hInstance,
		  HINSTANCE hPrevInstance, LPSTR lpCmd,
		  int nCmdShow)
	        : TApplication(name, hInstance,
			       hPrevInstance, lpCmd, nCmdShow) {};
    virtual void InitMainWindow();
    virtual void InitInstance();
};

// Declare TMDIFileWindow, a TMDIFrame descendant
class _CLASSTYPE TMDIFileWindow : public TMDIFrame {
public:
    WORD ChildNum;

    TMDIFileWindow(LPSTR ATitle, LPSTR MenuName);
    virtual void NewFile(RTMessage Msg) =
                 [CM_FIRST + CM_MDIFILENEW];
    virtual void OpenFile(RTMessage Msg) =
                 [CM_FIRST + CM_MDIFILEOPEN];
    virtual void SaveState(RTMessage Msg) =
                 [CM_FIRST + CM_SAVESTATE];
    virtual void RestoreState(RTMessage Msg) =
                 [CM_FIRST + CM_RESTORESTATE];
};

TMDIFileWindow::TMDIFileWindow(LPSTR ATitle, LPSTR MenuName)
                   : TMDIFrame(ATitle, MenuName)
{
  ChildNum = 1;
}

/* Respond to "New" command by constructing, creating, and setting up a
  new TFileWindow MDI child */
void TMDIFileWindow::NewFile(RTMessage)
{
  char ChildName[14];

  wsprintf(ChildName,"MDI Child %d", ChildNum++);
  GetApplication()->MakeWindow(new TFileWindow(this, ChildName, ""));
}

/* Respond to "Open" command by constructing, creating, and setting up a
  new TFileWindow MDI child */
void TMDIFileWindow::OpenFile(RTMessage)
{
  char FileName[MAXPATH];
  char ChildName[14];

  wsprintf(ChildName,"MDI Child %d", ChildNum++);
  if ( GetApplication()->ExecDialog(new TFileDialog(this, SD_FILEOPEN,
                             _fstrcpy(FileName, "*.*"))) == IDOK )
	GetApplication()->MakeWindow(new TFileWindow(this, ChildName, FileName));
}

/* Save the the position and contents of the windows to the
  "desk top" file. */
void TMDIFileWindow::SaveState(RTMessage)
{
  ofpstream os(DskFile);

  PutChildren(os);
  os.close();

  if ( os.bad() )
  {
    unlink(DskFile);
    MessageBox(HWindow, "Unable to write desktop file.", "Disk error",
      MB_OK | MB_ICONEXCLAMATION);
  }
}

void DoCreateChild(Pvoid P, Pvoid)
{
  if ( ((PTWindowsObject)P)->IsFlagSet(WB_AUTOCREATE) )
    ((PTWindowsObject)P)->Create();
}

/* Read windows positions and contents from the "desk top" file. */
void TMDIFileWindow::RestoreState(RTMessage)
{
  LPSTR ErrorMsg = NULL;

  ifpstream is(DskFile);
  if ( is.bad() )
    ErrorMsg = _fstrdup("Unable to open desktop file.");
  else
  {
    if ( CloseChildren() )
    {
      GetChildren(is);
      if ( is.bad() )
        ErrorMsg = _fstrdup("Error reading desktop file.");
	  if ( GetApplication()->LowMemory() )
      {
        CloseChildren();
        ErrorMsg = _fstrdup("Not enough memory to open file.");
      }
      else
        ForEach(DoCreateChild, NULL);
    }
  }
  if ( ErrorMsg )
    MessageBox(HWindow, ErrorMsg, "Disk error",
                                   MB_OK | MB_ICONEXCLAMATION);
}


/* Construct the TMDIFileApp's MainWindow of type TMDIFileWindow,
  loading its menu */
void TMDIFileApp::InitMainWindow()
{
  MainWindow = new TMDIFileWindow("MDI Files", "Commands");
  ((PTMDIFileWindow)MainWindow)->ChildMenuPos = 3;
}

/* Initialize each MS-Windows application instance, loading an
   accelerator table */
void TMDIFileApp::InitInstance()
{
  TApplication::InitInstance();
  if ( Status == 0 )
  {
	HAccTable = LoadAccelerators(hInstance, "FileCommands");
    if ( HAccTable == 0 )
      Status = EM_INVALIDWINDOW;
  }
}

// Run the MDIFileApp
int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
		   LPSTR lpCmd, int nCmdShow)
{
    TMDIFileApp MDIFileApp("MDIFileApp", hInstance, hPrevInstance,
		lpCmd, nCmdShow);
    MDIFileApp.Run();
    return MDIFileApp.Status;
}
