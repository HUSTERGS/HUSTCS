// ObjectWindows - (C) Copyright 1992 by Borland International

#include "colordlg.h"

const unsigned int CN_CLICKED = 0;
const unsigned int CN_DBLCLICKED = 1;

#ifdef __DLL__
extern PTModule TheModule;
#else
PTModule TheModule = NULL;
#endif


TColorControl::TColorControl(PTWindowsObject AParent, int ResourceId,
  COLORREF AColor, PTModule AModule)
  : TControl(AParent, ResourceId, AModule)
{
  Color = AColor;
  DisableTransfer();
}

LPSTR TColorControl::GetClassName()
{
  return "ColorControl";
}

void TColorControl::GetWindowClass(WNDCLASS& AWndClass)
{
  TControl::GetWindowClass(AWndClass);
  AWndClass.style |= CS_DBLCLKS;
}

void TColorControl::Paint(HDC DC, PAINTSTRUCT& PS)
{
  LOGBRUSH ALogBrush;
  HBRUSH NewBrush;
  HBRUSH OldBrush;

  ALogBrush.lbStyle = BS_SOLID;
  ALogBrush.lbColor = Color;
  NewBrush = CreateBrushIndirect(&ALogBrush);
  OldBrush = (HBRUSH)SelectObject(DC, NewBrush);
  Rectangle(DC, PS.rcPaint.left, PS.rcPaint.top, PS.rcPaint.right,
    PS.rcPaint.bottom);
  SelectObject(DC, OldBrush);
  DeleteObject(NewBrush);
}

void TColorControl::SetColor(COLORREF AColor)
{
  Color = AColor;
  InvalidateRect(HWindow, NULL, TRUE);
}

WORD TColorControl::Transfer(void *DataPtr, WORD TransferFlag)
{
  if ( TransferFlag == TF_GETDATA )
  {
    memcpy(DataPtr, &Color, sizeof Color);
  }
  else
    if ( TransferFlag == TF_SETDATA )
      memcpy(&Color, DataPtr, sizeof Color);
  return sizeof(Color);
}

void TColorControl::WMLButtonDown(RTMessage)
{
  SendMessage(Parent->HWindow, WM_COMMAND, Attr.Id,
    MAKELONG(HWindow, CN_CLICKED));
}

void TColorControl::WMLButtonDblClk(RTMessage)
{
  SendMessage(Parent->HWindow, WM_COMMAND, Attr.Id,
    MAKELONG(HWindow, CN_DBLCLICKED));
}

static void DisableChildTransfer(void *P, void *)
{
  ((PTWindowsObject)P)->DisableTransfer();
}

TColorDialog::TColorDialog(TWindowsObject *AParent, COLORREF& TheColor)
             : TDialog(AParent, "COLORDIALOG", TheModule)
{
  new TColorControl(this, ID_COLOR1, RGB(0x00, 0x00, 0x00), TheModule);
  new TColorControl(this, ID_COLOR2, RGB(0xFF, 0xFF, 0xFF), TheModule);
  new TColorControl(this, ID_COLOR3, RGB(0xFF, 0x00, 0x00), TheModule);
  new TColorControl(this, ID_COLOR4, RGB(0x00, 0xFF, 0x00), TheModule);
  new TColorControl(this, ID_COLOR5, RGB(0x00, 0x00, 0xFF), TheModule);
  new TColorControl(this, ID_COLOR6, RGB(0x00, 0xFF, 0xFF), TheModule);
  new TColorControl(this, ID_COLOR7, RGB(0xFF, 0x00, 0xFF), TheModule);
  new TColorControl(this, ID_COLOR8, RGB(0xFF, 0xFF, 0x00), TheModule);
  ColorBar1 = new TScrollBar(this, ID_COLORBAR1, TheModule);
  ColorBar2 = new TScrollBar(this, ID_COLORBAR2, TheModule);
  ColorBar3 = new TScrollBar(this, ID_COLORBAR3, TheModule);
  ForEach(DisableChildTransfer, 0);
  SelColor = new TColorControl(this, ID_SELCOLOR, TheColor, TheModule);
  SelColor->EnableTransfer();
  TransferBuffer = &TheColor;
}

void TColorDialog::DefChildProc(RTMessage Msg)
{
  TColorControl *TheControl;

  if ( Msg.WParam <= ID_COLORBAR3 )
  {
    SelColor->SetColor(RGB((unsigned int)ColorBar1->GetPosition(),
    (unsigned int)ColorBar2->GetPosition(),
    (unsigned int)ColorBar3->GetPosition()));
  }
  else
  {
    TheControl = (TColorControl *)ChildWithId(Msg.WParam);
    SelColor->SetColor(TheControl->Color);
    UpdateBars(TheControl->Color);
    if (Msg.LP.Hi == CN_DBLCLICKED)
    {
      CloseWindow(IDOK);
    }
  }
}

void TColorDialog::SetupWindow()
{
  TDialog::SetupWindow();
  ColorBar1->SetRange(0, 255);
  ColorBar2->SetRange(0, 255);
  ColorBar3->SetRange(0, 255);
}

void TColorDialog::TransferData(WORD TransferFlag)
{
  TDialog::TransferData(TransferFlag);
  if ( TransferFlag == TF_SETDATA )
  {
    UpdateBars(SelColor->Color);
  }
}

void TColorDialog::UpdateBars(COLORREF AColor)
{
  ColorBar1->SetPosition(GetRValue(AColor));
  ColorBar2->SetPosition(GetGValue(AColor));
  ColorBar3->SetPosition(GetBValue(AColor));
}

