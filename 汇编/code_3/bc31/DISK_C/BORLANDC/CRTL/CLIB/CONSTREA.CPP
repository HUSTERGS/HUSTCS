/*-----------------------------------------------------------------------*
 * filename - constrea.cpp
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1991, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#if !defined( __CONSTREA_H )
#include "constrea.h"
#endif  // __CONSTREA_H

#if !defined( __IOSTREAM_H )
#include <iostream.h>
#endif  // __IOSTREAM_H

conbuf *conbuf::current = 0;
long constream::isCon_ = 0L;

conbuf::conbuf()
{
    ::gettextinfo( &data );
    cursortype = _NORMALCURSOR;
}

int conbuf::overflow( int c )
{
    activate();
    if( c == '\n' )
        putch( '\r' );
    return putch( c );
}

void conbuf::makeActive()
{
    ::window( data.winleft, data.wintop, data.winright, data.winbottom );
    ::textattr( data.attribute );
    ::gotoxy( data.curx, data.cury );
    ::_setcursortype( cursortype );
}

void conbuf::makeInactive()
{
    ::gettextinfo( &data );
}

void conbuf::swap()
{
    if( current != 0 )
        current->deactivate();
    makeActive();
    current = this;
}

constream::constream() : ostream( &buf )
{
    cin.tie( this );
    setf( ios::unitbuf );
    if( !isCon_ )
        isCon_ = bitalloc();
    setf( isCon_ );
}

ostream& _Cdecl clreol( ostream& o )
{
    if( constream::isCon( o ) )
        ((constream&)o).rdbuf()->clreol();
    return o;
}

ostream& _Cdecl highvideo( ostream& o )
{
    if( constream::isCon( o ) )
        ((constream&)o).rdbuf()->highvideo();
    return o;
}

ostream& _Cdecl lowvideo( ostream& o )
{
    if( constream::isCon( o ) )
        ((constream&)o).rdbuf()->lowvideo();
    return o;
}

ostream& _Cdecl normvideo( ostream& o )
{
    if( constream::isCon( o ) )
        ((constream&)o).rdbuf()->normvideo();
    return o;
}

ostream& _Cdecl delline( ostream& o )
{
    if( constream::isCon( o ) )
        ((constream&)o).rdbuf()->delline();
    return o;
}

ostream& _Cdecl insline( ostream& o )
{
    if( constream::isCon( o ) )
        ((constream&)o).rdbuf()->insline();
    return o;
}

static ostream& scrsr( ostream& o, int c )
{
    if( constream::isCon( o ) )
        ((constream&)o).rdbuf()->setcursortype( c );
    return o;
}

omanip_int cdecl setcrsrtype( int c )
{
    return omanip_int( scrsr, c );
}


static ostream& sattr( ostream& o, int a )
{
    if( constream::isCon( o ) )
        ((constream&)o).rdbuf()->textattr( a );
    return o;
}

omanip_int cdecl setattr( int a )
{
    return omanip_int( sattr, a );
}

static ostream& sxy( ostream& o, int x, int y )
{
    if( constream::isCon( o ) )
        ((constream&)o).rdbuf()->gotoxy( x, y );
    return o;
}

omanip_int_int cdecl setxy( int a, int b )
{
    return omanip_int_int( sxy, a, b );
}

static ostream& sbk( ostream& o, int a )
{
    if( constream::isCon( o ) )
        ((constream&)o).rdbuf()->textbackground( a );
    return o;
}

omanip_int cdecl setbk( int a )
{
    return omanip_int( sbk, a );
}

static ostream& sclr( ostream& o, int a )
{
    if( constream::isCon( o ) )
        ((constream&)o).rdbuf()->textcolor( a );
    return o;
}

omanip_int cdecl setclr( int a )
{
    return omanip_int( sclr, a );
}


