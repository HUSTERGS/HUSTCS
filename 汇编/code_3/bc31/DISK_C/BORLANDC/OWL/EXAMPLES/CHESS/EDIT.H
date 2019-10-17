// ObjectWindows - (C) Copyright 1992 by Borland International

#ifndef _EDITBAR_H
#define _EDITBAR_H


_CLASSDEF(TEditBarWindow)

class TEditBarWindow: public TWindow
{
   int SelectedItem;
   RECT EditBarRect;
  public:
   TEditBarWindow(PTWindowsObject AParent, LPSTR ATitle);
   virtual void Paint(HDC, PAINTSTRUCT&);
   virtual void WMLButtonUp(TMessage&) = [WM_FIRST + WM_LBUTTONUP];
   virtual void GetWindowClass(WNDCLASS& WndClass)
   {
      TWindow::GetWindowClass(WndClass);
      WndClass.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
   }
   int GetSelectedItem()
   {
      return SelectedItem;
   }
};


#endif // _EDITBAR_H
