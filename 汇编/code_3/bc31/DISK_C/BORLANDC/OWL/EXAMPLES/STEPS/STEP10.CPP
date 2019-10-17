// ObjectWindows - (C) Copyright 1992 by Borland International

#include <stdio.h>
#include <stdlib.h>
#include <dir.h>
#include <array.h>
#include <abstarry.h>
#include <string.h>
#include <owl.h>
#include <inputdia.h>
#include <filedial.h>
#include "helpwind.h"
#include "steps.h"

class TMyApp : public TApplication
{
public:
  TMyApp(LPSTR AName, HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
    : TApplication(AName, hInstance, hPrevInstance, lpCmdLine, nCmdShow) {};
  virtual void InitMainWindow();
};

_CLASSDEF(TPoint)
class TPoint: public Object
{
public:
  int X, Y;
  TPoint(int AX, int AY) {X = AX, Y = AY;}
  virtual classType isA() const { return __firstUserClass; }
  virtual Pchar nameOf() const { return "TPoint"; }
  virtual hashValueType hashValue() const { return 0; }
  virtual int isEqual(RCObject APoint) const
    { return X == ((RTPoint)APoint).X && Y == ((RTPoint)APoint).Y; }
  virtual void printOn(Rostream outputStream) const
    { outputStream << "(" << X << "," << Y << ")"; }
};

_CLASSDEF(TPointArray)
class TPointArray : public Array, public TStreamable
{
public:
  TPointArray(int upper, int lower = 0, sizeType aDelta = 0)
    : Array(upper, lower, aDelta){};
  virtual classType isA() const { return __firstUserClass + 1; }
  virtual Pchar nameOf() const { return "TPointArray"; }
  static PTStreamable build();
protected:
  TPointArray(StreamableInit) : Array(50, 0, 50) {};
  virtual void write( Ropstream );
  virtual Pvoid read( Ripstream );
private:
  virtual const Pchar streamableName() const
    { return "TPointArray"; }
};

inline Ripstream operator >> ( Ripstream is, RTPointArray cl )
  { return is >> (RTStreamable)cl; }

inline Ripstream operator >> ( Ripstream is, RPTPointArray cl )
  { return is >> (RPvoid)cl; }

inline Ropstream operator << ( Ropstream os, RTPointArray cl )
  { return os << (RTStreamable)cl; }

inline Ropstream operator << ( Ropstream os, PTPointArray cl )
  { return os << (PTStreamable)cl; }


_CLASSDEF(TMyWindow)
class TMyWindow : public TWindow
{
public:
  HDC DragDC;
  BOOL ButtonDown;
  HPEN ThePen;
  int PenSize;
  PTPointArray Points;
  char FileName[MAXPATH];
  BOOL IsDirty, IsNewFile;
  TMyWindow(PTWindowsObject AParent, LPSTR ATitle);
  ~TMyWindow();
  virtual BOOL CanClose();
  void SetPenSize(int NewSize);
  virtual void Paint(HDC DC, PAINTSTRUCT& PS);
  virtual void OpenFile();
  virtual void SaveFile();
  virtual void SaveFileAs();
  virtual void WMLButtonDown(RTMessage Msg)
    = [WM_FIRST + WM_LBUTTONDOWN];
  virtual void WMLButtonUp(RTMessage Msg)
    = [WM_FIRST + WM_LBUTTONUP];
  virtual void WMMouseMove(RTMessage Msg)
    = [WM_FIRST + WM_MOUSEMOVE];
  virtual void WMRButtonDown(RTMessage Msg)
    = [WM_FIRST + WM_RBUTTONDOWN];
  virtual void CMFileNew(RTMessage Msg)
    = [CM_FIRST + CM_FILENEW];
  virtual void CMFileOpen(RTMessage Msg)
    = [CM_FIRST + CM_FILEOPEN];
  virtual void CMFileSave(RTMessage Msg)
    = [CM_FIRST + CM_FILESAVE];
  virtual void CMFileSaveAs(RTMessage Msg)
    = [CM_FIRST + CM_FILESAVEAS];
  virtual void CMHelp(RTMessage Msg)
    = [CM_FIRST + CM_HELP];
  static PTStreamable build();

protected:
  TMyWindow(StreamableInit) : TWindow(streamableInit) {};
  virtual void write( Ropstream );
  virtual Pvoid read( Ripstream );

private:
  const Pchar streamableName() const { return "TMyWindow"; }
};

inline Ripstream operator >> ( Ripstream is, RTMyWindow cl )
  { return is >> (RTStreamable)cl; }

inline Ripstream operator >> ( Ripstream is, RPTMyWindow cl )
  { return is >> (RPvoid)cl; }

inline Ropstream operator << ( Ropstream os, RTMyWindow cl )
  { return os << (RTStreamable)cl; }

inline Ropstream operator << ( Ropstream os, PTMyWindow cl )
  { return os << (PTStreamable)cl; }

TMyWindow::TMyWindow(PTWindowsObject AParent, LPSTR ATitle)
  : TWindow(AParent, ATitle)
{
  AssignMenu("COMMANDS");
  ButtonDown = FALSE;
  PenSize = 1;
  ThePen = CreatePen(PS_SOLID, PenSize, 0);
  Points = new TPointArray(50, 0, 50);
  IsNewFile = TRUE;
  IsDirty = FALSE;
}

TMyWindow::~TMyWindow()
{
  delete Points;
  DeleteObject(ThePen);
}

void TMyWindow::SetPenSize(int NewSize)
{
  DeleteObject(ThePen);
  ThePen = CreatePen(PS_SOLID, NewSize, 0);
  PenSize = NewSize;
}

void TMyWindow::Paint(HDC DC, PAINTSTRUCT&)
{
  RArrayIterator PointIterator = (RArrayIterator)(Points->initIterator());
  BOOL First = TRUE;

  SelectObject(DC, ThePen);
  while ( int(PointIterator) != 0 )
  {
    RObject AnObject = PointIterator++;
    if ( AnObject != NOOBJECT )
    {
      if ( First )
      {
        MoveTo(DC, ((PTPoint)(&AnObject))->X, ((PTPoint)(&AnObject))->Y);
        First = FALSE;
      }
      else
        LineTo(DC, ((PTPoint)(&AnObject))->X, ((PTPoint)(&AnObject))->Y);
    }
  }
  delete &PointIterator;
}

BOOL TMyWindow::CanClose()
{
  if ( !IsDirty )
    return TRUE;
  return MessageBox(HWindow, "Do you want to save?",
    "Drawing has changed", MB_YESNO | MB_ICONQUESTION) == IDNO;
}

void TMyWindow::WMLButtonDown(RTMessage Msg)
{
  Points->flush();
  InvalidateRect(HWindow, NULL, TRUE);
  if ( !ButtonDown )
  {
    ButtonDown = TRUE;
    SetCapture(HWindow);
    DragDC = GetDC(HWindow);
    SelectObject(DragDC, ThePen);
    MoveTo(DragDC, Msg.LP.Lo, Msg.LP.Hi);
    Points->add(* (new TPoint(Msg.LP.Lo, Msg.LP.Hi)));
  }
}

void TMyWindow::WMMouseMove(RTMessage Msg)
{
  if ( ButtonDown )
  {
    LineTo(DragDC, Msg.LP.Lo, Msg.LP.Hi);
    Points->add(* (new TPoint(Msg.LP.Lo, Msg.LP.Hi)));
  }
}

void TMyWindow::WMLButtonUp(RTMessage)
{
  if ( ButtonDown )
  {
    ButtonDown = FALSE;
    ReleaseCapture();
    ReleaseDC(HWindow, DragDC);
  }
}

void TMyWindow::WMRButtonDown(RTMessage)
{
  char InputText[6];
  int NewPenSize;

  sprintf(InputText, "%d", PenSize);
  if ( GetApplication()->ExecDialog(new TInputDialog(this, "Line Thickness",
    "Input a new thickness:", InputText, sizeof InputText)) == IDOK )
  {
      NewPenSize = atoi(InputText);
      if ( NewPenSize < 0 )
        NewPenSize = 1;
      SetPenSize(NewPenSize);
  }
}

void TMyWindow::CMFileNew(RTMessage)
{
  Points->flush();
  InvalidateRect(HWindow, NULL, TRUE);
  IsDirty = FALSE;
  IsNewFile = TRUE;
}

void TMyWindow::CMFileOpen(RTMessage)
{
  if ( GetApplication()->ExecDialog(new TFileDialog(this, SD_FILEOPEN,
    strcpy(FileName, "*.PTS"))) == IDOK )
      OpenFile();
}

void TMyWindow::CMFileSave(RTMessage)
{
  if ( IsNewFile )
    SaveFileAs();
  else SaveFile();
}

void TMyWindow::SaveFileAs()
{
  if ( IsNewFile )
    strcpy(FileName, "");
  if ( GetApplication()->ExecDialog(new TFileDialog(this, SD_FILESAVE,
    strcpy(FileName, "*.PTS"))) == IDOK )
      SaveFile();
}

void TMyWindow::CMFileSaveAs(RTMessage)
{
  SaveFileAs();
}

void TMyWindow::SaveFile()
{
   ofpstream os(FileName);

   os << Points;
   os.close();
   IsNewFile = IsDirty = FALSE;
}

void TMyWindow::OpenFile()
{
   ifpstream is(FileName);
   if ( is.bad() )
     MessageBox(HWindow, "Unable to open file", "File Error",
       MB_OK | MB_ICONEXCLAMATION);
   else
   {
     Points->flush();
     is >> Points;
     is.close();
     IsNewFile = IsDirty = FALSE;
     InvalidateRect(HWindow, NULL, 1);
   }
}


void TMyWindow::CMHelp(RTMessage)
{
  PTWindow HelpWindow;

  HelpWindow = new THelpWindow(this);
  HelpWindow->Attr.Style |= WS_POPUPWINDOW | WS_CAPTION;
  HelpWindow->Attr.X = 100;
  HelpWindow->Attr.Y = 100;
  HelpWindow->Attr.W = 300;
  HelpWindow->Attr.H = 300;
  GetApplication()->MakeWindow(HelpWindow);
}

Pvoid TMyWindow::read(Ripstream is)
{
  TWindow::read(is);
  is >> Points;
  return this;
}

void TMyWindow::write(Ropstream os)
{
  TWindow::write(os);
  os << Points;
}

PTStreamable TMyWindow::build()
{
  return new TMyWindow(streamableInit);
}

TStreamableClass RegMyWindow("TMyWindow", TMyWindow::build, __DELTA(TMyWindow));

Pvoid TPointArray::read(Ripstream is)
{
  sizeType NumPoints;
  PTPoint APoint;

  is >> NumPoints;
  for ( int i = 0; i < NumPoints; ++i )
  {
     APoint = new TPoint(0, 0);
     is >> APoint->X;
     is >> APoint->Y;
     add(* (APoint));
  };
  return this;
}

void TPointArray::write(Ropstream os)
{
  RContainerIterator PointIterator = initIterator();

  os << getItemsInContainer();
  while ( int(PointIterator) != 0 )
  {
    RObject PointObject = PointIterator++;
    if ( PointObject != NOOBJECT )
    {
      os << ((PTPoint)(&PointObject))->X;
      os << ((PTPoint)(&PointObject))->Y;
    }
  }
  delete &PointIterator;
}

PTStreamable TPointArray::build()
{
  return new TPointArray(streamableInit);
}

TStreamableClass RegPointArray("TPointArray", TPointArray::build,
  __DELTA(TPointArray));

void TMyApp::InitMainWindow()
{
  MainWindow = new TMyWindow(NULL, Name);
}

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
  LPSTR lpCmdLine, int nCmdShow)
{
  TMyApp MyApp("Sample ObjectWindows Program", hInstance, hPrevInstance,
               lpCmdLine, nCmdShow);
  MyApp.Run();
  return MyApp.Status;
}
