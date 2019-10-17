// ObjectWindows - (C) Copyright 1992 by Borland International

/* Simple four function calculator */
#include <owl.h>
#include <dialog.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define min(a,b) (((a) < (b)) ? (a) : (b))

#define APPNAME "Calc"

/* Number of digits in calculator display */
  const int DisplayDigits = 15;

/* Control ID of display static text */
  const int ID_DISPLAY = 400;

/* Color constants */
  const long RGB_YELLOW = 0x0000FFFFL;
  const long RGB_BLUE   = 0x00FF0000L;
  const long RGB_RED    = 0x000000FFL;


/* Calculator state */

  enum TCalcState {CS_FIRST, CS_VALID, CS_ERROR};

/* Calculator dialog window object */
class TCalc : public TDialog {
public:
    TCalcState CalcStatus;
    char Number[DisplayDigits + 1];
    BOOL Negative;
    char Operator;
    double Operand;
    HBRUSH BlueBrush;
    TCalc();
    virtual ~TCalc();
    virtual LPSTR GetClassName();
    virtual void GetWindowClass(WNDCLASS&);
    virtual void WMControlColor(TMessage& Msg)
                                = [WM_FIRST + WM_CTLCOLOR];
    virtual void WMPaint(TMessage& Msg)
                         = [WM_FIRST + WM_PAINT];
    virtual void DefChildProc(TMessage& Msg);
    virtual void DefCommandProc(TMessage& Msg);
    void FlashButton(char Key);
    void Error();
    void SetDisplay(double R);
    void GetDisplay(double& R);
    void CheckFirst();
    void InsertKey(char Key);
    void CalcKey(char Key);
    void Clear();
    virtual void UpdateDisplay();
};

/* Calculator application object */

class TCalcApp : public TApplication {
public:
    TCalcApp(LPSTR AName, HINSTANCE hInstance,
		  HINSTANCE hPrevInstance, LPSTR lpCmd,
		  int nCmdShow)
	        : TApplication(AName, hInstance,
			       hPrevInstance, lpCmd, nCmdShow) {};
    virtual void InitMainWindow();
    virtual void InitInstance();
    virtual BOOL ProcessAppMsg(LPMSG AMessage);
};


/* Calculator constructor.  Create blue brush for calculator background,
  and do a clear command. */

TCalc::TCalc() : TDialog(NULL, APPNAME)
{
  BlueBrush = CreateSolidBrush(RGB_BLUE);
  Clear();
}

/* Calculator destructor.  Delete the background brush. */

TCalc::~TCalc()
{
  DeleteObject(BlueBrush);
}

/* We're changing the window class so we must supply a new class name.*/

LPSTR TCalc::GetClassName()
{
  return APPNAME;
}

/* The calculator has its own icon which is installed here. */
void TCalc::GetWindowClass(WNDCLASS& AWndClass)
{
  TDialog::GetWindowClass(AWndClass);
  AWndClass.hIcon = LoadIcon(GetApplication()->hInstance, APPNAME);
}

/* Colorize the calculator. Allows background to show through corners of
  buttons, uses yellow text on black background in the display, and sets
  the dialog background to blue. */
void TCalc::WMControlColor(TMessage& Msg)
{
  switch (Msg.LP.Hi) {
    case CTLCOLOR_BTN:
      Msg.Result = (LRESULT)GetStockObject(NULL_BRUSH);
      break;
    case CTLCOLOR_STATIC:
	SetTextColor((HDC)Msg.WParam, RGB_YELLOW);
	SetBkMode((HDC)Msg.WParam, TRANSPARENT);
	Msg.Result = (LRESULT)GetStockObject(BLACK_BRUSH);
      break;
    case CTLCOLOR_DLG:
	SetBkMode((HDC)Msg.WParam, TRANSPARENT);
	Msg.Result = (LRESULT)BlueBrush;
      break;
    default:
      DefWndProc(Msg);
  }
}

/* Even dialogs can have their backgrounds painted on.  This creates
  a red ellipse over the blue background. */

void TCalc::WMPaint(TMessage&)
{
  HBRUSH OldBrush;
  HPEN OldPen;
  RECT R;
  PAINTSTRUCT PS;

  BeginPaint(HWindow, &PS);
  OldBrush = (HBRUSH)SelectObject(PS.hdc, CreateSolidBrush(RGB_RED));
  OldPen = (HPEN)SelectObject(PS.hdc, GetStockObject(NULL_PEN));
  GetClientRect(HWindow, &R);
  R.bottom = R.right;
  OffsetRect(&R, -R.right/4, -R.right/4);
  Ellipse(PS.hdc, R.left, R.top, R.right, R.bottom);
  SelectObject(PS.hdc, OldPen);
  DeleteObject(SelectObject(PS.hdc, OldBrush));
  EndPaint(HWindow, &PS);
}

/* Flash a button with the value of Key.  Looks exactly like a
  click of the button with the mouse. */

void TCalc::FlashButton(char Key)
{
  HWND Button;
  WORD Delay;

  if ( Key == 0x0D) Key = '=';  // Treat Enter like '='
  Button = GetDlgItem(HWindow, toupper(Key));
  if ( Button )
  {
    SendMessage(Button, BM_SETSTATE, 1, 0);
    for (Delay = 1; Delay <= 30000; ++Delay)
      ;
    SendMessage(Button, BM_SETSTATE, 0, 0);
  }
}

/* Rather than handle each button individually with child ID
  response methods, it is possible to handle them all at
  once with the default child procedure. */

void TCalc::DefChildProc(TMessage& Msg)
{
  if ( (Msg.WP.Hi == 0) && (Msg.LP.Hi == BN_CLICKED) )
    CalcKey(Msg.WP.Lo);
  TDialog::DefChildProc(Msg);
}

/* Rather than handle each accelerator individually with
  command ID response methods, it is possible to handle them
  all at once with the default command procedure. */
void TCalc::DefCommandProc(TMessage& Msg)
{
  if ( Msg.WP.Hi == 0 )
  {
    FlashButton(Msg.WP.Lo); /* flash button as if it were pushed */
    CalcKey(Msg.WP.Lo);
  }
  TDialog::DefCommandProc(Msg);
}

/* Set Display text to the current value. */
void TCalc::UpdateDisplay()
{
  char S[DisplayDigits + 2];

  if ( Negative )
    strcpy(S, "-");
  else
    S[0] = '\0';
  SetWindowText(GetDlgItem(HWindow, ID_DISPLAY), strcat(S, Number));
}

/* Clear the calculator. */
void TCalc::Clear()
{
  CalcStatus = CS_FIRST;
  _fstrcpy(Number, "0");
  Negative = FALSE;
  Operator = '=';
}

void TCalc::Error()
{
  CalcStatus = CS_ERROR;
  _fstrcpy(Number, "Error");
  Negative = FALSE;
}

void TCalc::SetDisplay(double R)
{
  LPSTR First, Last;
  int CharsToCopy;
  char S[64];

// limit results of calculations to 7 digits to the right of the decimal point
  R = (floor(R * 10000000L + .5))/10000000L ;

  sprintf(S, "%0.10f", R);
  First = S;
  Negative = FALSE;
  if ( S[0] == '-' )
  {
    ++First;
    Negative = TRUE;
  }
  if ( _fstrlen(First) > DisplayDigits + 1 + 10 )
    Error();
  else
  {
    Last = _fstrchr(First, 0);
    while ( Last[-1] == '0' )
      --Last;
    if ( Last[-1] == '.' )
      --Last;
    CharsToCopy = min(DisplayDigits + 1, (int)(Last - First));
    _fstrncpy(Number, First, CharsToCopy);
    Number[CharsToCopy] = '\0';
  }
}

void TCalc::GetDisplay(double& R)
{
  R = atof(Number);
  if ( Negative )
    R = -R;
}

void TCalc::CheckFirst()
{
  if ( CalcStatus == CS_FIRST )
  {
    CalcStatus = CS_VALID;
    _fstrcpy(Number, "0");
    Negative = FALSE;
  }
}

void TCalc::InsertKey(char Key)
{
  int L;

  L = _fstrlen(Number);
  if ( L < DisplayDigits )
  {
    Number[L] = Key;
    Number[L + 1] = '\0';
  }
}


/* Process calculator key. */
void TCalc::CalcKey(char Key)
{
  double R;

  Key = toupper(Key);
  if ( (CalcStatus == CS_ERROR) && (Key != 'C') )
    Key = ' ';
  if ( Key >= '0' && Key <= '9' )
  {
    CheckFirst();
    if ( _fstrcmp(Number, "0") == 0 )
      Number[0] = '\0';
    InsertKey(Key);
  }
  else
    if ( Key == '+' || Key == '-' || Key == '*' ||
         Key == '/' || Key == '=' || Key == '%' || Key == 0x0D )
    {
      if ( CalcStatus == CS_VALID )
      {
        CalcStatus = CS_FIRST;
        GetDisplay(R);
        if ( Key == '%' )
          if ( Operator == '+' || Operator == '-' )
            R = Operand * R / 100;
          else
            if ( Operator == '*' || Operator == '/' )
              R = R / 100;
        switch ( Operator ) {
          case '+': SetDisplay(Operand + R);
                    break;
   	    case '-': SetDisplay(Operand - R);
                    break;
	    case '*': SetDisplay(Operand * R);
                    break;
	    case '/': if ( R == 0 )
                      Error();
                    else
                      SetDisplay(Operand / R);
                    break;
        }
      }
      Operator = Key;
      GetDisplay(Operand);
    }
    else
      switch ( Key ) {
        case '.': CheckFirst();
	          if ( _fstrchr(Number, '.') == NULL )
                  InsertKey(Key);
                  break;
        case 0x8: CheckFirst();
                  if ( _fstrlen(Number) == 1 )
                    _fstrcpy(Number, "0");
	          else
                    Number[_fstrlen(Number) - 1] = '\0';
                  break;
        case '_': Negative = !Negative;
                  break;
        case 'C': Clear();
                  break;
      }
  UpdateDisplay();
}

/* Create calculator as the application's main window. */

void TCalcApp::InitMainWindow()
{
  MainWindow = new TCalc();
}

/* This application loads accelerators so that key input can be used. */

void TCalcApp::InitInstance()
{
  TApplication::InitInstance();
  HAccTable = LoadAccelerators(hInstance, APPNAME);
}

/* This is one of the few places where the order of processing of
  messages is important.  The usual order, ProcessDlgMsg,
  ProcessMDIAccels, ProcessAccels, allows an application to define
  accelerators which will not break the keyboard handling in
  child dialogs.  In this case, the dialog is the application.
  If we used the default ProcessAppMsg, then the keyboard
  handler, ProcessDlgMsg, would return TRUE and accelerators
  would not be processed.  In this case, what we are doing is safe
  because we are not defining any accelerators which conflict
  with the Window's keyboard handling for dialogs.  Making this
  change allows us to use keyboard input for the calculator.  Also,
  because this is our app, we know that it is not an MDI app,
  therefore we do not need to call ProcessMDIAccels (although it
  would not hurt to do so). */

BOOL TCalcApp::ProcessAppMsg(LPMSG Message)
{
  return ProcessAccels(Message) || ProcessDlgMsg(Message);
}

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
		   LPSTR lpCmd, int nCmdShow)
{
  TCalcApp CalcApp(APPNAME, hInstance, hPrevInstance,
		lpCmd, nCmdShow);
  CalcApp.Run();
  return CalcApp.Status;
}
