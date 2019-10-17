// Borland C++ - (C) Copyright 1991 by Borland International

/* vpoint.h--Example from Getting Started */

// version of point.h with virtual functions for use with VCIRCLE
// vpoint.h contains two classes:
// class Location describes screen locations in X and Y coordinates
// class Point describes whether a point is hidden or visible

enum Boolean {false, true};

class Location {
protected:          // allows derived class to access private data
   int X;
   int Y;

public:             // these functions can be accessed from outside
   Location(int InitX, int InitY);
   int GetX();
   int GetY();
};
class Point : public Location {      // derived from class Location
// public derivation means that X and Y are protected within Point

   protected:
   Boolean Visible;  // classes derived from Point will need access    

public:
   Point(int InitX, int InitY);      // constructor
   virtual void Show();
   virtual void Hide();
   Boolean IsVisible();
   void MoveTo(int NewX, int NewY);
};
