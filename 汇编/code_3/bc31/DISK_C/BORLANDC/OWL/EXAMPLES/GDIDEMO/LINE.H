// ObjectWindows - (C) Copyright 1992 by Borland International

// MoveToLineTo demo window header

#ifndef __LINE_H
#define __LINE_H

#include "demobase.h"

/* MoveToLineTo demo constants */
const int  MaxPoints    = 15; /* Number of points to be drawn in MoveToLineToDemo */
const int  IconicPoints = 6; /* Number of points to draw when iconized */

struct TRPoint {
  float X, Y;
};

_CLASSDEF(TMoveToLineToWindow)

class TMoveToLineToWindow : public TBaseDemoWindow
{
public:
         TMoveToLineToWindow(PTWindowsObject AParent, LPSTR ATitle);
         virtual LPSTR GetClassName() { return "LineDemoWindow"; };
         virtual void GetWindowClass( WNDCLASS& WndClass );
         virtual void Paint( HDC PaintDC, PAINTSTRUCT& PaintInfo );
         virtual void TimerTick();
         virtual void WMSize( TMessage &Message ) = [WM_FIRST + WM_SIZE];
private:
         TRPoint Points[ MaxPoints ];
         float Rotation;     // in radians
         int PointCount;
         BOOL Iconized;
         void RotatePoints();
         void DrawPoints(HDC);
};

#endif // ifndef __LINE_H
