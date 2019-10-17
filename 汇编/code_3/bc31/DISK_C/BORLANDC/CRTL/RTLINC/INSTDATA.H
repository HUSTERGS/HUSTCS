/*------------------------------------------------------------------------
 * filename - instdata.h
 *
 *        definitions for DLL instance data
 *-----------------------------------------------------------------------*/

/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     C/C++ Run Time Library - Version 4.0                     |*/
/*|                                                              |*/
/*|                                                              |*/
/*|     Copyright (c) 1991 by Borland International              |*/
/*|     All Rights Reserved.                                     |*/
/*|                                                              |*/
/*[]------------------------------------------------------------[]*/

#if !defined(__INSTDATA_H)
#define __INSTDATA_H

#if !defined( __WINDOWS_H )
#include <windows.h>
#endif

#if !defined( __STDLIB_H )
#include <stdlib.h>
#endif

const int DEFAULTINSTANCEDATATABLESIZE = 10;
const unsigned long INSTANCEDATASIGNATURE = 0x4e494246L;

class TInstanceDataBase
{
private:
    unsigned long Signature;
protected:    
    TInstanceDataBase() { Signature = INSTANCEDATASIGNATURE; }
public:
    BOOL Verify() { return (Signature==INSTANCEDATASIGNATURE); }
};

struct TInstanceDataEntry
{
    HANDLE hTask;
    TInstanceDataBase far * pInstanceData;
private:
    TInstanceDataEntry() {};    // forces no inheritance
};

class TInstanceDataTable
{
    int NumEntries;
    TInstanceDataEntry * Table;
public:
    TInstanceDataTable(int InitialCount = DEFAULTINSTANCEDATATABLESIZE);

    static TInstanceDataEntry * AllocTable(int Count);
    static void FreeTable(TInstanceDataEntry *pTable);

    virtual TInstanceDataBase far *NewEntry() = 0;

    BOOL AddEntry(HANDLE hTask, TInstanceDataBase far * pClientData);
    BOOL DeleteEntry(HANDLE hTask, TInstanceDataBase far * pClientData);

    TInstanceDataBase far * GetClientData(HANDLE hTask);
    TInstanceDataEntry *GrowTable(int Increment = 10);

};

#endif // __INSTDATA_H
