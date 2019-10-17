// ObjectWindows - (C) Copyright 1992 by Borland International

#include <windows.h>
#include <fstream.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <dos.h>
#include <time.h>
#include <ctype.h>

#include "wchess.h"
#include "wcdefs.h"
#include "externs.h"

/*
 *  Global declarations
 */

char *INIFile = "wchess.ini";
BOOL InLibrary;  		// True if program is in the opening library
BOOL MultiMove,      // True if multimove mode
     AutoPlay,		   // True if AutoPlay mode
	  SingleStep;		// Single Step mode, used for debugging purposes
LEVELTYPE Level;
double AverageTime = 5.0;
PIECETYPE Pieces[8]  = { rook, knight, bishop, queen,
                              king, bishop, knight, rook};
BYTE MaxLevel;
BOOL Turned;
BOOL UseLib;
LIBTYPE Openings;
COLORTYPE ProgramColor;
int MoveNo;
int PVTable[2][7][0x78];
MOVETYPE PlayerMove;
BOOL Logging;
NODEVAL Nodes;             // Number of analysed nodes
CLOCKTYPE ChessClock;
extern int LegalMoves;
LINETYPE HintLine;            /*  suggested hint line  */
MAXTYPE HintEvalu;            /*  Evaluation for hintline  */
enum ANALYSISCONTROL {Start, Return, Continue};

int OpCount, LibNo;

static DEPTHTYPE LibDepth;
static BOOL Found;
static DEPTHTYPE dep;

ofstream *OutputFile;

typedef enum {readmove, checkmove, gamemove} CONTROLVAR;
static CONTROLVAR Control;



void InsertPiece(PIECETYPE p, COLORTYPE c, SQUARETYPE sq)
{
    Board[sq].piece = p;
    Board[sq].color = c;
}


void ClearPVTable()
{
    COLORTYPE color;
    PIECETYPE piece;
    SQUARETYPE square;

    for (color = white; color <= black; ((int)color)++)
        for (piece = king; piece <= pawn; ((int)piece)++)
            for (square = 0; square <= 0x77; square++)
                PVTable[color][piece][square] = 0;
}


void ResetGame()
{
	ClearBoard();
   Running = FALSE;
   for (int i = 0; i < 8; i++)
      {
        InsertPiece(Pieces[i], white, i);
        InsertPiece(pawn, white, i + 0x10);
        InsertPiece(pawn, black, i + 0x60);
        InsertPiece(Pieces[i], black, i + 0x70);
      }
   CalcPieceTab();
   Player = white;
   ClearDisplay();
   InitDisplay();
   ColorToPlay(Player);
   Opponent = black;
}


void NewGame()
{
	SingleStep = InLibrary = FALSE;
   GameOver = FALSE;
   ResetGame();
   PrintCurLevel();
   ResetMoves();
   if (!*Openings)
         UseLib = 0;
   else
      UseLib = 200;
   MovTab[-1].content = king;
   InitChessTime();
   ProgramColor = white;
   MoveNo = 0;
   ClearHint();
   ClearPVTable();
   PlayerMove = ZeroMove;
   if (Logging && !AutoPlay)
      *OutputFile << "\n No  Player Program      Hint      Value Level       Nodes    Time\n";
   InitNode(&Nodes);
   ChessClock.totaltime = 0.0;
   Control = (AutoPlay) ? gamemove : readmove;
}


void ResetNewPos(void)
{
    ResetMoves();
    CalcPieceTab();
    UseLib = FALSE;
    Running = FALSE;
    ClearHint();
}


void ResetOpening()
{
   const char *libfilename = "opening.lib";
   ifstream fin(libfilename, ios::in | ios::binary);

   if (!fin)
      {
      MessageBox(NULL,"Cannot find Openings Library", "Error",
                 MB_ICONHAND | MB_OK);
		Openings = new unsigned char;
		*Openings = 0;
      return;
      }
   Openings = new unsigned char[32000];
   fin.read(Openings, 32000);
   fin.close();
   *Openings = 0xFF;
}


static void StartUp()
{
   long color;
   randomize();

   Level = (LEVELTYPE)GetPrivateProfileInt("WCHESS", "Level",
      (int)easygame, INIFile);

   if (GetPrivateProfileString("WCHESS", "AverageTime", "5.0", buf,
      80, INIFile))
      sscanf(buf, "%lf", &AverageTime);

   if (GetPrivateProfileString("WCHESS", "WhiteSquare", "", buf, 80, INIFile))
      {
      sscanf(buf, "%ld", &color);
      WhiteSquareColors[0] = color & 0xffL;
      WhiteSquareColors[1] = (BYTE)((color & 0xff00L) >> 8);
      WhiteSquareColors[2] = (BYTE)((color & 0xff0000L) >> 16);
      }

   if (GetPrivateProfileString("WCHESS", "BlackSquare", "", buf, 80, INIFile))
      {
      sscanf(buf, "%ld", &color);
      BlackSquareColors[0] = color & 0xff;
      BlackSquareColors[1] = ((color & 0xff00L) >> 8);
      BlackSquareColors[2] = ((color & 0xff0000L) >> 16);
      }

   MaxLevel = GetPrivateProfileInt("WCHESS", "MaxLevel", MAXPLY, INIFile);
   SoundOn = (BOOL)GetPrivateProfileInt("WCHESS", "SoundOn", 1, INIFile);

   if (!SoundOn)  // defaults to checked at startup
      CheckMenuItem(MainMenu, IDM_SOUND, MF_UNCHECKED);
   CalcAttackTab();
   MultiMove = FALSE;
   AutoPlay = FALSE;
   Turned = FALSE;
   ResetOpening();
   OutputFile = new ofstream("Chess.log");
   if (!OutputFile)
      {
      MessageBox(NULL, "Unable to open log file.\nLogging disabled", "OWL Chess", MB_OK | MB_ICONEXCLAMATION);
      Logging = FALSE;
      }
   else
      {
      *OutputFile << endl;
      *OutputFile << "            OWL CHESS by Borland International\n";
      *OutputFile << "            ==================================\n" << endl;
      }
}

const UNPLAYMARK = 0x3f;


/*
 *  Sets libno to the previous move in the block
 */

void PreviousLibNo(void)
{
    int n;

    n = 0;
    do
    {
        LibNo--;
        if (Openings[LibNo] >= 128) n++;
        if (Openings[LibNo] & 64) n--;
    } while (n);
}


/*
 *  Set libno to the first move in the block
 */

void FirstLibNo()
{
    while (!(Openings[LibNo - 1] & 64))
        PreviousLibNo();
}


/*
 *  set libno to the next move in the block.  Unplayable
 *  moves are skipped if skip is set
 */

void NextLibNo(short skip)
{
    int n;

    if (Openings[LibNo] >= 128) FirstLibNo();
    else
    {
        n = 0;
        do
        {
            if (Openings[LibNo] & 64) n++;
            if (Openings[LibNo] >= 128) n--;
            LibNo++;
        } while (n);
        if (skip && (Openings[LibNo] == UNPLAYMARK))
            FirstLibNo();
    }
}


/*
 *  find the node corresponding to the correct block
 */

static void FindNode(void)
{
    LibNo++;
    if (Depth > LibDepth)
    {
        Found = TRUE;
        return;
    }
    OpCount = -1;
    InitMovGen();
    do
    {
        OpCount++;
        MovGen();
    } while (Next.movpiece != empty && !EqMove(&Next, &MovTab[Depth]));
    if (Next.movpiece != empty)
    {
        while (((Openings[LibNo] & 63) != OpCount) &&
                (Openings[LibNo] < 128))
            NextLibNo(0);
        if ((Openings[LibNo] & 127) == 64 + OpCount)
        {
            MakeMove(&MovTab[Depth]);
            FindNode();
            TakeBackMove(&MovTab[Depth-1]);
        }
    }
}


/*
 *  Set LibNo to the block corresponding to the position
 */

void CalcLibNo(void)
{
    LibNo = 0;
    if (MoveNo < UseLib)
    {
        LibDepth = Depth;
        while (MovTab[Depth].movpiece != empty)
            TakeBackMove(&MovTab[Depth]);
        Found = FALSE;
        if (MovTab[Depth].content == king)
        {
            Depth++;
            FindNode();
            Depth--;
        }
        while(Depth < LibDepth)
            MakeMove(&MovTab[Depth + 1]);
        if (Found)
            UseLib = 200;
        else
        {
            UseLib = MoveNo;
            LibNo = 0;
        }
    }
}


/*
 *  find an opening move from the library
 */

static void FindOpeningMove(void)
{
    const unsigned char weight[7] = {7, 10, 12, 13, 14, 15, 16};
    unsigned char cnt, r, p, countp;

    r = random(16);   /*  calculate weighted random number in 0..16  */
    p = 0;
    while (r >= weight[p]) p++;
    for (countp = 1; countp <= p; countp++)  /* find corresponding node */
        NextLibNo(1);
    OpCount = Openings[LibNo] & 63;  /*  generate the move  */
    InitMovGen();
    for (cnt = 0; cnt <= OpCount; cnt++)
        MovGen();
                          /* store the move in mainline  */
    MainLine[0] = Next;
    MainLine[1] = ZeroMove;
    MainEvalu = 0;
    MaxDepth = 0;
    LegalMoves = 0;
    InitNode(&Nodes);
}



void OutputNode(NODEVAL *nodes)
{
   double nodereal;
   if (!Logging)
      return;
   char buf[20];
   nodereal = (nodes->nodebase * MAXINT) + nodes->nodeoffset;
   sprintf(buf, "%12.1f", nodereal);
   *OutputFile << buf;
}

static void ThinkAwhile();
void StartMove();

void ReturnAnalysis()
{
   int myx;
   char str[8];
   char buf[40];

   MovTab[0] = MainLine[0];   /*  copy the MainLine to HintLine  */
   for (myx = 1; myx <= MAXPLY; myx++)
       HintLine[myx - 1] = MainLine[myx];
   dep = MAXPLY;
   HintEvalu = MainEvalu;
   if (MovTab[0].movpiece == empty)
   {
       HintLine[0] = ZeroMove;   /*  No possible move  */
       if (AutoPlay)
       {
           NewGame();
           PrintBoard();
           StartMove();
       }
       return;
   }

//   FlashMove(&MovTab[Depth+1]);  /*  flash and perform the move  */
   DoSlideMove(MovTab[Depth+1]);
   EnterMove(&MovTab[Depth+1]);
   if (SoundOn)
      MessageBeep(0);
   StoreMoves();
   if (Logging && !AutoPlay)
      {
      sprintf(buf, "%3d. ",(MoveNo+1) / 2);
      *OutputFile << buf;
      strcpy(str, MoveStr(&MovTab[0]));
      if ((PlayerMove.movpiece == empty) && (Opponent == white))
          sprintf(buf, "%8.8s ", str);
      else
          sprintf(buf, "%s%8.8s",MoveStr(&PlayerMove), str);
      *OutputFile << buf;
      sprintf(buf, "    (%s)%9.2f%3d:%2d", MoveStr(&MainLine[1]),
           MainEvalu / 256.0, MaxDepth, LegalMoves);
      *OutputFile << buf;
      OutputNode(&Nodes);
      sprintf(buf, "%8.1lf\n", ChessClock.totaltime);
      *OutputFile << buf;
      }
   PlayerMove = ZeroMove;
   ColorToPlay(Player);
   if (AutoPlay)
   {
        if ((MoveNo >= 120) || (FiftyMoveCnt() >= 100) ||
            (Repetition(0) >= 3) || (MainEvalu <= -0x880))
            {
            NewGame();
            PrintBoard();
            }
        StartMove();
        return;
    }
   if (Level != easygame && !GameOver)
       ThinkAwhile();
}


/*
 *  Perform analysis in the opponents time of reflection.
 *  The program assumes that the opponent will perform the
 *  Hint move, and starts analysing on it for a counter move
 */


static void ThinkAwhile()
{
extern HCURSOR hArrowCursor;

   SetClassWord(hWndMain, GCW_HCURSOR, WORD( hArrowCursor ));
   SetCursor(hArrowCursor);
   SetMenu(hWndMain, MainMenu);
    if ((HintLine[0].movpiece == empty) || MultiMove)
        return;
    Analysis = FALSE;
    Opan = TRUE;
    AdjustMoves();          /*  Setup surroundings as if the  */
    MovTab[Depth+1] = HintLine[0];  /*  Opponent had performed  */
    MakeMove(&MovTab[Depth+1]);        /*  The hint move  */
    StoreMoves();
    AdjustMoves();
    Depth = 0;          /*  analyse until something is entered from by */
    FindMove(MaxLevel); /*  the user */
    Depth = -1;
    Opan = FALSE;
    if (Analysis)          /*  If the Opponent did make the  */
    {                      /*  Hint move then go and  */
        ReturnAnalysis();  /*  perform the counter move  */
        return;
    }
    TakeBackMove(&MovTab[Depth]);  /*  restore the surroundings  */
    if (GotValidMove)
      {
      AdjustMoves();
      EnterKeyMove();
      StoreMoves();
      SetMenu(hWndMain, ThinkMenu);
      SetClassWord(hWndMain, GCW_HCURSOR, WORD( hWaitCursor ));
      SetCursor(hWaitCursor);
      }
    return;
}


void StartMove()
{
   MSG msg;
   StartAnalysis();
   AdjustMoves();
   CalcLibNo();            /*  Try to find a move in the opening library  */
   Depth = 0;
   if (LibNo > 0)
   {
       OpeningLibMsg();
       InLibrary = TRUE;
       FindOpeningMove();
       if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
         {
            if (msg.message == WM_COMMAND && msg.wParam == CM_STOP)
               return;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
         }
   }
   else
   {
       if (InLibrary)
       {
           InLibrary = FALSE;
           ClearMessage();
       }
       FindMove(MaxLevel);
   }
   Depth = -1;
   ReturnAnalysis();
}


void ProgramMove()
{
   do
      {
      GotValidMove = FALSE;
      ColorToPlay(Player);
      StartMove();
      }
   while (GotValidMove);
}


void Talk()
{
   StartUp();
   NewGame();
}


BOOL Redo()
{
//   MakeMove(&MovTab[Depth+1]);
   EnterMove(&MovTab[Depth+1]);
   ClearHint();
//   UpdateBoard();
   ClearBestLine();
   ColorToPlay(Player);
   if (Depth >= -1)
      return FALSE;  // cannot redo again
   return TRUE;  // can redo again
}

BOOL Undo()
{
// TakeBackMove(&MovTab[Depth]);
   extern void RemoveMove(MOVETYPE *);
   RemoveMove(&MovTab[Depth]);
   ClearHint();
//   UpdateBoard();
   ClearBestLine();
   ColorToPlay(Player);
   if (MovTab[Depth].movpiece == empty)
      return FALSE;  // Can't undo anymore
   return TRUE;  // Can still undo
}

void QuitProgram()
{
   long color;

   if (Logging)
      OutputFile->close();
   color = RGB(WhiteSquareColors[0], WhiteSquareColors[1],
      WhiteSquareColors[2]);
   sprintf(buf, "%ld", color);
   WritePrivateProfileString("WCHESS", "WhiteSquare", buf, INIFile);
   color = RGB(BlackSquareColors[0], BlackSquareColors[1],
      BlackSquareColors[2]);
   sprintf(buf, "%ld", color);
   WritePrivateProfileString("WCHESS", "BlackSquare", buf, INIFile);
   sprintf(buf, "%d", Level);
   WritePrivateProfileString("WCHESS", "Level", buf, INIFile);
   sprintf(buf, "%lf", AverageTime);
   WritePrivateProfileString("WCHESS", "AverageTime", buf, INIFile);
   sprintf(buf, "%d", (int)MaxLevel);
   WritePrivateProfileString("WCHESS", "MaxLevel", buf, INIFile);
   sprintf(buf, "%d", (int)SoundOn);
   WritePrivateProfileString("WCHESS", "SoundOn", buf, INIFile);
}


void FindHintMove()
{
    /*  If hintline is empty the get the move from the
        opening library or perform a 1 - ply search  */
    if (HintLine[0].movpiece == empty)
    {
        AdjustMoves();
        CalcLibNo();
        Depth = 0;
        if (LibNo > 0)
            FindOpeningMove();
        else
        {
            Analysis = 1;
            Opan = 0;
            FindMove(1);
        }
        Depth = -1;
        HintLine[0] = MainLine[0];
        HintLine[1] = ZeroMove;
        HintEvalu = -MainEvalu;
    }
}

