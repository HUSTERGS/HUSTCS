// ObjectWindows - (C) Copyright 1992 by Borland International

#ifndef _INFO_H
#define _INFO_H

_CLASSDEF(TInfoWindow)
class TInfoWindow: public TWindow
{
	PTStatic Color;
	PTStatic RedInfo;
	PTStatic BlackInfo;
	PTStatic SearchDepth;
	PTStatic Iteration;
	PTStatic Value;
	PTStatic Nodes;
	PTStatic Seconds;
	PTStatic BestLine;
	PTStatic Message;
   RECT InfoRect;
  public:
   TInfoWindow(PTWindowsObject AParent, LPSTR ATitle);
	void SetTurnText(LPSTR text)
		{
      Color->SetText(text);
		}
	void SetRedInfoText(LPSTR text)
		{
		RedInfo->SetText(text);
		}
	void SetBlackInfoText(LPSTR text)
		{
		BlackInfo->SetText(text);
		}
	void SetSearchDepthText(LPSTR text)
		{
		SearchDepth->SetText(text);
		}
	void SetIterationText(LPSTR text)
		{
		Iteration->SetText(text);
		}
	void SetValueText(LPSTR text)
		{
		Value->SetText(text);
		}
	void SetNodeText(LPSTR text)
		{
		Nodes->SetText(text);
		}
	void SetSecondsText(LPSTR text)
		{
		Seconds->SetText(text);
		}
	void SetBestLineText(LPSTR text)
		{
		BestLine->SetText(text);
		}
	void SetMessageText(LPSTR text)
		{
		Message->SetText(text);
		}
   virtual void Paint( HDC PaintDC, PAINTSTRUCT& PaintInfo );
	void DrawInfoFrame(HDC);
    virtual void WMControlColor(TMessage& Msg)
                                = [WM_FIRST + WM_CTLCOLOR];
   void Reset();
   void IterReset();
};

	




#endif // _INFO_H
