/*---------------------------------------------------------*/
/*                                                         */
/*   Turbo Vision 1.0                                      */
/*   TVGUID021 Demo Source File                            */
/*   Copyright (c) 1991 by Borland International           */
/*                                                         */
/*---------------------------------------------------------*/

//  Polymorphism with a collection of graphics objects
//  writing objects to a stream

#include <stdlib.h>
#include <graphics.h>
#include <stdio.h>

#define Uses_TObject
#define Uses_TPoint
#define Uses_TRect
#define Uses_TCollection
#define Uses_ofpstream
#define Uses_ifpstream
#define Uses_TStreamableClass
#include <tv.h>

class TGraphObject : public TObject, public TStreamable
{

public:

    int x, y;
    TGraphObject();
    // for this example, the constructor assigns random values to x, y
    virtual void draw() = 0;
    // pure virtual function--must be defined in derived classes
    virtual void write( opstream& os);
    virtual void *read( ipstream& );

protected:

    TGraphObject( StreamableInit ) {}

private:

    virtual const char *streamableName() const = 0;

};

class TGraphPoint : public TGraphObject
{

public:

    TGraphPoint();
    // for this example, the constructor assigns random values to x, y
    virtual void draw();

    static const char * const name;
    static TStreamable *build();

protected:

    TGraphPoint( StreamableInit ) : TGraphObject( streamableInit ) {}

private:

    virtual const char *streamableName() const
        { return name; }

};

class TGraphCircle : public TGraphObject
{

public:

    int radius;
    TGraphCircle();
        // for this example, the constructor assigns random values to x, y,
        // and radius
    virtual void draw();
    virtual void write( opstream& os);
    virtual void *read( ipstream& );

    static const char * const name;
    static TStreamable *build();

protected:

    TGraphCircle( StreamableInit ) : TGraphObject( streamableInit ) {}

private:

    virtual const char *streamableName() const
        { return name; }

};

class TGraphRect : public TGraphObject
{

public:

    int width, height;
    TGraphRect();
    // for this example, the constructor assigns random values to x, y, w,
    // and h
    virtual void draw();
    virtual void write( opstream& os);
    virtual void *read( ipstream& );

    static const char * const name;
    static TStreamable *build();

protected:

    TGraphRect( StreamableInit ) : TGraphObject( streamableInit ) {}

private:

    virtual const char *streamableName() const
        { return name; }

};

class TGraphCollection : public TCollection
{

public:

    TGraphCollection() : TCollection( 12, 5 ) {}
    void drawAll();
    static const char * const name;
    static TStreamable *build();

private:

    virtual void freeItem( void *item );

    virtual const char *streamableName() const
        { return name; }

    virtual void *readItem( ipstream& );
    virtual void writeItem( void *, opstream& );

protected:

    TGraphCollection( StreamableInit ) : TCollection( streamableInit ) {}
};

TGraphObject::TGraphObject()
{
    x = random( getmaxx() );
    y = random( getmaxy() );
};

void TGraphObject::write( opstream& os )
{
    os << x << y;
}

void *TGraphObject::read( ipstream& is )
{
    is >> x >> y;
    return this;
}

inline ipstream& operator >> ( ipstream& is, TGraphObject& cl )
    { return is >> (TStreamable&)cl; }
inline ipstream& operator >> ( ipstream& is, TGraphObject*& cl )
    { return is >> (void *&)cl; }

inline opstream& operator << ( opstream& os, TGraphObject& cl )
    { return os << (TStreamable&)cl; }
inline opstream& operator << ( opstream& os, TGraphObject* cl )
    { return os << (TStreamable *)cl; }

TGraphPoint::TGraphPoint() : TGraphObject()
{
};

void TGraphPoint::draw()
{
    // make a nice fat, visible point
    for( int dx = x-2; dx < x+2; dx++ )
        for( int dy = y-2; dy < y+2; dy++ )
            putpixel( dx, dy, 1);
}

TStreamable *TGraphPoint::build()
{
    return new TGraphPoint( streamableInit );
}

const char * const TGraphPoint::name = "TGraphPoint";

TGraphCircle::TGraphCircle() : TGraphObject()
{
    radius = 20 + random( 20 );
}

void TGraphCircle::draw()
{
    circle( x, y, radius);
}

void TGraphCircle::write( opstream& os )
{
    TGraphObject::write( os );
    os << radius;
}

void *TGraphCircle::read( ipstream& is )
{
    TGraphObject::read( is );
    is >> radius;
    return this;
}

TStreamable *TGraphCircle::build()
{
    return new TGraphCircle( streamableInit );
}

const char * const TGraphCircle::name = "TGraphCircle";

TGraphRect::TGraphRect() : TGraphObject()
{
    width  = 10 + random( 20 ) + x;
    height =  6 + random( 15 ) + y;
}

void TGraphRect::draw()
{
    rectangle( x, y, x + width, y + height );
}

void TGraphRect::write( opstream& os )
{
    TGraphObject::write( os );
    os << width << height;
}

void *TGraphRect::read( ipstream& is )
{
    TGraphObject::read( is );
    is >> width >> height;
    return this;
}

TStreamable *TGraphRect::build()
{
    return new TGraphRect( streamableInit );
}

const char * const TGraphRect::name = "TGraphRect";

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

static void callDraw( void *p, void * )
{
    ((TGraphObject *)p)->draw();
    // Call the appriate draw member function
}

void TGraphCollection::drawAll()
{
    forEach( &callDraw, 0 );    // Draw each object
}

void TGraphCollection::freeItem( void *item )
{
    delete (TGraphObject *)item;
}

void *TGraphCollection::readItem( ipstream& is )
{
    TGraphObject *ptr;
    is >> ptr;
    return ptr;
}

void TGraphCollection::writeItem( void *ptr, opstream& os )
{
    os << (TGraphObject *)ptr;
}

const char * const TGraphCollection::name = "TGraphCollection";

TStreamable *TGraphCollection::build()
{
    return new TGraphCollection( streamableInit );
}

inline ipstream& operator >> ( ipstream& is, TGraphCollection& cl )
    { return is >> (TStreamable&)cl; }
inline ipstream& operator >> ( ipstream& is, TGraphCollection*& cl )
    { return is >> (void *&)cl; }

inline opstream& operator << ( opstream& os, TGraphCollection& cl )
    { return os << (TStreamable&)cl; }
inline opstream& operator << ( opstream& os, TGraphCollection* cl )
    { return os << (TStreamable *)cl; }

TStreamableClass RGraphPoint( TGraphPoint::name,
                              TGraphPoint::build,
                              __DELTA(TGraphPoint) 
                            );

TStreamableClass RGraphCircle( TGraphCircle::name,
                               TGraphCircle::build,
                               __DELTA(TGraphCircle) 
                             );

TStreamableClass RGraphRect( TGraphRect::name,
                             TGraphRect::build,
                             __DELTA(TGraphRect) 
                           );

TStreamableClass RGraphCollection( TGraphCollection::name,
                                   TGraphCollection::build,
                                   __DELTA(TGraphCollection) 
                                 );

int main()
{
    startGraphics();

    TGraphCollection *list = new TGraphCollection;  // Create collection

    for( int i = 0; i < 12; i++ )
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

    list->drawAll();
    getchar();
    // pause to admire?

    ofpstream of( "graph.sav" );
    of << list;
    of.close();

    list->removeAll();
    cleardevice();
    list->drawAll();
    getchar();

    ifpstream in( "graph.sav" );
    in >> list;
    in.close();

    list->drawAll();
    getchar();

    closegraph();
    return 0;
}

