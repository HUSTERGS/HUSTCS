// ObjectWindows - (C) Copyright 1992 by Borland International

// Font demo window for GDIDemo program

#include <owl.h>
#include <string.h>
#include "demobase.h"
#include "font.h"


typedef struct {
    HFONT Handle;   /* Handle to logical font */
    short Height;   /* Height of logical font in pixels */
    long  Width;    /* Width of name of the font in pixels */
    char Name[ LF_FACESIZE ];  /* Name of this font */
} FontInfoRec;


/* local variables used by EnumerateFonts callback function */
        int FontUsers = 0;
FontInfoRec FontInfo[ MaxNumFonts ];
        int NumFonts;            /* Number of system fonts available */
        HDC TheDC;

/* EnumerateFont is a call back function.  It receives information
  about system fonts.  It creates an example of each font by calling
  CreateFont. When MaxNumFonts have been processed, 0 is returned
  notifying windows to stop sending information, otherwise 1 is
  returned telling windows to send more information if available */

int FAR PASCAL _export EnumerateFont( LPLOGFONT LogFont, LPTEXTMETRIC,
                                      short, LPSTR)
{
  HFONT OldFont;

  /* Create the font described by LogFont */
  FontInfo[NumFonts].Handle = CreateFontIndirect(LogFont);

  /* Save the height of the font for positioning when drawing in the window */
  FontInfo[NumFonts].Height = LogFont->lfHeight;

  /* Save the name of the font for drawing in the window */
  _fstrcpy(FontInfo[NumFonts].Name, (LPSTR) LogFont->lfFaceName);
  OldFont = (HFONT)SelectObject(TheDC, FontInfo[NumFonts].Handle);
  FontInfo[NumFonts].Width = GetTextExtent(TheDC,
                                           (LPSTR) LogFont->lfFaceName,
                                           _fstrlen((LPSTR) LogFont->lfFaceName));
  SelectObject(TheDC, OldFont);
  NumFonts++;
  if (NumFonts > MaxNumFonts) {
    return 0;  /* Don't send any more information */
  } else {
    return 1; /* Send more information if available */
  }
};

/* Collect all of the system fonts */
void GetFontInfo()
{
  OLDFONTENUMPROC EnumProc;
  if (FontUsers == 0) {
    TheDC = GetDC(GetFocus());
    NumFonts = 0;

    /* Create an instance of the call back function.  This allows
      our program to refer to an exported function.  Otherwise the
      Data segment will not be correct. */
    EnumProc = (OLDFONTENUMPROC)MakeProcInstance((FARPROC) EnumerateFont, GetApplicationObject()->hInstance);

    /* Gather information about all fonts that are allowable in our window (DC) */
    EnumFonts(TheDC, NULL, EnumProc, NULL);

    /* Free the instance of our call back function */
    FreeProcInstance((FARPROC)EnumProc);
    ReleaseDC(GetFocus(), TheDC);
  };
  FontUsers++;
};

/* Release font information */
void ReleaseFontInfo()
{
  FontUsers--;
  if (FontUsers == 0) {
    for( int I = 0; I < NumFonts; I++)
      DeleteObject(FontInfo[I].Handle);
  }
};

/* Initialize object and collect font information */
TFontWindow::TFontWindow( PTWindowsObject AParent, LPSTR ATitle ) :
                TBaseDemoWindow( AParent, ATitle )
{
  GetFontInfo();
  Attr.Style |= WS_VSCROLL | WS_HSCROLL;
  FontsHeight = 0;
  FontsWidth = 0;
  for( int I = 0; I < NumFonts; I++) {
    FontsHeight += FontInfo[I].Height;
    if (FontsWidth < FontInfo[I].Width)
      FontsWidth = FontInfo[I].Width;
  };
  Scroller = new TScroller(this, 1, 1, 0, 0);
};

/* Draw each font name in it's font in the Display context.  Each
  line is incremented by the height of the font */

void TFontWindow::Paint( HDC PaintDC, PAINTSTRUCT& )
{
  int I, Position;

  Position = 0;
  for( I = 0; I < NumFonts; I++) {
    SelectObject(PaintDC, FontInfo[I].Handle);
    TextOut(PaintDC, 10, Position, FontInfo[I].Name, strlen(FontInfo[I].Name));
    Position += FontInfo[I].Height;
  }
};

void TFontWindow::Destroy()
{
  TBaseDemoWindow::Destroy();
  ReleaseFontInfo();
};

void TFontWindow::WMSize( TMessage& Message )
{
  TBaseDemoWindow::WMSize(Message);
  if (Scroller)
    Scroller->SetRange( FontsWidth - Message.LP.Lo + 10,
                        FontsHeight - Message.LP.Hi);
};

