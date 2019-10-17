// ObjectWindows - (C) Copyright 1992 by Borland International

// BitBlt demo window header

#include "demobase.h"

/* BitBlt demo constants */
const int BackgroundID      = 100; /* Bitmap ID of background bitmap */
const int ShipID             = 101; /* Bitmap ID of Ship Bitmap */
const int MonoShipID         = 102; /* Bitmap ID of Monochrome mask of ship */
const int BitmapSize         = 72;  /* Size of Ship bitmap */


_CLASSDEF(TBitBltWindow)

class TBitBltWindow : public TBaseDemoWindow
{
public:
         TBitBltWindow( PTWindowsObject AParent, LPSTR ATitle);
         virtual ~TBitBltWindow();
         virtual LPSTR GetClassName() { return "BitBltWindow"; };
         virtual void GetWindowClass( WNDCLASS& WndClass );
         virtual void WMSize( TMessage& Message ) = [WM_FIRST + WM_SIZE];
         virtual void WMPaint( TMessage& Message ) = [WM_FIRST + WM_PAINT];
         virtual void Paint( HDC PaintDC, PAINTSTRUCT& PaintInfo );
         virtual void SetupWindow();
         virtual void TimerTick();
private:
         POINT WindowSize;
         HBITMAP ScratchBitmap,
                 StretchedBkgnd,
                 Background,
                 MonoShip,
                 Ship;
         int OldX, OldY, Delta, X, Y;
         int CurClick;
         void CalculateNewXY();
};
