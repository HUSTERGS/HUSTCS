/*---------------------------------------------------------*/
/*                                                         */
/*   Turbo Vision 1.0                                      */
/*   TVGUID20 Demo Source File                            */
/*   Copyright (c) 1991 by Borland International           */
/*                                                         */
/*---------------------------------------------------------*/

//  Polymorphism with a collection of graphics objects

#include <stdlib.h>
#include <graphics.h>
#include <stdio.h>

#define Uses_TObject
#define Uses_TPoint
#define Uses_TRect
#define Uses_TCollection
#include <tv.h>

class TGraphObject : public TObject
{

public:

    int x, y;
    TGraphObject();
    // for this example, the constructor assigns random values to x, y
    virtual void draw() = 0;
    // pure virtual function--must be defined in derived classes

};

class TGraphPoint : public TGraphObject
{

public:

    TGraphPoint();
    // for this example, the constructor assigns random values to x, y
    virtual void draw();

};

class TGraphCircle : public TGraphObject
{

public:

    int radius;
    TGraphCircle();
    // for this example, the constructor assigns random values to x, y,
    // and radius
    virtual void draw();
};

class TGraphRect : public TGraphObject
{

public:

    int width, height;
    TGraphRect();
    // for this example, the constructor assigns random values to x, y, w,
    // and h
    virtual void draw();
};

TGraphObject::TGraphObject()
{
    x = random( getmaxx() );
    y = random( getmaxy() );
};

TGraphPoint::TGraphPoint() : TGraphObject()
{
};

void TGraphPoint::draw()
{

    // make a nice fat, visible point
    for( int dx = x-2; dx < x+2; dx++)
        for( int dy = y-2; dy < y+2; dy++)
            putpixel( dx, dy, 1);
}

TGraphCircle::TGraphCircle() : TGraphObject()
{
    radius = 20 + random( 20 );
}

void TGraphCircle::draw()
{
    circle( x, y, radius);
}

TGraphRect::TGraphRect() : TGraphObject()
{
    width  = 10 + random( 20 ) + x;
    height =  6 + random( 15 ) + y;
}

void TGraphRect::draw()
{
    rectangle( x, y, x + width, y + height );
}

void startGraphics()
{
    int gdriver = DETECT, gmode, errorcode;
    initgraph( &gdriver, &gmode, "..\\..\\bgi" );

    errorcode = graphresult();
    if( errorcode != grOk )
        {
        printf( "Graphics init error: %s\n", grapherrormsg(errorcode));
        getchar();
        exit(1);
        }
}

void callDraw( void *p, void * )
{
    ((TGraphObject *)p)->draw();
    // Call the appropriate draw member function
}

void drawAll( TNSCollection *c, void * )
{
    c->forEach( &callDraw, 0 );   // Draw each object
}

int main()
{
    startGraphics();
    TNSCollection *list = new TNSCollection(10, 5);   // Create collection

    for( int i = 0; i < 20; i++ )
        {
        switch ( i % 3 )
            {
            case 0:
                TGraphPoint *gp = new TGraphPoint;
                list->insert( gp );
                break;
            case 1:
                TGraphCircle *gc = new TGraphCircle;
                list->insert( gc );
                break;
            case 2:
                TGraphRect *gr = new TGraphRect;
                list->insert( gr );
                break;
            }
        }

    drawAll( list, 0 );
    getchar();
    // pause to admire?

    closegraph();
    return 0;
}

