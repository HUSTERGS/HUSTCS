/*  iomanip.h -- streams I/O manipulator declarations

    Copyright (c) 1990, 1992 by Borland International
    All rights reserved
*/

#ifndef __cplusplus
#error Must use C++ for the io stream manipulators.
#endif

#ifndef __IOMANIP_H
#define __IOMANIP_H

#if !defined(___DEFS_H)
#include <_defs.h>
#endif

#if !defined(__IOSTREAM_H)
#include <iostream.h>
#endif

#if !defined(__GENERIC_H)
#include <generic.h>
#endif

#pragma option -Vo-
#if defined(__BCOPT__) && !defined(_RTL_ALLOW_po)
#pragma option -po-
#endif

#define SMANIP(typ)     _Paste2(smanip_, typ)
#define SAPP(typ)       _Paste2(sapply_, typ)
#define IMANIP(typ)     _Paste2(imanip_, typ)
#define OMANIP(typ)     _Paste2(omanip_, typ)
#define IOMANIP(typ)    _Paste2(iomanip_, typ)
#define IAPP(typ)       _Paste2(iapply_, typ)
#define OAPP(typ)       _Paste2(oapply_, typ)
#define IOAPP(typ)      _Paste2(ioapply_, typ)

#define IOMANIPdeclare(typ)                                             \
class _CLASSTYPE SMANIP(typ) {                                                     \
        ios _FAR & (_Cdecl *_fn)(ios _FAR &, typ);                                          \
        typ _ag;                                                        \
public:                                                                 \
        _Cdecl SMANIP(typ)(ios _FAR & (_Cdecl *_f)(ios _FAR &, typ), typ _a) : _fn(_f), _ag(_a) { }\
        friend istream _FAR & _Cdecl operator>>(istream _FAR & _s, const SMANIP(typ) _FAR & _f) {       \
                        (*_f._fn)(_s, _f._ag); return _s; }             \
        friend ostream _FAR & _Cdecl operator<<(ostream _FAR & _s, const SMANIP(typ) _FAR & _f) {       \
                        (*_f._fn)(_s, _f._ag); return _s; }             \
        };                                                              \
class _CLASSTYPE SAPP(typ) {                                                       \
        ios _FAR & (_Cdecl *_fn)(ios _FAR &, typ);                                          \
public:                                                                 \
        SAPP(typ)(ios _FAR & (_Cdecl *_f)(ios _FAR &, typ)) : _fn(_f) { }                   \
        SMANIP(typ) _Cdecl operator()(typ _z) { return SMANIP(typ)(_fn, _z); }  \
        };                                                              \
class _CLASSTYPE IMANIP(typ) {                                                     \
        istream _FAR & (_Cdecl *_fn)(istream _FAR &, typ);                                  \
        typ _ag;                                                        \
public:                                                                 \
        _Cdecl IMANIP(typ)(istream _FAR & (_Cdecl *_f)(istream _FAR &, typ), typ _z ) :            \
                _fn(_f), _ag(_z) { }                                    \
        friend istream _FAR & _Cdecl operator>>(istream _FAR & _s, const IMANIP(typ) _FAR & _f) {       \
                return(*_f._fn)(_s, _f._ag); }                          \
        };                                                              \
class _CLASSTYPE IAPP(typ) {                                                       \
        istream _FAR & (_Cdecl *_fn)(istream _FAR &, typ);                                  \
public:                                                                 \
        _Cdecl IAPP(typ)(istream _FAR & (_Cdecl *_f)(istream _FAR &, typ)) : _fn(_f) { }           \
        IMANIP(typ) _Cdecl operator()(typ _z) {                         \
                return IMANIP(typ)(_fn, _z); }                          \
        };                                                              \
class _CLASSTYPE OMANIP(typ) {                                                     \
        ostream _FAR & (_Cdecl *_fn)(ostream _FAR &, typ);                                  \
        typ _ag;                                                        \
public:                                                                 \
        _Cdecl OMANIP(typ)(ostream _FAR & (_Cdecl *_f)(ostream _FAR &, typ), typ _z ) :            \
                _fn(_f), _ag(_z) { }                                    \
        friend ostream _FAR & _Cdecl operator<<(ostream _FAR & _s, const OMANIP(typ) _FAR & _f) {       \
                return(*_f._fn)(_s, _f._ag); }                          \
        };                                                              \
class _CLASSTYPE OAPP(typ) {                                                       \
        ostream _FAR & (_Cdecl *_fn)(ostream _FAR &, typ);                                  \
public:                                                                 \
        _Cdecl OAPP(typ)(ostream _FAR & (_Cdecl *_f)(ostream _FAR &, typ)) : _fn(_f) { }           \
        OMANIP(typ) _Cdecl operator()(typ _z) {                         \
                return OMANIP(typ)(_fn, _z); }                          \
        };                                                              \
class _CLASSTYPE IOMANIP(typ) {                                                    \
        iostream _FAR & (_Cdecl *_fn)(iostream _FAR &, typ);                                \
        typ _ag;                                                        \
public:                                                                 \
        _Cdecl IOMANIP(typ)(iostream _FAR & (_Cdecl *_f)(iostream _FAR &, typ), typ _z ) : \
                _fn(_f), _ag(_z) { }                                    \
        friend istream _FAR & _Cdecl operator>>(iostream _FAR & _s, const IOMANIP(typ) _FAR & _f) {     \
                return(*_f._fn)(_s, _f._ag); }                          \
        friend ostream _FAR & _Cdecl operator<<(iostream _FAR & _s, const IOMANIP(typ) _FAR & _f) {     \
                return(*_f._fn)(_s, _f._ag); }                          \
        };                                                              \
class _CLASSTYPE IOAPP(typ) {                                                      \
        iostream _FAR & (_Cdecl *_fn)(iostream _FAR &, typ);                                \
public:                                                                 \
        _Cdecl IOAPP(typ)(iostream _FAR & (_Cdecl *_f)(iostream _FAR &, typ)) : _fn(_f) { }        \
        IOMANIP(typ) _Cdecl operator()(typ _z) { return IOMANIP(typ)(_fn, _z); }\
        }



IOMANIPdeclare(int);
IOMANIPdeclare(long);

// set the conversion base to 0, 8, 10, or 16
smanip_int      _Cdecl _FARFUNC setbase(int _b);

// clear the flags bitvector according to the bits set in b
smanip_long     _Cdecl _FARFUNC resetiosflags(long _b);

// set the flags bitvector according to the bits set in b
smanip_long     _Cdecl _FARFUNC setiosflags(long _b);

// set fill character for padding a field
smanip_int      _Cdecl _FARFUNC setfill(int _f);

// set the floating-point precision to n digits
smanip_int      _Cdecl _FARFUNC setprecision(int _n);

// set the field width to n
smanip_int      _Cdecl _FARFUNC setw(int _n);

#pragma option -Vo.
#if defined(__BCOPT__)
#pragma option -po.
#endif

#endif
