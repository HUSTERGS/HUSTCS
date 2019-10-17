// ObjectWindows - (C) Copyright 1992 by Borland International

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "wcdefs.h"
#include "externs.h"


struct SAVERESTORE
{
COLORTYPE Player, Opponent, ProgramColor;
BOOL Turned;
BOOL MultiMove, AutoPlay, SingleStep;
LEVELTYPE Level;
double AverageTime;
BOOL MaxLevel;
int MoveNo;
double ChessClockTotalTime, BlackTotalTime, WhiteTotalTime;
int PieceValue[7];
};


static BOOL SaveBoard(char *savefile)
{
    FILE *gameboard;
   SAVERESTORE *Save;

   Save = new SAVERESTORE;
   if (Save == NULL)
      {
      MessageBox(hWndMain, "Not enough memory to perform operation",
         "OWL Chess", MB_OK | MB_ICONHAND);
      return 0;
      }
    if ((gameboard = fopen(savefile, "wb")) == NULL)
    {
        sprintf(buf, "Cannot open %s for writing", savefile);
        MessageBox(hWndMain, buf, "OWL Chess", MB_OK | MB_ICONHAND);
        delete Save;
        return 0;
    }

   Save->Player = Player;
   Save->Opponent = Opponent;
   Save->ProgramColor = ProgramColor;
   Save->Turned = Turned;
   Save->MultiMove = MultiMove;
   Save->AutoPlay = AutoPlay;
   Save->SingleStep = SingleStep;
   Save->Level = Level;
   Save->AverageTime = AverageTime;
   Save->MaxLevel = MaxLevel;
   Save->MoveNo = MoveNo;
   Save->ChessClockTotalTime = ChessClock.totaltime;
   Save->BlackTotalTime = ChessTime[black].totaltime;
   Save->WhiteTotalTime = ChessTime[white].totaltime;
   memcpy(Save->PieceValue, PieceValue, 7 * sizeof(int));
   fwrite(Save, sizeof(SAVERESTORE), 1, gameboard);
   fwrite(Board, sizeof(Board), 1, gameboard);
   fclose(gameboard);
   delete Save;
   return 1;
}


void SaveGame(char *savefile)
{
    if (strlen(savefile) > 0)
    {
        if (!SaveBoard(savefile))
        {
            Error("Error during Save");
        }
    }
}


void LoadBoard(char *loadfile)
{
   FILE *load;
   SAVERESTORE *Restore;

   Restore = new SAVERESTORE;

   if (!Restore)
      {
      MessageBox(hWndMain, "Not enough memory to perform operation",
         "OWL Chess", MB_OK | MB_ICONHAND);
      return;
      }

    if ((load = fopen(loadfile, "rb")) == NULL)
        Error("File not found");
    else
    {
        fread(Restore, sizeof(SAVERESTORE), 1, load);
        fread(Board, sizeof(Board), 1, load);
        fclose(load);
        Player = Restore->Player;
        Opponent = Restore->Opponent;
        ProgramColor = Restore->ProgramColor;
        Turned = Restore->Turned;
        MultiMove = Restore->MultiMove;
        AutoPlay = Restore->AutoPlay;
        SingleStep = Restore->SingleStep;
        Level = Restore->Level;
        AverageTime = Restore->AverageTime;
        MaxLevel = Restore->MaxLevel;
        MoveNo = Restore->MoveNo;
        ChessClock.totaltime = Restore->ChessClockTotalTime;
        ChessTime[black].totaltime = Restore->BlackTotalTime ;
        ChessTime[white].totaltime = Restore->WhiteTotalTime;
        memcpy(PieceValue, Restore->PieceValue, 7 * sizeof(int));
        ClearDisplay();
        InitDisplay();
        InvalidateRect(hWndMain, NULL, TRUE);
        PrintCurLevel();
        ResetNewPos();
    }
   delete Restore;
}

/****************************************************************************/

void RestoreGame(char *loadfile)
{
    if (strlen(loadfile))
	   LoadBoard(loadfile);
    else
      Error("Game not loaded");
}

