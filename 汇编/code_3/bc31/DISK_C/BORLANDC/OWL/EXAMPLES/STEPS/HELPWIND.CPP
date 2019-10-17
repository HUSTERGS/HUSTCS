// ObjectWindows - (C) Copyright 1992 by Borland International

#include <stdlib.h>
#include <stdio.h>
#include <dos.h>
#include <string.h>
#include <owl.h>
#include <static.h>
#include <edit.h>
#include <listbox.h>
#include <button.h>
#include "helpwind.h"

THelpWindow::THelpWindow(PTWindowsObject AParent) :
   TWindow(AParent, "Help System")
{
  DisableAutoCreate();
  Attr.Style |= WS_POPUPWINDOW | WS_CAPTION;
  Attr.X = 100;
  Attr.Y = 100;
  Attr.W = 300;
  Attr.H = 300;
  ListBox = new TListBox(this, ID_LISTBOX, 20, 20, 180, 80);
  new TButton(this, ID_BUTTON1, "Help", 220, 20, 60, 30, TRUE);
  new TButton(this, ID_BUTTON2, "Cancel", 220, 70, 60, 30, FALSE);
  Edit = new TEdit(this, ID_EDIT, "", 20, 180, 260, 90, 40, TRUE);
  new TStatic(this, -1, "Help Information:", 20, 160, 160, 20, 0);
}

void THelpWindow::SetupWindow()
{
  TWindow::SetupWindow();
  ListBox->AddString("List Boxes");
  ListBox->AddString("Buttons");
  ListBox->AddString("Check Boxes");
  ListBox->AddString("Radio Buttons");
  ListBox->AddString("Group Boxes");
  ListBox->AddString("Scroll Bars");
  ListBox->AddString("Edit Controls");
  ListBox->AddString("Static Controls");
  ListBox->AddString("Combo Boxes");
  ListBox->SetSelIndex(0);
};

void THelpWindow::HandleListBoxMsg(RTMessage Msg)
{
  char SelString[25];

  if ( Msg.LP.Hi == LBN_DBLCLK )
  {
    ListBox->GetSelString(SelString, sizeof(SelString));
    FillEdit(SelString);
  }
}

void THelpWindow::HandleButton1Msg(RTMessage)
{
  char SelString[25];

  ListBox->GetSelString(SelString, sizeof(SelString));
  FillEdit(SelString);
}

void THelpWindow::HandleButton2Msg(RTMessage)
{
  CloseWindow();
}

void THelpWindow::FillEdit(Pchar SelString)
{
  Pchar HelpStr;

  if ( strcmp(SelString, "Buttons") == 0 )
  {  HelpStr =
       "Button controls are used to allow\r\n"
       "the user to enter a command.  The\r\n"
       "user \"presses\" a button by clicking\r\n"
       "upon it with the mouse.  Button\r\n"
       "controls display a text string which\r\n"
       "indicates the action performed when\r\n"
       "the button is pressed.";
  };
  if ( strcmp(SelString, "Check Boxes") == 0 )
  {  HelpStr =
       "Check boxes are used to represent\r\n"
       "an option which may be selected by\r\n"
       "the user.  The user clicks upon the\r\n"
       "check box to toggle its check state.\r\n"
       "Check boxes are often displayed\r\n"
       "within a group box.  Normally, any\r\n"
       "number of check boxes in a group\r\n"
       "may be selected, simultaneously.";
  }
  if ( strcmp(SelString, "Radio Buttons") == 0 )
  {  HelpStr =
       "Radio Buttons are used to represent\r\n"
       "an option which may be selected by\r\n"
       "the user, by clicking upon it.  Radio\r\n"
       "buttons are usually displayed within\r\n"
       "a group box, and normally are\r\n"
       "mutually exclusive options.";
  };
  if ( strcmp(SelString, "Group Boxes") == 0 )
  {  HelpStr =
       "Group boxes are rectangular\r\n"
       "controls normally used to group\r\n"
       "check boxes and radio buttons.  See\r\n"
       "\"Check Boxes\" and \"Radio Button\"\r\n"
       "HELP information.";
  };
  if ( strcmp(SelString, "List Boxes") == 0 )
  {  HelpStr =
       "List boxes are used to retrieve user\r\n"
       "input in the form of a selection of a\r\n"
       "text item from a list.  The user\r\n"
       "selects an item in the list by single-\r\n"
       "or double- clicking upon it.";
  };
  if ( strcmp(SelString, "Scroll Bars") == 0 )
  {  HelpStr =
       "Scroll bar controls are used to\r\n"
       "retrieve a value in a particular\r\n"
       "range.  The user inputs a value by\r\n"
       "moving a sliding box (a \"thumb\")\r\n"
       "along the scroll bar.  The position\r\n"
       "of the box represents the input\r\n"
       "value.";
  };
  if (strcmp(SelString, "Edit Controls") == 0 )
  {  HelpStr =
       "This is an edit control.  An edit\r\n"
       "control is used to retrieve text\r\n"
       "input from a user.  The user can\r\n"
       "enter and modify text in the edit\r\n"
       "control using the mouse and the\r\n"
       "keyboard.  An edit control often\r\n"
       "contains default text input when\r\n"
       "initially displayed.";
  };
  if ( strcmp(SelString, "Static Controls") == 0 )
  {  HelpStr =
       "Static controls are simple text items\r\n"
       "that are displayed in a window.\r\n"
       "Unlike most other types of controls,\r\n"
       "static controls cannot be modified\r\n"
       "by the user. They are often used in\r\n"
       "combination with other controls to\r\n"
       "display information to guide user\r\n"
       "input.";
  };
  if ( strcmp(SelString, "Combo Boxes") == 0 )
  {  HelpStr =
       "Combo boxes provide the function-\r\n"
       "ality of both list boxes and edit\r\n"
       "controls. They are used to retrieve\r\n"
       "user input in the form of either a\r\n"
       "selection of a text item from a list\r\n"
       "or as text input into the edit control.\r\n"
       "The user has the option of selecting\r\n"
       "a listed item or typing in an item not\r\n"
       "listed.";
  };
  Edit->SetText(HelpStr);
}



