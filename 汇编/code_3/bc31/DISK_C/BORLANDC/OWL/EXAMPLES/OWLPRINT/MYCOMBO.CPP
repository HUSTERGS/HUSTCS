// ObjectWindows - (C) Copyright 1992 by Borland International

/* -------------------------------------------------------
  MYCOMBO.CPP
  Defines type TMyComboBox.  This is a replacement for TComboBox which
  differs solely in that it uses a TNSCollection as part of its
  transferbuffer instead of an Array.
  Note that if you actually intend to stream this class, you will
  need to define the build, read, write, etc. needed, since this
  will class will otherwise use those inherited from TComboBox.
  -------------------------------------------------------- */

#include <owl.h>

#include "mycombo.h"

/* Constructor for a TMyComboBoxData object. Initializes Strings and
   Selection. */
TMyComboBoxData::TMyComboBoxData()
{
  Strings = new TNSCollection(5, 5);
  Selection = NULL;
}

/* Destructor for TMyComboBoxData. Deletes Strings and Selection. */
TMyComboBoxData::~TMyComboBoxData()
{
  if ( Strings )
    delete Strings;
  if ( Selection )
    delete Selection;
}

/* Adds the supplied string to the Strings Array and copies it into
   Selection if IsSelected is TRUE. */
void TMyComboBoxData::AddString(Pchar AString, BOOL IsSelected)
{
  Strings->insert(strdup(AString));
  if ( IsSelected )
  {
      if (AString != Selection)
      {
          if (Selection)
              delete Selection;
          Selection = strdup(AString);
      }
  }
}

static void DoAddForCB(Pvoid AString, Pvoid AComboBox)
{
  if (AString)
     ((PTMyComboBox)AComboBox)->AddString((Pchar)AString);
}

/* Transfers the items and selection of the combo box to or from a
   transfer buffer if TF_SETDATA or TF_GETDATA, repectively, is passed
   as the TransferFlag. DataPtr should point to a PTMyComboBoxData
   (i.e. it should be a pointer to a pointer to a TMyComboBoxData)
   which points to the data to be transferred.
   Transfer returns the size of PTMyComboBox (the pointer not the
   object). To retrieve the size without transferring data, pass
   TF_SIZEDATA as the TransferFlag. */
WORD TMyComboBox::Transfer(Pvoid DataPtr, WORD TransferFlag)
{
  PTMyComboBoxData ComboBoxData = *(PTMyComboBoxData _FAR *)DataPtr;

  if ( TransferFlag == TF_GETDATA )
  {
    int StringSize = GetWindowTextLength(HWindow) + 1;
    if (!StringSize)
        StringSize = 80;
    if ( ComboBoxData->Selection )
      delete ComboBoxData->Selection;
    ComboBoxData->Selection= new char[StringSize];
    GetWindowText(HWindow, ComboBoxData->Selection, StringSize);
  }
  else
    if ( TransferFlag == TF_SETDATA )
    {
      ClearList();
      ComboBoxData->Strings->forEach(DoAddForCB, this);

      int SelIndex = FindExactString(ComboBoxData->Selection, -1);
      if ( SelIndex > -1 )
          SetSelIndex(SelIndex);

      SetWindowText(HWindow, ComboBoxData->Selection);
    }
  return sizeof(PTMyComboBoxData);
}

