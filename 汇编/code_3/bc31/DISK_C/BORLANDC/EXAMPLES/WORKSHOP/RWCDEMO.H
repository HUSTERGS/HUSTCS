// (C) Copyright 1991, 1992 by Borland International

#define max(a,b)	(((a) > (b)) ? (a) : (b))
#define min(a,b)    (((a) < (b)) ? (a) : (b))
#include "rwcdemoc.h"
#include "rwcwnd.h"
struct WinApp
{
	static HINSTANCE        hInstance;
	static HINSTANCE        hPrevInst;
	static int              cmdShow;
	static HWND             hWndClient;
	static TMDIChildWindow *currentWindow;
};

LRESULT CALLBACK _export FrameWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
