// Borland C++ - (C) Copyright 1991 by Borland International

/* VCIRC.CPP--Example from Getting Started */

// A Circle class derived from Point

#include <graphics.h>    // graphics library declarations
#include "vpoint.h"       // Location and Point class declarations
#include <conio.h>       // for getch() function

// link with vpoint.obj and graphics.lib

class Circle : public Point { // derived from class Point
			 // and ultimately from class Location
   int Radius;           // private by default

public:
   Circle(int InitX, int InitY, int InitRadius);
   void Show(void);
   void Hide(void);
   void Expand(int ExpandBy);
   void Contract(int ContractBy);
};

// Circle constructor calls base Point constructor first
Circle::Circle(int InitX, int InitY, int InitRadius) : Point(InitX,InitY)
{
   Radius = InitRadius;
};

void Circle::Show()
{
   Visible = true;
   circle(X, Y, Radius);      // draw the circle using BGI function
}

void Circle::Hide()
{
   if (!Visible) return;      // no need to hide
   unsigned int TempColor;    // to save current color
   TempColor = getcolor();    // set to current color
   setcolor(getbkcolor());    // set drawing color to background
   Visible = false;
   circle(X, Y, Radius);      // draw in background color to erase
   setcolor(TempColor);       // set color back to current color
};

void Circle::Expand(int ExpandBy)
{
   Boolean vis = Visible;  // is current circle visible?
   if (vis) Hide();        // if so, hide it
   Radius += ExpandBy;     // expand radius
   if (Radius < 0)         // avoid negative radius
      Radius = 0;
   if (vis) Show();        // draw new circle if previously visible
};

inline void Circle::Contract(int ContractBy)
{
   Expand(-ContractBy);       // redraws with (Radius - ContractBy)
};

main()                        // test the functions
{
   // initialize the graphics system
   int graphdriver = DETECT, graphmode;
   initgraph(&graphdriver, &graphmode, "..\\bgi");

   Circle MyCircle(50, 100, 25);    // declare a circle object
   MyCircle.Show();                 // show it
   getch();                         // wait for keypress
   MyCircle.MoveTo(100, 125);       // move the circle (tests hide
                                    // and show also)
   getch();
   MyCircle.Expand(25);             // make it bigger
   getch();
   MyCircle.Contract(35);           // make it smaller
   getch();
   closegraph();
   return 0;
}

