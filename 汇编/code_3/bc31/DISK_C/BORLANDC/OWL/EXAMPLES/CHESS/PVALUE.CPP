// ObjectWindows - (C) Copyright 1992 by Borland International

#include <static.h>
#include <filedial.h>
#include <inputdia.h>
#include <bwcc.h>
#include <string.h>
#include <stdio.h>
#include "wcdefs.h"
#include "info.h"
#include "wchess.h"
#include "pvalue.h"
#include "externs.h"

const int DefaultValues[5] = {0x90, 0x4c, 0x30, 0x30, 0x10};

enum PIECES { pvqueen, pvrook, pvbishop, pvknight, pvpawn};

#define min(x, y)   (((x) < (y)) ? (x) : (y))
#define max(x, y)   (((x) > (y)) ? (x) : (y))


TPieceValueDialog::TPieceValueDialog(PTWindowsObject AParent, LPSTR AName)
   : TDialog(AParent, AName)
   {
   }

inline void TPieceValueDialog::PVSetFocus(HWND hWnd)
{
   SendMessage(HWindow, WM_NEXTDLGCTL, WPARAM(hWnd), 1L);
   SendMessage(hWnd, EM_SETSEL, 0, MAKELONG(0, 32767));
}

BOOL TPieceValueDialog::GetColorValue(WORD Id)
{
   int NewVal;
   BOOL Ok;
   int *CurVal;
   HWND hScroller;

   NewVal = GetDlgItemInt(HWindow, Id, &Ok, TRUE);

   switch (Id)
      {
      case IDD_EQUEEN:
         CurVal = &Values[pvqueen];
         hScroller = GetDlgItem(HWindow, IDD_QUEEN);
         break;
      case IDD_EROOK:
         CurVal = &Values[pvrook];
         hScroller = GetDlgItem(HWindow, IDD_ROOK);
         break;
      case IDD_EBISHOP:
         CurVal = &Values[pvbishop];
         hScroller = GetDlgItem(HWindow, IDD_BISHOP);
         break;
      case IDD_EKNIGHT:
         CurVal = &Values[pvknight];
         hScroller = GetDlgItem(HWindow, IDD_KNIGHT);
         break;
      case IDD_EPAWN:
         CurVal = &Values[pvpawn];
         hScroller = GetDlgItem(HWindow, IDD_PAWN);
         break;
      }

   if (Ok)
      {
      Ok = (NewVal > 255) ? FALSE : ( (NewVal < 0 ) ? FALSE : TRUE );
      }
   else 
      NewVal = *CurVal;
     
   if (!Ok)
      {
      Error("Please enter a valid number between 0 and 255.");
      PVSetFocus(GetDlgItem(HWindow, Id));
      }
   else if (NewVal != *CurVal)
      {
      *CurVal = NewVal;
      SetScrollPos(hScroller, SB_CTL, *CurVal, TRUE);
      }
   return Ok;
}

void TPieceValueDialog::Ok(RTMessage)
{
   MSG msg;

   while (PeekMessage(&msg, HWindow, PV_KILLFOCUS, PV_KILLFOCUS, PM_NOREMOVE))
      continue;

   if ( GetColorValue(IDD_EQUEEN) && GetColorValue(IDD_EROOK) &&
      GetColorValue(IDD_EBISHOP) && GetColorValue(IDD_EKNIGHT) &&
      GetColorValue(IDD_EPAWN) )
      {
      PieceValue[queen] = Values[pvqueen] * 16;
      PieceValue[rook]  = Values[pvrook] * 16;
      PieceValue[bishop] = Values[pvbishop] * 16;
      PieceValue[knight] = Values[pvknight] * 16;
      PieceValue[pawn] = Values[pvpawn] * 16;
      CloseWindow(IDOK);
      }
}

void TPieceValueDialog::SetupWindow()
{
   TDialog::SetupWindow();
   Values[pvqueen] = PieceValue[queen] / 16;
   Values[pvrook] = PieceValue[rook] / 16;
   Values[pvbishop] = PieceValue[bishop] / 16;
   Values[pvknight] = PieceValue[knight] / 16;
   Values[pvpawn] = PieceValue[pawn] / 16;

   SetDlgItemInt(HWindow, IDD_EQUEEN, Values[pvqueen], FALSE);
   SetDlgItemInt(HWindow, IDD_EROOK, Values[pvrook], FALSE);
   SetDlgItemInt(HWindow, IDD_EBISHOP, Values[pvbishop], FALSE);
   SetDlgItemInt(HWindow, IDD_EKNIGHT, Values[pvknight], FALSE);
   SetDlgItemInt(HWindow, IDD_EPAWN, Values[pvpawn], FALSE);

   SetScrollRange(GetDlgItem(HWindow, IDD_QUEEN), SB_CTL, 0, 255, FALSE);
   SetScrollPos(GetDlgItem(HWindow, IDD_QUEEN), SB_CTL, Values[pvqueen], FALSE);

   SetScrollRange(GetDlgItem(HWindow, IDD_ROOK), SB_CTL, 0, 255, FALSE);
   SetScrollPos(GetDlgItem(HWindow, IDD_ROOK), SB_CTL, Values[pvrook], FALSE);

   SetScrollRange(GetDlgItem(HWindow, IDD_BISHOP), SB_CTL, 0, 255, FALSE);
   SetScrollPos(GetDlgItem(HWindow, IDD_BISHOP), SB_CTL, Values[pvbishop], FALSE);

   SetScrollRange(GetDlgItem(HWindow, IDD_KNIGHT), SB_CTL, 0, 255, FALSE);
   SetScrollPos(GetDlgItem(HWindow, IDD_KNIGHT), SB_CTL, Values[pvknight], FALSE);

   SetScrollRange(GetDlgItem(HWindow, IDD_PAWN), SB_CTL, 0, 255, FALSE);
   SetScrollPos(GetDlgItem(HWindow, IDD_PAWN), SB_CTL, Values[pvpawn], FALSE);
}


void TPieceValueDialog::IDDDefault(RTMessage)
{
   memcpy(Values, DefaultValues, 5 * sizeof(int));

   SetDlgItemInt(HWindow, IDD_EQUEEN, Values[pvqueen], FALSE);
   SetDlgItemInt(HWindow, IDD_EROOK, Values[pvrook], FALSE);
   SetDlgItemInt(HWindow, IDD_EBISHOP, Values[pvbishop], FALSE);
   SetDlgItemInt(HWindow, IDD_EKNIGHT, Values[pvknight], FALSE);
   SetDlgItemInt(HWindow, IDD_EPAWN, Values[pvpawn], FALSE);

   SetScrollPos(GetDlgItem(HWindow, IDD_QUEEN), SB_CTL, Values[pvqueen], TRUE);
   SetScrollPos(GetDlgItem(HWindow, IDD_ROOK), SB_CTL, Values[pvrook], TRUE);
   SetScrollPos(GetDlgItem(HWindow, IDD_BISHOP), SB_CTL, Values[pvbishop], TRUE);
   SetScrollPos(GetDlgItem(HWindow, IDD_KNIGHT), SB_CTL, Values[pvknight], TRUE);
   SetScrollPos(GetDlgItem(HWindow, IDD_PAWN), SB_CTL, Values[pvpawn], TRUE);
}

void TPieceValueDialog::WMHScroll(RTMessage msg)
{
   int ID = GetDlgCtrlID(HWND(msg.LP.Hi));
   HWND hScroller;
   int *curvalue;
   int dlgitem;

   if (ID == GetDlgCtrlID(hScroller = GetDlgItem(HWindow, IDD_QUEEN)))
      {
      curvalue = &Values[pvqueen];
      dlgitem = IDD_EQUEEN;
      }
   else if (ID == GetDlgCtrlID(hScroller = GetDlgItem(HWindow, IDD_ROOK)))
      {
      curvalue = &Values[pvrook];
      dlgitem = IDD_EROOK;
      }
   else if (ID == GetDlgCtrlID(hScroller = GetDlgItem(HWindow, IDD_BISHOP)))
      {
      curvalue = &Values[pvbishop];
      dlgitem = IDD_EBISHOP;
      }
   else if (ID == GetDlgCtrlID(hScroller = GetDlgItem(HWindow, IDD_KNIGHT)))
      {
      curvalue = &Values[pvknight];
      dlgitem = IDD_EKNIGHT;
      }
   else if (ID == GetDlgCtrlID(hScroller = GetDlgItem(HWindow, IDD_PAWN)))
      {
      curvalue = &Values[pvpawn];
      dlgitem = IDD_EPAWN;
      }
   else
      return;

   switch (msg.WParam)
      {
      case SB_PAGEDOWN :
         *curvalue += 15;
      case SB_LINEDOWN :
         *curvalue = min(255, *curvalue + 1);
         break;
      case SB_PAGEUP :
         *curvalue -= 15;
      case SB_LINEUP :
         *curvalue = max(0, *curvalue - 1);
         break;
      case SB_TOP:
         *curvalue = 0;
         break;
      case SB_BOTTOM :
         *curvalue = 255;
         break;
      case SB_THUMBPOSITION :
      case SB_THUMBTRACK :
         *curvalue = msg.LP.Lo;
         break;
      default:
         break;
      }
   SetScrollPos(hScroller, SB_CTL, *curvalue, TRUE);
   SetDlgItemInt(HWindow, dlgitem, *curvalue, FALSE);
}

void TPieceValueDialog::PVKillFocus(RTMessage msg)
{
   WORD Id = msg.WParam;
   HWND Focus = GetFocus();

   if ( ( GetDlgItem(HWindow, Id) == Focus || 
      GetDlgItem(HWindow, IDCANCEL) == Focus ||
      GetDlgItem(HWindow, IDD_DEFAULT) == Focus) ||
      GetActiveWindow() != HWindow)
      return;
   GetColorValue(Id);   
}

void TPieceValueDialog::WMCommand(RTMessage msg)
{
   WORD ID = msg.WParam;

   if (msg.LP.Lo)
      {
      switch (msg.LP.Hi)
         {
         case EN_KILLFOCUS:
            if (SendMessage(HWND(msg.LP.Lo), EM_GETMODIFY, 0, 0L))
               PostMessage(HWindow, PV_KILLFOCUS, ID, 0L);
         default:
            TWindowsObject::WMCommand(msg);
            return;
         }
      }
   else
      TWindowsObject::WMCommand(msg);
}
