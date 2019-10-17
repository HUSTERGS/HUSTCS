// Borland C++ - (C) Copyright 1991 by Borland International

/* VPOINT.CPP--Example from Getting Started */

// VPOINT.CPP contains the definitions for the Point and Location
// classes that are declared in the file vpoint.h

#include "vpoint.h"
#include <graphics.h>

// member functions for the Location class
Location::Location(int InitX, int InitY) {
   X = InitX;
   Y = InitY;
};

int Location::GetX(void) {
   return X;
};

int Location::GetY(void) {
   return Y;
};

// member functions for the Point class: These assume
// the main program has initialized the graphics system

Point::Point(int InitX, int InitY) : Location(InitX,InitY) {
   Visible = false;                  // make invisible by default
};

void Point::Show(void) {
   Visible = true;
   putpixel(X, Y, getcolor());       // uses default color
};

void Point::Hide(void) {
   Visible = false;
   putpixel(X, Y, getbkcolor()); // uses background color to erase
};

Boolean Point::IsVisible(void) {
   return Visible;
};

void Point::MoveTo(int NewX, int NewY) {
   Hide();         // make current point invisible
   X = NewX;       // change X and Y coordinates to new location
   Y = NewY;
   Show();         // show point at new location
};

