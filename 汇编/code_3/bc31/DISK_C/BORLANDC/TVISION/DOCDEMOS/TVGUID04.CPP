/*---------------------------------------------------------*/
/*                                                         */
/*   Turbo Vision 1.0                                      */
/*   TVGUID04 Demo Source File                             */
/*   Copyright (c) 1991 by Borland International           */
/*                                                         */
/*---------------------------------------------------------*/

#include <stdlib.h>               // for random()

#define Uses_TEvent
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
#define Uses_TWindow
#include <tv.h>

const int cmMyFileOpen = 200; // assign new command values
const int cmMyNewWin   = 201;


class TMyApp : public TApplication
{

public:
    TMyApp();
    static TStatusLine *initStatusLine( TRect r );
    static TMenuBar *initMenuBar( TRect r );
    virtual void handleEvent( TEvent& event);
    void myNewWindow();
};


static short winNumber = 0;          // initialize window number

class TDemoWindow : public TWindow   // define a new window class
{

public:

   TDemoWindow( const TRect& r, const char *aTitle, short aNumber );
    // declare a constructor

    //   static TFrame *initFrame( TRect r );
    // override needed only if you want a nonstandard frame
    // Here we'll inherit TWindow::initFrame unchanged
    // so TWindowInit will take &TDemoWindow::initFrame to give
    // a standard frame

};


TMyApp::TMyApp() :
    TProgInit( &TMyApp::initStatusLine,
               &TMyApp::initMenuBar,
               &TMyApp::initDeskTop
             )
{
}

TStatusLine *TMyApp::initStatusLine(TRect r)
{
    r.a.y = r.b.y - 1;     // move top to 1 line above bottom
    return new TStatusLine( r,
        *new TStatusDef( 0, 0xFFFF ) +
        // set range of help contexts
            *new TStatusItem( 0, kbF10, cmMenu ) +
            // define an item
            *new TStatusItem( "~Alt-X~ Exit", kbAltX, cmQuit ) +
            // define an item
            *new TStatusItem( "~Alt-F3~ Close", kbAltF3, cmClose )
            // and another one
        );
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
            *new TMenuItem( "~Z~oom", cmZoom,     kbF5, hcNoContext, "F5" )
        );
}

void TMyApp::handleEvent(TEvent& event)
{
    TApplication::handleEvent(event); // act like base!
    if( event.what == evCommand )
        {
        switch( event.message.command )
            {
            case cmMyNewWin:       // but respond to additional commands
                myNewWindow();     // define action for cmMyNewWin
                break;
            default:
                return;
            }
        clearEvent( event );       // clear event after handling
        }
}

void TMyApp::myNewWindow()
{
    TRect r( 0, 0, 26, 7 );           // set initial size and position
    r.move( random(53), random(16) ); // randomly move around screen
    TDemoWindow *window = new TDemoWindow ( r, "Demo Window", ++winNumber);
    deskTop->insert(window); // put window into desktop and draw it
}


TDemoWindow::TDemoWindow( const TRect& r, const char *aTitle, short aNumber):
                          TWindow( r, aTitle, aNumber),
                          TWindowInit( &TDemoWindow::initFrame
                        )

{
}

int main()
{
    TMyApp myApp;
    myApp.run();
    return 0;
}
