/*  strstream.h -- class strstream declarations

    Copyright (c) 1990, 1992 by Borland International
    All rights reserved
*/

#ifndef __cplusplus
#error Must use C++ for the type strstream.
#endif

#ifndef __STRSTREAM_H
#define __STRSTREAM_H

#if !defined(___DEFS_H)
#include <_defs.h>
#endif

#if !defined(__IOSTREAM_H)
#include <iostream.h>
#endif

#pragma option -Vo-
#if defined(__BCOPT__) && !defined(_RTL_ALLOW_po)
#pragma option -po-
#endif

_CLASSDEF(strstreambuf)
_CLASSDEF(strstreambase)
_CLASSDEF(istrstream)
_CLASSDEF(ostrstream)
_CLASSDEF(strstream)

class _CLASSTYPE strstreambuf : public streambuf {
public:
    _Cdecl strstreambuf();
    _Cdecl strstreambuf(int n);
    _Cdecl strstreambuf(void _FAR * (*a)(long), void (*f)(void _FAR *));
    _Cdecl strstreambuf( signed char _FAR * _s, int,
                         signed char _FAR * _strt=0);
    _Cdecl strstreambuf( unsigned char _FAR * _s, int,
                         unsigned char _FAR * _strt=0);
    _Cdecl ~strstreambuf();

    void    _Cdecl freeze(int = 1);
    char _FAR * _Cdecl str();
virtual int _Cdecl doallocate();
virtual int _Cdecl overflow(int);
virtual int _Cdecl underflow();
virtual int _Cdecl sync();
virtual streambuf _FAR * _Cdecl setbuf(char _FAR *, int);
virtual streampos  _Cdecl seekoff(streamoff, ios::seek_dir, int);

private:
    void _FAR * _Cdecl (*allocf)(long);
    void    _Cdecl (*freef)(void _FAR *);
    short   ssbflags;
    enum    { dynamic = 1, frozen = 2, unlimited = 4 };
    int next_alloc;

    void    _Cdecl init(signed char _FAR *, int, signed char _FAR *);
};


class _CLASSTYPE strstreambase : public virtual ios {
public:
    strstreambuf _FAR * _Cdecl rdbuf();

protected:
        _Cdecl strstreambase(signed char _FAR *, int, signed char _FAR *);
        _Cdecl strstreambase();
        _Cdecl ~strstreambase();
private:
        strstreambuf buf;
};
inline strstreambuf _FAR * _Cdecl strstreambase::rdbuf()
                                    { return &this->buf; }


class _CLASSTYPE istrstream : public strstreambase, public istream {
public:
        _Cdecl istrstream(signed char _FAR *);
        _Cdecl istrstream(unsigned char _FAR *);
        _Cdecl istrstream(signed char _FAR *, int);
        _Cdecl istrstream(unsigned char _FAR *, int);
        _Cdecl ~istrstream();
};


class _CLASSTYPE ostrstream : public strstreambase, public ostream {
public:
        _Cdecl ostrstream(signed char _FAR *, int, int = ios::out);
        _Cdecl ostrstream(unsigned char _FAR *, int, int = ios::out);
        _Cdecl ostrstream();
        _Cdecl ~ostrstream();

    char _FAR * _Cdecl str();
    int     _Cdecl pcount();
};
inline char _FAR * _Cdecl ostrstream::str()
                { return strstreambase::rdbuf()->str(); }
inline int  _Cdecl ostrstream::pcount()
                { return strstreambase::rdbuf()->out_waiting(); }


class _CLASSTYPE strstream : public strstreambase, public iostream {
public:
        _Cdecl strstream();
        _Cdecl strstream(signed char _FAR *, int _sz, int _m);
        _Cdecl strstream(unsigned char _FAR *, int _sz, int _m);
        _Cdecl ~strstream();

    char _FAR * _Cdecl str();
};
inline char _FAR * _Cdecl strstream::str()
                { return strstreambase::rdbuf()->str(); }

#pragma option -Vo.
#if defined(__BCOPT__)
#pragma option -po.
#endif

#endif
