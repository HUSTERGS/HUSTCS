// ObjectWindows - (C) Copyright 1992 by Borland International

// Artypriv.h - classes used internally by the TArtyWindow

#ifndef __ARTYINTERNAL_H
#define __ARTYINTERNAL_H

/* Arty demo constants */
const int   MaxLineCount      =  100;
const int   MaxIconicLineCount=  5;
const int   MaxColorDuration  =  10;


typedef struct {
    int LX1,LY1, LX2,LY2;
    long int Color;
} TLineRec;

typedef TLineRec TLineList[MaxLineCount];
typedef TLineList* PTLineList;

class TList
{
public:
         TList( int Max );
         void Redraw( HDC );
         void ResetLines();
         void ScaleTo( int, int );
         void LineTick( HDC );
protected:
         TLineList Line;
         int  Xmax, Ymax;
         void AdjustX( int&, int& );
         void AdjustY( int&, int& );
         void Draw( HDC, int, int, int, int, LONG);
         virtual void DrawLine( HDC, int );
         virtual void EraseLine( HDC, int );
         void SelectNewColor();
         void SelectNewDeltaValues();
private: int  MaxLines,
              X1, Y1, X2, Y2,
              MaxDelta,
              ColorDuration,
              IncrementCount,
              DeltaX1, DeltaY1, DeltaX2, DeltaY2,
              CurrentLine;
         long PenColor;
};

typedef TList* PTList;

class TQuadList : public TList   /* Quads draw 4 reflections of each line */
{
public:
         TQuadList( int Max )
            : TList( Max ) {}
         virtual void DrawLine( HDC, int );
         virtual void EraseLine( HDC, int );
};

typedef TQuadList* PTQuadList;


#endif  // ifndef __ARTYINTERNAL_H
