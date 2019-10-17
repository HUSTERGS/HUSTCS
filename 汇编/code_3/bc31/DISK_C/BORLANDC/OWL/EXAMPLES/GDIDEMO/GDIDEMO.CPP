// ObjectWindows - (C) Copyright 1992 by Borland International

// GDIDemo program

#include <owl.h>
#include <string.h>
#include <mdi.h>
#include "demobase.h"
#include "line.h"
#include "font.h"
#include "bitblt.h"
#include "arty.h"

// Menu bar constants
const int  MenuID           =  100;  // Resource ID of the menu
const int  QuitID           =  100;  // File->Quit ID
const int MoveToLineToDemoID=  200;  // Demo->MoveToDemo ID
const int FontDemoID        =  202;  // Demo->Font Demo ID
const int BitBltDemoID      =  203;  // Demo->BitBlt Demo ID
const int ArtyDemoID        =  204;  // Demo->Arty Demo ID



/* TGDIDemoWindow --------------------------------------------------- */

_CLASSDEF(TGDIDemoWindow)

class TGDIDemoWindow : public TMDIFrame
{
public:
         TGDIDemoWindow( LPSTR ATitle, LPSTR MenuName )
                   : TMDIFrame(ATitle, MenuName) {} ;
         virtual void SetupWindow();
         virtual void MoveToLineToDemo( TMessage& ) = [CM_FIRST + MoveToLineToDemoID];
         virtual void FontDemo( TMessage& )         = [CM_FIRST + FontDemoID];
         virtual void BitBltDemo( TMessage& )       = [CM_FIRST + BitBltDemoID];
         virtual void ArtyDemo( TMessage& )         = [CM_FIRST + ArtyDemoID];
         virtual void Quit( TMessage& )             = [CM_FIRST + QuitID];
         virtual void WMTimer( TMessage& )          = [WM_FIRST + WM_TIMER];
         virtual void WMDestroy( TMessage& )        = [WM_FIRST + WM_DESTROY];
};


void TGDIDemoWindow::SetupWindow()
{
  int Result;

  TMDIFrame::SetupWindow();
  Result = IDRETRY;
  while ((SetTimer(HWindow, 0, 50, NULL) == 0) && (Result == IDRETRY)) {
    Result = MessageBox(GetFocus(),"Could not Create Timer", "GDIDemo", MB_RETRYCANCEL);
  };
  if (Result == IDCANCEL)  PostQuitMessage(0);
};

void TGDIDemoWindow::MoveToLineToDemo( TMessage& )
{
  GetApplication()->MakeWindow(new TMoveToLineToWindow(this, "MoveTo/LineTo Window"));
};

void TGDIDemoWindow::FontDemo( TMessage& )
{
  GetApplication()->MakeWindow(new TFontWindow(this, "Font Window"));
};

void TGDIDemoWindow::BitBltDemo( TMessage& )
{
  GetApplication()->MakeWindow(new TBitBltWindow(this, "BitBlt Window"));
};

void TGDIDemoWindow::ArtyDemo( TMessage& )
{
  GetApplication()->MakeWindow(new TArtyWindow(this, "Arty Window"));
};

void TGDIDemoWindow::Quit( TMessage& )
{
  CloseWindow();
};

void ChildTimers( Pvoid P, Pvoid)
{
  ((PTBaseDemoWindow)P)->TimerTick();
};

/* In response to WMTimer messages, each MDI child window's TimerTick
  Method is called. */
void TGDIDemoWindow::WMTimer( TMessage& )
{
  ForEach(ChildTimers, NULL);
};

void TGDIDemoWindow::WMDestroy( TMessage& Message )
{
  KillTimer(HWindow, 0);
  TMDIFrame::WMDestroy(Message);
};




/* TGDIDemoApp ------------------------------------------------------ */

_CLASSDEF(TGDIDemoApp)

class TGDIDemoApp : public TApplication
{
public:
        TGDIDemoApp(LPSTR name, HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    LPSTR lpCmd, int nCmdShow)  :
              TApplication(name, hInstance, hPrevInstance, lpCmd, nCmdShow) {};
        virtual void InitMainWindow();
};

void TGDIDemoApp::InitMainWindow()
{
  /* Create a main window of type TGDIWindow. */
  MainWindow = new TGDIDemoWindow("GDI Demo", (LPSTR)MAKEINTRESOURCE(MenuID));
};

// Run the GDIDemoApp
int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
		   LPSTR lpCmd, int nCmdShow)
{
    TGDIDemoApp GDIDemoApp("GDIDemoApp", hInstance, hPrevInstance,
		                       lpCmd, nCmdShow);
    GDIDemoApp.Run();
    return GDIDemoApp.Status;
}
