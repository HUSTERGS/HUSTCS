// ObjectWindows - (C) Copyright 1992 by Borland International

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include "cdlgdll.h"
#include "usecdll.h"

LRESULT FAR PASCAL _export WndProc (HWND, UINT, WPARAM, LPARAM);

char appName[] = "DLL Test (non-OWL app)";

int PASCAL WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR,
  int nCmdShow )
{
  WNDCLASS wndClass;
  MSG  msg;
  HWND hWnd;

  if ( !hPrevInstance )
  {
    wndClass.style	    = CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc    = WndProc;
    wndClass.cbClsExtra	    = 0;
    wndClass.cbWndExtra	    = 0;
    wndClass.hInstance 	    = hInstance;
    wndClass.hIcon	    = LoadIcon( 0, IDI_APPLICATION );
    wndClass.hCursor	    = LoadCursor( 0, IDC_ARROW );
    wndClass.hbrBackground  = (HBRUSH)GetStockObject( WHITE_BRUSH );
    wndClass.lpszMenuName   = "COMMANDS";
    wndClass.lpszClassName  = appName;

    if ( !RegisterClass( &wndClass ) )
      return FALSE;
  }

  hWnd = CreateWindow(appName, appName, WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, 0, 0, hInstance, NULL);

  ShowWindow( hWnd, nCmdShow );

  while ( GetMessage( &msg, 0, 0, 0 ) )
  {
    TranslateMessage( &msg );
    DispatchMessage( &msg );
  }

  return msg.wParam;
}

LRESULT FAR PASCAL _export WndProc (HWND hWnd, UINT Message, WPARAM wParam,
  LPARAM lParam)
{
  switch(Message)
  {
    case WM_DESTROY:
      PostQuitMessage(0);
      break;

    case WM_COMMAND:
      if ( (LOWORD(lParam) == 0) && (wParam == CM_COLOR) )
      {
        COLORREF TheColor;
        char MsgStr[128];

        TheColor = RGB(0x00, 0x00, 0x00);
        if ( GetColor(hWnd, TheColor) )
          sprintf(MsgStr,
           "RGB intensities: \r\n\r\n Red - %d \r\n Green - %d \r\n Blue - %d",
            GetRValue(TheColor), GetGValue(TheColor), GetBValue(TheColor));
        else
          strcpy(MsgStr, "Cancelled");
        MessageBox(hWnd, MsgStr, appName, MB_OK);
      }
      else
        return DefWindowProc(hWnd, Message, wParam, lParam);
      break;

    default:
      return DefWindowProc(hWnd, Message, wParam, lParam);
  }
  return 0L;
}
