/* stdiostream.h -- class stdiobuf and stdiostream declarations

    Copyright (c) 1990, 1992 by Borland International
    All rights reserved

    NOTE: These are inefficient and obsolete.  Use the standard classes and
    functions in <fstream.h> instead.
*/

#ifndef __cplusplus
#error Must use C++ for the type stdiostream.
#endif

#ifndef __STDSTREAM_H
#define __STDSTREAM_H

#if !defined(___DEFS_H)
#include <_defs.h>
#endif

#if !defined(__IOSTREAM_H)
#include <iostream.h>
#endif

#if !defined(__STDIO_H)
#include <stdio.h>
#endif

#pragma option -Vo-
#if defined(__BCOPT__) && !defined(_RTL_ALLOW_po)
#pragma option -po-
#endif

_CLASSDEF(stdiobuf)
_CLASSDEF(stdiostream)

class _CLASSTYPE stdiobuf : public streambuf {
public:
    _Cdecl stdiobuf(FILE _FAR *);
    FILE _FAR * _Cdecl stdiofile();
    _Cdecl ~stdiobuf();

    virtual int _Cdecl overflow(int=EOF);
    virtual int _Cdecl pbackfail(int);
    virtual int _Cdecl sync();
    virtual streampos _Cdecl seekoff(streamoff, ios::seek_dir, int);
    virtual int _Cdecl underflow();

private:
    FILE _FAR * sio;
    char    lahead[2];
};
inline  FILE _FAR * _Cdecl stdiobuf::stdiofile() { return sio; }


class _CLASSTYPE stdiostream : public ios {
public:
        _Cdecl stdiostream(FILE _FAR *);
        _Cdecl ~stdiostream();
    stdiobuf _FAR * _Cdecl rdbuf();

private:
    stdiobuf buf;
};
inline  stdiobuf _FAR * _Cdecl stdiostream::rdbuf() { return &buf; }

#pragma option -Vo.
#if defined(__BCOPT__)
#pragma option -po.
#endif

#endif
