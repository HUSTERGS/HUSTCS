// ObjectWindows - (C) Copyright 1992 by Borland International

#ifndef __MYCOMBOBOX_H
#define __MYCOMBOBOX_H

#ifndef __COMBOBOX_H
#include <combobox.h>
#endif

#pragma option -Vo-

_CLASSDEF(TMyComboBox)
_CLASSDEF(TMyComboBoxData)

/* --------------------------------------------------------
  TMyComboBox
  -------------------------------------------------------- */

class _EXPORT TMyComboBox : public TComboBox
{
public:
    TMyComboBox(PTWindowsObject AParent, int AnId, int X, int Y, int W,
	      int H, DWORD AStyle, WORD ATextLen, PTModule AModule = NULL)
	      : TComboBox(AParent, AnId, X, Y, W, H, AStyle, ATextLen,
		AModule) {}
    TMyComboBox(PTWindowsObject AParent, int ResourceId, WORD ATextLen,
	      PTModule AModule = NULL)
	      : TComboBox(AParent, ResourceId, ATextLen, AModule) {}

    virtual WORD Transfer(Pvoid DataPtr, WORD TransferFlag);
};

class _EXPORT TMyComboBoxData
{
public:
    PTNSCollection Strings;
    Pchar Selection;

    TMyComboBoxData();
    ~TMyComboBoxData();
    void AddString(Pchar AString, BOOL IsSelected = FALSE);
};

#pragma option -Vo.

#endif
