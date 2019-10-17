// ObjectWindows - (C) Copyright 1992 by Borland International

// MoveToLineTo demo window

#include <owl.h>
#include <math.h>
#include "demobase.h"
#include "line.h"

/* TMoveToLineToWindow --------------------------------------------- */

TMoveToLineToWindow::TMoveToLineToWindow( PTWindowsObject AParent, LPSTR ATitle ) :
	 TBaseDemoWindow(AParent, ATitle)
{
  Rotation = 0;
  PointCount = MaxPoints;
  Iconized = FALSE;
  RotatePoints();
}

void TMoveToLineToWindow::GetWindowClass( WNDCLASS& WndClass )
{
  TBaseDemoWindow::GetWindowClass( WndClass );
  WndClass.hIcon = 0;  // we'll draw our own icon when minimized.
}

void TMoveToLineToWindow::Paint( HDC PaintDC, PAINTSTRUCT& )
{
  DrawPoints( PaintDC );
};

void TMoveToLineToWindow::WMSize( TMessage &Message )
{
  TBaseDemoWindow::WMSize( Message );
  if (IsIconic(HWindow)) {
    if (!Iconized) {
      Rotation = 0;
      Iconized = TRUE;
      PointCount = IconicPoints;
      RotatePoints();
    };
  } else {
    if (Iconized) {
      Rotation = 0;
      Iconized = FALSE;
      PointCount = MaxPoints;
      RotatePoints();
    };
  };
}

void TMoveToLineToWindow::TimerTick()
{
    RotatePoints();
    if (IsIconic(HWindow)) {
      /* Iconized windows don't process paint messages, so we'll manually
         update the image here.  Doing this painting during the timer tick
         will slow things down a bit, especially with several of these
         windows iconized at the same time. */
      HDC DC = GetDC(HWindow);
      DrawPoints( DC );
      ReleaseDC(HWindow, DC);
    } else
      // Let the Paint method draw the new figure...
      InvalidateRect(HWindow, NULL, FALSE);
      /* In terms of Windows resources and system wide performance, letting
      paint do the work is 'faster' because it reduces the CPU time spent
      handling each timer tick.  Paint messages are low priority, so other
      messages like mouse clicks and other user input get processed first.
      The downside is that the paint messages are handled last, when there's
      nothing else to do, which can make animation look a bit jerky on
      a busy machine. */
}

const float M_2PI = 2 * M_PI;               // 2 pi radians in a circle

void TMoveToLineToWindow::RotatePoints()
{
  // NOTE: all figures are in radians
  float StepAngle = M_2PI / PointCount;  // angular distance between points

  Rotation += M_PI / 32;   // Increment the angle of rotation of figure
  if (Rotation > StepAngle)
    Rotation -= StepAngle;   // Keep rotation less than distance between points

/* The loop below has I walking through the Points array, while J walks
simultaneously through the angles to each point on the circle.  Incrementing
J by StepAngle moves J to the next point on the circle with no complicated
arithmetic (everything has been set up in advance of the loop).  Initiallizing
J with Rotation causes the entire figure to shift clockwise a small amount. */

  int I;
  float J;
  for( I = 0, J = Rotation; I < PointCount; I++, J += StepAngle ) {
    Points[I].X = cos(J);   // These values will be multiplied by the
    Points[I].Y = sin(J);   // current radius at display time.
  }

}

void TMoveToLineToWindow::DrawPoints(HDC PaintDC)
{
  RECT TheRect;
  int I, J, CenterX, CenterY;
  WORD Radius;

  GetClientRect(HWindow, &TheRect);
  CenterX = TheRect.right / 2;
  CenterY = TheRect.bottom / 2;
  Radius = min(CenterY, CenterX);

/* The follow memory DC operations are not required to draw lines, but
   were added to reduce screen flicker and speed up screen updates. */
  HDC     MemDC = CreateCompatibleDC(PaintDC);
     // Keep old bitmap handle so we can put it back when we're done.
  HBITMAP OldBM = (HBITMAP)SelectObject(MemDC, CreateCompatibleBitmap( PaintDC, Radius*2, Radius*2 ));
     // Initiallize the new bitmap to all white.
  BitBlt( MemDC, 0, 0, Radius*2, Radius*2, 0, 0, 0, WHITENESS);

/* The Ellipse and the for loop are all that's really needed to draw.  If
you substitute PaintDC for MemDC, the draws will go directly to the screen.
(Though the figure would no longer be centered, since the figure is drawn
on a MemDC bitmap, and the bitmap is then centered on the PaintDC...)
Since this line window is animated, it is frequently updated, which would
cause the window to spend most of its time flickering if the PaintDC were
used.  Thus, the need for memory DC operations.  If the window were not
animated, drawing onto the PaintDC would look just fine. */

  Ellipse( MemDC, 0, 0, Radius*2, Radius*2);

  for( I = 0; I < PointCount; I++) {
    for( J = I + 1; J < PointCount; J++) {
      MoveTo( MemDC, Radius + floor(Points[I].X * Radius),
		       Radius + floor(Points[I].Y * Radius));
      LineTo( MemDC, Radius + floor(Points[J].X * Radius),
		       Radius + floor(Points[J].Y * Radius));
    }
  }

/* Now transfer what was drawn on the (invisible) memory DC onto the visible
   PaintDC.  This one BitBlt transfer is much faster than the many individual
   operations that were performed above.  */

  BitBlt( PaintDC, CenterX - Radius, CenterY - Radius, Radius*2, Radius*2, MemDC, 0, 0, SRCCOPY);

  // Delete the bitmap we created, and put the old bitmap back in the DC
  DeleteObject(SelectObject( MemDC, OldBM));
  // Now dispose of the temporary memory DC we created
  DeleteDC(MemDC);

/* Footnotes:  Drawing this figure doesn't require a memory DC.  Animating
the figure requires a memory DC only to reduce flicker to a tolerable level.
To make the animation faster still, (but use more memory, too),
you could keep that memory DC hanging around between screen paints -
constructing a DC takes some effort, and we're constructing one every time
we get a timer message.   You'd get the biggest improvement in animation
speed by calculating a sequence of bitmaps, then just displaying them in the
proper sequence.  This demo reconstructs the points list and redraws the figure
for every timer message - a lot of work for the CPU, but it's code is simpler
and doesn't use as much memory as more elaborate schemes might.

  A challenge:  Turn the rotating figure into a ball that bounces off the
walls of the window.  Don't forget the english (spin) the ball should pick up
when bouncing off the wall...  */
}
