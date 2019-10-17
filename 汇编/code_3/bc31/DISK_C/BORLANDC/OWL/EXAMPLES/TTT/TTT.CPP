// ObjectWindows - (C) Copyright 1992 by Borland International

// -------------------------------------------------------------------------
//
//    TTT - TicTacToe Demo Program
//
//    Plays a game of TicTacToe with the user.
//
//    TTTTGameApp - Main TicTacToe application, derived from TApplication
//    TGameWindow - Main window for the app, derived from TWindow
//    Square - Game squares (windows), derived from TWindow
//    TGameAboutBox - A TDialog box for info about TicTacToe
//    TGameOptionsBox - A TDialog box for setting TicTacToe options
//    YouMeRadioButton - A radio button which controls game settings
//    XORadioButton - A radio button which controls game settings
//
// -------------------------------------------------------------------------

#include <owl.h>
#include <bbutton.h>
#include <bwcc.h>
#include <bstatic.h>
#include <bradio.h>
#include <bgrpbox.h>
#include <string.h>

#include "ttt.h"

const unsigned int TGW_WIDTH = 280, TGW_HEIGHT = 300;
const unsigned int TGAB_WIDTH = 250, TGAB_HEIGHT = 300;
const unsigned int TGAB_INITIAL_X = 5, TGAB_INITIAL_Y = 10;

const unsigned int SW_SIZE = 40;
const unsigned int BOARDXOFFSET = 30+SW_SIZE+3;
const unsigned int BOARDYOFFSET = 10+SW_SIZE+2;

enum SQUARESTATUS { SQS_UNOCCUPIED, SQS_X, SQS_O };

SQUARESTATUS UserSide;
BOOL Playing;

class Square : public TWindow
{
public:
   Square(PTWindowsObject, int, int);
   void makeAnX(void)
   {
       SquareStatus = SQS_X;
       InvalidateRect(HWindow, NULL, TRUE);
   }
   void makeAnO(void)
   {
       SquareStatus = SQS_O;
       InvalidateRect(HWindow, NULL, TRUE);
   }
   void reset(void)
   {
       SquareStatus = SQS_UNOCCUPIED;
       InvalidateRect(HWindow, NULL, TRUE);
   }
   virtual void WMLButtonDown(RTMessage Msg) = [WM_FIRST + WM_LBUTTONDOWN];
   virtual void Paint(HDC PaintDC, PAINTSTRUCT _FAR &PaintInfo);
   SQUARESTATUS SquareStatus;
private:
   int Row, Col;
};

class TTTTGameApp : public TApplication
{
public:
   TTTTGameApp(LPSTR AName, HINSTANCE hInstance, HINSTANCE hPrevInstance,
               LPSTR lpCmdLine, int nCmdShow)
    : TApplication(AName, hInstance, hPrevInstance, lpCmdLine, nCmdShow)
   {
      UserSide = SQS_X;
      ComputerGoesFirst = FALSE;
      Playing = TRUE;
      UserBoardMap = ComputerBoardMap = 0;
   }
   virtual void InitMainWindow();
   BOOL isWon(void);
   int UserBoardMap, ComputerBoardMap;
   BOOL ComputerGoesFirst;
   void computerTurn(void);
   BOOL gameOver(void)
       { return ( (UserBoardMap|ComputerBoardMap) == 0x1FF ); }
   Square *theBoard[3][3];
};

class TGameWindow : public TWindow
{
public:
   TGameWindow(PTWindowsObject AParent, LPSTR ATitle);
   virtual void CMGameNew(RTMessage Msg) = [CM_FIRST + CM_GAMENEW];
   virtual void CMGameOptions(RTMessage Msg) = [CM_FIRST + CM_GAMEOPTIONS];
   virtual void CMAbout(RTMessage Msg) = [CM_FIRST + CM_ABOUT];
   virtual void Paint(HDC PaintDC, PAINTSTRUCT _FAR &PaintInfo);
};

class TGameAboutBox : public TDialog
{
public:
   TGameAboutBox::TGameAboutBox(PTWindowsObject AParent);
};

class TGameOptionsBox : public TDialog
{
public:
   TGameOptionsBox::TGameOptionsBox(PTWindowsObject AParent);
   virtual void SetupWindow(void);
   TBGroupBox     *YouMeGroup, *XOGroup;
   TBRadioButton  *You, *Me, *X, *O;
   virtual void HandleYouMeGroupMsg(RTMessage Msg) =
       [ID_FIRST + IDYOUMEGROUP];
   virtual void HandleXOGroupMsg(RTMessage Msg) = [ID_FIRST + IDXOGROUP];
};

TTTTGameApp *GameApp;

static const int freeMasks[] =
    { 0x006, 0x005, 0x003, 0x030, 0x028, 0x018, 0x180, 0x140, 0x0C0,
      0x048, 0x041, 0x009, 0x090, 0x082, 0x012, 0x120, 0x104, 0x024,
      0x110, 0x101, 0x011, 0x050, 0x044, 0x014 };

static const int winningMasks[] =
    { 0x1C0, 0x038, 0x007, 0x124, 0x092, 0x049, 0x111, 0x054 };

static void freeSquare( int mask, int i, int *row, int *col )
{
   int j, test, mode = i/9; // row, col, or diag
   if (mode==0)
      mask ^= 0x007 << (i/3)*3;
   else if (mode==1)
      mask ^= 0x049 << ((i%9)/3);
   else if (((i%9)/3)==0)
      mask ^= 0x111;
   else
      mask ^= 0x054;
   for( j = 0, test = 1; test; test <<= 1, j++ )
      if ( test & mask )
         break;
   *row = j/3; *col = j%3;
}

// The following routine can be improved upon.  Write your own
// version of this routine so that the machine always wins or draws the game.
void TTTTGameApp::computerTurn(void)
{
   BOOL madeMove = FALSE;
   for( int i = 0; i < 24; i++ )
      if ( ( UserBoardMap & freeMasks[i] ) == freeMasks[i] )
      {
         int targetRow, targetCol, targetMask;
         freeSquare( freeMasks[i], i, &targetRow, &targetCol );
         if ( ComputerBoardMap &
             ( targetMask = 1 << ((targetRow*3)+targetCol) ) )
            continue;
         if ( UserSide == SQS_X )
            (theBoard[targetRow][targetCol])->makeAnO();
         else
	    (theBoard[targetRow][targetCol])->makeAnX();
         ComputerBoardMap |= targetMask;
         madeMove = TRUE;
         break;
      }
   if ( !madeMove )
   {
      if ( !( (ComputerBoardMap|UserBoardMap) & 0x010 ) )
      {
         if ( UserSide == SQS_X )
            (theBoard[1][1])->makeAnO();
         else
            (theBoard[1][1])->makeAnX();
         ComputerBoardMap |= 0x010;
      }
      else
      {
         int i, mask = UserBoardMap|ComputerBoardMap;
         for( i = 0; mask & 1; mask >>= 1 )
            i++;
         if ( UserSide == SQS_X )
            (theBoard[i/3][i%3])->makeAnO();
         else
            (theBoard[i/3][i%3])->makeAnX();
         ComputerBoardMap |= 1 << i;
      }
   }
   if ( isWon() )
   {
      Playing = FALSE;
      MessageBox(MainWindow->HWindow, "I won!", "", MB_OK );
   }
   else if ( gameOver() )
   {
      Playing = FALSE;
      MessageBox(MainWindow->HWindow, "Scratch", "", MB_OK );
   }
}

BOOL TTTTGameApp::isWon(void)
{
   for( int i = 0; i < 8; i++ )
      if ( ((UserBoardMap & winningMasks[i]) == winningMasks[i]) ||
              ((ComputerBoardMap & winningMasks[i]) == winningMasks[i] ) )
         return TRUE;
   return FALSE;
}

Square::Square(PTWindowsObject AParent, int x, int y) :
    TWindow(AParent, ""), SquareStatus(SQS_UNOCCUPIED), Row(x), Col(y)
{
   Attr.W = Attr.H = SW_SIZE;
   Attr.X = BOARDXOFFSET + y*(SW_SIZE+3); // x and y are reversed because
   Attr.Y = BOARDYOFFSET + x*(SW_SIZE+3); // of screen coordinates
   Attr.Style = WS_VISIBLE|WS_CHILD;
}

void Square::WMLButtonDown(RTMessage)
{
   if ( Playing && ( SquareStatus == SQS_UNOCCUPIED ) )
   {
      if ( UserSide == SQS_X )
      {
         makeAnX();
         GameApp->UserBoardMap |= 1 << ((Row*3)+Col);
      }
      else
      {
         makeAnO();
         GameApp->UserBoardMap |= 1 << ((Row*3)+Col);
      }
      if ( GameApp->isWon() )
      {
         Playing = FALSE;
         MessageBox(HWindow, "You won!", "", MB_OK );
      }
      else if ( GameApp->gameOver() )
      {
         Playing = FALSE;
         MessageBox(HWindow, "Scratch", "", MB_OK );
      }
      else
         GameApp->computerTurn();
   }
   else
      MessageBeep(0);
}

void Square::Paint(HDC PaintDC, PAINTSTRUCT&)
{
   if ( SquareStatus == SQS_O )
      Ellipse(PaintDC,0,0,SW_SIZE,SW_SIZE);
   else if ( SquareStatus == SQS_X )
   {
      MoveTo(PaintDC,0,0);
      LineTo(PaintDC,SW_SIZE,SW_SIZE);
      MoveTo(PaintDC,SW_SIZE,0);
      LineTo(PaintDC,0,SW_SIZE);
   }
}

TGameWindow::TGameWindow(PTWindowsObject AParent, LPSTR ATitle) :
    TWindow(AParent, ATitle)
{
   AssignMenu("COMMANDS");
   Attr.X = TGAB_INITIAL_X;
   Attr.Y = TGAB_INITIAL_Y;
   Attr.W = TGW_WIDTH;
   Attr.H = TGW_HEIGHT;
}

void TGameWindow::Paint(HDC PaintDC, PAINTSTRUCT&)
{
   MoveTo(PaintDC, BOARDXOFFSET+SW_SIZE+2, BOARDYOFFSET);
   LineTo(PaintDC, BOARDXOFFSET+SW_SIZE+2, BOARDYOFFSET+(SW_SIZE*3)+6);
   MoveTo(PaintDC, BOARDXOFFSET+(SW_SIZE*2)+5, BOARDYOFFSET);
   LineTo(PaintDC, BOARDXOFFSET+(SW_SIZE*2)+5, BOARDYOFFSET+(SW_SIZE*3)+6);
   MoveTo(PaintDC, BOARDXOFFSET, BOARDYOFFSET+SW_SIZE+2);
   LineTo(PaintDC, BOARDXOFFSET+(SW_SIZE*3)+6, BOARDYOFFSET+SW_SIZE+2);
   MoveTo(PaintDC, BOARDXOFFSET, BOARDYOFFSET+(SW_SIZE*2)+5);
   LineTo(PaintDC, BOARDXOFFSET+(SW_SIZE*3)+6, BOARDYOFFSET+(SW_SIZE*2)+5);
}

void TGameWindow::CMGameNew(RTMessage)
{
   Playing = TRUE;
   GameApp->UserBoardMap = 0;
   GameApp->ComputerBoardMap = 0;
   for(int i = 0; i < 3; i++ )
      for(int j = 0; j < 3; j++ )
         GameApp->theBoard[i][j]->reset();
   if ( GameApp->ComputerGoesFirst )
      GameApp->computerTurn();
}

void TGameWindow::CMGameOptions(RTMessage)
{
   TGameOptionsBox *OptionsDialog = new TGameOptionsBox(this);
   GetApplication()->ExecDialog(OptionsDialog);
}

void TGameWindow::CMAbout(RTMessage)
{
   TGameAboutBox *HelpDialog = new TGameAboutBox(this);
   GetApplication()->ExecDialog(HelpDialog);
}

TGameAboutBox::TGameAboutBox(PTWindowsObject AParent) :
    TDialog(AParent, "ABOUT")
{
#  define ABOUTSTR "Tic Tac Toe\n(C) Borland International\n 1992"
   PTStatic textPtr = new TBStatic(this, IDSTATIC, ABOUTSTR, 23, 20, 190,
           45, strlen(ABOUTSTR) );
   textPtr->Attr.Style |= SS_CENTER;
   new TBButton(this, IDOK, "Ok", 80, 90, 40, 40, TRUE);
}

TGameOptionsBox::TGameOptionsBox(PTWindowsObject AParent) :
    TDialog(AParent, "OPTIONS")
{
   new TBButton(this, IDOK, "Ok", 30, 240, 40, 40, TRUE);
   new TBButton(this, IDCANCEL, "Cancel", 150, 240, 40, 40, TRUE);
   YouMeGroup = new TBGroupBox(this, IDYOUMEGROUP, "Who goes first?", 15,
       30, 200, 20);
   You = new TBRadioButton(this, IDYOU, "You", 15, 55, 50, 20, YouMeGroup);
   Me = new TBRadioButton(this, IDME, "Me", 15, 80, 50, 20, YouMeGroup);
   XOGroup = new TBGroupBox(this, IDXOGROUP, "I am playing", 15, 120,
       200, 20);
   X = new TBRadioButton(this, IDX, "X's", 15, 145, 50, 20, XOGroup);
   O = new TBRadioButton(this, IDO, "O's", 15, 170, 50, 20, XOGroup);
}

void TGameOptionsBox::SetupWindow(void)
{
   TDialog::SetupWindow();
   if ( GameApp->ComputerGoesFirst )
      Me->Check();
   else
      You->Check();

   if ( UserSide == SQS_X )
      O->Check();
   else
      X->Check();
}

void TGameOptionsBox::HandleYouMeGroupMsg(RTMessage)
{
   GameApp->ComputerGoesFirst =
       (You->GetCheck() == BF_CHECKED) ? FALSE : TRUE;
}

void TGameOptionsBox::HandleXOGroupMsg(RTMessage)
{
   UserSide = (X->GetCheck() == BF_CHECKED) ? SQS_O : SQS_X;
   Playing = FALSE;
}

void TTTTGameApp::InitMainWindow()
{
   (void)BWCCGetVersion();    // Make sure BWCC gets initialized.
   MainWindow = new TGameWindow(NULL, Name);
   for(int i = 0; i < 3; i++ )
      for(int j = 0; j < 3; j++ )
	 theBoard[i][j] = new Square(MainWindow, i, j);
}

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
   GameApp = new TTTTGameApp("TicTacToe", hInstance, hPrevInstance,
       lpCmdLine, nCmdShow);
   GameApp->Run();
   return GameApp->Status;
}
