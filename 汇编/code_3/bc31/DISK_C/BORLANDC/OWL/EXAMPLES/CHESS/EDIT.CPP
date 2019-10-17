// ObjectWindows - (C) Copyright 1992 by Borland International

#include <windows.h>
#include <owl.h>
#include "wcdefs.h"
#include "edit.h"
#include "externs.h"


TEditBarWindow::TEditBarWindow(PTWindowsObject AParent, LPSTR ATitle) :
	TWindow(AParent, ATitle)
{
	Attr.Style = WS_CHILD;
	Attr.X = (3 * BORDERSIZE) + (MAXBDSIZE * SQUARE_SIZE) + (2 * MYFRAMESIZE);
	Attr.Y = BORDERSIZE;
   EditBarRect.right = Attr.W = (SQUARE_SIZE*2) + 6;
   EditBarRect.bottom = Attr.H = (SQUARE_SIZE * 6) + 6;
   EditBarRect.left = EditBarRect.top = 0;
   SelectedItem = 0;
}


void TEditBarWindow::Paint(HDC hDC, PAINTSTRUCT&)
{
   int i;
   BITMAP Bitmap;
   HBITMAP hBitmap, hOldBmp, hMaskBmp;
   HDC hMemoryDC = CreateCompatibleDC(hDC);

   DrawFrame(hDC, EditBarRect, TRUE);
    
   GetObject(PieceBmpArray[0][white], sizeof(BITMAP), (LPSTR)&Bitmap);

   for (i = 0; i < 6; i++)
      {
      hBitmap = PieceBmpArray[i][white];
      hMaskBmp = MaskArray[i];
      hOldBmp = (HBITMAP)SelectObject(hMemoryDC, hMaskBmp);      
      BitBlt(hDC, 3, 3 + (SQUARE_SIZE * i), Bitmap.bmWidth, Bitmap.bmHeight,
         hMemoryDC, 0, 0, SRCAND);
      SelectObject(hMemoryDC, hBitmap);      
      BitBlt(hDC, 3, 3 + (SQUARE_SIZE * i), Bitmap.bmWidth, Bitmap.bmHeight,
         hMemoryDC, 0, 0, (SelectedItem == i)
         ? NOTSRCERASE : SRCINVERT);
      SelectObject(hMemoryDC, hOldBmp);
      }


   for (i = 0; i < 6; i++)
      {
      hBitmap = PieceBmpArray[i][black];
      hMaskBmp = MaskArray[i];
      hOldBmp = (HBITMAP)SelectObject(hMemoryDC, hMaskBmp);      
      BitBlt(hDC, 3 + SQUARE_SIZE, 3 + (SQUARE_SIZE * i), Bitmap.bmWidth, Bitmap.bmHeight,
         hMemoryDC, 0, 0, SRCAND);
      SelectObject(hMemoryDC, hBitmap);      
      BitBlt(hDC, 3+SQUARE_SIZE, 3 + (SQUARE_SIZE * i), Bitmap.bmWidth, Bitmap.bmHeight,
         hMemoryDC, 0, 0, (SelectedItem == (i + 6))
         ? NOTSRCERASE : SRCINVERT);
      SelectObject(hMemoryDC, hOldBmp);
      }
   DeleteDC(hMemoryDC);
}


void TEditBarWindow::WMLButtonUp(TMessage&)
{
   POINT Point;
   int i, j, temp;
   RECT Rect;
   BITMAP Bitmap;
   HBITMAP hBitmap, hOldBmp, hMaskBmp;
   HDC hDC = GetDC(HWindow);
   HDC hMemoryDC = CreateCompatibleDC(hDC);

   int PreviousItem = SelectedItem;

   GetCursorPos( &Point );
   ScreenToClient(HWindow, &Point);

   for (i = 0; i < 6; i++)
      for (j = 0; j < 2; j++)
         {
            Rect.left = (j * SQUARE_SIZE) + 3;
            Rect.right = Rect.left + SQUARE_SIZE;
            Rect.top = (i * SQUARE_SIZE) + 3;
            Rect.bottom = Rect.top + SQUARE_SIZE;
            if (PtInRect(&Rect, Point))
               SelectedItem = (i + ((j) ? 6 : 0));
         }
   if (SelectedItem == PreviousItem)
      return;


   GetObject(PieceBmpArray[0][white], sizeof(BITMAP), (LPSTR)&Bitmap);

   temp = PreviousItem % 6;

   hBitmap = PieceBmpArray[temp][(PreviousItem < 6) ? white : black];
   hMaskBmp = MaskArray[temp];
   hOldBmp = (HBITMAP)SelectObject(hMemoryDC, hMaskBmp);      
   BitBlt(hDC, (PreviousItem < 6) ? 3 : 3 + SQUARE_SIZE,
      3 + (SQUARE_SIZE * temp), Bitmap.bmWidth, Bitmap.bmHeight,
      hMemoryDC, 0, 0, SRCERASE);
   SelectObject(hMemoryDC, hBitmap);      
   BitBlt(hDC, (PreviousItem < 6) ? 3 : 3 + SQUARE_SIZE,
      3 + (SQUARE_SIZE * temp), Bitmap.bmWidth, Bitmap.bmHeight,
      hMemoryDC, 0, 0, SRCINVERT);
   SelectObject(hMemoryDC, hOldBmp);

   temp = SelectedItem % 6;

   hBitmap = PieceBmpArray[temp][(SelectedItem < 6) ? white : black];
   hMaskBmp = MaskArray[temp];
   hOldBmp = (HBITMAP)SelectObject(hMemoryDC, hMaskBmp);      
   BitBlt(hDC, (SelectedItem < 6) ? 3 : 3 + SQUARE_SIZE,
      3 + (SQUARE_SIZE * temp), Bitmap.bmWidth, Bitmap.bmHeight,
      hMemoryDC, 0, 0, SRCAND);
   SelectObject(hMemoryDC, hBitmap);      
   BitBlt(hDC, (SelectedItem < 6) ? 3 : 3 + SQUARE_SIZE,
      3 + (SQUARE_SIZE * temp), Bitmap.bmWidth, Bitmap.bmHeight,
      hMemoryDC, 0, 0, NOTSRCERASE);
   SelectObject(hMemoryDC, hOldBmp);
   DeleteDC(hMemoryDC);
   ReleaseDC(HWindow, hDC);
}
