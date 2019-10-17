// ObjectWindows - (C) Copyright 1992 by Borland International

#include <owl.h>
#include <filedial.h>
#include <string.h>
#include <dir.h>
#include <dos.h>

#define BSA_NAME "BitmapScroll"


/* TBitScrollApp, a TApplication descendant */

class TBitScrollApp : public TApplication {
public:
    TBitScrollApp(LPSTR AName, HINSTANCE hInstance,
		  HINSTANCE hPrevInstance, LPSTR lpCmd,
		  int nCmdShow)
	        : TApplication(AName, hInstance,
			       hPrevInstance, lpCmd, nCmdShow) {};
    virtual void InitMainWindow();
};

/* TBMPFileDialog, a TFileDialog descendant which uses .bmp as its
    default extension. */
class TBMPFileDialog : public TFileDialog {
public:
    TBMPFileDialog(PTWindowsObject AParent, int ResourceId,
                   LPSTR AFilePath, PTModule AModule = NULL)
     : TFileDialog(AParent, ResourceId, AFilePath, AModule)
       { strcpy(Extension, ".bmp"); }
};

/* TBitScrollWindow, a TWindow descendant */

class TBitScrollWindow : public TWindow {
public:
    char FileName[MAXPATH];
    HBITMAP BitmapHandle;
    WORD PixelHeight , PixelWidth;
    long Mode;

    TBitScrollWindow(LPSTR);
    virtual ~TBitScrollWindow();
    virtual LPSTR GetClassName();
    virtual void GetWindowClass(WNDCLASS&);
    virtual void Paint(HDC, PAINTSTRUCT&);
    virtual void CMFileOpen(TMessage&) = [CM_FIRST + CM_FILEOPEN];
    virtual void WMSize(TMessage&) = [WM_FIRST + WM_SIZE];
    void AdjustScroller();
    BOOL LoadBitmapFile(LPSTR);
    BOOL OpenDIB(int TheFile);
    void GetBitmapData(int TheFile, HANDLE, long);
};

/* __ahIncr, ordinal 114, is a 'magic' function. Defining this
  function causes Windows to patch the value into the passed
  reference.  This makes it a type of global variable. To use
  the value of AHIncr, use FP_OFF(AHIncr). */

extern "C" {
void FAR PASCAL  __ahIncr();
}

/* Construct the TBitScrollApp's MainWindow of type TBitScrollWindow */

void TBitScrollApp::InitMainWindow()
{
  MainWindow = new TBitScrollWindow(BSA_NAME);
}

/* Constructor for a TBitScrollWindow, sets scroll styles and constructs
  the Scroller object.  Also sets the Mode based on whether the display
  is monochrome (two-color) or polychrome. */

TBitScrollWindow::TBitScrollWindow(LPSTR ATitle)
                 :TWindow(NULL, ATitle)
{
  HDC DCHandle;

  Attr.Style |= WS_VSCROLL | WS_HSCROLL;
  AssignMenu(BSA_NAME);
  BitmapHandle = 0;
  Scroller = new TScroller(this, 1, 1, 200, 200);
  DCHandle = CreateDC("Display", NULL, NULL, NULL);
  if ( GetDeviceCaps(DCHandle, NUMCOLORS) < 3 )
    Mode = NOTSRCCOPY;
  else
    Mode = SRCCOPY;
  DeleteDC(DCHandle);
}

/* Change the class name to the application name. */

LPSTR TBitScrollWindow::GetClassName()
{
  return BSA_NAME;
}

/* Allow the iconic picture to be drawn from the client area. */

void TBitScrollWindow::GetWindowClass(WNDCLASS& WndClass)
{
  TWindow::GetWindowClass(WndClass);
  WndClass.hIcon = 0; /* Client area will be painted by the app. */
}

TBitScrollWindow::~TBitScrollWindow()
{
  if ( BitmapHandle )
    DeleteObject(BitmapHandle);
}

/* If the the "Open..." menu item is selected, then we prompt the user
   for a new bitmap file.  If the user selects one and it is one that
   we can read, we display it in the window and change the window's
   caption to reflect the new bitmap file. */

void TBitScrollWindow::CMFileOpen(TMessage&)
{
  char TempName [MAXPATH];
  char CaptionBuffer [MAXPATH+ 12 /*BSA_NAME*/ + 2 /*" "*/ + 1 /*'\0'*/ ];

  if (GetApplication()->ExecDialog( new TBMPFileDialog
    (this, SD_FILEOPEN, strcpy(TempName, "*.bmp"))) == IDOK )
    if ( LoadBitmapFile(TempName) )
    {
      strcpy(FileName, TempName);
      strcpy(CaptionBuffer, BSA_NAME);
      strcat(CaptionBuffer, ": ");
      strcat(CaptionBuffer, strlwr(FileName));
      SetWindowText(HWindow, CaptionBuffer);
    }
}

/* Adjust the Scroller range so that the the origin is the
  upper-most scrollable point and the corner is the
  bottom-most. */

void TBitScrollWindow::AdjustScroller()
{
  RECT ClientRect;

  GetClientRect(HWindow, &ClientRect);
  Scroller->SetRange(PixelWidth - (ClientRect.right - ClientRect.left),
      PixelHeight - (ClientRect.bottom - ClientRect.top));
  Scroller->ScrollTo(0, 0);
  InvalidateRect(HWindow, NULL, TRUE);
}

/* Reset scroller range. */

void TBitScrollWindow::WMSize(TMessage& Msg)
{
  TWindow::WMSize(Msg);
  if ( (Msg.WParam != SIZEICONIC) )
    AdjustScroller();
}

/* Copys the bitmap bit data from the file into memory. Since
  copying cannot cross a segment (64K) boundary, we are forced
  to do segment arithmetic to compute the next segment.  Created
  a LongType type to simplify the process. */

void TBitScrollWindow::GetBitmapData(int TheFile, HANDLE BitsHandle,long BitsByteSize)
{
  long Count;
  long Start, ToAddr, Bits;

  Start = 0L;
  Bits = (long)GlobalLock(BitsHandle);
  Count = BitsByteSize - Start;
  while ( Count > 0 )
  {
    ToAddr = MAKELONG(LOWORD(Start),
                      HIWORD(Bits) + (HIWORD(Start) * FP_OFF(__ahIncr)));
    if ( Count > 0x4000 )
      Count = 0x4000;
    _lread(TheFile, (LPSTR)ToAddr, (WORD)Count);
    Start = Start + Count;
    Count = BitsByteSize - Start;
  }
  GlobalUnlock(BitsHandle);
}

/* Attempt to open a Windows 3.0 device independent bitmap. */

BOOL TBitScrollWindow::OpenDIB(int TheFile)
{
    WORD bitCount;
    WORD size;
    long longWidth;
    HDC DCHandle;
    LPSTR BitsPtr;
    BITMAPINFO *BitmapInfo;
    HBITMAP BitsHandle , NewBitmapHandle;
    DWORD NewPixelWidth , NewPixelHeight;
    BOOL retval;

  retval= TRUE;
  _llseek(TheFile, 28, 0);
  _lread(TheFile, (LPSTR)&bitCount, sizeof(bitCount));
  if ( bitCount <= 8 )
  {
    size = sizeof(BITMAPINFOHEADER) + ((1 << bitCount) * sizeof(RGBQUAD));
    BitmapInfo = (BITMAPINFO *)new char[size];
    _llseek(TheFile, sizeof(BITMAPFILEHEADER), 0);
    _lread(TheFile, (LPSTR)BitmapInfo, size);
    NewPixelWidth = BitmapInfo->bmiHeader.biWidth;
    NewPixelHeight = BitmapInfo->bmiHeader.biHeight;
    longWidth = (((NewPixelWidth * bitCount) + 31)/32) * 4;
    BitmapInfo->bmiHeader.biSizeImage = longWidth * NewPixelHeight;
    GlobalCompact(-1);
    BitsHandle = (HBITMAP)GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT,
      BitmapInfo->bmiHeader.biSizeImage);
    GetBitmapData(TheFile, BitsHandle, BitmapInfo->bmiHeader.biSizeImage);
    DCHandle = CreateDC("Display", NULL, NULL, NULL);
    BitsPtr = (LPSTR)GlobalLock((HGLOBAL)BitsHandle);
    NewBitmapHandle =
      CreateDIBitmap(DCHandle, &(BitmapInfo->bmiHeader), CBM_INIT, BitsPtr,
      BitmapInfo, 0);
    DeleteDC(DCHandle);
    GlobalUnlock(BitsHandle);
    GlobalFree(BitsHandle);
    delete BitmapInfo;
    if ( NewBitmapHandle )
    {
      if ( BitmapHandle )
        DeleteObject(BitmapHandle);
      BitmapHandle = NewBitmapHandle;
      PixelWidth = (WORD)NewPixelWidth;
      PixelHeight = (WORD)NewPixelHeight;
    }
    else
      retval = FALSE;
  }
  else
    retval = FALSE;
return retval;
}

/* Test if the passed file is a Windows 3.0 DI bitmap and if so read it.
  Report errors if unable to do so. Adjust the Scroller to the new
  bitmap dimensions. */

BOOL TBitScrollWindow::LoadBitmapFile(LPSTR Name)
{
    int TheFile;
    long TestWin30Bitmap;
    char ErrorMsg[50] = "";
    BOOL retval;

  TheFile = _lopen(Name, OF_READ);
  if ( TheFile != -1 )
  {
    _llseek(TheFile, 14, 0);
    _lread(TheFile, (LPSTR)&TestWin30Bitmap, sizeof(TestWin30Bitmap));
    if ( TestWin30Bitmap == 40 )
      if ( OpenDIB(TheFile) )
	  AdjustScroller();
      else
	  strcpy(ErrorMsg,
                    "Unable to create Windows 3.0 bitmap from file");
    else
      strcpy(ErrorMsg, "Not a Windows 3.0 bitmap file");
    _lclose(TheFile);
  }
  else
    strcpy(ErrorMsg, "Cannot open bitmap file");
  if ( ErrorMsg[0] == '\0' )
    retval= TRUE;
  else
  {
    MessageBox(HWindow, ErrorMsg, BSA_NAME, MB_OK);
    retval= FALSE;
  }
  return retval;
}

/* Responds to an incoming "paint" message by redrawing the bitmap.
   (The Scroller's BeginView method, which sets the viewport origin
   relative to the present scroll position, has already been called.)  */

void TBitScrollWindow::Paint(HDC, PAINTSTRUCT& PaintInfo)
{
  HDC MemoryDC;
  HANDLE OldBitmapHandle;
  RECT ClientRect;

  if ( BitmapHandle )
  {
    MemoryDC = CreateCompatibleDC(PaintInfo.hdc);
    OldBitmapHandle = SelectObject(MemoryDC, BitmapHandle);
    if ( Mode == SRCCOPY )
    {
      SetBkColor(PaintInfo.hdc, GetNearestColor(PaintInfo.hdc, 0x800000L));
      SetTextColor(PaintInfo.hdc, 0xFFFFFFL);
    }
    if ( IsIconic(HWindow) )
    {
      GetClientRect(HWindow, &ClientRect);
      StretchBlt(PaintInfo.hdc, 0, 0,
                 ClientRect.right - ClientRect.left,
                 ClientRect.bottom - ClientRect.top,
                 MemoryDC, 0, 0, PixelWidth, PixelHeight, Mode);
    }
    else
      BitBlt(PaintInfo.hdc, 0, 0, PixelWidth, PixelHeight,
             MemoryDC, 0, 0, Mode);
    SelectObject(MemoryDC, OldBitmapHandle);
    DeleteDC(MemoryDC);
  }
}


/* Run the BitScrollApp */
int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
		   LPSTR lpCmd, int nCmdShow)
{
  TBitScrollApp ScrollApp(BSA_NAME, hInstance, hPrevInstance,
		lpCmd, nCmdShow);
  ScrollApp.Run();
  return ScrollApp.Status;
}
