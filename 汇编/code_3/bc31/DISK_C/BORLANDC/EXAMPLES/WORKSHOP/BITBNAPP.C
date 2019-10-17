// (C) Copyright 1991, 1992 by Borland International

#define STRICT
#include <windows.h>

#pragma argsused        // intentionally not using all pararmeters, here.
BOOL _export CALLBACK BitBnAppDialogProc( HWND hWnd, UINT message,
                                                WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_COMMAND:
		  if ( HIWORD( lParam) == BN_CLICKED)
			DestroyWindow( hWnd);
		  return TRUE;

		case WM_DESTROY:
		  PostQuitMessage( 0);
		  break;

		case WM_INITDIALOG:
		  return TRUE;


	}
	return FALSE;

}

#pragma argsused
int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCommand, int cmdShow)
{
	HWND	hMain;
	MSG	msg;
	HMODULE	hDll;


	hDll = LoadLibrary( "BITBTN.DLL");
	if ( (int) hDll < 32)
	{
		MessageBox( 0,
		  "You must compile BITBTN.DLL before running this program",
		  "Fatal error", MB_OK | MB_ICONHAND);
		return 255;
	}
	hMain = CreateDialog( hInstance, MAKEINTRESOURCE( 100),
		 0, BitBnAppDialogProc);

	if ( hMain)
	{
	       while (GetMessage(&msg, NULL, 0, 0))
	       {
		       TranslateMessage(&msg);
		       DispatchMessage(&msg);
	       }
	}
	else
	{
	       MessageBox( 0, "Could not create window", "Fatal Error",
		 MB_OK | MB_ICONHAND);
	       return 254;
	}
	FreeLibrary( hDll);

	return msg.wParam;
}
