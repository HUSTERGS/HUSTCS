/*---------------------------------------------------------*/
/*                                                         */
/*   Turbo Vision 1.0                                      */
/*   Turbo Vision BGI Support Demo                         */
/*   Copyright (c) 1991 by Borland International           */
/*                                                         */
/*---------------------------------------------------------*/

#define Uses_TKeys
#define Uses_TApplication
#define Uses_TEvent
#define Uses_TRect
#define Uses_TDialog
#define Uses_TButton
#define Uses_TMenuBar
#define Uses_TSubMenu
#define Uses_TMenuItem
#define Uses_TStatusLine
#define Uses_TStatusItem
#define Uses_TStatusDef
#define Uses_TDeskTop
#define Uses_MsgBox
#define Uses_TChDirDialog
#define Uses_THistory
#define Uses_TWindow
#define Uses_TInputLine
#include <tv.h>

#include "Tvbgi.h"
#include <stdlib.h>
#include <graphics.h>
#include <string.h>
#include <strstrea.h>

TBGIApp::TBGIApp() :
    TProgInit( &TBGIApp::initStatusLine,
	       &TBGIApp::initMenuBar,
	       &TBGIApp::initDeskTop )
{
    fexpand(pathToDrivers);
    bgiPath = new char[sizeof(pathToDrivers)];
    strcpy(bgiPath, pathToDrivers);
    appDriver = DETECT;
    appMode = 0;
    if (graphAppInit(appDriver, appMode, bgiPath, True) == False)
	messageBox("Cannot load graphics driver.", mfError | mfOKButton);
}

TBGIApp::~TBGIApp()
{
    graphAppDone();
	delete bgiPath;
}

void TBGIApp::newWin()
{
    static ushort winNum = 0;
    TWindow *p;

    TRect r(deskTop->getExtent());
    r = TRect( winNum % (deskTop->size.y-1),
	           winNum % (deskTop->size.y-1),
	           deskTop->size.x,
	           deskTop->size.y);

    char msgStr[12];
    ostrstream os( msgStr, 12 );
    os << "Window " << winNum << ends;
    p = new TWindow( r, msgStr, 0 );
    p->options |= ofTileable;
    deskTop->insert( validView(p) );
    winNum++;
}

// Draw random polygons with random fill styles on the screen }

void TBGIApp::doGraphics()
{
    const int maxPts = 5;
    const int CLIP_ON = 1;
    typedef TPoint PolygonType[maxPts];
    char errorMsg[MAXSIZE];
    TEvent event;
    PolygonType poly;
    ushort i, color;
    ushort maxX, maxY;

    suspend();

    if (graphicsStart() == False)
	{
	strcpy(errorMsg,grapherrormsg(graphresult()));
	strcat( errorMsg,"." );
	messageBox(errorMsg, mfError | mfOKButton);
	}
    else
	{
	maxX = getmaxx();
	maxY = getmaxy();
	outtextxy(0, (maxY - textheight("M")),
	    "Press any key to return...");
	setviewport(0, 0, maxX - 1, (maxY - (textheight("M") + 5)), CLIP_ON);
	do {
	    color = random(getmaxcolor()) + 1;
	    setfillstyle(random(11) + 1, color);
	    setcolor(color);
	    for(i = 0; i < maxPts; ++i)
		{
		poly[i].x = random(maxX);
		poly[i].y = random(maxY);
		}
	    fillpoly(maxPts, (int *) poly);
	    event.getKeyEvent();
	   } while (event.what == evNothing);
	graphicsStop();
	}

    resume();
}

void TBGIApp::setBGIPath()
{
    char s[MAXPATH];

    TDialog *d = new TDialog(TRect(0,0,35,8), "Path to BGI Files");
    d->options |= ofCentered;

    // Buttons
    d->insert(new TButton( TRect(23,5,33,7), "Cancel", cmCancel, bfNormal) );
    d->insert(new TButton( TRect(12,5,22,7),"O~K~", cmOK, bfDefault) );

    // Input line, history list and label 
    TInputLine *pathInput = new TInputLine( TRect(3,3,30,4), 68 );
    d->insert( pathInput );
    d->insert( new THistory(TRect(30,3,33,4), pathInput, hlSetBGIPath) );

    fexpand(bgiPath);
    strcpy(s,bgiPath);
    d->setData(s);
    d = (TDialog *) validView(d);
    if (d != NULL)
	{
	if (deskTop->execView(d) == cmOK)
	    {
	    d->getData(s);
	    delete bgiPath;
	    if ( (strlen(s) > 0) && (s[strlen(s)-1] != '\\') )
		strcat(s,"\\");
	    bgiPath = new char [sizeof(s)];
	    strcpy(bgiPath, s);
	    if ( graphAppInit(appDriver, appMode, bgiPath, True) == False )
		messageBox("Cannot load graphics driver.", mfError | mfOKButton);
	    }
	destroy( d );
	}
}

void TBGIApp::changeDir()
{
    TView *p;

    p = validView(new TChDirDialog(0, hlChangeDir));
    if (p != NULL)
	{
	deskTop->execView(p);
	destroy( p );
	}
}

void TBGIApp::tile()
{
    TRect r(deskTop->getExtent());
    deskTop->tile(r);
}

void TBGIApp::cascade()
{
    TRect r(deskTop->getExtent());
    deskTop->cascade(r);
}

void TBGIApp::handleEvent(TEvent& event)
{
    TApplication::handleEvent(event);
    switch (event.what)
	{
	case evCommand:
	switch (event.message.command)
	    {
	    case cmNewWin:
		newWin();
		break;
	    case cmChangeDir:
		changeDir();
		break;
	    case cmSetBGIPath:
		setBGIPath();
		break;
	    case cmDoGraphics:
		doGraphics();
		break;
	    case cmTile:
		tile();
		break;
	    case cmCascade:
		cascade();
		break;
	    default :
		return;

	    }
	break;
	default:
	    return;
	}
    clearEvent(event);
}

TMenuBar *TBGIApp::initMenuBar(TRect r)
{

    r.b.y = r.a.y + 1;

    return new TMenuBar( r,
       *new TSubMenu( "~T~est", hcNoContext ) +
	//*new TMenuItem( "~B~GI settings...", 0, kbNoKey, hcNoContext ) +
	*new TMenuItem( "~G~raph", cmDoGraphics, kbAltF5, hcNoContext, "Alt-F5" ) +
	*new TMenuItem( "~S~et BGI path...", cmSetBGIPath,kbNoKey, hcNoContext ) +
	     newLine() +
	*new TMenuItem( "~C~hange dir...", cmChangeDir, kbNoKey, hcNoContext ) +
	*new TMenuItem( "E~x~it", cmQuit, kbAltX, hcNoContext, "Alt-X" ) +
	*new TSubMenu( "~W~indows", hcNoContext ) +
	*new TMenuItem( "~S~ize/move", cmResize, kbCtrlF5, hcNoContext, "Ctrl-F5" ) +
	*new TMenuItem( "~Z~oom", cmZoom, kbF5, hcNoContext, "F5" ) +
	*new TMenuItem( "~T~ile", cmTile, kbNoKey, hcNoContext ) +
	*new TMenuItem( "C~a~scade", cmCascade, kbNoKey, hcNoContext ) +
	*new TMenuItem( "~N~ext", cmNext, kbF6, hcNoContext, "F6" ) +
	*new TMenuItem( "~P~revious", cmPrev, kbShiftF6, hcNoContext, "Shift-F6" ) +
	*new TMenuItem( "~C~lose",cmClose, kbAltF3, hcNoContext, "Alt-F3" ) +
	     newLine() +
	*new TMenuItem( "Add ~w~indow", cmNewWin, kbF4, hcNoContext, "F4" )
	);

}

TStatusLine *TBGIApp::initStatusLine(TRect r)
{
    r.a.y = r.b.y - 1;
    return new TStatusLine( r,
	*new TStatusDef( 0, 0xFFFF ) +
	    *new TStatusItem( "~Alt-X~ Exit", kbAltX, cmQuit ) +
	    *new TStatusItem( "~Alt-F5~ Graph", kbAltF5, cmDoGraphics ) +
	    *new TStatusItem( 0, kbF10, cmMenu ) +
	    *new TStatusItem( 0, kbAltF3, cmClose ) +
	    *new TStatusItem( 0, kbF5, cmZoom ) +
	    *new TStatusItem( 0, kbCtrlF5, cmResize ) +
	    *new TStatusItem("", kbF6, cmNext)
	    );
}

void TBGIApp::outOfMemory()
{
    messageBox("Out of memory.", mfError | mfOKButton);
}


int main()
{
    TBGIApp bgiApp;

    bgiApp.run();
    return 0;
}
