// ObjectWindows - (C) Copyright 1992 by Borland International

#ifndef __COLORDLG_H
#define __COLORDLG_H

#include <stdio.h>
#include <dos.h>
#include <mem.h>
#include <string.h>
#include <owl.h>
#include <scrollba.h>
#include "colordlg.rch"

_CLASSDEF(TColorControl)
_CLASSDEF(TColorDialog)

class _EXPORT TColorControl : public TControl
{
public:
  COLORREF Color;

  TColorControl(PTWindowsObject AParent, int ResourceId, COLORREF AColor,
    PTModule AModule = NULL);

protected:
  virtual LPSTR GetClassName();
  virtual void GetWindowClass(WNDCLASS _FAR & AWndClass);
  virtual void Paint(HDC, PAINTSTRUCT _FAR & PS);
  virtual WORD Transfer(Pvoid DataPtr, WORD TransferFlag);
  virtual void WMLButtonDown(RTMessage Msg)
    = [WM_FIRST + WM_LBUTTONDOWN];
  virtual void WMLButtonDblClk(RTMessage Msg)
    = [WM_FIRST + WM_LBUTTONDBLCLK];

public:
  virtual void SetColor(COLORREF AColor);
};

class _EXPORT TColorDialog : public TDialog
{
protected:
  PTScrollBar ColorBar1;
  PTScrollBar ColorBar2;
  PTScrollBar ColorBar3;
  PTColorControl SelColor;

public:
  TColorDialog(PTWindowsObject AParent, COLORREF _FAR & TheColor);

protected:
  virtual void DefChildProc(RTMessage Msg);
  virtual void SetupWindow();
  virtual void TransferData(WORD TransferFlag);
  virtual void UpdateBars(COLORREF AColor);
};

#endif

