/*---------------------------------------------------------*/
/*                                                         */
/*   Turbo Vision 1.0                                      */
/*   TVGUID16 Demo Source File                             */
/*   Copyright (c) 1991 by Borland International           */
/*                                                         */
/*---------------------------------------------------------*/

// same as tvguid15 except for saving and restoring dialog contents
// modify TMyApp::newDialog

#include <stdlib.h>             // for exit(), random()
#include <iostream.h>
#include <fstream.h>            // for ifstream
#include <stdio.h>              // for puts() etc
#include <string.h>             // for strlen etc
#include <ctype.h>

#define Uses_TEventQueue
#define Uses_TEvent
#define Uses_TProgram
#define Uses_TApplication
#define Uses_TKeys
#define Uses_TRect
#define Uses_TMenuBar
#define Uses_TSubMenu
#define Uses_TMenuItem
#define Uses_TStatusLine
#define Uses_TStatusItem
#define Uses_TStatusDef
#define Uses_TDeskTop
#define Uses_TView
#define Uses_TWindow
#define Uses_TFrame
#define Uses_TScroller
#define Uses_TScrollBar
#define Uses_TDialog
#define Uses_TButton
#define Uses_TSItem
#define Uses_TCheckBoxes
#define Uses_TRadioButtons
#define Uses_TLabel
#define Uses_TInputLine
#include <tv.h>

const int cmMyFileOpen = 200;   // assign new command values
const int cmMyNewWin   = 201;
const int cmNewDialog  = 202;

struct DialogData
{
    ushort checkBoxData;
    ushort radioButtonData;
    char inputLineData[128];
};

DialogData *demoDialogData;

// we'll save dialog box data in above struct

const char *fileToRead  = "tvguid16.cpp";
const int maxLineLength = maxViewWidth+1;
const int maxLines      = 100;
char *lines[maxLines];
int lineCount = 0;
static short winNumber  = 0;    // initialize window number

class TMyApp : public TApplication
{

public:
    TMyApp();
    ~TMyApp();
    static TStatusLine *initStatusLine( TRect r );
    static TMenuBar *initMenuBar( TRect r );
    virtual void handleEvent( TEvent& event);
    void newWindow();
    void newDialog();
};

class TInterior : public TScroller
{

public:

    TInterior( const TRect& bounds, TScrollBar *aHScrollBar,
           TScrollBar *aVScrollBar );   // constructor
    virtual void draw();                // override TView::draw
};

class TDemoWindow : public TWindow      // define a new window class
{

public:

    TDemoWindow( const TRect& bounds, const char *aTitle, short aNumber );
    TInterior *makeInterior( const TRect& r, Boolean left );
    virtual void sizeLimits( TPoint& minP, TPoint& maxP );
    // override TWindow::sizeLimits

private:

    TInterior *lInterior, *rInterior;

};

void readFile( const char *fileName )
{
    ifstream fileToView( fileName );
    if( !fileToView )
        {
        cout << "Invalid file name..." << endl;
        exit( 1 );
        }
    else
        {
        char buf[maxLineLength];
        while( lineCount < maxLines &&
               fileToView.getline( buf, maxLineLength ) != 0 )
            {
            lines[lineCount] = newStr( buf );
            lineCount++;
            }
        }
}

void deleteFile()
{
    for( int i = 0; i < lineCount; i++ )
        delete lines[i];
}

TInterior::TInterior( const TRect& bounds, TScrollBar *aHScrollBar,
              TScrollBar *aVScrollBar ) :
       TScroller( bounds, aHScrollBar, aVScrollBar )
{
    options = options | ofFramed;
    setLimit( maxLineLength, lineCount );
}

void TInterior::draw()       // modified for scroller
{
    ushort color = getColor(0x0301);
    for( int i = 0; i < size.y; i++ )
        // for each line:
        {
        TDrawBuffer b;
        b.moveChar( 0, ' ', color, size.x );
        // fill line buffer with spaces
        int j = delta.y + i;       // delta is scroller offset
        if( j < lineCount && lines[j] != 0 )
            {
            char s[maxLineLength];
            if( delta.x > strlen(lines[j] ) )
                s[0] = EOS;
            else
                {
                strncpy( s, lines[j]+delta.x, size.x );
                s[size.x] = EOS;
                }
            b.moveCStr( 0, s, color );
            }
        writeLine( 0, i, size.x, 1, b);
        }

}

// modified from tvguid08:
TDemoWindow::TDemoWindow( const TRect& bounds, const char *aTitle,
              short aNumber) :
         TWindow( bounds, aTitle, aNumber),
         TWindowInit( &TDemoWindow::initFrame )
{
    TRect lbounds = getExtent();
    TRect r( lbounds.a.x, lbounds.a.y, lbounds.b.x/2+1, lbounds.b.y );
    lInterior = makeInterior( r, True );
    lInterior->growMode = gfGrowHiY;
    insert( lInterior );
    // creates left-side scrollable interior and inserts into window
    r = TRect( lbounds.b.x/2, lbounds.a.y, lbounds.b.x, lbounds.b.y );
    rInterior = makeInterior( r, False );
    rInterior->growMode = gfGrowHiX | gfGrowHiY;
    insert( rInterior );
    // likewise for right-side scroller
}

TInterior *TDemoWindow::makeInterior( const TRect& bounds, Boolean left )
{
    TRect r = TRect( bounds.b.x-1, bounds.a.y+1, bounds.b.x, bounds.b.y-1 );
    TScrollBar *vScrollBar = new TScrollBar( r );
    if( vScrollBar == 0 )
        {
        cout << "vScrollbar init error" << endl;
        exit(1);
        }
        // production code would display error dialog box
    vScrollBar->options |= ofPostProcess;
    if( left )
        vScrollBar->growMode = gfGrowHiY;
    insert( vScrollBar );

    r = TRect( bounds.a.x+2, bounds.b.y-1, bounds.b.x-2, bounds.b.y );
    TScrollBar *hScrollBar = new TScrollBar( r );
    if( hScrollBar == 0 )
        {
        cout << "hScrollbar init error" << endl;
        exit(1);
        }
    hScrollBar->options |= ofPostProcess;
    if( left )
        hScrollBar->growMode = (gfGrowHiY | gfGrowLoY);
    insert( hScrollBar );

    r = bounds;
    r.grow( -1, -1 );
    return new TInterior( r, hScrollBar, vScrollBar );
}

void TDemoWindow::sizeLimits( TPoint& minP, TPoint& maxP )
{
    TWindow::sizeLimits( minP, maxP );
    minP.x = lInterior->size.x+9;
}

TMyApp::TMyApp() :
    TProgInit( &TMyApp::initStatusLine,
               &TMyApp::initMenuBar,
               &TMyApp::initDeskTop
             )
{
    // new for tvguid16: set up initial dialog data
    demoDialogData = new DialogData;
    demoDialogData->checkBoxData = 1;
    demoDialogData->radioButtonData = 2;
    strcpy( demoDialogData->inputLineData, "Phone Mum!" );
}

TMyApp::~TMyApp()
{

   delete demoDialogData;

}

void TMyApp::handleEvent(TEvent& event)
{
    TApplication::handleEvent(event);
    if( event.what == evCommand )
        {
        switch( event.message.command )
            {
            case cmMyNewWin:
                newWindow();
                break;
            case cmNewDialog:
                newDialog();
                break;
            default:
                return;
            }
        clearEvent( event );            // clear event after handling
        }
}

TMenuBar *TMyApp::initMenuBar( TRect r )
{
    r.b.y = r.a.y + 1;    // set bottom line 1 line below top line
    return new TMenuBar( r,
        *new TSubMenu( "~F~ile", kbAltF )+
            *new TMenuItem( "~O~pen", cmMyFileOpen, kbF3, hcNoContext, "F3" )+
            *new TMenuItem( "~N~ew",  cmMyNewWin,   kbF4, hcNoContext, "F4" )+
            newLine()+
            *new TMenuItem( "E~x~it", cmQuit, cmQuit, hcNoContext, "Alt-X" )+
        *new TSubMenu( "~W~indow", kbAltW )+
            *new TMenuItem( "~N~ext", cmNext,     kbF6, hcNoContext, "F6" )+
            *new TMenuItem( "~Z~oom", cmZoom,     kbF5, hcNoContext, "F5" )+
            *new TMenuItem( "~D~ialog", cmNewDialog, kbF2, hcNoContext, "F2" )
            // new dialog menu added here
        );
}

TStatusLine *TMyApp::initStatusLine( TRect r )
{
    r.a.y = r.b.y - 1;     // move top to 1 line above bottom
    return new TStatusLine( r,
        *new TStatusDef( 0, 0xFFFF ) +
        // set range of help contexts
            *new TStatusItem( 0, kbF10, cmMenu ) +
            // define an item
            *new TStatusItem( "~Alt-X~ Exit", kbAltX, cmQuit ) +
            // and another one
            *new TStatusItem( "~Alt-F3~ Close", kbAltF3, cmClose )
            // and another one
        );
}

void TMyApp::newWindow()
{
    TRect r( 0, 0, 45, 13 );            // set initial size and position
    r.move( random(34), random(11) );   // randomly move around screen
    TDemoWindow *window = new TDemoWindow ( r, "Demo Window", ++winNumber);
    deskTop->insert(window);    // put window into desktop and draw it
}

// changed from tvguid12: add buttons
void TMyApp::newDialog()
{
    TDialog *pd = new TDialog( TRect( 20, 6, 60, 19), "Demo Dialog" );
    if( pd )
        {
        TView *b = new TCheckBoxes( TRect( 3, 3, 18, 6),
            new TSItem( "~H~varti",
            new TSItem( "~T~ilset",
            new TSItem( "~J~arlsberg", 0 )
            )));
        pd->insert( b );

        pd->insert( new TLabel( TRect( 2, 2, 10, 3), "Cheeses", b ));

        b = new TRadioButtons( TRect( 22, 3, 34, 6),
            new TSItem( "~S~olid",
            new TSItem( "~R~unny",
            new TSItem( "~M~elted", 0 )
            )));
        pd->insert( b );

        pd->insert( new TLabel( TRect( 21, 2, 33, 3), "Consistency", b ));

        // add input line
        b = new TInputLine( TRect( 3, 8, 37, 9 ), 128 );
        pd->insert( b );
        pd->insert( new TLabel( TRect( 2, 7, 24, 8 ),
                "Delivery Instructions", b ));

        pd->insert( new TButton( TRect( 15, 10, 25, 12 ), "~O~K", cmOK,
                    bfDefault ));
        pd->insert( new TButton( TRect( 28, 10, 38, 12 ), "~C~ancel", cmCancel,
                    bfNormal ));

        // we save the dialog data:
        pd->setData( demoDialogData );

        ushort control = deskTop->execView( pd );

        // and read it back when the dialog box is successfully closed
        if( control != cmCancel )
            pd->getData( demoDialogData );
        }
    destroy( pd );
}

int main()
{
    readFile( fileToRead );
    TMyApp myApp;
    myApp.run();
    deleteFile();
    return 0;
}
