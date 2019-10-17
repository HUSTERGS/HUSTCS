// ObjectWindows - (C) Copyright 1992 by Borland International

// Arty demo window object header

#ifndef __ARTY_H
#define __ARTY_H

#include <owl.h>
#include <static.h>
#include "demobase.h"
#include "artypriv.h"  // defines classes used internally by Arty, such as PTList

_CLASSDEF(TArtyWindow)

class TArtyWindow : public TBaseDemoWindow
{
private:
         PTList List,
                BigLineList,
                IconicLineList;
         int  TextHeight;
         BOOL Iconized;
         BOOL Paused;
         PTStatic StaticControl;
public:
         TArtyWindow( PTWindowsObject AParent, LPSTR ATitle );
         virtual ~TArtyWindow();
         virtual LPSTR GetClassName() { return "ArtyWindow"; };
         virtual void GetWindowClass( WNDCLASS& WndClass );
         virtual void Paint( HDC, PAINTSTRUCT& );
         virtual void WMLButtonDown( TMessage& ) = [WM_FIRST + WM_LBUTTONDOWN];
         virtual void WMRButtonDown( TMessage& ) = [WM_FIRST + WM_RBUTTONDOWN];
         virtual void WMSize( TMessage& ) = [WM_FIRST + WM_SIZE];
         virtual void TimerTick();
};

#endif  // ifndef __ARTY_H
