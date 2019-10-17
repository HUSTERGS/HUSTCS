// ObjectWindows - (C) Copyright 1992 by Borland International

#ifndef __HELPWIND_H
#define __HELPWIND_H

#ifndef __OWL_H
#include <owl.h>
#endif

#ifndef __LISTBOX_H
#include <listbox.h>
#endif

#ifndef __EDIT_H
#include <edit.h>
#endif

#define ID_LISTBOX  101
#define ID_BUTTON1  102
#define ID_BUTTON2  103
#define ID_EDIT     104

_CLASSDEF(THelpWindow)
class _EXPORT THelpWindow : public TWindow
{
public:
  PTListBox ListBox;
  PTEdit Edit;
  THelpWindow(PTWindowsObject AParent);
  virtual void SetupWindow();
  virtual void HandleListBoxMsg(RTMessage Msg) =
    [ID_FIRST + ID_LISTBOX];
  virtual void HandleButton1Msg(RTMessage Msg) =
    [ID_FIRST + ID_BUTTON1];
  virtual void HandleButton2Msg(RTMessage Msg) =
    [ID_FIRST + ID_BUTTON2];
  virtual void FillEdit(Pchar SelString);
};

#endif
