// ObjectWindows - (C) Copyright 1992 by Borland International

/* printer.h */

#ifndef __PRINTER_H
#define __PRINTER_H

// OWL headers
#include <owl.h>
#include <objstrm.h>
#include <owldefs.h>
#include <tcollect.h>

#ifdef __cplusplus
extern "C" {
#endif

// Windows header
#include <drivinit.h>

// Standard header
#include <string.h>

#ifdef __cplusplus
}
#endif


#define PS_OK 0
#define PS_INVALIDDEVICE -1  // Device parameters (to set device) invalid
#define PS_UNASSOCIATED -2   // Object not associated with a printer

// TPrintout banding flags

#define PF_GRAPHICS 0x01     // Current band only accepts graphics
#define PF_TEXT 0x02         // Current band only accepts text
#define PF_BOTH 0x03         // Current band accepts both text and graphics

/*
TPrintout represents the physical printed document which is to
sent to a printer to be printed. TPrintout does the rendering of
the document onto the printer. For every document, or document
type, a corresponding TPrintout class should be created.
*/

_CLASSDEF(TPrintout)
class TPrintout: public TStreamable
{
protected:
  Pchar Title;
  BOOL Banding;
  BOOL ForceAllBands;
public:
  TPrintout(Pchar ATitle);
  virtual ~TPrintout();
  virtual void PrintPage(HDC DC, WORD Page, POINT Size, LPRECT Rect, WORD Flags) = 0;
  virtual BOOL IsNextPage();

  // The following are pure virtual functions in TStreamable
  // and so must be redefined here to make this an instance class.
  // These should be redefined if you actually want your TPrintout
  // class to be streamable.
private:
  virtual const Pchar streamableName() const
  {
	return "TPrintout";
  }
protected:
  virtual Pvoid read(Ripstream)
  {
	return this;
  }
  virtual void write(Ropstream)
  {}

  friend class _CLASSTYPE TPrinter;
};

/*
TPrinter represent the physical printer device.  To print a
TPrintout, send the TPrintout to the TPrinter's Print function.
*/

// DeviceMode functions have no template in windows.h or drivinit.h.
typedef WORD (FAR PASCAL *PTDeviceModeFcn)(HWND, HANDLE, LPSTR, LPSTR);

_CLASSDEF(TPrinter)
class TPrinter: public TStreamable
{
protected:
  Pchar Device, Driver, Port;    // Printer device description
  int Status;                    // Device status, error is != PS_OK
  int Error;                     // < 0 if error occurred during print
	HINSTANCE DeviceModule;        // Handle to printer driver module
  PTDeviceModeFcn DeviceMode;    // Function pointer to DevMode
  LPFNDEVMODE ExtDeviceMode;     // Function pointer to ExtDevMode
  PDEVMODE DevSettings;          // Local copy of printer settings
  int DevSettingSize;            // Size of the printer settings
  void GetDefaultPrinter();

public:
  TPrinter();
  virtual ~TPrinter();
  void ClearDevice();
  void Configure(PTWindowsObject Window);
  virtual HDC GetDC();
  virtual void ReportError(PTPrintout Printout);
  void SetDevice(Pchar ADevice, Pchar ADriver, Pchar APort);
  void Setup(PTWindowsObject Parent);
  BOOL Print(PTWindowsObject ParentWin, PTPrintout Printout);
private:
  // Private member used by Print
  void CalcBandingFlags();

  // The following are pure virtual functions in TStreamable
  // and so must be redefined here to make this an instance class.
private:
  virtual const Pchar streamableName() const
  {
	return "TPrinter";
  }
protected:
  virtual Pvoid read(Ripstream)
  {
	return this;
  }
  virtual void write(Ropstream)
  {}

  friend class _CLASSTYPE TPrinterSetupDlg;
};

/*
TPrinterSetupDlg is a dialog to modify which printer a TPrinter
object is attached to. It displays all the active printers
in the system allowing the user to select the desired printer.
The dialog also allows the user to call up the printer's
"setup" dialog for further configuration of the printer.
*/

#define ID_COMBO 100
#define ID_SETUP 101

_CLASSDEF(TPrinterSetupDlg)
class TPrinterSetupDlg: public TDialog
{
protected:
  PTPrinter Printer;
public:
  TPrinterSetupDlg(PTWindowsObject AParent, LPSTR TemplateName, PTPrinter APrinter);
  virtual ~TPrinterSetupDlg();
  virtual void TransferData(WORD TransferFlag);
  virtual void IDSetup(RTMessage)
    = [ID_FIRST + ID_SETUP];
  virtual void Cancel(RTMessage)
    = [ID_FIRST + IDCANCEL];
private:
  Pchar OldDevice, OldDriver, OldPort;
  PTNSCollection DeviceCollection;
};

#define ID_TITLE 101
#define ID_DEVICE 102
#define ID_PORT 103

_CLASSDEF(TPrinterAbortDlg)
class TPrinterAbortDlg: public TDialog
{
public:
  TPrinterAbortDlg(PTWindowsObject AParent, Pchar Template,
    Pchar Title, Pchar Device, Pchar Port);
  virtual void SetupWindow();
  virtual void WMCommand(RTMessage)
    = [WM_FIRST + WM_COMMAND];
};

#endif
