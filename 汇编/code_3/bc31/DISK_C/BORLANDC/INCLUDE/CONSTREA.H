/*  constrea.h

    Defines the class constream, which writes output to the screen
    using the iostream interface.

    Copyright (c) 1991, 1992 by Borland International
    All Rights Reserved.
*/

#if !defined(__CONSTREA_H)
#define __CONSTREA_H

#if defined( _Windows )
#error constream not available for Windows
#endif

#if !defined(__IOSTREAM_H)
#include <iostream.h>
#endif  // __IOSTREAM_H

#if !defined(__IOMANIP_H)
#include <iomanip.h>
#endif  // __IOMANIP_H

#if !defined(__CONIO_H)
#include <conio.h>
#endif  // __CONIO_H

class conbuf : public streambuf
{

public:

    conbuf();
    ~conbuf();
    virtual int _Cdecl overflow( int = EOF );

    void _Cdecl clreol();

    void _Cdecl setcursortype( int );

    void _Cdecl highvideo();
    void _Cdecl lowvideo();
    void _Cdecl normvideo();

    void _Cdecl textattr( int );
    void _Cdecl textbackground( int );
    void _Cdecl textcolor( int );

    void _Cdecl gotoxy( int, int );
    int  _Cdecl wherex();
    int  _Cdecl wherey();

    void _Cdecl delline();
    void _Cdecl insline();

    void _Cdecl clrscr();
    void _Cdecl window( int, int, int, int );

    static void _Cdecl textmode( int );

    void activate();
    void deactivate();

private:

    virtual void makeActive();
    virtual void makeInactive();
    virtual void swap();

    text_info data;
    int cursortype;
    static conbuf *current;

};

inline conbuf::~conbuf()
{
    current = 0;
}

inline void conbuf::clreol()
{
    activate();
    ::clreol();
}

inline void conbuf::setcursortype( int t )
{
    activate();
    cursortype = t;
    ::_setcursortype( t );
}

inline void _Cdecl conbuf::highvideo()
{
    activate();
    ::highvideo();
}

inline void _Cdecl conbuf::lowvideo()
{
    activate();
    ::lowvideo();
}

inline void _Cdecl conbuf::normvideo()
{
    activate();
    ::normvideo();
}

inline void conbuf::gotoxy( int x, int y )
{
    activate();
    ::gotoxy( x, y );
}

inline int _Cdecl conbuf::wherex()
{
    activate();
    return ::wherex();
}

inline int _Cdecl conbuf::wherey()
{
    activate();
    return ::wherey();
}

inline void conbuf::textattr( int a )
{
    activate();
    ::textattr( a );
}

inline void _Cdecl conbuf::textbackground(int newcolor)
{
    activate();
    ::textbackground( newcolor );
}

inline void _Cdecl conbuf::textcolor(int newcolor)
{
    activate();
    ::textcolor( newcolor );
}

inline void _Cdecl conbuf::delline()
{
    activate();
    ::delline();
}

inline void _Cdecl conbuf::insline()
{
    activate();
    ::insline();
}

inline void conbuf::clrscr()
{
    activate();
    ::clrscr();
}

inline void conbuf::window(int left, int top, int right, int bottom)
{
    activate();
    ::window( left, top, right, bottom );
}

inline void _Cdecl conbuf::textmode( int mode )
{
    ::textmode( mode );
}

inline void conbuf::activate()
{
    if( current != this )
        swap();
}

inline void conbuf::deactivate()
{
    makeInactive();
}

class constream : public ostream
{

public:

    constream();

    conbuf* _Cdecl rdbuf();     // get the assigned conbuf

    void    _Cdecl clrscr();
    void    _Cdecl window( int, int, int, int );
    void    _Cdecl textmode( int );

    static int _Cdecl isCon( ostream& );

private:

    static long isCon_;
    conbuf buf;

};

inline conbuf* _Cdecl constream::rdbuf()
{
    return (conbuf *)ostream::rdbuf();
}

inline void _Cdecl constream::clrscr()
{
    rdbuf()->clrscr();
}

inline void _Cdecl constream::window( int l, int t, int r, int b )
{
    rdbuf()->window( l, t, r, b );
}

inline void _Cdecl constream::textmode( int m )
{
    rdbuf()->textmode( m );
}

inline int _Cdecl constream::isCon( ostream& o )
{
    return (o.flags() & isCon_) != 0;
}

class omanip_int_int
{

public:
    omanip_int_int(ostream& (*_f)(ostream&, int, int ), int _z1, int _z2 ) :
        _fn(_f), _ag1(_z1), _ag2(_z2) { }
    friend ostream& _Cdecl operator<<(ostream& _s, omanip_int_int& _f)
        { return(*_f._fn)(_s, _f._ag1, _f._ag2); }

private:
    ostream& _Cdecl (*_fn)(ostream&, int, int);
    int _ag1;
    int _ag2;
};

ostream& _Cdecl clreol( ostream& );
ostream& _Cdecl highvideo( ostream& );
ostream& _Cdecl lowvideo( ostream& );
ostream& _Cdecl normvideo( ostream& );
ostream& _Cdecl delline( ostream& );
ostream& _Cdecl insline( ostream& );

omanip_int cdecl setcrsrtype( int );
omanip_int cdecl setattr( int );
omanip_int cdecl setbk( int );
omanip_int cdecl setclr( int );
omanip_int_int cdecl setxy( int, int );

#endif  // __CONSTREA_H

