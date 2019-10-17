// ObjectWindows - (C) Copyright 1992 by Borland International

// Font demo window header

#ifndef __FONTWINDOW_H
#define __FONTWINDOW_H

#include "demobase.h"

/* Font demo constants */
const int MaxNumFonts = 20; /* Maximum number of fonts to be displayed in FontDemo */

_CLASSDEF(TFontWindow)

class TFontWindow : public TBaseDemoWindow
{
private:
         long FontsHeight, FontsWidth;
public:
         TFontWindow( PTWindowsObject AParent, LPSTR ATitle );
         virtual void Paint(HDC PaintDC, PAINTSTRUCT& PaintInfo);
         virtual void Destroy();
         virtual void WMSize( TMessage& Message ) = [ WM_FIRST + WM_SIZE ];
};

#endif  // ifndef __FONTWINDOW_H
