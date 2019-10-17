// ObjectWindows - (C) Copyright 1992 by Borland International

#ifndef __PVALUE_H
#define __PVALUE_H

#define PV_KILLFOCUS     (WM_USER + 100)

_CLASSDEF(TPieceValueDialog)

class TPieceValueDialog : public TDialog
{
      int Values[5];
      void PVSetFocus(HWND);
      BOOL GetColorValue(WORD);
   public:
      TPieceValueDialog(PTWindowsObject AParent, LPSTR AName);
      virtual void SetupWindow();
      virtual void PVKillFocus(RTMessage) = [WM_FIRST + PV_KILLFOCUS];
      virtual void Ok(RTMessage);
      virtual void WMHScroll(RTMessage);
      virtual void WMCommand(RTMessage);
      virtual void IDDDefault(RTMessage) = [ID_FIRST + IDD_DEFAULT];
};

#endif // __PVALUE_H
