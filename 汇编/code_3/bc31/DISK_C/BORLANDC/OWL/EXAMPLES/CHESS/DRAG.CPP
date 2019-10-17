// ObjectWindows - (C) Copyright 1992 by Borland International

#include <windows.h>
#include <math.h>
#include "wcdefs.h"
#include "externs.h"

#define AnimationSpeed     2

static HDC hSaveDC;
static POINT LastPoint;
static HBITMAP hOldBmp, hDragPiece, hDragMask;
static HCURSOR hPrevCursor;

#undef max
#undef min
#define max(a, b)  (((a) > (b)) ? (a) : (b))
#define min(a, b)  (((a) < (b)) ? (a) : (b))
static BOOL IsDragging = FALSE;
static POINT StartPoint;
static POINT CurPoint;
void FAR PASCAL ReturnHome(int X, int Y, LPSTR lpData);

static void SaveBackground(POINT& p)
{
   HDC hDC;
   HBITMAP hBitmap;
   BITMAP Bitmap;
   

   LastPoint = p;
   hDC = GetDC(hWndMain);

   hBitmap = PieceBmpArray[0][white]; // handle to any of the bitmaps is ok
   GetObject(hBitmap, sizeof(BITMAP), (LPSTR) &Bitmap);

   
   hSaveDC = CreateCompatibleDC(hDC);
   hOldBmp = (HBITMAP)SelectObject(hSaveDC, 
	   CreateCompatibleBitmap(hDC, Bitmap.bmWidth,Bitmap.bmHeight));

   BitBlt(hSaveDC, 0, 0, Bitmap.bmWidth, Bitmap.bmHeight,
      hDC, p.x, p.y, SRCCOPY);

   ReleaseDC(hWndMain, hDC);
}


static void RestoreBackground()
{
   HDC hDC;
   HBITMAP hBitmap;
   BITMAP Bitmap;

   hDC = GetDC(hWndMain);
   hBitmap = PieceBmpArray[0][white]; // handle to any of the bitmaps is ok
   GetObject(hBitmap, sizeof(BITMAP), (LPSTR) &Bitmap);

   BitBlt(hDC, LastPoint.x, LastPoint.y, Bitmap.bmWidth, Bitmap.bmHeight,
      hSaveDC, 0, 0, SRCCOPY);

   DeleteObject(SelectObject(hSaveDC, hOldBmp));
   DeleteDC(hSaveDC);
   ReleaseDC(hWndMain, hDC);
}


static void ShowPiece(POINT& p)
{
   HBITMAP hOldBmp;
   BITMAP Bitmap;
   HDC hMemoryDC, hDC;

   hDC = GetDC(hWndMain);
   hMemoryDC = CreateCompatibleDC(hDC);
   GetObject(hDragPiece, sizeof(BITMAP), (LPSTR) &Bitmap);

   hOldBmp = (HBITMAP)SelectObject(hMemoryDC, hDragMask);
   BitBlt(hDC, p.x, p.y, Bitmap.bmWidth, Bitmap.bmHeight,
      hMemoryDC, 0, 0, SRCAND);

   SelectObject(hMemoryDC, hDragPiece);
   BitBlt(hDC, p.x, p.y, Bitmap.bmWidth, Bitmap.bmHeight,
      hMemoryDC, 0, 0, SRCINVERT);

   SelectObject(hMemoryDC, hOldBmp);
   DeleteDC(hMemoryDC);
   ReleaseDC(hWndMain, hDC);
}

BOOL Intersect(RECT& r1, RECT& r2)
{
   POINT p;

   p.x = r1.left;
   p.y = r1.top;

   if (PtInRect(&r2, p))
      return TRUE;
   p.y = r1.bottom;
   if (PtInRect(&r2, p))
      return TRUE;
   p.x = r1.right;
   if (PtInRect(&r2, p))
      return TRUE;
   p.y = r1.top;
   if (PtInRect(&r2, p))
      return TRUE;
   return FALSE;
}


static void UpdateScreen(POINT& p)
{
   HDC hDC, hUpdateDC, hNewSaveDC;
   HBITMAP hUOldBmp, hNewOldBmp;
   BITMAP Bitmap;
   RECT rect, rect1, rect2;
   int Width, Height;

   GetObject(hDragPiece, sizeof(BITMAP), (LPSTR) &Bitmap);

   rect1.left = p.x;
   rect1.top = p.y;
   rect1.right = p.x + Bitmap.bmWidth;
   rect1.bottom = p.y + Bitmap.bmHeight;
   rect2.left = LastPoint.x;
   rect2.top = LastPoint.y;
   rect2.right = LastPoint.x + Bitmap.bmWidth;
   rect2.bottom = LastPoint.y + Bitmap.bmHeight;
   
   if (!Intersect(rect1, rect2))
      {
      RestoreBackground();
      SaveBackground(p);
      ShowPiece(p);
      return;
      }

   hDC = GetDC(hWndMain);

   hNewSaveDC = CreateCompatibleDC(hDC);
   hNewOldBmp = (HBITMAP)SelectObject(hNewSaveDC, 
	   CreateCompatibleBitmap(hDC, Bitmap.bmWidth, Bitmap.bmHeight));

   rect.left = min(rect1.left, rect2.left);
   rect.top = min(rect1.top, rect2.top);
   rect.bottom = max(rect1.bottom, rect2.bottom);
   rect.right = max(rect1.right, rect2.right);

   Width = rect.right - rect.left;
   Height = rect.bottom - rect.top;

   hUpdateDC = CreateCompatibleDC(hDC);
   hUOldBmp = (HBITMAP)SelectObject(hUpdateDC, 
	           CreateCompatibleBitmap(hDC, Width,Height));

   /* get new section */
   BitBlt(hUpdateDC, 0, 0, Width, Height, hDC, rect.left, rect.top, SRCCOPY);

   /* restore old section */
   BitBlt(hUpdateDC, abs(rect.left - rect2.left), abs(rect.top - rect2.top),
      Bitmap.bmWidth, Bitmap.bmHeight, hSaveDC, 0, 0, SRCCOPY);

   /* save new background */
   BitBlt(hNewSaveDC, 0, 0, Bitmap.bmWidth, Bitmap.bmHeight,
      hUpdateDC, abs(rect.left - rect1.left), abs(rect.top - rect1.top),
      SRCCOPY);

   /* blit the mask */
   DeleteObject(SelectObject(hSaveDC, hDragMask));

   BitBlt(hUpdateDC, abs(rect.left - rect1.left), abs(rect.top - rect1.top),
      Bitmap.bmWidth, Bitmap.bmHeight, hSaveDC, 0, 0, SRCAND);

   /* blit the piece */
   SelectObject(hSaveDC, hDragPiece);
   BitBlt(hUpdateDC, abs(rect.left - rect1.left), abs(rect.top - rect1.top),
      Bitmap.bmWidth, Bitmap.bmHeight, hSaveDC, 0, 0, SRCINVERT);

   /* put it on the screen */
   BitBlt(hDC, rect.left, rect.top, Width, Height, hUpdateDC, 0, 0, SRCCOPY);

   SelectObject(hSaveDC, hOldBmp); // don't delete current bmp (hDragPiece) 
   DeleteDC(hSaveDC);
   hSaveDC = hNewSaveDC;
   hOldBmp = hNewOldBmp;
   LastPoint = p;
   DeleteObject(SelectObject(hUpdateDC, hUOldBmp));
   DeleteDC(hUpdateDC);
   ReleaseDC(hWndMain, hDC);
}

void DragStart(SQUARETYPE square, POINT& point)
{
   point.x -= 18;
   point.y -= 18;

   StartPoint = GetSquareXY(square);

   hDragPiece = PieceBmpArray[Board[square].piece-1][Board[square].color];
   hDragMask = MaskArray[Board[square].piece-1];

   hPrevCursor = SetCursor(0);
   SetClassWord(hWndMain, GCW_HCURSOR, 0);
   SetCapture(hWndMain);
   ClearSquare(square);
   SaveBackground(point);  
   ShowPiece(point);   
   IsDragging = TRUE;
}

void DragEnd(BOOL ValidMove)
{
   if (!IsDragging)
      return;
   if (ValidMove)
      RestoreBackground();
   else
      {
      LineDDA(CurPoint.x, CurPoint.y, StartPoint.x, StartPoint.y, 
	        LINEDDAPROC(ReturnHome), NULL);
      RestoreBackground();
      }
   SetCursor(hPrevCursor);
   SetClassWord(hWndMain, GCW_HCURSOR, WORD(hPrevCursor));
   ReleaseCapture();
   IsDragging = FALSE;
}

void Drag(POINT& p)
{
   p.x -= 18;
   p.y -= 18;
   CurPoint = p;
   UpdateScreen(p);
}

#pragma argsused
void FAR PASCAL ReturnHome(int X, int Y, LPSTR lpData)
{
   POINT Point;
   static int Count = AnimationSpeed;

   if (Count != 0)
      {
      Count--;
      return;
      }
   Count = AnimationSpeed;
   Point.x = X;
   Point.y = Y;
   UpdateScreen(Point);
}


void SlidePiece(SQUARETYPE end, SQUARETYPE start)
{
   POINT p1 = GetSquareXY(start);
   POINT p2;

   if (IsDragging)
      MessageBox(NULL, "SlidePiece called before DragEnd", "WChess", MB_OK);
 
   hDragPiece = PieceBmpArray[Board[start].piece-1][Board[start].color];
   hDragMask = MaskArray[Board[start].piece-1];

   hPrevCursor = SetCursor(0);
   SetClassWord(hWndMain, GCW_HCURSOR, 0);
   ClearSquare(start);
   SaveBackground(p1);
   ShowPiece(p1);
   
   p2 = GetSquareXY(end);
   LineDDA(p1.x, p1.y, p2.x, p2.y, LINEDDAPROC(ReturnHome), NULL);
   UpdateScreen(p2);
   DeleteObject(SelectObject(hSaveDC, hOldBmp));
   DeleteDC(hSaveDC);
   SetCursor(hPrevCursor);
   SetClassWord(hWndMain, GCW_HCURSOR, WORD(hPrevCursor));
}
