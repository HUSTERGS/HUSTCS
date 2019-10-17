// (C) Copyright 1991, 1992 by Borland International

#define STRICT
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#if defined( BWCC)
#include <bwcc.h>
#else
#define IDHELP 210
#endif
#include "rwcdemo.h"
#include "rwcdlg.h"

#define TextStart 200


static char szNotImplemented[] = "Feature Not Implemented";
static char szDemoApp[] = "RWCDemo";
HMENU   hMenuInit;


HBITMAP bmpStatusLine;
HBITMAP bmpStatusBar;

HINSTANCE  WinApp::hInstance;
HINSTANCE  WinApp::hPrevInst;
int        WinApp::cmdShow;
HWND      WinApp::hWndClient;
TMDIChildWindow *WinApp::currentWindow;
UINT    wm_DrawStatusLine;

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR, int cmdShow)
{
        HACCEL  hAccel;
        HWND    hwndFrame;
        MSG     msg;
        WNDCLASS        wndClass;

        WinApp::hInstance = hInstance;
        WinApp::hPrevInst = hPrevInst;
        WinApp::cmdShow = cmdShow;
        WinApp::currentWindow = NULL;

        if (!WinApp::hPrevInst)
        {
                wndClass.style          = CS_HREDRAW | CS_VREDRAW;
                wndClass.lpfnWndProc    = FrameWndProc;
                wndClass.cbClsExtra     = 0;
                wndClass.cbWndExtra     = 0;
                wndClass.hInstance      = hInstance;
                wndClass.hIcon          = LoadIcon(WinApp::hInstance, MAKEINTRESOURCE(ico_RWCDemo));
                wndClass.hCursor        = LoadCursor(NULL, IDC_ARROW);
                wndClass.hbrBackground  = (HBRUSH)(COLOR_APPWORKSPACE + 1);
                wndClass.lpszMenuName   = NULL;
                wndClass.lpszClassName  = "MDIFrame";

                RegisterClass(&wndClass);

        }

        hMenuInit       = LoadMenu(WinApp::hInstance, MAKEINTRESOURCE(100));
        hAccel  = LoadAccelerators(WinApp::hInstance, MAKEINTRESOURCE(acc_Main));
        wm_DrawStatusLine = RegisterWindowMessage("RWCDrawStatusLine");
        hwndFrame = CreateWindow("MDIFrame", "RWCDemo",
                        WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
                        CW_USEDEFAULT, CW_USEDEFAULT,
                        CW_USEDEFAULT, CW_USEDEFAULT,
                        NULL, hMenuInit, hInstance, NULL);

        WinApp::hWndClient = GetWindow(hwndFrame, GW_CHILD);

        ShowWindow(hwndFrame, WinApp::cmdShow);
        UpdateWindow(hwndFrame);

        while (GetMessage(&msg, NULL, 0, 0))
                if (!TranslateMDISysAccel(WinApp::hWndClient, &msg) &&
                        !TranslateAccelerator(hwndFrame, hAccel, &msg))
                {
                        TranslateMessage(&msg);
                        DispatchMessage(&msg);
                }
        return msg.wParam;
}

void NewWindow(TMDIChildWindow* window)
{
        MDICREATESTRUCT mdiCreate;

        mdiCreate.szClass = window->className();
        mdiCreate.szTitle = window->title;
        mdiCreate.hOwner = WinApp::hInstance;
        mdiCreate.x = CW_USEDEFAULT;
        mdiCreate.y = CW_USEDEFAULT;
        mdiCreate.cx = CW_USEDEFAULT;
        mdiCreate.cy = CW_USEDEFAULT;
        mdiCreate.style = 0;
        mdiCreate.lParam = NULL;
        WinApp::currentWindow = window;

        SendMessage(WinApp::hWndClient, WM_MDICREATE, 0,
                (LONG) (LPMDICREATESTRUCT) &mdiCreate);
}

int ExecuteDialog(HWND hWindow, TDialog *d)
{
  return DialogBoxParam(WinApp::hInstance, d->name, hWindow, d->dialogFunc, (LONG) (void far *) d);
}

int DoCommands(HWND hWindow, int Command, HWND hWndSource, UINT Notification)
{
        TDialog *d;
        int FileType;

        switch(Command)
        {
                case cm_Exit:
                        //Iterate through all child windows.  If still can close then
                        PostQuitMessage(0);
                        return 0;
		case cm_Open:
			char szFileName[ fsFileSpec + 1];

			strcpy( szFileName, "*.*");
			d = new TFileOpen(&FileType, szFileName);
                        if ( ExecuteDialog(hWindow, d) == IDOK)
                        {
#if defined (BWCC)
                                BWCCMessageBox(GetFocus(), szNotImplemented, szDemoApp, MB_OK);
#else
                                MessageBox(GetFocus(), szNotImplemented, szDemoApp, MB_OK);
#endif
                        }
                        delete d;
                        return 0;

                case cm_New:
                        d = new TFileNew(&FileType);
                        if (ExecuteDialog(hWindow, d) == IDOK)
                                switch(FileType)
                                {
                                        case ScribbleWindow:
                                                NewWindow(new TScribbleWindow("Untitled"));
                                                break;
                                        case GraphWindow:
                                                NewWindow(new TShapeWindow("Untitled"));
                                                break;
                                        default:
                                                NewWindow(new TEditWindow("Untitled"));
                                                break;

                                }
                        delete d;
                        return 0;
                case cm_SaveAs:
                        d = new TDialog(dlg_SaveAs);

                        if ( ExecuteDialog(hWindow, d) == IDOK)
                        {
#if defined (BWCC)
                                BWCCMessageBox(GetFocus(), szNotImplemented, szDemoApp, MB_OK);
#else
                                MessageBox(GetFocus(), szNotImplemented, szDemoApp, MB_OK);
#endif
                        }
                        delete d;
                        return 0;

                case cm_Print:
                        d = new TDialog(dlg_Print);
                        ExecuteDialog(hWindow, d);
                        delete d;
#if defined (BWCC)
                        BWCCMessageBox(GetFocus(), szNotImplemented, szDemoApp, MB_OK);
#else
                        MessageBox(GetFocus(), szNotImplemented, szDemoApp, MB_OK);
#endif
                        return 0;

                case cm_About_CUA:
                        d = new TDialog(dlg_About);
                        ExecuteDialog(hWindow, d);
                        return 0;

                case cm_Directories:
                        d = new TDialog(dlg_Directories);
                        ExecuteDialog(hWindow, d);
#if defined (BWCC)
                        BWCCMessageBox(GetFocus(), szNotImplemented, szDemoApp, MB_OK);
#else
                        MessageBox(GetFocus(), szNotImplemented, szDemoApp, MB_OK);
#endif
                        return 0;

                case cm_Preferences:
                        d = new TDialog(dlg_Preferences);
                        ExecuteDialog(hWindow, d);
#if defined (BWCC)
                        BWCCMessageBox(GetFocus(), szNotImplemented, szDemoApp, MB_OK);
#else
                        MessageBox(GetFocus(), szNotImplemented, szDemoApp, MB_OK);
#endif
                        return 0;

                case cm_Mouse:
                        d = new TDialog(dlg_Mouse);
                        ExecuteDialog(hWindow, d);
#if defined (BWCC)
                        BWCCMessageBox(GetFocus(), szNotImplemented, szDemoApp, MB_OK);
#else
                        MessageBox(GetFocus(), szNotImplemented, szDemoApp, MB_OK);
#endif
                        return 0;
                case cm_Options_Open:
                        d = new TDialog(dlg_Options_Open);
                        ExecuteDialog(hWindow, d);
                        return 0;

                case cm_Options_Save:
#if defined (BWCC)
                        BWCCMessageBox(GetFocus(), szNotImplemented, szDemoApp, MB_OK);
#else
                        MessageBox(GetFocus(), szNotImplemented, szDemoApp, MB_OK);
#endif
                        return 0;

                case cm_Options_SaveAs:
                        d = new TDialog(dlg_Options_SaveAs);
                        ExecuteDialog(hWindow, d);
#if defined (BWCC)
                        BWCCMessageBox(GetFocus(), szNotImplemented, szDemoApp, MB_OK);
#else
                        MessageBox(GetFocus(), szNotImplemented, szDemoApp, MB_OK);
#endif
                        return 0;

                case cm_Tile:
                  SendMessage(WinApp::hWndClient, WM_MDITILE, 0, 0L);
                  return 0;
                case cm_Cascade:
                  SendMessage(WinApp::hWndClient, WM_MDICASCADE, 0, 0L);
                  return 0;
                case cm_ArrangeIcons:
                  SendMessage(WinApp::hWndClient, WM_MDIICONARRANGE, 0, 0L);
                  return 0;

                default:
                        HWND hChildWnd = (HWND) (SendMessage(WinApp::hWndClient,
                                WM_MDIGETACTIVE, 0, NULL));

                        if (IsWindow(hChildWnd))
                                SendMessage(hChildWnd, WM_COMMAND, Command, MAKELONG( hWndSource, Notification));
                        break;
        }
        return 0;
}

void DoSize(HWND hWindow)
{
        RECT rect;
        HDC DC, srcDC, destDC;
        HBITMAP bmp;
        HANDLE oldSrc, oldDest;

        GetClientRect(hWindow, &rect);
        MoveWindow(WinApp::hWndClient, 0, 0, rect.right, rect.bottom - 20, 1);
        InvalidateRect(hWindow, NULL, 1);
        DC = GetDC(hWindow);
        srcDC = CreateCompatibleDC(DC);
        destDC = CreateCompatibleDC(DC);
        ReleaseDC(hWindow, DC);

        bmp = LoadBitmap(WinApp::hInstance, MAKEINTRESOURCE(bmp_StatusLine));
        oldSrc = SelectObject(srcDC, bmp);
        if (bmpStatusLine)
          DeleteObject(bmpStatusLine);
        bmpStatusLine = CreateCompatibleBitmap(DC, rect.right, 20);
        oldDest = SelectObject(destDC, bmpStatusLine);
        BitBlt(destDC, 0, 0, 5, 20, srcDC, 0, 0, SRCCOPY);
        StretchBlt(destDC, 5, 0, rect.right - 5, 20,
                           srcDC, 6, 0, 20, 20, SRCCOPY);
        BitBlt(destDC, rect.right - 5, 0, 5, 20, srcDC, 59, 0, SRCCOPY);
        SelectObject(srcDC, oldSrc);
        SelectObject(destDC, oldDest);
        DeleteDC(srcDC);
        DeleteDC(destDC);
        DeleteObject(bmp);
}

void BlastStatusLine(HWND hWindow, HDC PaintDC)
{
        HDC memDC;
        RECT clientRect;
        HANDLE oldBmp;

        GetClientRect(hWindow, &clientRect);
        memDC = CreateCompatibleDC(PaintDC);
        oldBmp = SelectObject(memDC, bmpStatusLine);
        BitBlt(PaintDC, 0, clientRect.bottom - 20,
                clientRect.right - clientRect.left, 20,
                memDC, 0, 0, SRCCOPY);
        SelectObject(memDC, bmpStatusBar);
        BitBlt(PaintDC, 40, clientRect.bottom - 20,
                                        10, 20, memDC, 0, 0, SRCCOPY);
        BitBlt(PaintDC, 100, clientRect.bottom - 20,
                                        10, 20, memDC, 0, 0, SRCCOPY);
        BitBlt(PaintDC, TextStart, clientRect.bottom - 20,
                                        10, 20, memDC, 0, 0, SRCCOPY);
        SelectObject(memDC, oldBmp);
        DeleteDC(memDC);
}

void DoPaint(HWND hWindow)
{
        HDC PaintDC;
        PAINTSTRUCT PS;

        PaintDC = BeginPaint(hWindow, &PS);
        BlastStatusLine(hWindow, PaintDC);
        EndPaint(hWindow, &PS);
}

#define WindowMenuPos 4
#define EditFirst                 cm_Undo
#define EnvironmentFirst          cm_Preferences
#define FileFirst                 cm_New
#define HelpFirst                 cm_Index
#define OptionFirst               cm_Directories
#define ViewFirst                 cm_All
#define WindowFirst               cm_Tile
#define StatusLineHeight        20
int CurrentID;
HMENU CurrentPopup;

void drawStatusLine(HWND hWindow)
{
  HDC DC;
  RECT Rect;
  char Str[128];
  int StrID;

  if (CurrentID)
  {
        switch(CurrentID)
        {
          case cm_New: StrID = sth_FileNew; break;
          case cm_Open: StrID = sth_FileOpen; break;
          case cm_Save: StrID = sth_FileSave; break;
          case cm_SaveAs: StrID = sth_FileSaveAs; break;
          case cm_Print: StrID = sth_FilePrint; break;
          case cm_Exit: StrID = sth_FileExit; break;
          case cm_Undo: StrID = sth_EditUndo; break;
          case cm_Cut: StrID = sth_EditCut; break;
          case cm_Copy: StrID = sth_EditCopy; break;
          case cm_Paste: StrID = sth_EditPaste; break;
          case cm_Delete: StrID = sth_EditDelete; break;
          case cm_Clear: StrID = sth_EditClear; break;
          case cm_Options_Open: StrID = sth_OptionsOpen; break;
          case cm_All: StrID = sth_ViewAll; break;
          case cm_By: StrID = sth_ViewBy; break;
          case cm_Some: StrID = sth_ViewSome; break;
          case cm_Directories: StrID = sth_OptionsDirectory; break;
          case cm_Options_Save: StrID = sth_OptionsSave; break;
          case cm_Options_SaveAs: StrID = sth_OptionsSaveAs; break;
          case cm_Preferences: StrID = sth_EnvironmentPreferences; break;
          case cm_Mouse: StrID = sth_EnvironmentMouse; break;
          case cm_Tile: StrID = sth_WindowTile; break;
          case cm_Cascade: StrID = sth_WindowCascade; break;
          case cm_ArrangeIcons: StrID = sth_WindowArrange; break;
          case cm_CloseAll: StrID = sth_WindowCloseAll; break;
          case cm_Index: StrID = sth_HelpIndex; break;
          case cm_Topic_Search: StrID = sth_HelpTopic; break;
          case cm_Glossary: StrID = sth_HelpGlossary; break;
          case cm_Using_Help: StrID = sth_HelpUsing; break;
          case cm_About_CUA: StrID = sth_HelpAbout; break;
          default:
                return;
        }
  }
  else
  if (CurrentPopup)
  {
        switch(GetMenuItemID(CurrentPopup, 0))
        {
          case FileFirst: StrID = sth_File; break;
          case EditFirst: StrID = sth_Edit; break;
          case ViewFirst: StrID = sth_View; break;
          case WindowFirst: StrID = sth_Window; break;
          case OptionFirst: StrID = sth_Option; break;
          case EnvironmentFirst: StrID = sth_OptionsEnvironment; break;
          case HelpFirst: StrID = sth_Help; break;
          default: return;
        }
  }

  DC = GetDC(hWindow);
  BlastStatusLine(hWindow, DC);
  if ((CurrentPopup) || (CurrentID != 0))
  {
        LOGFONT lf;
        HFONT   hSmall, hOld;
        int     TextHeight;

        // get a slightly smaller font

        hOld = (HFONT) GetStockObject( ANSI_VAR_FONT);
        if ( hOld)
        {
                GetObject( hOld, sizeof( LOGFONT), (LPSTR) &lf);
                if ( lf.lfHeight > 3)
                  lf.lfHeight -= 3;
                lf.lfWidth = 0;
                hSmall = CreateFontIndirect( &lf);
        }
        else
                hSmall = 0;
        if ( hSmall)
                hOld = (HFONT) SelectObject( DC, hSmall);
        else
                hOld = 0;

        LoadString(WinApp::hInstance, StrID, Str, sizeof(Str));
        GetClientRect(hWindow, &Rect);
        SetBkColor(DC, RGB(192, 192, 192));
        TextHeight = (int) HIWORD( GetTextExtent( DC, Str, 1) );
        TextOut(DC, TextStart+10,
          Rect.bottom - StatusLineHeight + ( ( StatusLineHeight - TextHeight ) / 2),
          Str, strlen(Str));
        if ( hOld)
                SelectObject( DC, hOld);
        if ( hSmall)
                DeleteObject( hSmall);
  }
  ReleaseDC(hWindow, DC);
}

void menuSelect(HWND hWindow, WORD wParam, LONG lParam)
{

  if (LOWORD(lParam) == 0x0FFFF)
  {
        CurrentPopup = 0;
        CurrentID = 0;
  }
  else
  if (LOWORD(lParam) & MF_POPUP)
  {
        CurrentPopup = (HMENU) wParam;
        CurrentID = 0;
  }
  else
        CurrentID = wParam;
  PostMessage(hWindow,wm_DrawStatusLine, 0, 0);
}

LRESULT CALLBACK _export FrameWndProc(HWND hWindow, UINT message, WPARAM wParam, LPARAM lParam)
{
        int rc;

        switch(message)
        {
                case WM_CREATE:
                        CLIENTCREATESTRUCT clientCreate;
                        clientCreate.idFirstChild = 2000;
                        clientCreate.hWindowMenu = GetSubMenu(hMenuInit, WindowMenuPos);
                        WinApp::hWndClient = CreateWindow("MDICLIENT", NULL,
                                WS_CHILD | WS_CLIPCHILDREN | WS_VISIBLE,
                                0, 0, 0, 0, hWindow, (HMENU) 1, WinApp::hInstance,
                                (LPSTR) &clientCreate);
                        bmpStatusBar = LoadBitmap(WinApp::hInstance, MAKEINTRESOURCE(bmp_StatusBar));
                        return 0;

                case WM_SIZE:
                        DoSize(hWindow);
                        return 0;

                case WM_PAINT:
                        DoPaint(hWindow);
                        return 0;

                case WM_COMMAND:
                        rc = DoCommands(hWindow, (int) wParam, (HWND) lParam, HIWORD( lParam) );
                        if (rc)
                          return rc;
                        break;
                case WM_DESTROY:
                        if (bmpStatusLine)
                                DeleteObject(bmpStatusLine);
                        DeleteObject(bmpStatusBar);
                        PostQuitMessage(0);
                        return 0;

                case WM_MENUSELECT:
                        menuSelect(hWindow, wParam, lParam);
                        return 0;

                case WM_ENTERIDLE:

                        // handle F1 key for dialog box help

                        if
                        (
                          ( wParam == MSGF_DIALOGBOX) &&
                          ( GetKeyState( VK_F1) &0x8000 )
                        )
                          PostMessage( (HWND)lParam, WM_COMMAND,
                            IDHELP, 0);
                        return 0;

                default:
                        if (message == wm_DrawStatusLine)
                        {
                                drawStatusLine(hWindow);
                                return 0;
                        }
                        else
                                return DefFrameProc(hWindow, WinApp::hWndClient,
                                        message, wParam, lParam);
        }
        return rc;
}

LRESULT CALLBACK _export WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
        TMDIChildWindow *window = (TMDIChildWindow *) GetWindowWord(hwnd, 0);

        switch(message)
        {
                case WM_CREATE:
                        if (WinApp::currentWindow != 0)
                        {
                                SetWindowWord(hwnd, 0, (WORD) WinApp::currentWindow);
                                window = WinApp::currentWindow;
                                WinApp::currentWindow = NULL;
                                window->hWindow = hwnd;
                                window->create();
                                return 0;
                        }
                        break;
                case WM_PAINT:
                        HDC hdc;
                        PAINTSTRUCT ps;

                        hdc = BeginPaint(hwnd, &ps);
                        window->paint(hdc, &ps);
                        EndPaint(hwnd, &ps);
                        return 0;
                case WM_LBUTTONDOWN:
                        window->lButtonDown(wParam, lParam);
                        return 0;

                case WM_LBUTTONUP:
                        window->lButtonUp(wParam, lParam);
                        return 0;

                case WM_MOUSEMOVE:
                        window->mouseMove(wParam, lParam);
                        return 0;
                case WM_RBUTTONDOWN:
                        window->rButtonDown(lParam);
                        return 0;
                case WM_SIZE:
                        window->size(wParam, lParam);
                        return 0;

                case WM_SETFOCUS:
                        window->setFocus();
                        return 0;
                case WM_DESTROY:
                        delete window;

        }
        return DefMDIChildProc(hwnd, message, wParam, lParam);
}


