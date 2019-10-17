// ObjectWindows - (C) Copyright 1992 by Borland International

#include <owl.h>
#include <static.h>
#include "checkers.h"
#include "info.h"
#include "board.h"

extern short LINESIZE;
extern short CHARSIZE;
extern int CAPTIONY;
extern int BORDERSIZE;
const BORDERYEXTRA = 4; // 4 for spacing
const MYFRAMESIZE = 3;
extern short INFOXSIZE, INFOYSIZE;

short LEFTMARGIN = 6;
short SEPERATOR = 4;

#define MAXLINE  (INFOXSIZE - LEFTMARGIN)

#define COLORX  (LEFTMARGIN + CHARSIZE * 6)
#define COLORY  (SEPERATOR + 2)
#define COLORW  (CHARSIZE * 6)
#define REDINFOX  (LEFTMARGIN + CHARSIZE * 7)
#define REDINFOY  (COLORY + LINESIZE + SEPERATOR * 2)
#define REDINFOW  (MAXLINE - REDINFOX)
#define BLACKINFOX  (REDINFOX)
#define BLACKINFOY  (REDINFOY + LINESIZE + SEPERATOR)
#define BLACKINFOW  (REDINFOW)
#define SEARCHX  (LEFTMARGIN + CHARSIZE * 14)
#define SEARCHY  (BLACKINFOY + LINESIZE + SEPERATOR * 2)
#define SEARCHW  (MAXLINE - SEARCHX)
#define ITERX  (LEFTMARGIN + CHARSIZE * 12)
#define ITERY  (SEARCHY + LINESIZE + SEPERATOR)
#define ITERW  (MAXLINE - ITERX)
#define VALUEX  (LEFTMARGIN + CHARSIZE * 7)
#define VALUEY  (ITERY + LINESIZE + SEPERATOR)
#define VALUEW  (MAXLINE - VALUEX)
#define NODEX  (LEFTMARGIN + CHARSIZE * 9)
#define NODEY  (VALUEY + LINESIZE + SEPERATOR)
#define NODEW  (MAXLINE - NODEX)
#define SECX   (LEFTMARGIN + CHARSIZE * 11)
#define SECY  (NODEY + LINESIZE + SEPERATOR)
#define SECW  (MAXLINE - SECX)
#define STATBESTY  (SECY + LINESIZE + SEPERATOR * 2)
#define BESTX  (LEFTMARGIN)
#define BESTY  (STATBESTY + LINESIZE + SEPERATOR)
#define BESTW  (MAXLINE - LEFTMARGIN)
#define BESTH  (LINESIZE * 3 + SEPERATOR * 3 - 9)
#define MESSX  (LEFTMARGIN)
#define MESSY  (BESTY + BESTH + SEPERATOR * 2)
#define MESSW  (MAXLINE - MESSX)


#define EmptyStr  ""


TInfoWindow::TInfoWindow(PTWindowsObject AParent, LPSTR ATitle) :
	TWindow(AParent, ATitle)
{
   short temp;

	Attr.Style |= WS_CHILD | WS_VISIBLE;
	Attr.X = (3 * BORDERSIZE) + (MAXBDSIZE * SQUARE_SIZE) + (2 * MYFRAMESIZE);
	Attr.Y = BORDERSIZE - MYFRAMESIZE;
   LEFTMARGIN= MYFRAMESIZE + CHARSIZE/2;
   SEPERATOR = LINESIZE/4;
   INFOXSIZE = (28 * CHARSIZE) + (2 * LEFTMARGIN);
   INFOYSIZE = MESSY + LINESIZE + SEPERATOR + (MYFRAMESIZE*2);
   temp = MAXBDSIZE * SQUARE_SIZE + (2 * MYFRAMESIZE);
   INFOYSIZE = (temp > INFOYSIZE) ? temp : INFOYSIZE;
	InfoRect.right = Attr.W = INFOXSIZE;
	InfoRect.bottom = Attr.H = INFOYSIZE;
	InfoRect.left = InfoRect.top =  0;
	new TStatic(this, -1, "Turn:", LEFTMARGIN, COLORY,
		CHARSIZE * 6, LINESIZE, 5);
	new TStatic(this, -1, "Red:", LEFTMARGIN, REDINFOY,
		CHARSIZE * 5, LINESIZE, 4);
	new TStatic(this, -1, "Black:", LEFTMARGIN, BLACKINFOY,
		CHARSIZE * 7, LINESIZE, 6);
	new TStatic(this, -1, "Searchdepth:", LEFTMARGIN, SEARCHY,
		CHARSIZE * 13, LINESIZE, 12);
	new TStatic(this, -1, "Iteration:", LEFTMARGIN, ITERY,
		CHARSIZE * 11, LINESIZE, 10);
	new TStatic(this, -1, "Value:", LEFTMARGIN, VALUEY,
		CHARSIZE * 7, LINESIZE, 6);
	new TStatic(this, -1, "Nodes:", LEFTMARGIN, NODEY,
		CHARSIZE * 7, LINESIZE, 7);
	new TStatic(this, -1, "Seconds:", LEFTMARGIN, SECY,
		CHARSIZE * 9, LINESIZE, 9);
	new TStatic(this, -1, "Bestline:", LEFTMARGIN, STATBESTY,
		CHARSIZE * 9, LINESIZE, 9);
	Color = new TStatic(this, -1, EmptyStr, COLORX, COLORY,
		COLORW, LINESIZE, 6);
	RedInfo = new TStatic(this, -1, EmptyStr, REDINFOX, REDINFOY,
		REDINFOW, LINESIZE, REDINFOW/CHARSIZE);
	BlackInfo = new TStatic(this, -1, EmptyStr, BLACKINFOX, BLACKINFOY,
		BLACKINFOW, LINESIZE, BLACKINFOW / CHARSIZE);
	SearchDepth = new TStatic(this, -1, EmptyStr, SEARCHX, SEARCHY,
		SEARCHW, LINESIZE, SEARCHW / CHARSIZE);
	Iteration = new TStatic(this, -1, EmptyStr, ITERX, ITERY,
		ITERW, LINESIZE, ITERW/CHARSIZE);
	Value = new TStatic(this, -1, EmptyStr, VALUEX, VALUEY,
		VALUEW, LINESIZE, VALUEW / CHARSIZE);
	Nodes = new TStatic(this, -1, EmptyStr, NODEX, NODEY,
		NODEW, LINESIZE, NODEW / CHARSIZE);
	Seconds = new TStatic(this, -1, EmptyStr, SECX, SECY,
		SECW, LINESIZE, SECW / CHARSIZE);
	BestLine = new TStatic(this, -1, EmptyStr, BESTX, BESTY,
		BESTW, BESTH, ((BESTW / CHARSIZE) * 3));
	Message = new TStatic(this, -1, EmptyStr, MESSX, MESSY,
		MESSW, LINESIZE, MESSW / CHARSIZE);
}


void TInfoWindow::Paint( HDC PaintDC, PAINTSTRUCT& )
{
	DrawInfoFrame(PaintDC);
}

void TInfoWindow::DrawInfoFrame(HDC hDC)
{

   DrawFrame(hDC, InfoRect);
}

void TInfoWindow::WMControlColor(TMessage& Msg)
{
	SetBkColor((HDC)Msg.WParam, RGB(192, 192, 192));
	Msg.Result = (LRESULT)GetStockObject(LTGRAY_BRUSH);
}

void TInfoWindow::Reset()
{
   Color->SetText("Red");
   RedInfo->Clear();
   BlackInfo->Clear();
   SearchDepth->Clear();
   Iteration->Clear();
   Value->Clear();
   Nodes->Clear();
   Seconds->Clear();
   BestLine->Clear();
   Message->Clear();
}

void TInfoWindow::IterReset()
{
   Color->SetText("Red");
   Iteration->Clear();
   Value->Clear();
   Nodes->Clear();
   Seconds->Clear();
   BestLine->Clear();
}





