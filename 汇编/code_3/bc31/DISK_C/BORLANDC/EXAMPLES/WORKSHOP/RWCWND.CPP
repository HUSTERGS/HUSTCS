// (C) Copyright 1991, 1992 by Borland International

#define STRICT
#include <windows.h>
#if defined( BWCC)
#include <bwcc.h>
#else
#define IDHELP 210
#endif
#include "rwcdemo.h"
TMDIChildWindow::TMDIChildWindow(char *aTitle)
{
        title = strdup(aTitle);
        registerWnd();
}

TMDIChildWindow::~TMDIChildWindow()
{
        free(title);
}

void TMDIChildWindow::registerWnd()
{
        WNDCLASS wndClass;

        getWindowClass(&wndClass);
        RegisterClass(&wndClass);
}

void TMDIChildWindow::getWindowClass(WNDCLASS *wndClass)
{
        wndClass->style         = CS_HREDRAW | CS_VREDRAW;
        wndClass->lpfnWndProc   = ::WndProc;
        wndClass->cbClsExtra    = 0;
        wndClass->cbWndExtra    = sizeof(LOCALHANDLE);
        wndClass->hInstance     = WinApp::hInstance;
        wndClass->hIcon         = LoadIcon(NULL, IDI_APPLICATION);
        wndClass->hCursor       = LoadCursor(NULL, IDC_ARROW);
        wndClass->hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
        wndClass->lpszMenuName  = NULL;
        wndClass->lpszClassName = className();
}

void TMDIChildWindow::rButtonDown(LONG lParam)
{
        HMENU AMenu = CreatePopupMenu();
        char *AName = getPopupTitle();

        if (AName)
        {
                AppendMenu(AMenu, MF_POPUP, (UINT) getPopupMenu(), AName);
                ClientToScreen(hWindow, &(MAKEPOINT(lParam)));
                TrackPopupMenu(AMenu, 0, LOWORD(lParam), HIWORD(lParam), 0,
                        hWindow, NULL);
                DestroyMenu(AMenu);
        }
}

TDocument::TDocument(char *aFileName) : TMDIChildWindow(aFileName)
{
        isNewFile = 1;
        changed = 0;
        if (aFileName)
          fileName = strdup(aFileName);
        else
          fileName = NULL;
}

TDocument::~TDocument()
{
        if (fileName)
                free(fileName);
}

void TDragWindow::lButtonDown(WORD, LONG)
{
        dragDC = GetDC(hWindow);
        buttonDown = 1;
        SetCapture(hWindow);
}

void TDragWindow::lButtonUp(WORD, LONG)
{
        buttonDown = 0;
        ReleaseDC(hWindow, dragDC);
        ReleaseCapture();
}

void TScribbleWindow::lButtonDown(WORD wParam, LONG lParam)
{
        TDragWindow::lButtonDown(wParam, lParam);
        MoveTo(dragDC, LOWORD(lParam), HIWORD(lParam));
}

void TScribbleWindow::lButtonUp(WORD wParam, LONG lParam)
{
        LineTo(dragDC, LOWORD(lParam), HIWORD(lParam));
        TDragWindow::lButtonUp(wParam, lParam);
}

void TScribbleWindow::mouseMove(WORD, LONG lParam)
{
        if (buttonDown)
                LineTo(dragDC, LOWORD(lParam), HIWORD(lParam));
}

void TGraphObject::DrawRect(HDC HandleDC, RECT R)
{
        SetRect(&R, min(R.right, R.left), min(R.top, R.bottom),
                        max(R.right, R.left), max(R.top, R.bottom));
        Assign(&R);
        Draw(HandleDC);
}

void TShapeWindow::lButtonDown(WORD wParam, LONG lParam)
{
        TDragWindow::lButtonDown(wParam, lParam);
        oldRop = SetROP2(dragDC, R2_NOTXORPEN);
        SetRect(&R, LOWORD(lParam), HIWORD(lParam), LOWORD(lParam), HIWORD(lParam));
        currentShape = new TRectangle(&R);
}

void TShapeWindow::lButtonUp(WORD wParam, LONG lParam)
{
	SetROP2(dragDC, oldRop);
        currentShape->Assign(&R);
        currentShape->Draw(dragDC);
	TDragWindow::lButtonUp(wParam, lParam);
	delete currentShape;
}

void TShapeWindow::mouseMove(WORD, LONG lParam)
{
        if (buttonDown)
        {
                currentShape->DrawRect(dragDC, R);
                SetRect(&R, R.left, R.top, LOWORD(lParam), HIWORD(lParam));
                currentShape->DrawRect(dragDC, R);
        }
}

BOOL TDocument::canClear()
{
        char s[80];
        int rslt;

        if (isModified())
        {
                if (!fileName)
                  strcpy(s, "Untitled file has changed. Save?");
                else
                  wvsprintf(s, "File \"%s\" has changed.  Save?", fileName);
#if defined (BWCC)
                rslt = BWCCMessageBox(hWindow, s, "File Changed", MB_YESNOCANCEL |
                  MB_ICONQUESTION);
#else
                rslt = MessageBox(hWindow, s, "File Changed", MB_YESNOCANCEL |
                  MB_ICONQUESTION);
#endif
                return (rslt == IDYES ? save() : rslt != IDCANCEL);
        }
        else
          return 1;
}

void TDocument::newFile()
{
        if (canClear())
        {
                clearWindow();
                clearModify();
                isNewFile = 1;
                setFileName(NULL);
        }
}

void TDocument::setFileName(char *aFileName)
{
        char *newCaption;

        if (fileName != aFileName)
        {
                if (fileName)
                        free(fileName);
                if (aFileName)
                        fileName = strdup(aFileName);
                else
                        fileName = NULL;
        }

        if (!fileName)
                newCaption = "(Untitled)";
        else
                newCaption = fileName;

        SetWindowText(hWindow, newCaption);
}

BOOL TDocument::save()
{
        if (isModified())
                if (fileName)
                        write();
                else
                        return saveAs();

        return 1;
}

TEditWindow::TEditWindow(char *AFilename) :
  TDocument(AFilename)
{
}

void TEditWindow::create()
{
  TDocument::create();
  editor = CreateWindow("edit", NULL,
          WS_CHILD | WS_VISIBLE | ES_NOHIDESEL | ES_MULTILINE,
          0, 0, 0, 0, hWindow, (HMENU) 100, WinApp::hInstance, NULL);
                //size method will size control
}

void TEditWindow::size(WORD wParam, LONG lParam)
{
        TDocument::size(wParam, lParam);
        SetWindowPos(editor, 0, -1, -1, LOWORD(lParam) + 2, HIWORD(lParam)+2,
          SWP_NOZORDER);
}

void TEditWindow::setFocus()
{
        SetFocus(editor);
}

HMENU TShapeWindow::getPopupMenu()
{
        return LoadMenu(WinApp::hInstance, MAKEINTRESOURCE(1001));
}


HMENU TScribbleWindow::getPopupMenu()
{
        return LoadMenu(WinApp::hInstance, MAKEINTRESOURCE(1000));
}

