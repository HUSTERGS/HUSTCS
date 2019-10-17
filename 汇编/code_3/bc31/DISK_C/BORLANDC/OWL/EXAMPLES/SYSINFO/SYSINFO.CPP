// ObjectWindows - (C) Copyright 1992 by Borland International

#include <owl.h>
#include <dialog.h>
#include <static.h>

#include <dos.h>
#include <string.h>

#include "sysinfo.h"

class TSysInfoApp : public TApplication
{
public:
	TSysInfoApp( LPSTR name, HINSTANCE hInstance,
		  HINSTANCE hPrevInstance, LPSTR lpCmd,
		  int nCmdShow)
	        : TApplication(name, hInstance,
			       hPrevInstance, lpCmd, nCmdShow) {};
	virtual void InitMainWindow( void );
};

struct SysInfoRecord
{
	char InstanceNumber[ 31 ];
	char WindowsVersion[ 31 ];
	char OperationMode[ 31 ];
	char CPUType[ 31 ];
	char CoProcessor[ 31 ];
	char Global[ 31 ];
	char VersionDos[ 31 ];
};

class TSysInfoWindow : public TDialog
{
	SysInfoRecord TransferRecord;
public:
	TSysInfoWindow( PTWindowsObject aParent, LPSTR aTitle );
	void GetSysInformation( void );
	void InitChildren( void );
};

typedef TSysInfoWindow* pSysInfoWindow;

TSysInfoWindow::TSysInfoWindow( PTWindowsObject aParent, LPSTR aTitle ) :
	TDialog( aParent, aTitle )
{
	InitChildren();
	GetSysInformation();
}

void TSysInfoWindow::InitChildren( void )
{
      PTStatic TmpStatic;

	TmpStatic = new TStatic( this, ID_INSTANCENUMBER, sizeof( TransferRecord.InstanceNumber ) );
      TmpStatic->EnableTransfer();

	TmpStatic = new TStatic( this, ID_WINDOWSVERSION, sizeof( TransferRecord.WindowsVersion ) );
      TmpStatic->EnableTransfer();

	TmpStatic = new TStatic( this, ID_OPERATIONMODE, sizeof( TransferRecord.OperationMode ) );
      TmpStatic->EnableTransfer();

	TmpStatic = new TStatic( this, ID_CPUTYPE, sizeof( TransferRecord.CPUType ) );
      TmpStatic->EnableTransfer();

	TmpStatic = new TStatic( this, ID_COPROCESSOR, sizeof( TransferRecord.CoProcessor ) );
      TmpStatic->EnableTransfer();

	TmpStatic = new TStatic( this, ID_GLOBAL, sizeof( TransferRecord.Global ) );
      TmpStatic->EnableTransfer();

	TmpStatic = new TStatic( this, ID_VERSIONDOS, sizeof( TransferRecord.VersionDos ) );
      TmpStatic->EnableTransfer();
}

void TSysInfoWindow::GetSysInformation( void )
{
	DWORD SysFlags;
	char tempstr[ 31 ];
	WORD ArgList[ 2 ];
	WORD Ver;
	DWORD Available;
	HINSTANCE hInstance = GetApplication()->hInstance;

	SysFlags = GetWinFlags();

	ArgList[ 0 ] = GetModuleUsage( hInstance );
	wvsprintf( (LPSTR) TransferRecord.InstanceNumber, (LPSTR) "%d", (LPSTR) ArgList );

	Ver = GetVersion();
	ArgList[0] = (WORD) LOBYTE(LOWORD( Ver ));
	ArgList[1] = (WORD) HIBYTE(LOWORD( Ver ));
	wvsprintf( (LPSTR) TransferRecord.WindowsVersion, (LPSTR) "%d.%d", (LPSTR) ArgList );

	if ( SysFlags & WF_ENHANCED )
		LoadString( hInstance, ID_ENHANCED, tempstr, sizeof( tempstr ) );
	else if ( SysFlags & WF_STANDARD )
		LoadString( hInstance, ID_STANDARD, tempstr, sizeof( tempstr ) );
	else if ( SysFlags & WF_PMODE )
		LoadString( hInstance, ID_REAL, tempstr, sizeof( tempstr ) );
	else
		LoadString( hInstance, ID_UNKNOWN, tempstr, sizeof( tempstr ) );
	strcpy( TransferRecord.OperationMode, tempstr );

	if ( SysFlags & WF_CPU086 )
		LoadString( hInstance, ID_CPU8086, tempstr, sizeof( tempstr ) );
	else if ( SysFlags & WF_CPU186 )
		LoadString( hInstance, ID_CPU80186, tempstr, sizeof( tempstr ) );
	else if ( SysFlags & WF_CPU286 )
		LoadString( hInstance, ID_CPU80286, tempstr, sizeof( tempstr ) );
	else if ( SysFlags & WF_CPU386 )
		LoadString( hInstance, ID_CPU80386, tempstr, sizeof( tempstr ) );
	else if ( SysFlags & WF_CPU486 )
		LoadString( hInstance, ID_CPU80486, tempstr, sizeof( tempstr ) );
	else
		LoadString( hInstance, ID_UNKNOWN, tempstr, sizeof( tempstr ) );
	strcpy( TransferRecord.CPUType, tempstr );

	if ( SysFlags & WF_80x87 )
		LoadString( hInstance, ID_YES, tempstr, sizeof( tempstr ) );
	else
		LoadString( hInstance, ID_NO, tempstr, sizeof( tempstr ) );
	strcpy( TransferRecord.CoProcessor, tempstr );

	Available = GetFreeSpace( 0 ) / 1024;
	ArgList[0] = LOWORD( Available );
	ArgList[1] = HIWORD( Available );
	wvsprintf( (LPSTR) TransferRecord.Global, (LPSTR) "%lu", (LPSTR) ArgList );

	ArgList[0] = _osmajor;
	ArgList[1] = _osminor;
	wvsprintf( (LPSTR) TransferRecord.VersionDos, (LPSTR) "%d.%d", (LPSTR) ArgList );

	TransferBuffer = (LPSTR) &TransferRecord;
}

void TSysInfoApp::InitMainWindow( void )
{
	MainWindow = new TSysInfoWindow( NULL, (LPSTR) "SysInfo" );
}

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
		   LPSTR lpCmd, int nCmdShow)
{
	TSysInfoApp SysInfoApp( "SysInfo", hInstance, hPrevInstance,
		lpCmd, nCmdShow);
	SysInfoApp.Run();
	return ( SysInfoApp.Status );
}
