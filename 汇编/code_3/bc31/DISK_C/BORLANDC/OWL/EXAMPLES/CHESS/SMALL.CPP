// ObjectWindows - (C) Copyright 1992 by Borland International

#include <windows.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include "wcdefs.h"
#include "wchess.h"
#include "externs.h"

/*
 *  Global Variables
 */


MOVETYPE ZeroMove = { 8, 8, 0, empty, empty };
CLOCKTYPE ChessTime[2];
MOVETYPE KeyMove;
BOOL Running;
COLORTYPE RunColor;
BOOL Analysis, Opan;
double WantedTime;
extern double AverageTime;
BOOL GameOver = FALSE;
char EndGameMessage[80];


void EndMessage(char *);

/*
 *  Initialize the chess clocks
 */

void InitChessTime()
{
   InitTime(&ChessTime[white]);
   InitTime(&ChessTime[black]);
}

void StopChessTime()
{
    if (Running)
    {
        StopTime(&ChessTime[RunColor]);
        KillTimer(hWndMain, TIMEID);
        Running = FALSE;
    }
}

/*
 *  Stop the running chess clock and start the clock for color
 */

void StartChessTime(COLORTYPE color)
{
    RunColor = color;
    Running = TRUE;
    StartTime(&ChessTime[RunColor]);
    SetTimer(hWndMain, TIMEID, 1000, NULL);
}

/*
 *  reset MovTab
 */

void ResetMoves()
{
   Depth = -1;
   MovTab[-1] = ZeroMove;
}


/*
 *  Clear HintLine
 */

void ClearHint()
{
   HintLine[0] = ZeroMove;
   HintEvalu = 0;
}

void InitNode(NODEVAL *nodes)
{
   nodes->nodebase = 0;
   nodes->nodeoffset = 0;
}

/*
 *  Test if the move is legal for Programcolor == player in the
 *  given position
 */

BOOL IllegalMove(MOVETYPE *move)
{
   BOOL illegal;

   Perform(move, 0);
   illegal = Attacks(Opponent, PieceTab[Player][0].isquare);
   Perform(move, 1);
   return illegal;
}



/*
 *  Make move for programcolor = player and updates variables
 */

void MakeMove(MOVETYPE *move)
{
    Depth++;
    MoveNo++;
    Perform(move, 0);
    ProgramColor = Opponent;
    Opponent = Player;
    Player = ProgramColor;
}


/*
 *  Prints comment to the game (check, mate, draw, resign)
 */

void PrintComment(void)
{
   extern char buf[];
    short check, possiblemove, checkmate;
    int nummoves;

    Message("");
    checkmate = 0;
    Depth++;
    possiblemove = 0;
    InitMovGen();
    do
    {
        MovGen();
        if (Next.movpiece != empty)
            if (!IllegalMove(&Next))
                possiblemove = 1;
    } while (Next.movpiece != empty && !possiblemove);

    Depth--;
    check = Attacks(Opponent, PieceTab[Player][0].isquare); /* calculate check */
    /*  No possible move means checkmate or stalemate  */
    if (!possiblemove)
    {
        if (check)
        {
            checkmate = 1;
            EndMessage("CheckMate");
        }
        else
            EndMessage("Stalemate!");
    }
    else
        if (HintEvalu >= MATEVALUE - DEPTHFACTOR * 16)
        {
            nummoves = (MATEVALUE - HintEvalu + 0x40) / (DEPTHFACTOR * 2);
            sprintf(buf, "Mate in %d Move%c", nummoves, (nummoves > 1) ? 's!':'!');
            Message(buf);
        }
    if (check && !checkmate)
        Message("Check!");
    else  /*  test 50 move rule and repetition of moves  */
      {
      if (FiftyMoveCnt() >= 100)
         {
         EndMessage("50 Move rule");
         }
      else
         if (Repetition(0) >= 3)
         {
            EndMessage("3 fold Repetition");
         }
         else                /*  Resign if the position is hopeless  */
            if (-25500 < HintEvalu && HintEvalu < -0x880)
               {
               switch (Opponent)
                  {
                  case white :
                     EndMessage(" White resigns");
                     break;
                  case black :
                     EndMessage(" Black resigns");
                  }
               }
      }
}

void EnterMove(MOVETYPE *move)
{
   StopChessTime();
   PrintMove(MoveNo, ProgramColor, move, ChessTime[RunColor].totaltime);
   MakeMove(move);
   UpdateBoard();
   PrintComment();
   StartChessTime(ProgramColor);
}

void RemoveMove(MOVETYPE *move)
{
   StopChessTime();
   PrintMove(MoveNo, ProgramColor, move, ChessTime[RunColor].totaltime);
   TakeBackMove(move);
   UpdateBoard();
   PrintComment();
   StartChessTime(ProgramColor);
}

/*
 *  perform the move entered by the user 
 */

void EnterKeyMove(void)
{
    MovTab[Depth+1] = KeyMove;
    PlayerMove = KeyMove;
    ClearHint();
    DragEnd(TRUE);
    EnterMove(&MovTab[Depth+1]);
}


/*
 *  move movtab to depth = -1
 */

void AdjustMoves()
{
    int i;

    for (i = Depth; i>= BACK; i--)
        MovTab[i - (Depth+1)] = MovTab[i];
    Depth = -1;
}


/*
 *  Move movtab one move BACK
 */


void StoreMoves(void)
{
    int i;
    Depth--;
    for (i = BACK; i <= Depth; i++)
        MovTab[i] = MovTab[i+1];
    MovTab[BACK] = ZeroMove;
}
    

/*
 *  Check to see if the input move is legal
 */
               
BOOL MoveCheck(SQUARETYPE startsq, SQUARETYPE endsq)
{
   Depth++;
   KeyMove = ZeroMove;
   InitMovGen();
   do
      {
      MovGen();
      if (Next.new1 == endsq && Next.old == startsq)
         {
         KeyMove = Next;
         break;
         }
      } while (Next.movpiece != empty);
   if (KeyMove.movpiece == empty)
      {
      Warning("Impossible move");
      Depth--;
      return FALSE;
      }
   if (IllegalMove(&KeyMove))
      {
      Warning("Illegal move. Check!");
      Depth--;
      return FALSE;
      }
   Depth--;
   if (!ComputerThinking)
      {
      AdjustMoves();
      EnterKeyMove();
      StoreMoves();
      }
   return TRUE;
}


/*
 *  calculate the WANTED response time
 */

void StartAnalysis()
{
    int timecontrol;
   extern HWND hWndMain;
   extern HCURSOR hWaitCursor;

    Analysis = 1;
    Opan = 0;
    SetClassWord(hWndMain, GCW_HCURSOR, WORD(hWaitCursor));
    SetCursor(hWaitCursor);   
    switch (Level)
    {
        case easygame :
        case normal :
            /*  Divides the Time left till nest time control
                between moves left.  There is a margin of
                4 moves to make sure that the program does
                not lose on time  */
            timecontrol = (((MoveNo >> 1) + 20) / 20) * 20;
            if (timecontrol <= 40) timecontrol = 40;
            WantedTime = (AverageTime * timecontrol -
                    ChessTime[ProgramColor].totaltime) /
                        (timecontrol + 4 - (MoveNo >> 1));

            /*  In the begining of the game the program thinks
                around twice as long, since the early middle
                game is normally the most crucial part of
                a game  */

            if ((MoveNo >> 1) <= 40)
                WantedTime = 5.0 + (WantedTime - 5.0) *
                        ((80 - (MoveNo >> 1)) /40);
            break;
        case fullgametime :
            /*  Assumes that the game will last for around 40 moves and
                divides the time left accordingly  */
             WantedTime = (AverageTime * 60.0 -
                    ChessTime[ProgramColor].totaltime) / 44;

            /*  In the begining of the game the program thinks
                around twice as long, since the early middle
                game is normally the most crucial part of
                a game  */
            if ((MoveNo >> 1) <= 40)
                WantedTime = 5.0 + (WantedTime - 5.0) *
                        ((80 - (MoveNo >> 1)) /40);
            break;
        case matching :
            /*  Spend as much time as the Opponent does  */
            if (MoveNo >= 2)
                WantedTime = ChessTime[Opponent].totaltime / (MoveNo >> 1);
            else
                WantedTime = 5.0;
            WantedTime += (ChessTime[Opponent].totaltime -
                        ChessTime[ProgramColor].totaltime) * 0.25;
        default :
            WantedTime = 1000000.0;
    }
}


/*
 *  take BACK move and update variables
 */

void TakeBackMove(MOVETYPE *move)
{
    ProgramColor = Opponent;
    Opponent = Player;
    Player = ProgramColor;
    Perform(move, 1);
    MoveNo--;
    Depth--;
}


void IncNode(NODEVAL *nodes)
{
    if (nodes->nodeoffset >= MAXINT)
    {
        nodes->nodebase++;
        nodes->nodeoffset = 0;
    }
    else
        nodes->nodeoffset++;
}


void Wait(int tenths)
{
    clock_t NumTicksToWait;

    /* two ticks == approx. 1/10 second, since 18.2 clocks is approx a
       second */
    NumTicksToWait = (tenths * 2) + clock();
    while (NumTicksToWait > clock()) ;
}


/*
 *  Flash a move once on the screen
 */

void FlashMove(MOVETYPE *move)
{
    MakeMove(move);
    UpdateBoard();
    Wait(4);
    TakeBackMove(move);
    UpdateBoard();
    Wait(4);
}

void DoSlideMove(MOVETYPE &move)
{
   SQUARETYPE castsquare, cornersquare;
   SlidePiece(move.new1, move.old);
   if (move.spe)
   {
       if (move.movpiece == king)
       {
           GenCastSquare(move.new1, &castsquare, &cornersquare);
           SlidePiece(castsquare, cornersquare);
       }
   }
}

void EndMessage(char *message)
{
   strcpy(EndGameMessage, message);
   GameOver = TRUE;
}


void ShowHint()
{
    DEPTHTYPE dep = 0;
    buf[0] = '\0';
    Message(buf);
    while (HintLine[dep].movpiece != empty)
    {
        strcat(buf, MoveStr(&HintLine[dep]));
        strcat(buf, " ");
        Message(buf);
        MakeMove(&HintLine[dep]);
        UpdateBoard();
        Wait(6);
        dep++;
    }
    while (dep > 0)
    {
        dep--;
        TakeBackMove(&HintLine[dep]);
    }
    UpdateBoard();
}
