// ObjectWindows - (C) Copyright 1992 by Borland International

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <static.h>
#include <filedial.h>
#include <inputdia.h>
#include <bwcc.h>

#include "wcdefs.h"
#include "wchess.h"
#include "info.h"
#include "externs.h"


/*
 *  Global variables
 */

BOARDIDTYPE Display[0x78];
char *PieceLetter = " KQRBNP";
char buf[280];   //  general string buffer, used in several modules

/*
 *  static global variables
 */

static RECT BoardRect;


/*
 *  get handle to bitmap of current piece
 */

HBITMAP GetBitmapHandle(PIECETYPE piece, COLORTYPE pcolor)
{
   if (piece == 0)
      return 0;
   return PieceBmpArray[piece - 1][pcolor];
}


/*
 *  Clear all information from Info window
 */

void ClearInfoWindow()
{
   TInfo->Reset();
}

/*
 *  Prints current color to play
 */

void ColorToPlay(COLORTYPE color)
{
   if (color == white)
      TInfo->SetTurnText("White");
   else
      TInfo->SetTurnText("Black");
}

void Message(char *str)
{
   TInfo->SetMessageText(str);
}

void Error(char *str)
{
   if (SoundOn)
      MessageBeep(0);
   strcpy(buf, str);
   SendMessage(hWndMain, WM_COMMAND, EM_ERROR, 0L);
}

void Warning(char *str)
{
   if (SoundOn)
      MessageBeep(0);
   Message(str);
}


/*
 *  convert a move to a string
 */

char *MoveStr(MOVETYPE *move)
{
    static char str[7];

    strcpy(str, "      ");
    if (move->movpiece != empty)
    {
        if (move->spe && move->movpiece == king)  /*  castling  */
        {
            if (move->new1 > move->old) strcpy(str, "O-O   ");
            else strcpy(str, "O-O-O ");
        }
        else
        {
            str[0] = PieceLetter[move->movpiece];
            str[1] = 'a' + move->old % 16;
            str[2] = '1' + move->old / 16;
            if (move->content == empty)
                str[3] = '-';
            else
                str[3] = 'x';
            str[4] = 'a' + move->new1 % 16;
            str[5] = '1' + move->new1 / 16;
        }
    }
    return (str);
}


void PrintMove(int moveno, COLORTYPE programcolor, MOVETYPE *move, double time)
{
   int minutes;
   minutes = (int)(time / 60.0);

   sprintf(buf, "%2.2d:%#04.1f %3.3d. %s", minutes, time - minutes * 60.0, moveno / 2 + 1, MoveStr(move));
   if (programcolor == white)
      TInfo->SetWhiteInfoText(buf);
   else
      TInfo->SetBlackInfoText(buf);
}


/*
 *  draw 3d type frame
 */

void DrawFrame(HDC hDC, RECT& BoardRect, BOOL DrawBackground)
{
    int x1, y1, x2, y2;
    POINT pArray[3];
    HPEN hPen, hOldPen;
    HBRUSH hOldBrush;
     
    x1 = BoardRect.left;
    x2 = BoardRect.right;
    y1 = BoardRect.top;
    y2 = BoardRect.bottom;
    if (DrawBackground == FALSE)
      hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(NULL_BRUSH));
    else
      hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(LTGRAY_BRUSH));
   
    hOldPen = (HPEN)SelectObject(hDC, GetStockObject(WHITE_PEN));

    Rectangle(hDC, x1, y1, x2, y2);
    SelectObject(hDC, hPen = CreatePen(PS_SOLID, 1, RGB(192, 192, 192)));
    Rectangle(hDC, x1+1, y1+1, x2-1, y2-1);
    DeleteObject(SelectObject(hDC, GetStockObject(WHITE_PEN)));

    pArray[0].x = x1 + 2;
    pArray[1].y = pArray[0].y = y2 - 3;
    pArray[2].x = pArray[1].x = x2 - 3;
    pArray[2].y = y1 + 2;

    Polyline(hDC, pArray, 3);
    hPen = CreatePen(PS_SOLID, 1, RGB(128, 128, 128));
    SelectObject(hDC, hPen);
    pArray[0].x = x1;
    pArray[1].y = pArray[0].y = y2-1;
    pArray[2].x = pArray[1].x = x2-1;
    pArray[2].y = y1;

    Polyline(hDC, pArray, 3);
    pArray[1].x = pArray[0].x = x1 + 2;
    pArray[0].y = y2 - 3;
    pArray[2].y = pArray[1].y = y1 + 2;
    pArray[2].x = x2 - 3;
    Polyline(hDC, pArray, 3);
    SelectObject(hDC, hOldBrush);
    DeleteObject(SelectObject(hDC, hOldPen));
}


/*
 *  Display the current level indicator
 */

void PrintCurLevel()
{
   extern BOOL MultiMove;

   if (MultiMove)
      strcpy(buf, "Two Player");
   else
      {
      switch (Level)
         {
         case normal:
            sprintf(buf, "%1.0f sec / move", AverageTime);
            break;
         case fullgametime:
            sprintf(buf, "%2.2f min / game", AverageTime);
            break;
         case easygame:
            strcpy(buf, "Easy");
            break;
         case infinite :
            strcpy(buf, "Infinte");
            break;
         case plysearch :
            sprintf(buf, "Ply-Depth = %d", MaxLevel);
            break;
         case matesearch:
            strcpy(buf, "MateSearch");
            break;
         case matching :
            strcpy(buf, "Match users time");
            break;
         }
      }
   TInfo->SetLevelText(buf);
}

POINT GetSquareXY(SQUARETYPE square)
{
   POINT p;

   if (Turned)
      square ^= 0x77;
   p.x = (square % 8) * SQUARE_SIZE + BORDERSIZE + MYFRAMESIZE;
   p.y = (7 - square / 16) * SQUARE_SIZE + BORDERSIZE + MYFRAMESIZE;
   return p;
}

void ClearSquare(SQUARETYPE square)
{
   HANDLE hOldBrush;
   POINT p;
   HDC hDC;

   p = GetSquareXY(square);
   
   hDC = GetDC(hWndMain);
   if ((square % 8 + square /16) % 2 == 1)
      hOldBrush = SelectObject(hDC, hWhiteBrush);
   else
      hOldBrush = SelectObject(hDC, hBlackBrush);
   PatBlt(hDC, p.x, p.y, SQUARE_SIZE, SQUARE_SIZE, PATCOPY);
   SelectObject(hDC, hOldBrush);
   ReleaseDC(hWndMain, hDC);
}

void ClearDisplay()
{
   SQUARETYPE sq;
   ClearInfoWindow();
   for (sq = 0; sq <= 0x77; sq++)
      Display[sq].piece = empty;
}


/*
 *  Draw the board on the screen
 */

void DrawBoard()
{
   unsigned char no;
   HDC hDC;
   const SQUARETYPE printno[64] = { 0, 0x10, 0x20, 0x30, 0x40, 0x50,
                                        0x60, 0x70, 0x71, 0x72, 0x73,
                                        0x74, 0x75, 0x76, 0x77, 0x67,
                                        0x57, 0x47, 0x37, 0x27, 0x17,
                                           7,    6,    5,    4,    3,
                                           2,    1, 0x11, 0x21, 0x31,
                                         0x41, 0x51, 0x61, 0x62, 0x63,
                                        0x64, 0x65, 0x66, 0x56, 0x46,
                                        0x36, 0x26, 0x16, 0x15, 0x14,
                                        0x13, 0x12, 0x22, 0x32, 0x42,
                                        0x52, 0x53, 0x54, 0x55, 0x45,
                                        0x35, 0x25, 0x24, 0x23, 0x33,
                                        0x43, 0x44, 0x34};

   
   BoardRect.left = BoardRect.top = BORDERSIZE;
   BoardRect.right = BoardRect.bottom = BORDERSIZE + (2 * MYFRAMESIZE) +
      (8 * SQUARE_SIZE);
   hDC = GetDC(hWndMain);
   DrawFrame(hDC, BoardRect);
   ReleaseDC(hWndMain, hDC);
   for (no = 0; no < 64; no++)
      ClearSquare(printno[no]);
}

                                                                       
void PrintPiece(SQUARETYPE square, PIECETYPE piece, COLORTYPE color, DWORD Rop)
{
   HBITMAP hBitmap, hOldBmp, hMaskBmp;
   BITMAP Bitmap;
   HDC hMemoryDC, hDC;
   POINT p;

   if (piece == empty)
      return;

   hBitmap = PieceBmpArray[piece-1][color];
   hMaskBmp = MaskArray[piece-1];

   hDC = GetDC(hWndMain);
   hMemoryDC = CreateCompatibleDC(hDC);
   GetObject(hBitmap, sizeof(BITMAP), (LPSTR) &Bitmap);
   hOldBmp = (HBITMAP)SelectObject(hMemoryDC, hMaskBmp);
   p = GetSquareXY(square);

   BitBlt(hDC, p.x, p.y, Bitmap.bmWidth, Bitmap.bmHeight,
      hMemoryDC, 0, 0, SRCAND);
   SelectObject(hMemoryDC, hBitmap);
   BitBlt(hDC, p.x, p.y, Bitmap.bmWidth, Bitmap.bmHeight,
      hMemoryDC, 0, 0, Rop);
   SelectObject(hMemoryDC, hOldBmp);
   DeleteDC(hMemoryDC);
   ReleaseDC(hWndMain, hDC);
}

void InitDisplay()
{
   SQUARETYPE square;

   for (square = 0; square <= 0x77; square++)
      if (!(square & 0x88))
         if ((Board[square].piece != Display[square].piece) ||
            (Board[square].piece != empty) && (Board[square].color !=
            Display[square].color))
            {
               Display[square].piece = Board[square].piece;
               Display[square].color = Board[square].color;
            }
}


/*
 *   Draw a box in the square of an attacked piece.
 *   Square is black if Defended is TRUE, else it is red.
 */

static void FrameSquare(SQUARETYPE square, BOOL Defended)
{
   POINT p;
   HPEN   hOldPen;
   HBRUSH hOldBrush;
   HDC hDC;
   hDC = GetDC(hWndMain);

   p = GetSquareXY(square);
   hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(NULL_BRUSH));
   if (Defended)
      hOldPen = (HPEN)SelectObject(hDC, GetStockObject(BLACK_PEN));
   else
      hOldPen = (HPEN)SelectObject(hDC, CreatePen(PS_SOLID,1,RGB(192, 0, 0)));


   Rectangle(hDC, p.x+1, p.y+1, p.x+SQUARE_SIZE-1, p.y+SQUARE_SIZE-1);
   SelectObject(hDC, hOldBrush);
   if (Defended)
      SelectObject(hDC, hOldPen);
   else
      DeleteObject(SelectObject(hDC, hOldPen));
   ReleaseDC(hWndMain, hDC);
}

void HideAttacks(void)
{
   SQUARETYPE square;

   for (square = 0; square <= 0x77; square++)
      if (!(square & 0x88))
         {
            if (Board[square].attacked == TRUE)
            {
            Board[square].attacked = FALSE;
            ClearSquare(square);
            PrintPiece(square, Board[square].piece,
               Board[square].color, SRCINVERT);
            }
         }
}

void ShowAttacks()
{
   SQUARETYPE square;

   for (square = 0; square <= 0x77; square++)
      if (!(square & 0x88))
         {
         if (Attacks(ComputerColor, square) && Board[square].color != ComputerColor && Board[square].piece != empty)
            {
            Board[square].attacked = TRUE;
            if (Attacks((COLORTYPE)!ComputerColor, square))
               FrameSquare(square, TRUE);
            else
               FrameSquare(square, FALSE);
            }
         else if (Board[square].attacked == TRUE)
            {
            Board[square].attacked = FALSE;
            ClearSquare(square);
            PrintPiece(square, Board[square].piece,
               Board[square].color, SRCINVERT);
            }
         }
}

void UpdateBoard()
{
   SQUARETYPE square;
   for (square = 0; square <= 0x77; square++)
      if (!(square & 0x88))
         if ((Board[square].piece != Display[square].piece) ||
            (Board[square].piece != empty) && (Board[square].color !=
            Display[square].color))
            {
               if (Display[square].piece != empty)
                  ClearSquare(square);
               Display[square].piece = Board[square].piece;
               Display[square].color = Board[square].color;
               if (Board[square].piece != empty)
                  PrintPiece(square, Board[square].piece,
                     Board[square].color, SRCINVERT);
            }
   if (Level == easygame && !Editing)
      ShowAttacks();
}

static void DrawAlphaNum();

void PrintBoard()
{
   SQUARETYPE square;

   DrawBoard();
   for (square = 0; square <= 0x77; square++)
      if (!(square & 0x88))
            {
               if (Display[square].piece != empty)
                  PrintPiece(square, Display[square].piece,
                     Display[square].color, SRCINVERT);
            }
   DrawAlphaNum();
   if (Level == easygame && !Editing)
      ShowAttacks();
}


/*
 *  find a square with a given point and determine whether it
 *  contains a player of the given color
 */

SQUARETYPE GetValidSquare(POINT p, COLORTYPE player, BOOL CheckPiece)
{
   POINT point;
   SQUARETYPE square;
   RECT sqrect;
   
   
   for (square = 0; square <= 0x77; square++)
      {
      if (!(square & 0x88))
         {
         point = GetSquareXY(square);
         sqrect.left = point.x;
         sqrect.top = point.y;
         sqrect.right = sqrect.left + SQUARE_SIZE;
         sqrect.bottom = sqrect.top + SQUARE_SIZE;
         if (PtInRect(&sqrect, p))
            {
            if ((Display[square].color == player && Display[square].piece
               != empty) || !CheckPiece)
               return square;
            }
         }
      }
   return -1;      
}

void DrawNormalBitmap(SQUARETYPE square)
{
   ClearSquare(square);
   PrintPiece(square, Display[square].piece, Display[square].color, SRCINVERT);
}

void DrawInvertedBitmap(SQUARETYPE square)
{
   PrintPiece(square, Display[square].piece, Display[square].color, NOTSRCERASE);
}

void OpeningLibMsg()
{
   TInfo->SetMessageText("Using opening library");
}

void PrintNodes(NODEVAL *nodes, double time)
{
    double nodereal;
    char buf[80];

    nodereal = (nodes->nodebase * MAXINT) + nodes->nodeoffset;
   if (time)
      {
      sprintf(buf, "%7.1f", nodereal/time);
      TInfo->SetSecondsText(buf);
      }
   sprintf(buf, "%7.0f ", nodereal);
   TInfo->SetNodeText(buf);
}


/*
 *  Print bestline on screen
 */

void PrintBestMove(MOVETYPE *mainline, MAXTYPE mainevalu)
{
   DEPTHTYPE dep = 0;

   *buf = 0;

   if (ShowBestLine == FALSE)
      return;
   while (dep < 7 && (mainline[dep].movpiece != empty))
   {
      strcat(buf, MoveStr(&mainline[dep++]));
      strcat(buf, " ");
   }
   TInfo->SetBestLineText(buf);
   sprintf(buf, "%7.2f", mainevalu /256.0);
   TInfo->SetValueText(buf);
}

void ClearBestLine()
{
   TInfo->SetBestLineText("");
}

void ClearMessage()
{
   TInfo->SetMessageText("");
}

static char * CharArray[] = { "a","b", "c", "d", "e", "f", "g", "h" };
static char * NumArray[] = { "1", "2", "3", "4", "5", "6", "7", "8" };

static void DrawBump(HDC hDC, int x, int y)
{
   int x2, y2;
   HPEN hOldPen;
   HBRUSH hOldBrush;
   POINT pArray[3];

   x2 = x + CHARSIZE + 2;
   y2 = y-- + LINESIZE + 1;
   x-=2;
   
   hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(LTGRAY_BRUSH));
   hOldPen = (HPEN)SelectObject(hDC, GetStockObject(WHITE_PEN));

   Rectangle(hDC, x, y, x2, y2);

   SelectObject(hDC, CreatePen(PS_SOLID, 1, RGB(128, 128, 128)));
   pArray[0].x = ++x;
   pArray[1].y = pArray[0].y = y2;
   pArray[2].x = pArray[1].x = x2;
   pArray[2].y = ++y;
   Polyline(hDC, pArray, 3);

   SelectObject(hDC, hOldBrush);
   DeleteObject(SelectObject(hDC, hOldPen));
}

static void DrawAlphaNum()
{
   int i;
   int XPos, YPos;
   HDC hDC;

   hDC = GetDC(hWndMain);


   XPos = (BORDERSIZE + MYFRAMESIZE)/2 - CHARSIZE/2;
   YPos = (BORDERSIZE + SQUARE_SIZE/2) - LINESIZE / 2;

   SetBkColor(hDC, RGB(192, 192, 192));

   for (i = 7; i >= 0; i--)
      {
      DrawBump(hDC, XPos, YPos);
      if (Turned)
         {
         TextOut(hDC, XPos, YPos, NumArray[7-i], 1);
         }
      else
         TextOut(hDC, XPos, YPos, NumArray[i], 1);
      YPos += SQUARE_SIZE;
      }

   XPos = BORDERSIZE + SQUARE_SIZE / 2 - CHARSIZE/2;
   YPos = BORDERSIZE + (8 * SQUARE_SIZE) + (2 * MYFRAMESIZE) + 1;
   
   for (i = 0; i < 8; i++)
      {
      DrawBump(hDC, XPos, YPos);
      if (Turned)
         TextOut(hDC, XPos, YPos, CharArray[7-i], 1);
      else
         TextOut(hDC, XPos, YPos, CharArray[i], 1);
      XPos += SQUARE_SIZE;
      }
   ReleaseDC(hWndMain, hDC);
}

