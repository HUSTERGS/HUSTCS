/*------------------------------------------------------------------------
 * filename - instdata.c
 *
 * Functions to manage instance data for RTL DLL
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1991, 1992 by Borland International
 *      All Rights Reserved.
 *
 */

#include <windows.h>
#include <dos.h>
#include <mem.h>
#include <instdata.h>

#if defined(__DLL__)

TInstanceDataTable::TInstanceDataTable(int InitialCount)
{
    if (InitialCount != 0)
    Table = AllocTable(InitialCount);

    if (Table)
         NumEntries = InitialCount;
    else
         NumEntries = 0;
}

// TInstanceDataTable::~TInstanceDataTable()
// {
//     if (NumEntries != 0 && Table)
//     {
//         FreeTable(Table);
//         Table = NULL;
//         NumEntries = 0;
//     }
// }

BOOL TInstanceDataTable::AddEntry(HANDLE hTask,
                                  TInstanceDataBase far *pClientData)
{
    TInstanceDataEntry *pFreeEntry = NULL;  // no free entry yet

    // First see if table already.  If so, replace entry

    for (TInstanceDataEntry * pEntry = Table; pEntry < &Table[NumEntries];
         pEntry++)
    {
        if (pEntry->hTask == hTask) // already in table?
        {
            pEntry->pInstanceData = pClientData;
            return TRUE;
        }
        else                    // see if entry is free
        {
            if (!pFreeEntry && pEntry->hTask == 0)  // remember this entry
                pFreeEntry = pEntry;
        }
    }

    // Not in table.  See if we encountered a free entry in table.  If
    // so, use it.  Otherwise grow table.

    if ((pEntry = (pFreeEntry ? pFreeEntry : GrowTable())) != NULL)
    {
        pEntry->hTask = hTask;
        pEntry->pInstanceData = pClientData;
        return TRUE;
    }
    else
        return FALSE;
}

TInstanceDataTable::DeleteEntry(HANDLE hTask,
                                TInstanceDataBase far *pClientData)
{
    for (TInstanceDataEntry * pEntry = Table; pEntry < &Table[NumEntries];
         pEntry++)
    {
        if (pEntry->hTask == hTask && pEntry->pInstanceData == pClientData)
        {
            pEntry->hTask = 0;       // found entry.  Zero it.
            pEntry->pInstanceData = 0;
            return TRUE;            // indicate success
        }
    }
    return FALSE;   // not found
}

TInstanceDataEntry *TInstanceDataTable::GrowTable(int Increment)
{
    int OldNumEntries = NumEntries;
    TInstanceDataEntry * OldInstanceDataTable = Table;

    NumEntries = NumEntries + Increment;

    Table = AllocTable(NumEntries);

    // copy old table to new location
    _fmemcpy(Table, OldInstanceDataTable,
        OldNumEntries * sizeof(TInstanceDataEntry));

    FreeTable(OldInstanceDataTable);

    // return pointer to first entry in new block
    return Table;
}

TInstanceDataBase far *TInstanceDataTable::GetClientData(HANDLE hTask)
{
    TInstanceDataBase far *InstanceDataPtr;
    WORD Temp;

    for (TInstanceDataEntry * pEntry = Table; pEntry < &Table[NumEntries];
         pEntry++)
    {
        if (pEntry->hTask == hTask)
        {
            InstanceDataPtr = pEntry->pInstanceData;
            Temp = FP_SEG(InstanceDataPtr);

            asm lar ax, Temp;       // get access rights
            asm jnz invalid;        // invalid selector

            asm and ax, 0x0800;     // code or data
            asm jnz invalid;        // code

            if (InstanceDataPtr->Verify())
                return InstanceDataPtr;
        invalid:
            // Selector invalid.  Create a new client data object
            // and set pEntry->InstanceData to point to it.
            return (pEntry->pInstanceData = NewEntry());
        }
    }
    // no entry found in table.  Add one.
    InstanceDataPtr = NewEntry();
    AddEntry(hTask, InstanceDataPtr);
    return InstanceDataPtr;
}

TInstanceDataEntry * TInstanceDataTable::AllocTable(int Count)
{
    TInstanceDataEntry * pTable;
    pTable = (TInstanceDataEntry *)
        LocalLock(LocalAlloc(LMEM_ZEROINIT,
            Count * sizeof(TInstanceDataEntry)));
    return pTable;
}

void TInstanceDataTable::FreeTable(TInstanceDataEntry *pTable)
{
    HANDLE hMem = LocalHandle(FP_OFF(pTable));
    if (LocalUnlock(hMem))
        LocalFree(hMem);
}

#endif // __DLL__
