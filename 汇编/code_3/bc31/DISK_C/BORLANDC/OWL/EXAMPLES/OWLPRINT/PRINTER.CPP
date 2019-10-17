// ObjectWindows - (C) Copyright 1992 by Borland International

#include "printer.h"
#include "mycombo.h"
#include "ids.h"

#include <static.h>
#include <safepool.h>

// A few private constants

#define SR_ON 32512
#define SR_ERRORTEMPLATE 32513
#define SR_OUTOFMEMORY 32514
#define SR_OUTOFDISK 32515
#define SR_PRNCANCEL 32516
#define SR_PRNMGRABORT 32517
#define SR_GENERROR 32518
#define SR_ERRORCAPTION 32519

static BOOL UserAbort = FALSE;


/*
** FetchStr
** Returns a pointer to the first comma delimited field pointed to
** by Str. It replaces the comma with a a null character and moves the Str
** to the beginning of the next string (skipping white space). Str will
** will point to a null character if no more strings are left. This
** routine is used to fetch strings out of text retrieved from WIN.INI.
*/

static Pchar FetchStr(Pchar& Str)
{
  Pchar result = Str;
  LPSTR tempStr = Str;  // Used because AnsiNext returns an LPSTR;
                        // Note that we could simply use Str instead
                        // if we assumed a large data model.

  if (Str == NULL)
        return result;
  while ((*tempStr != '\0') && (*tempStr != ','))
    tempStr = AnsiNext(tempStr);
  if (*tempStr != '\0')
  {
        *tempStr = '\0';
        tempStr++;
        while (*tempStr == ' ')
                tempStr = AnsiNext(tempStr);
  }
  // Change Str to point to next field.
  Str += int(tempStr - (LPSTR) Str);
  return result;
}


/*
** newstrdup
** Allocate space for and copy a string; allocation is performed
** using 'new' so 'delete' should be used for de-allocation.
*/

static Pchar newstrdup(Pchar S)
{
  Pchar P = new char[strlen(S)+1];
  strcpy(P, S);
  return P;
}


// TPrintout


TPrintout::TPrintout(Pchar ATitle)
{
  Title = newstrdup(ATitle);
  Banding = FALSE;
  ForceAllBands = TRUE;
}

TPrintout::~TPrintout()
{
  delete Title;
}

BOOL TPrintout::IsNextPage()
{
  return FALSE;
}

// TReplaceStatic

_CLASSDEF(TReplaceStatic)
class TReplaceStatic: public TStatic
{
private:
  Pchar Text;
public:
  TReplaceStatic(PTWindowsObject AParent, int ResourceId, Pchar AText);
  virtual ~TReplaceStatic();
  virtual void SetupWindow();
};

TReplaceStatic::TReplaceStatic(PTWindowsObject AParent, int ResourceId,
        Pchar AText) : TStatic(AParent, ResourceId, 0)
{
  Text = newstrdup(AText);
}

TReplaceStatic::~TReplaceStatic()
{
  delete Text;
}

void TReplaceStatic::SetupWindow()
{
  char A[80];
  char B[80];

  TStatic::SetupWindow();
  GetText(A, sizeof(A) - 1);
  LPSTR C[1];
  C[0] = Text;
  wvsprintf((LPSTR) B, (LPSTR) A, (LPSTR) C);
  SetText(B);
}


// TPrinterAbortDlg

TPrinterAbortDlg::TPrinterAbortDlg(PTWindowsObject AParent, Pchar Template,
  Pchar Title, Pchar Device, Pchar Port)
  : TDialog(AParent, Template)
{
  new TReplaceStatic(this, ID_TITLE, Title);
  new TReplaceStatic(this, ID_DEVICE, Device);
  new TReplaceStatic(this, ID_PORT, Port);
}

void TPrinterAbortDlg::SetupWindow()
{
  TDialog::SetupWindow();
  EnableMenuItem(GetSystemMenu(HWindow, FALSE), SC_CLOSE, MF_GRAYED);
}

void TPrinterAbortDlg::WMCommand(RTMessage)
{
  UserAbort = TRUE;
}


// TPrinter

/*
**  This object type is an encapsulation around the Windows printer
**  device interface.  After the object is initialized the Status
**  field must be checked to see if the object was created correctly.
**
**  Examples:
**   Creating a default device printing object:
**
**     DefaultPrinter = new TPrinter();
**
**   Creating a device for a specific printer:
**
**     PostScriptPrinter = new TPrinter();
**     PostScriptPrinter->SetDevice("PostScript Printer",
**       "PSCRIPT", "LPT2:");
**
**   Allowing the user to configure the printer:
**
**     DefaultPrinter->Configure(MyWindow);
*/

// Initialize the TPrinter object assigned to the default printer

TPrinter::TPrinter()
{
  Device = NULL;
  Driver = NULL;
  Port = NULL;
  DeviceModule = 0;
  DevSettings = NULL;
  Error = 0;
  SetDevice(NULL, NULL, NULL);  // Associate with default printer
}

// Deallocate allocated resources

TPrinter::~TPrinter()
{
  ClearDevice();
}

// Clears the association of this object with the current device

void TPrinter::ClearDevice()
{
  delete Device;
  Device = NULL;

  delete Driver;
  Driver = NULL;

  delete Port;
  Port = NULL;

        if ((int)DeviceModule >= 32) {
                FreeLibrary(DeviceModule);
                DeviceModule = 0;
  }
  if (DevSettings)
        delete [] (Pchar) DevSettings;
  Status = PS_UNASSOCIATED;
}


// GetDefaultPrinter and Equal are helper functions used by
// TPrinter::SetDevice

void TPrinter::GetDefaultPrinter()
{
  char Printer[80];
  Pchar Cur;

  GetProfileString("windows", "device", "", Printer,
    sizeof(Printer) - 1);
  Cur = Printer;
  Device = newstrdup(FetchStr(Cur));
  Driver = newstrdup(FetchStr(Cur));
  Port = newstrdup(FetchStr(Cur));
}

static BOOL Equal(Pchar S1, Pchar S2)
{
  return ((S1 != NULL) && (S2 != NULL) && (strcmp(S1, S2) == 0));
}

/*
Associates the printer object with a new device. If the ADevice
parameter is NULL the Windows default printer is used, otherwise,
the parameters must be ones contained in the [devices] section
of the WIN.INI file.
*/

void TPrinter::SetDevice(Pchar ADevice, Pchar ADriver, Pchar APort)
{
  char DriverName[80];
  DEVMODE StubDevMode;

  if (Equal(Device, ADevice) && Equal(Driver, ADriver) &&
    Equal(Port, APort))
        return;
  ClearDevice();
  if (ADevice == NULL)
    GetDefaultPrinter();
  else {
    Device = newstrdup(ADevice);
    Driver = newstrdup(ADriver);
    Port = newstrdup(APort);
  }
  Status = PS_OK;
  strncpy(DriverName, Driver, sizeof(DriverName) - 1);
  strncat(DriverName, ".DRV", sizeof(DriverName) - strlen(DriverName) - 1);
  DeviceModule = LoadLibrary(DriverName);
        if ((int)DeviceModule < 32)
        Status = PS_INVALIDDEVICE;
  else {
    // Grab the DevMode procedures
    ExtDeviceMode = (LPFNDEVMODE) GetProcAddress(DeviceModule, "ExtDeviceMode");
    DeviceMode = (PTDeviceModeFcn) GetProcAddress(DeviceModule, "DeviceMode");
    if ((DeviceMode == NULL) && (ExtDeviceMode == NULL))
      Status = PS_INVALIDDEVICE;
    if (ExtDeviceMode != NULL) {
      // Get default printer settings
      DevSettingSize = ExtDeviceMode(0, DeviceModule, &StubDevMode,
        Device, Port, &StubDevMode, NULL, 0);
      DevSettings = (PDEVMODE) new char[DevSettingSize];
      ExtDeviceMode(0, DeviceModule, DevSettings, Device, Port,
        DevSettings, NULL, DM_OUT_BUFFER);
    }
    else
      DevSettings = NULL;  // Cannot use local settings
  }
}

// Configure brings up a dialog as a child of the given window
// to configure the associated printer driver.

void TPrinter::Configure(PTWindowsObject Window)
{
  if (Status == PS_OK)
    if (ExtDeviceMode == NULL) // driver only supports DevMode
      // if DeviceMode == NULL, Status will != PS_OK
      DeviceMode(Window->HWindow, DeviceModule, Device, Port);
    else
      // Request driver to modify local copy of printer settings
      ExtDeviceMode(Window->HWindow, DeviceModule, DevSettings, Device,
        Port, DevSettings, NULL, DM_IN_BUFFER | DM_PROMPT | DM_OUT_BUFFER);
}

// Returns a device context for the associated printer, 0 if an
// error occurs or Status is != PS_OK

HDC TPrinter::GetDC()
{
  if (Status == PS_OK)
    return CreateDC(Driver, Device, Port, (LPSTR) (LPDEVMODE) DevSettings);
  else
    return 0;
}

static BOOL ProcessDlgMsg(LPMSG PMessage, PTApplication Application)
{
        if (Application->KBHandlerWnd && Application->KBHandlerWnd->HWindow)
           return IsDialogMessage(Application->KBHandlerWnd->HWindow, PMessage);
        else
           return FALSE;
}

static BOOL ProcessAccels(LPMSG PMessage, PTApplication Application)
{
        return Application->HAccTable &&
                 TranslateAccelerator(
                         Application->MainWindow->HWindow, Application->HAccTable, PMessage);
}

static BOOL ProcessMDIAccels(LPMSG PMessage, PTApplication Application)
{
        return (PTWindowsObject)(Application->MainWindow->GetClient()) &&
           TranslateMDISysAccel(
            ((PTWindowsObject)(Application->MainWindow->GetClient()))->HWindow, PMessage);
}

static BOOL ProcessAppMsg(LPMSG PMessage)
{
        PTApplication Application = GetApplicationObject();

        if ( Application->KBHandlerWnd )
           if ( Application->KBHandlerWnd->IsFlagSet(WB_MDICHILD) )
             return ProcessMDIAccels(PMessage, Application) ||
                    ProcessDlgMsg(PMessage, Application) ||
                    ProcessAccels(PMessage, Application);
           else
            return ProcessDlgMsg(PMessage, Application) ||
                   ProcessMDIAccels(PMessage, Application) ||
                   ProcessAccels(PMessage, Application);
        else
           return ProcessMDIAccels(PMessage, Application) ||
                  ProcessAccels(PMessage, Application);
}

// Abort procedure used for printing
BOOL FAR PASCAL _export AbortProc(HDC, short)
{
  MSG Msg;

  while (!UserAbort && PeekMessage(&Msg, NULL, NULL, NULL, PM_REMOVE))
    if (!ProcessAppMsg(&Msg)) {
      TranslateMessage(&Msg);
      DispatchMessage(&Msg);
    }
  return (!UserAbort);
}


// Static variables used by CalcBandingFlags and Print
static BOOL UseBandInfo;
static HDC PrnDC;
static WORD Flags;
static BOOL FirstBand;
static RECT BandRect;
static POINT PageSize;

void TPrinter::CalcBandingFlags()
{
  struct TBandInfoStruct {
    BOOL fGraphicsFlag;
    BOOL fTextFlag;
    RECT GraphicsRect;
  };

  TBandInfoStruct BandInfoRec;
  WORD pFlags = 0;

  // Calculate text verses graphics banding
  if (UseBandInfo) {
    Escape(PrnDC, BANDINFO, sizeof(TBandInfoStruct), NULL,
        (LPSTR) &BandInfoRec);
    if (BandInfoRec.fGraphicsFlag)
        pFlags = PF_GRAPHICS;
    if (BandInfoRec.fTextFlag)
        pFlags = pFlags | PF_TEXT;
    Flags = (Flags & !PF_BOTH) | pFlags;
  }
  else {
    // If a driver does not support BANDINFO the Microsoft
    //  Recommended way of determining text only bands is if
    //  the first band is the full page, all others are
    //  graphics only.  Otherwise it handles both.
    if ( (FirstBand) && (BandRect.left == 0)
       && (BandRect.top == 0)
       && (BandRect.right == PageSize.x)
       && (BandRect.bottom == PageSize.y) )
      Flags = PF_TEXT;
    else
      if ((Flags & PF_BOTH) == PF_TEXT)
        // All other bands are graphics only
        Flags = ((Flags & !PF_BOTH) | PF_GRAPHICS);
      else
        Flags = Flags | PF_BOTH;
  }
  FirstBand = FALSE;
}

BOOL TPrinter::Print(PTWindowsObject ParentWin, PTPrintout Printout)
{
  typedef BOOL (FAR PASCAL *PTAbortProc)( HDC Prn, short Code );


  BOOL Banding;
  PTAbortProc AbortProcInst;
  WORD PageNumber;

  BOOL result = FALSE; // Assume error occurred

  Error = 0;

  if ( Printout == NULL )
        return result;
  if ( ParentWin == NULL )
        return result;
  if ( Status != PS_OK )
  {
        Error = SP_ERROR;
        ReportError(Printout);
        return result;
  }

  PrnDC = GetDC();
  if ( PrnDC == 0 )
        return result;

  PTWindowsObject Dlg = GetApplicationObject()->MakeWindow(
                new TPrinterAbortDlg(ParentWin, "AbortDialog", Printout->Title, Device, Port) );

  if ( Dlg == NULL )
  {
    DeleteDC(PrnDC);
    return result;
  }

  EnableWindow(ParentWin->HWindow, FALSE);

  AbortProcInst = (PTAbortProc) MakeProcInstance( (FARPROC) AbortProc,
        GetApplicationObject()->hInstance);
  Escape(PrnDC, SETABORTPROC, 0, LPSTR(AbortProcInst), NULL);

  // Get the page size
  PageSize.x = GetDeviceCaps(PrnDC, HORZRES);
  PageSize.y = GetDeviceCaps(PrnDC, VERTRES);

  // Only band if the user requests banding and the printer
  //  supports banding
  Banding = ( Printout->Banding ) &&
        (GetDeviceCaps(PrnDC, RASTERCAPS) & RC_BANDING);
  if ( !Banding )
  {
    // Set the banding rectangle to full page
    BandRect.left = 0;
    BandRect.top = 0;
    BandRect.right = PageSize.x;
    BandRect.bottom = PageSize.y;
  }
  else
  {
    // Only use BANDINFO if supported (note: using Flags as a temporary)
    Flags = BANDINFO;
    // Escape(QUERYESCSUPPORT) returns nonzero for implemented
    // escape function, and zero otherwise.
    UseBandInfo =
      Escape(PrnDC, QUERYESCSUPPORT, sizeof(Flags), (LPSTR) &Flags, NULL);
  }

  Flags = PF_BOTH;

  Error = Escape(PrnDC, STARTDOC, strlen(Printout->Title),
    Printout->Title, NULL);
  PageNumber = 1;
  if ( Error > 0 )
  {
    do
    {
      if ( Banding )
      {
        FirstBand = TRUE;
        Error = Escape(PrnDC, NEXTBAND, 0, NULL, (LPSTR) &BandRect);
      }
      do
      {
        // Call the abort proc between bands or pages
        (*AbortProcInst)(PrnDC, 0);

        if ( Banding )
        {
          CalcBandingFlags();
          if ( (Printout->ForceAllBands) &&
             ( ( Flags & PF_BOTH ) == PF_TEXT ) )
                SetPixel(PrnDC, 0, 0, 0);
        }

        if ( Error > 0 )
        {
          Printout->PrintPage(PrnDC, PageNumber, PageSize, &BandRect, Flags);
          if ( Banding )
            Error = Escape(PrnDC, NEXTBAND, 0, NULL, (LPSTR) &BandRect);
        }
      } while ( (Error > 0) && (Banding) && (!IsRectEmpty(&BandRect)) );

      // NewFrame should only be called if not banding
      if ( (Error > 0) && (!Banding) )
        Error = Escape(PrnDC, NEWFRAME, 0, NULL, NULL);

      PageNumber++;
    } while ( (Error > 0) && (Printout->IsNextPage()) );

    // Tell GDI the document is finished
    if ( Error > 0 ) {
      if ( Banding && UserAbort )
        Escape(PrnDC, ABORTDOC, 0, NULL, NULL);
      else
        Escape(PrnDC, ENDDOC, 0, NULL, NULL);
    }
  }

  // Free allocated resources
  FreeProcInstance((FARPROC) AbortProcInst);
  EnableWindow(ParentWin->HWindow, TRUE);
  delete Dlg;
  DeleteDC(PrnDC);

  if ( Error & SP_NOTREPORTED )
    ReportError(Printout);

  result = (Error > 0) && (!UserAbort);

  UserAbort = FALSE;

  return result;
}

void TPrinter::Setup(PTWindowsObject Parent)
{
  GetApplicationObject()->ExecDialog(
                new TPrinterSetupDlg(Parent, "PrinterSetup", this));
}

void TPrinter::ReportError(PTPrintout Printout)
{
  char ErrorMsg[80];
  char ErrorCaption[80];
  char ErrorTemplate[40];
  char ErrorStr[40];
  WORD ErrorId;
  Pchar Title;

  switch (Error) {
    case SP_APPABORT:
      ErrorId = SR_PRNCANCEL;
      break;
    case SP_ERROR:
      ErrorId = SR_GENERROR;
      break;
    case SP_OUTOFDISK:
      ErrorId = SR_OUTOFDISK;
      break;
    case SP_OUTOFMEMORY:
      ErrorId = SR_OUTOFMEMORY;
      break;
    case SP_USERABORT:
      ErrorId = SR_PRNMGRABORT;
      break;
    default:
      return;
  }

        HINSTANCE hInstance = GetApplicationObject()->hInstance;

  LoadString(hInstance, SR_ERRORTEMPLATE, ErrorTemplate,
    sizeof(ErrorTemplate));
  LoadString(hInstance, ErrorId, ErrorStr, sizeof(ErrorStr));
  Title = Printout->Title;
  LPSTR C[1];
  C[0] = Title;
  wvsprintf(ErrorMsg, ErrorTemplate, (LPSTR) C);
  LoadString(hInstance, SR_ERRORCAPTION, ErrorCaption,
    sizeof(ErrorCaption));
  MessageBox(0, ErrorMsg, ErrorCaption, MB_OK | MB_ICONSTOP);
}


// TPrinterSetupDlg

// TPrinterSetupDlg assumes the template passed has a ComboBox with
// the control ID of 100 and a "Setup" button with id 101

const pdStrWidth = 80;

_CLASSDEF(TTransferBuffer)
struct TTransferBuffer {
    PTMyComboBoxData ComboBoxData;

    TTransferBuffer()
    {
        ComboBoxData = new TMyComboBoxData;
    }
    ~TTransferBuffer()
    {
        delete ComboBoxData;
    }
    int insert( Pchar ComboBoxString )
    {
        return ComboBoxData->Strings->insert( ComboBoxString );
    }
    // indexOf returns the index of the entry in ComboBoxData
    // that has a an identical copy of string; note that this
    // is different from TNSCollection::indexOf which looks
    // for the actual pointer, not a copy.
    static Boolean isCopy( Pvoid s1, Pvoid s2 )
    {
        return (strcmp( (Pchar) s1, (Pchar) s2 ) ) ?
                False :
                True;
    }
    int indexOf( Pchar string )
    {
        PTNSCollection Collection = ComboBoxData->Strings;
        Pchar string2 = (Pchar) Collection->firstThat( isCopy, string );
        return Collection->indexOf( string2 );
    }
};

struct TDeviceRec
{
    Pchar Driver, Device, Port;
};
typedef TDeviceRec *PTDeviceRec;

_CLASSDEF(TDeviceCollection)
class TDeviceCollection : public TNSCollection
{
public:
        TDeviceCollection( ccIndex aLimit, ccIndex aDelta )
                : TNSCollection( aLimit, aDelta ) {}
        virtual void freeItem( Pvoid item );
};

void TDeviceCollection::freeItem( Pvoid item )
{
  PTDeviceRec p = (PTDeviceRec) item;

  delete p->Driver;
  delete p->Device;
  delete p->Port;
  delete p;
}

static void FormDriverStr( Pchar DriverStr, int MaxLen, Pchar Device,
        Pchar Port)
{
    strncpy(DriverStr, Device, MaxLen);
    LoadString(GetApplicationObject()->hInstance, SR_ON,
        (DriverStr + strlen(DriverStr)), MaxLen - strlen(DriverStr) - 1);
    strncat(DriverStr, Port, MaxLen - strlen(DriverStr));
}

TPrinterSetupDlg::TPrinterSetupDlg( PTWindowsObject AParent,
  LPSTR TemplateName, PTPrinter APrinter)
  : TDialog(AParent, TemplateName)
{
  Pchar Devices;                            // List of devices from the
                                            //  WIN.INI
  Pchar Device;                             // Current device
  int DevicesSize;                          // Amount of bytes allocated
                                            //  to store 'devices'
  Pchar Driver;                             // Name of the driver for the
                                            //  device
  Pchar Port;                               // Name of the port for the
                                            //  device
  char DriverLine[pdStrWidth];              // Device line from WIN.INI
  Pchar LineCur;                            // FetchStr pointer into
                                            // DriverLine
  char DriverStr[pdStrWidth];               // Text being built for display
  Pchar StrCur;                             // Temp pointer used for copying
                                            //  Port into the line
  int StrCurSize;                           // Room left in DriverStr to
                                            //  copy Port
  PTDeviceRec DevRec;                       // Record pointer built to
                                            //  store in DeviceCollection

  new TMyComboBox(this, ID_COMBO, pdStrWidth);

  PTTransferBuffer TransBuff = new TTransferBuffer;
  TransferBuffer = TransBuff;

  Printer = APrinter;
  DeviceCollection = new TDeviceCollection(5, 5);

  DevicesSize = DEFAULT_SAFETY_POOL_SIZE / 2;
  Devices = new char[DevicesSize];

  // Save initial values of printer for Cancel
  OldDevice = newstrdup(Printer->Device);
  OldDriver = newstrdup(Printer->Driver);
  OldPort = newstrdup(Printer->Port);

  // Get a list of devices from WIN.INI.  Stored in the form of
  //  <device 1>\0<device 2>\0...<driver n>\0\0
  GetProfileString("devices", NULL, "", Devices, DevicesSize);

  Device = Devices;
  while ( *Device != '\0' )
  {
      GetProfileString("devices", Device, "", DriverLine,
        sizeof(DriverLine) - 1);

      FormDriverStr(DriverStr, sizeof(DriverStr) - 1,Device, "");

      // Get driver portion of DeviceLine
      LineCur = DriverLine;
      Driver = FetchStr(LineCur);

      // Copy the port information from the line
      /*   This code is complicated because the device line is of
          the form:
           <device name> = <driver name> , <port> { , <port> }
          where port (in {}) can be repeated. */

      StrCur = ( DriverStr + strlen(DriverStr) );
      StrCurSize = sizeof(DriverStr) - strlen(DriverStr) - 1;
      Port = FetchStr(LineCur);
      while ( *Port != '\0' )
      {
        strncpy(StrCur, Port, StrCurSize);
        Pchar tempStr = newstrdup(DriverStr);
        TransBuff->insert(tempStr);
        DevRec = new TDeviceRec;
        DevRec->Device = newstrdup(Device);
        DevRec->Driver = newstrdup(Driver);
        DevRec->Port = newstrdup(Port);
        DeviceCollection->atInsert(TransBuff->indexOf(tempStr), DevRec);
        Port = FetchStr(LineCur);
      }
      Device += (strlen(Device) + 1);
    }
    delete [] Devices;

    // Set the current selection to Printer's current device
    TransBuff->ComboBoxData->Selection = new char[pdStrWidth];
    if ( *(Printer->Device) != '\0' )
        FormDriverStr(TransBuff->ComboBoxData->Selection, pdStrWidth, Printer->Device, Printer->Port);
    else
        TransBuff->ComboBoxData->Selection = NULL;
}

TPrinterSetupDlg::~TPrinterSetupDlg( void )
{
  delete OldDevice;
  delete OldDriver;
  delete OldPort;
  delete DeviceCollection;
  delete (PTTransferBuffer) TransferBuffer;
  TransferBuffer = NULL;
}

void TPrinterSetupDlg::TransferData(WORD TransferFlag)
{
  TDialog::TransferData(TransferFlag);
  if ( TransferFlag == TF_GETDATA )
  {
    PTTransferBuffer TransBuff = (PTTransferBuffer) TransferBuffer;
    if ( ( TransBuff->ComboBoxData->Selection ) &&
         ( *(TransBuff->ComboBoxData->Selection) != '\0' ) )
    {
        // Use the current selection to set Printer
        PTDeviceRec DevRec = (PTDeviceRec)(DeviceCollection->
                at(TransBuff->indexOf(
                        TransBuff->ComboBoxData->Selection) ) );
        // Set the printer to the new device
        Printer->SetDevice(DevRec->Device,
                DevRec->Driver,
                DevRec->Port);
    }
  }
}

void TPrinterSetupDlg::IDSetup(RTMessage)
{
  TransferData(TF_GETDATA);
  Printer->Configure(this);
}

void TPrinterSetupDlg::Cancel(RTMessage Msg)
{
  TDialog::Cancel(Msg);
  // Restore old settings, just in case the user pressed the Setup button
  if ( OldDriver == NULL )
        Printer->ClearDevice();
  else
        Printer->SetDevice(OldDevice, OldDriver, OldPort);
}
