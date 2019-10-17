// ObjectWindows - (C) Copyright 1992 by Borland International

// Base window classes for the GDI demo windows

#ifndef __DEMOBASE_H
#define __DEMOBASE_H

#include <owl.h>

#define max(a,b)    (((a) > (b)) ? (a) : (b))
#define min(a,b)    (((a) < (b)) ? (a) : (b))

/* TBaseDemoWindow -------------------------------------------------- */

_CLASSDEF(TBaseDemoWindow)

class TBaseDemoWindow : public TWindow  {
public:
        TBaseDemoWindow( PTWindowsObject AParent, LPSTR ATitle)
           : TWindow(AParent, ATitle) {};
        virtual void TimerTick() {};
};


/* TBaseDemoWindow.TimerTick is a trivial method that gets called
  whenever application receives a WM_Timer.  Descendants will override
  this procedure if they need timer messages.*/



#endif // ifndef __DEMOBASE_H
