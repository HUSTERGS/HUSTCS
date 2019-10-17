/*---------------------------------------------------------*/
/*                                                         */
/*   Turbo Vision 1.0                                      */
/*   Turbo Vision FileViewer Demo                          */
/*   Copyright (c) 1991 by Borland International           */
/*                                                         */
/*---------------------------------------------------------*/

#define Uses_TKeys
#define Uses_MsgBox
#define Uses_TApplication
#define Uses_TEvent
#define Uses_TRect
#define Uses_TFileDialog
#define Uses_TChDirDialog
#define Uses_TDeskTop
#define Uses_TMenuBar
#define Uses_TMenuItem
#define Uses_TSubMenu
#define Uses_TStatusLine
#define Uses_TStatusDef
#define Uses_TStatusItem
#include <tv.h>

#if !defined( __STRING_H )
#include <String.h>
#endif  // __STRING_H

#if !defined( __FSTREAM_H )
#include <Fstream.h>
#endif  // __FSTREAM_H

#if !defined( __DIR_H )
#include <Dir.h>
#endif  // __DIR_H

#if !defined( __FILEVIEW_H )
#include "FileView.h"
#endif  // __FILEVIEW_H

class TFileViewerApp : public TApplication
{

public:

    TFileViewerApp();

    virtual void handleEvent( TEvent& event );
    static TMenuBar *initMenuBar( TRect );
    static TStatusLine *initStatusLine( TRect );
    virtual void outOfMemory();

private:

    void openFile();
    void changeDir();
    void tile();
    void cascade();

};

TFileViewerApp::TFileViewerApp() :
    TProgInit( &TFileViewerApp::initStatusLine,
               &TFileViewerApp::initMenuBar,
               &TFileViewerApp::initDeskTop
             )
{
}


void TFileViewerApp::openFile()
{
    TFileDialog *d= (TFileDialog *)validView(
        new TFileDialog( "*.*", "Open a File", "~N~ame", fdOpenButton, 100 ));
    if( d != 0 && deskTop->execView( d ) != cmCancel )
        {
        char fileName[MAXPATH];
        d->getFileName( fileName );
        TView *w= validView( new TFileWindow( fileName ) );
        if( w != 0 )
            deskTop->insert(w);
        }
    destroy( d );
}

void TFileViewerApp::changeDir()
{
    TView *d = validView( new TChDirDialog( 0, hlChangeDir ) );
    if( d != 0 )
        {
        deskTop->execView( d );
	    destroy( d );
        }
}

void TFileViewerApp::tile()
{
    deskTop->tile( deskTop->getExtent() );
}

void TFileViewerApp::cascade()
{
    deskTop->cascade( deskTop->getExtent() );
}

void TFileViewerApp::handleEvent( TEvent& event )
{
    TApplication::handleEvent( event );
    if( event.what == evCommand )
        {
        switch( event.message.command )
            {
            case cmFileOpen:
                openFile();
                break;
            case cmChangeDir:
                changeDir();
                break;
            case cmCascade:
                cascade();
                break;
            case cmTile:
                tile();
                break;
            default:
                return ;
	    }
        clearEvent( event );
        }
}

TMenuBar *TFileViewerApp::initMenuBar( TRect r )
{
    r.b.y = r.a.y+1;

    return new TMenuBar( r,
      *new TSubMenu( "~F~ile", kbAltF ) +
        *new TMenuItem( "~O~pen...", cmFileOpen, kbF3, hcNoContext, "F3" ) +
        *new TMenuItem( "~C~hange dir...", cmChangeDir, kbNoKey ) +
        *new TMenuItem( "E~x~it", cmQuit, kbAltX, hcNoContext, "Alt-X" ) +
      *new TSubMenu( "~W~indows", kbAltW ) +
        *new TMenuItem( "~R~esize/move", cmResize, kbCtrlF5, hcNoContext, "Ctrl-F5" ) +
        *new TMenuItem( "~Z~oom", cmZoom, kbF5, hcNoContext, "F5" ) +
        *new TMenuItem( "~N~ext", cmNext, kbF6, hcNoContext, "F6" ) +
        *new TMenuItem( "~C~lose", cmClose, kbAltF3, hcNoContext, "Alt-F3" ) +
        *new TMenuItem( "~T~ile", cmTile, kbNoKey ) +
        *new TMenuItem( "C~a~scade", cmCascade, kbNoKey )
        );

}

TStatusLine *TFileViewerApp::initStatusLine( TRect r )
{
    r.a.y = r.b.y-1;
    return new TStatusLine( r,
        *new TStatusDef( 0, 0xFFFF ) +
            *new TStatusItem( 0, kbF10, cmMenu ) +
            *new TStatusItem( "~Alt-X~ Exit", kbAltX, cmQuit ) +
            *new TStatusItem( "~F3~ Open", kbF3, cmFileOpen ) +
            *new TStatusItem( "~F5~ Zoom", kbF5, cmZoom ) +
            *new TStatusItem( "~Alt-F3~ Close", kbAltF3, cmClose )
	    );


}

void TFileViewerApp::outOfMemory()
{
    messageBox( "Not enough memory available to complete operation.",
                mfError | mfOKButton );
}
            

int main()
{
    TFileViewerApp fileViewerApp;
    fileViewerApp.run();
    return 0;
}
