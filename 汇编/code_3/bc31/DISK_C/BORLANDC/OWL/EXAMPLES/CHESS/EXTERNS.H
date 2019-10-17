// ObjectWindows - (C) Copyright 1992 by Borland International

#ifndef __EXTERNS_H
#define __EXTERNS_H

#ifndef __WCDEFS_H
#include "wcdefs.h"
#endif

#ifndef __INFO_H
#include "info.h"
#endif

extern COLORTYPE Opponent;
extern PIECETAB PieceTab[][16];
extern BOARDTYPE Board[0x78];
extern BYTE WhiteSquareColors[];
extern BYTE BlackSquareColors[];
extern char buf[];

extern PTInfoWindow TInfo;
extern HBRUSH hBlackBrush;
extern HBRUSH hWhiteBrush;
extern BOOL ShowBestLine;
extern BOOL Turned;
extern HWND hWndMain;
extern HBITMAP PieceBmpArray[][2];
extern HBITMAP MaskArray[];
extern LEVELTYPE Level;
extern double AverageTime;
extern COLORTYPE RunColor;
extern BYTE MaxLevel;
extern COLORTYPE ComputerColor;
extern int BORDERSIZE;
extern short CHARSIZE;
extern short LINESIZE;
extern BOOL Editing;
extern COLORTYPE Player;
extern COLORTYPE ProgramColor;
extern MAXTYPE MainEvalu;
extern int PVTable[2][7][0x78];
extern int DirTab[];
extern int KnightDir[];
extern int PawnDir[];
extern DEPTHTYPE Depth;
extern short INFOXSIZE, INFOYSIZE;
extern int OfficerNo[];
extern int PawnNo[];
extern MOVETYPE *MovTab;
extern MOVETYPE ZeroMove;
extern int PieceValue[];
extern CLOCKTYPE ChessTime[];
extern BOOL MultiMove, AutoPlay, SingleStep;
extern int MoveNo;
extern CLOCKTYPE ChessClock;
extern BOOL Analysis, Opan;
extern NODEVAL Nodes;             
extern CASTMOVETYPE CastMove[2][2];
extern MAXTYPE RootValue;
extern MOVETYPE KeyMove;
extern BOARDIDTYPE Display[];
extern LINETYPE HintLine;
extern MAXTYPE HintEvalu;
extern MOVETYPE Next;
extern MOVETYPE PlayerMove;
extern BOOL ComputerThinking;
extern LINETYPE MainLine;
extern int MaxDepth;
extern HCURSOR hWaitCursor;
extern HMENU ThinkMenu;
extern HMENU MainMenu;
extern BOOL Running;
extern BOOL GotValidMove;
extern BOOL GameOver;
extern char EndGameMessage[];
extern BOOL NoComputerMove;
extern BOOL SoundOn;


extern void DragStart(SQUARETYPE, POINT&);
extern void DragEnd(BOOL);
extern void Drag(POINT&);
extern short Attacks(COLORTYPE acolor, SQUARETYPE square);
extern POINT GetSquareXY(SQUARETYPE);
extern void ClearSquare(SQUARETYPE square);
extern void DrawFrame(HDC, RECT&, BOOL=FALSE);
extern void GenCastSquare(SQUARETYPE new1, SQUARETYPE *castsquare,
                    SQUARETYPE *cornersquare);
extern void CalcCastling(COLORTYPE incolor,  CASTDIRTYPE *cast);
extern void ClearBoard();
extern void ResetNewPos();
extern void Error(char *);
extern void ColorToPlay(COLORTYPE);
extern void InitDisplay();
extern void ClearDisplay();
extern void ClearInfoWindow();
extern void NewGame();
extern void InsertPiece(PIECETYPE p, COLORTYPE c, SQUARETYPE sq);
extern void PrintCurLevel();
extern void InitNode(NODEVAL*);
extern void InitTime(CLOCKTYPE *clock);
extern void StartTime(CLOCKTYPE *);
extern void StopTime(CLOCKTYPE *);
extern void PrintNodes(NODEVAL *, double);
extern void Perform(MOVETYPE *, BOOL);
extern void TakeBackMove(MOVETYPE *move);
extern void MakeMove(MOVETYPE *);
extern BOOL EqMove(MOVETYPE *a, MOVETYPE *b);
extern void IncNode(NODEVAL *nodes);
extern short PieceAttacks(PIECETYPE, COLORTYPE, SQUARETYPE, SQUARETYPE);
extern FIFTYTYPE FiftyMoveCnt(void);
extern REPEATTYPE Repetition(short immediate);
extern void PrintBestMove(MOVETYPE *mainline, MAXTYPE mainevalu);
extern void DisplayMove(BOOL *singlestep, DEPTHTYPE maxdepth, MAXTYPE evaluation, BOOL);
extern int StatEvalu(MOVETYPE *move);
extern short KillMovGen(MOVETYPE *move);
extern void CalcPVTable();
extern void EnterKeyMove();
extern void StartAnalysis();
extern void Warning(char *);
extern void PrintMove(int, COLORTYPE, MOVETYPE *, double);
extern void UpdateBoard();
extern void InitMovGen();
extern void MovGen();
extern void Message(char *);
extern void CalcPieceTab();
extern void ClearBestLine();
extern void ResetMoves();
extern void InitChessTime();
extern void ClearHint();
extern void ClearPVTable();
extern void AdjustMoves();
extern void FindMove(int maxlevel);
extern void OpeningLibMsg();
extern char *MoveStr(MOVETYPE *);
extern void ClearMessage();
extern void EnterMove(MOVETYPE *move);
extern void FlashMove(MOVETYPE *move);
extern void StoreMoves();
extern void CalcAttackTab();
extern void SaveGame(char *savefile);
extern void RestoreGame(char *);
extern BOOL Undo();
extern BOOL Redo();
extern void PrintBoard();
extern void FindHintMove();
extern void ShowHint();
extern void Talk();
extern SQUARETYPE GetValidSquare(POINT, COLORTYPE, BOOL);
extern void DrawInvertedBitmap(SQUARETYPE);
extern void DrawNormalBitmap(SQUARETYPE);
extern void InitCommStuff();
extern BOOL MoveCheck(SQUARETYPE, SQUARETYPE);
extern void ProgramMove();
extern WORD MessageToPost;
extern void QuitProgram();
extern void HideAttacks();
extern void DisplayTime();
void DoSlideMove(MOVETYPE&);
void SlidePiece(SQUARETYPE, SQUARETYPE);
void GenCastSquare(SQUARETYPE, SQUARETYPE*, SQUARETYPE*);

#endif // __EXTERNS_H
