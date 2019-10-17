// ObjectWindows - (C) Copyright 1992 by Borland International

#include <static.h>
#include <filedial.h>
#include <inputdia.h>
#include <bwcc.h>

#include "checkers.h"
#include "info.h"
#include "board.h"

short LINESIZE;
short CHARSIZE;
int CAPTIONY;
int BORDERSIZE;
const BORDERYEXTRA = 4; // 4 for spacing
const MYFRAMESIZE = 3;
short INFOXSIZE, INFOYSIZE;

#undef MAXPATH
#define MAXPATH  160

HBITMAP RedManBmp, BlackManBmp, RedKingBmp, BlackKingBmp;


// Must overload TDialog to handle IDYES and IDNO messages
class TEndDialog : public TDialog
{
  public:
   TEndDialog(PTWindowsObject AParent, LPSTR AName)
      : TDialog(AParent, AName)
      { }

   virtual void Yes(RTMessage) = [ID_FIRST+IDYES]
   {
      CloseWindow(IDYES);
   }
   virtual void No(RTMessage) = [ID_FIRST+IDNO]
   {
      ShutDownWindow();
   }
};

class TCheckers: public TApplication
{
  public:
   TCheckers(LPSTR AName, HINSTANCE hInstance, HINSTANCE hPrevInstance,
      LPSTR lpCmdLine, int nCmdShow) : TApplication(AName, hInstance,
      hPrevInstance, lpCmdLine, nCmdShow)
      {
      }
   virtual void InitMainWindow();
   void InitInstance()
   {
      TApplication::InitInstance();
      HAccTable = LoadAccelerators(hInstance, "CheckerCommands");
      BWCCGetVersion();
   }
};



_CLASSDEF(TCheckersWindow)
class TCheckersWindow : public TWindow
{
   PTInfoWindow TInfo;
   PBOARD bd;
   HCURSOR CursorHand, CursorPiece;
   BOOL HoldingPiece;
   SIDE WhoseTurn;
   int MovingPieceType;
   POINT MoveStartPoint, MoveEndPoint;
   RECT MainWndRect;
   RECT InfoAreaRect;
   BOOL NewGame;
   char *FileName;
   HMENU hMenu;
  public :
   TCheckersWindow(PTWindowsObject AParent, LPSTR ATitle);
   ~TCheckersWindow()
   {
      if (bd)
         delete bd;
      delete FileName;
      delete TInfo;
      DeleteObject(RedManBmp);
      DeleteObject(BlackManBmp);
      DeleteObject(RedKingBmp);
      DeleteObject(BlackKingBmp);
   }
   virtual void SetupWindow()
   {
      TWindow::SetupWindow();
      CursorPiece = LoadCursor( GetApplication()->hInstance, "HandWPiece");
      RedManBmp = LoadBitmap(GetApplication()->hInstance, "RedManBitmap");
      BlackManBmp = LoadBitmap(GetApplication()->hInstance, "BlackManBitmap");
      RedKingBmp = LoadBitmap(GetApplication()->hInstance, "RedKingBitmap");
      BlackKingBmp = LoadBitmap(GetApplication()->hInstance, "BlackKingBitmap");
      GetClientRect(HWindow, &MainWndRect);
      InfoAreaRect = MainWndRect;
      InfoAreaRect.left = (MainWndRect.right -= ((BORDERSIZE * 2) + INFOXSIZE));
      hMenu = GetMenu(HWindow);
      bd = new BOARD;
      bd->SetInfoPtr(TInfo);
      bd->SetupBoard();
      WhoseTurn = Red;
      HoldingPiece = FALSE;
      TInfo->SetTurnText("Red");
      NewGame = TRUE;
   }
   virtual void GetWindowClass(WNDCLASS& WndClass)
   {
      TWindow::GetWindowClass( WndClass );
      CursorHand = LoadCursor( GetApplication()->hInstance, "Hand");
      WndClass.hCursor = CursorHand;
      WndClass.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
      WndClass.lpszMenuName = "Checkers";
      WndClass.hIcon = LoadIcon( GetApplication()->hInstance, "CheckersIcon");
   }
   virtual void Paint( HDC PaintDC, PAINTSTRUCT& PaintInfo );
   virtual void WMLButtonDown( TMessage& Message ) = [ WM_FIRST + WM_LBUTTONDOWN ];
   virtual void WMLButtonUp( TMessage& Message ) = [ WM_FIRST + WM_LBUTTONUP ];
   virtual void CMNewGame(RTMessage Msg) = [CM_FIRST + CM_FILENEW];
   virtual void CMRestoreGame(RTMessage Msg) = [CM_FIRST + CM_FILEOPEN];
   virtual void CMSaveGame(RTMessage Msg) = [CM_FIRST + CM_FILESAVE];
   virtual void CMSaveGameAs(RTMessage Msg) = [CM_FIRST + CM_FILESAVEAS];
   virtual void UndoMove(RTMessage Msg) = [CM_FIRST + CM_UNDO];
   virtual void RedoUndo(RTMessage Msg) = [CM_FIRST + CM_REDO];
   virtual void SetSearchDepth(RTMessage Msg) = [CM_FIRST + CM_SEARCHDEPTH];
   virtual void ToggleAutoPlay(RTMessage Msg) = [CM_FIRST + CM_AUTO];
   virtual void ToggleIteration(RTMessage Msg) = [CM_FIRST + CM_ITERATE];
   virtual void ToggleKillerTable(RTMessage Msg) = [CM_FIRST + CM_KILLER];
   virtual void ComputersMove(RTMessage) = [CM_FIRST + CM_MOVE];
   virtual void About(RTMessage Msg) = [CM_FIRST + CM_ABOUT];
   virtual void Logging(RTMessage) = [CM_FIRST + CM_LOG];
   virtual void Exit(RTMessage) = [CM_FIRST + IDM_EXIT]
      {
      CloseWindow();
      }
   void SaveGameAs();
   virtual BOOL CanClose()
   {
      if (WhoseTurn == Black)
         return FALSE;
      return TRUE;
   }
};

//->TWindow member functions<----------------------------------------

void TCheckers::InitMainWindow()
{
   MainWindow = new TCheckersWindow(NULL, "OWL Checkers");
}


//->TCheckersWindow member functions<--------------------------------

TCheckersWindow::TCheckersWindow(PTWindowsObject AParent, LPSTR ATitle) :
   TWindow(AParent, ATitle)
{
   HDC hDC;
   TEXTMETRIC tm;

   hDC = GetDC(HWindow);
   GetTextMetrics(hDC, &tm);
   CHARSIZE = tm.tmAveCharWidth;
   LINESIZE = tm.tmHeight + tm.tmExternalLeading;
   ReleaseDC(HWindow, hDC);
   CAPTIONY = GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYMENU);
   BORDERSIZE = LINESIZE + MYFRAMESIZE;
   TInfo = new TInfoWindow(this, "InfoWindow");
   Attr.Style = WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX;
   Attr.X = 5;
   Attr.Y = 5;
   Attr.H = CAPTIONY + (BORDERSIZE * 2) + INFOYSIZE + BORDERYEXTRA +
      (2 * GetSystemMetrics(SM_CYBORDER));
   Attr.W = (BORDERSIZE * 4) + (MAXBDSIZE * SQUARE_SIZE) + INFOXSIZE +
      (2 * GetSystemMetrics(SM_CXBORDER)) + (2*MYFRAMESIZE);
   FileName = new char[MAXPATH];
   bd = NULL;
}

void TCheckersWindow::WMLButtonDown( TMessage& )
{
   POINT Point;
   if (WhoseTurn == Black)
      return;
   SetCapture(HWindow);
   GetCursorPos( &Point );
   ScreenToClient(HWindow, &Point);

   MoveStartPoint = bd->GetValidSquare(Point, WhoseTurn);
   if (MoveStartPoint.x)
      {
      MovingPieceType = bd->GetPieceType(MoveStartPoint);
      HDC hDC = GetDC(HWindow);
      SetClassWord( HWindow, GCW_HCURSOR, (WORD)CursorPiece);
      SetCursor(CursorPiece);
      bd->ClearSquare(hDC, MoveStartPoint);
      HoldingPiece = TRUE;
      ReleaseDC(HWindow, hDC);
      }
}

void TCheckersWindow::WMLButtonUp( TMessage& )
{
   POINT Point;

   ReleaseCapture();
   if (!HoldingPiece || WhoseTurn == Black)
      return;

   GetCursorPos(&Point);
   ScreenToClient(HWindow, &Point);
   TInfo->SetMessageText("");
   MoveEndPoint = bd->GetEmptySquare(Point);
   HDC hDC = GetDC(HWindow);
   SetClassWord( HWindow, GCW_HCURSOR, (WORD)CursorHand);
   SetCursor(CursorHand);
   if (MoveEndPoint.x && bd->UserMove(MoveStartPoint, MoveEndPoint))
      {
      bd->RedrawBoard(hDC);
      EnableMenuItem( hMenu, CM_UNDO, MF_BYCOMMAND | MF_ENABLED );
      EnableMenuItem( hMenu, CM_REDO, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
      if (!bd->AnotherJump())
         {
         if (bd->NoMoreBlack())
            {
         if (GetApplication()->ExecDialog(new TEndDialog(this, "UserWonDlg"))
            == IDYES)
               {
               PostMessage(HWindow, WM_COMMAND, CM_FILENEW, 0L);
               ReleaseDC(HWindow, hDC);
               return;
               }
            else
               {
               PostMessage(HWindow, WM_COMMAND, CM_EXIT, 0L);
               ReleaseDC(HWindow, hDC);
               return;
               }
            }
         PostMessage(HWindow, WM_COMMAND, CM_MOVE, 0L);
         }
      else
         TInfo->SetMessageText("Another jump required");
      }
   else
      {
      TInfo->SetMessageText("Not a legal move!");
      bd->DrawPiece(hDC, MovingPieceType, MoveStartPoint);
      }
   HoldingPiece = FALSE;
   ReleaseDC(HWindow, hDC);
}



void TCheckersWindow::Paint(HDC PaintDC, PAINTSTRUCT&)
{
   DrawFrame(PaintDC, MainWndRect);
   DrawFrame(PaintDC, InfoAreaRect);
   bd->DrawCheckersFrame(PaintDC);
   if (WhoseTurn == Black)  // computer is thinking
      bd->DrawLastBoard(PaintDC);
   else
      bd->DrawBoard(PaintDC);
   bd->DrawAlphaNum(PaintDC);
}

void TCheckersWindow::ComputersMove(RTMessage)
{
   bd->EndUsersTime();
   TInfo->SetMessageText("Thinking...");
   HCURSOR hCurTemp;
   SetClassWord(HWindow, GCW_HCURSOR, WORD(hCurTemp =
	                                       LoadCursor(0, IDC_WAIT)));
   SetCursor(hCurTemp);
   WhoseTurn = Black;
   TInfo->SetTurnText("Black");
   EnableMenuItem(hMenu, 0, MF_BYPOSITION | MF_DISABLED | MF_GRAYED);
   EnableMenuItem(hMenu, 1, MF_BYPOSITION | MF_DISABLED | MF_GRAYED);
   EnableMenuItem(hMenu, 3, MF_BYPOSITION | MF_DISABLED | MF_GRAYED);
   ModifyMenu( hMenu, CM_MOVE, MF_BYCOMMAND | MF_ENABLED |
           MF_STRING, CM_STOP, "&Stop");
   DrawMenuBar(HWindow);
   bd->ComputersTurn();
   HDC hDC = GetDC(HWindow);
   bd->RedrawBoard(hDC);
   ReleaseDC(HWindow, hDC);
   WhoseTurn = Red;
   TInfo->SetTurnText("Red");
   SetClassWord( HWindow, GCW_HCURSOR, (WORD)CursorHand);
   POINT CursorPoint;
   GetCursorPos(&CursorPoint);
   ScreenToClient(HWindow, &CursorPoint);
#pragma warn -stv
   if (PtInRect(&MainWndRect, CursorPoint))
      SetCursor( CursorHand );
#pragma warn +stv
   ModifyMenu( hMenu, CM_STOP, MF_BYCOMMAND | MF_ENABLED |
           MF_STRING, CM_MOVE, "&Pass");
   EnableMenuItem(hMenu, 0, MF_BYPOSITION | MF_ENABLED);
   EnableMenuItem(hMenu, 1, MF_BYPOSITION | MF_ENABLED);
   EnableMenuItem(hMenu, 3, MF_BYPOSITION | MF_ENABLED);
   DrawMenuBar(HWindow);

   if (bd->NoMoreRed())
      {
   if (GetApplication()->ExecDialog(new TEndDialog(this, "GameWonDlg"))
      == IDYES)
          {
          PostMessage(HWindow, WM_COMMAND, CM_FILENEW, 0L);
          return;
          }
       else
          {
          PostMessage(HWindow, WM_COMMAND, CM_EXIT, 0L);
          return;
          }
       }
   TInfo->SetMessageText("");
   bd->StartUsersTime();
}

void TCheckersWindow::CMNewGame(RTMessage)
{
   TInfo->Reset();
   bd->SetupBoard();
   EnableMenuItem(hMenu, CM_UNDO, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
   EnableMenuItem(hMenu, CM_REDO, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
   HoldingPiece = FALSE;
   TInfo->SetTurnText("Red");
   WhoseTurn = Red;
   NewGame = TRUE;
   HDC hDC = GetDC(HWindow);
   bd->DrawBoard(hDC);
   ReleaseDC(HWindow, hDC);
}

void TCheckersWindow::CMRestoreGame(RTMessage)
{
   if (GetApplication()->ExecDialog(new TFileDialog(this,
      SD_FILEOPEN, strcpy(FileName, "*.CHK"))) == IDOK)
      {
      bd->LoadGame(FileName);
      NewGame = FALSE;
      EnableMenuItem(hMenu, CM_REDO, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
      EnableMenuItem(hMenu, CM_UNDO, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
      HDC hDC = GetDC(HWindow);
      bd->DrawBoard(hDC);
      ReleaseDC(HWindow, hDC);
      }
}

void TCheckersWindow::SaveGameAs()
{
   if (GetApplication()->ExecDialog(new TFileDialog(this,
      SD_FILESAVE, strcpy(FileName, "*.CHK")))
         == IDOK)
      {
      bd->SaveGame(FileName);
      NewGame = FALSE;
      }
}

void TCheckersWindow::CMSaveGame(RTMessage)
{
   if (NewGame == TRUE)
      SaveGameAs();
   else
      bd->SaveGame(FileName);
}

void TCheckersWindow::CMSaveGameAs(RTMessage)
{
   SaveGameAs();
}

void TCheckersWindow::UndoMove(RTMessage)
{
   EnableMenuItem(hMenu, CM_REDO, MF_BYCOMMAND | MF_ENABLED);
   if (bd->UndoMove())
      EnableMenuItem(hMenu, CM_UNDO, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
   HDC hDC = GetDC(HWindow);
   bd->RedrawBoard(hDC);
   ReleaseDC(HWindow, hDC);
}

void TCheckersWindow::RedoUndo(RTMessage)
{
   EnableMenuItem(hMenu, CM_UNDO, MF_BYCOMMAND | MF_ENABLED);
   if (bd->RedoMove())
      EnableMenuItem(hMenu, CM_REDO, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
   HDC hDC = GetDC(HWindow);
   bd->RedrawBoard(hDC);
   ReleaseDC(HWindow, hDC);
}

void TCheckersWindow::SetSearchDepth(RTMessage)
{

   char *SearchDepthText;

   SearchDepthText = new char[48];
   strcpy(SearchDepthText, "3");
   if (GetApplication()->ExecDialog(new TInputDialog(this, "Set Search Depth", "Enter new search depth:",
      SearchDepthText, 47)) == IDOK)
      {
      int NewSearchDepth = atoi(SearchDepthText);
      bd->SetSearchDepth(NewSearchDepth);
      }
   delete SearchDepthText;
}

void TCheckersWindow::ToggleAutoPlay(RTMessage)
{
   // Left as an exersize
}

void TCheckersWindow::ToggleIteration(RTMessage)
{
   if (GetMenuState(hMenu, CM_ITERATE, MF_BYCOMMAND) & MF_CHECKED)
      CheckMenuItem(hMenu, CM_ITERATE, MF_UNCHECKED);
   else
      CheckMenuItem(hMenu, CM_ITERATE, MF_CHECKED);
   bd->ToggleIter();
   TInfo->IterReset();
}


void TCheckersWindow::ToggleKillerTable(RTMessage)
{
   if (GetMenuState(hMenu, CM_KILLER, MF_BYCOMMAND) & MF_CHECKED)
      CheckMenuItem(hMenu, CM_KILLER, MF_UNCHECKED);
   else
      CheckMenuItem(hMenu, CM_KILLER, MF_CHECKED);
   bd->ToggleKiller();
   TInfo->IterReset();
}

void TCheckersWindow::Logging(RTMessage)
{
   if (GetMenuState(hMenu, CM_LOG, MF_BYCOMMAND) & MF_CHECKED)
      CheckMenuItem(hMenu, CM_LOG, MF_UNCHECKED);
   else
      CheckMenuItem(hMenu, CM_LOG, MF_CHECKED);
   bd->ToggleLogging();
}

void TCheckersWindow::About(RTMessage)
{
   GetApplication()->ExecDialog(new TDialog(this, "About"));
}


int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,
   int nCmdShow)
{
   TCheckers CheckersApp("CheckersApp", hInstance, hPrevInstance, lpCmdLine,
      nCmdShow);
   CheckersApp.Run();
   return CheckersApp.Status;
}


