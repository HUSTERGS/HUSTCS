/*------------------------------------------------------------------------
 * filename - rtldata.cpp
 *
 * Functions to initialize and access DLL RTL instance data
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1991, 1992 by Borland International
 *      All Rights Reserved.
 *
 */

#include <InstData.h>
#include <RtlData.h>
#include <fcntl.h>
#include <dos.h>
#include <stdio.h>
#include <_nfile.h>

class _RTLDataClass : TInstanceDataBase, public _RTLData
{

public:

    _RTLDataClass();
    void *operator new (size_t s);
    void operator delete(void *ptr);

};

static _RTLData initValues =
{
    //  _streams initial values
    {
        { 0, _F_STDIN,   0, 0, 0, NULL, NULL, 0, 0 },
        { 0, _F_STDOUT,  1, 0, 0, NULL, NULL, 0, 0 },
        { 0, _F_STDERR,  2, 0, 0, NULL, NULL, 0, 0 },
        { 0, _F_STDAUX,  3, 0, 0, NULL, NULL, 0, 0 },
        { 0, _F_STDPRN,  4, 0, 0, NULL, NULL, 0, 0 }
    //  remainder are initialized to all 0's
    },

    //  _openfd initial values
    {
    O_RDONLY | O_DEVICE,
    O_WRONLY | O_DEVICE,
    O_WRONLY | O_DEVICE,
    O_RDWR   | O_DEVICE | O_BINARY,
    O_WRONLY | O_DEVICE | O_BINARY,

    ~0, ~0, ~0,
    ~0, ~0, ~0, ~0,
    ~0, ~0, ~0, ~0,
    ~0, ~0, ~0, ~0
    },

    _NFILE_,    // _nfiles

    O_TEXT,     // _fmode
    ~0,         // _notUmask
    0,          // _doserrno
    0,          // _new_handler
    {'\0'},     // strbuf (strerror.c)
    0,          // Ss (strtok.c)
    {'\0'},     // template (tmpnam.c)
    0,          // _tmpnum (tmpnam.c)
    {'\0'},     // a (ctime.c)
    {'\0'},     // _DfltZone (tzset.cas)
    {'\0'},     // _DfltLight (tzset.cas)
    DefaultTimeZone * 60L * 60L,        // timezone set for EST (tzset.cas)
    DefaultDaylight     // daylight set for daylight savings (tzset.cas)
};

_RTLDataClass::_RTLDataClass()
{
    int i;

    (_RTLData&)*this = initValues;
    for( i = 5; i < _NFILE_; i++ )
        _streams[i].fd = -1;
    for( i = 0; i < _NFILE_; i++ )
        _streams[i].token = (short)&_streams[i];
    _AH = 0;
    geninterrupt( 0x1A );
    _StartTime = ((long)_DX << 16) | _CX;
    tzname_[0] = &_DfltZone[0];
    tzname_[1] = &_DfltLight[0];
};

void *_RTLDataClass::operator new (size_t s)
{
    return GlobalLock(GlobalAlloc(GMEM_ZEROINIT, s));
}

void _RTLDataClass::operator delete(void *ptr)
{
    HANDLE hMem = LOWORD(GlobalHandle(FP_SEG(ptr)));
    if (hMem)
        if (GlobalUnlock(hMem))
            GlobalFree(hMem);
}

const DEFTABLESIZE = 10;

class TRTLDataTable : public TInstanceDataTable
{

public:

    TRTLDataTable( int initCount = DEFTABLESIZE ) :
        TInstanceDataTable( initCount ) {}
    _RTLDataClass _FAR * GetClientData(HANDLE hTask)
        { return (_RTLDataClass _FAR *)
                    TInstanceDataTable::GetClientData(hTask); }
protected:

    virtual TInstanceDataBase far *NewEntry();

};

TInstanceDataBase far *TRTLDataTable::NewEntry()
{
    return (TInstanceDataBase far *) new _RTLDataClass;
}

extern "C" _RTLData _FAR * _export pascal __getRTLInstanceData()
{
    static TRTLDataTable RTLData;
    return (_RTLData _FAR *)RTLData.GetClientData(GetCurrentTask());
}

extern "C" int far * _export __getErrno()
{
    return &(__getRTLInstanceData()->errno_);
}

extern "C" int far * _export __getDOSErrno()
{
    return &(__getRTLInstanceData()->_doserrno_);
}

extern "C" FILE far * _export __getStream( int strm )
{
    return &((__getRTLInstanceData()->_streams)[strm]);
}

extern "C" TSubAllocClientData far *__GetSubAllocClientData(void)
{
    return &(__getRTLInstanceData()->subAllocData);
}

#undef sys_errlist

extern char _FAR *_Cdecl sys_errlist[];

extern "C" char far * far * _export __get_sys_errlist()
{
    return sys_errlist;
}

#undef sys_nerr

extern  int _Cdecl sys_nerr;

extern "C" int _export __get_sys_nerr()
{
    return sys_nerr;
}

extern "C" int far * _export __getDaylight()
{
    return &(__getRTLInstanceData()->daylight_);
}

extern "C" long far * _export __getTimezone()
{
    return &(__getRTLInstanceData()->timezone_);
}

extern "C" char far * far * _export __getTzname()
{
    return (__getRTLInstanceData()->tzname_);
}

