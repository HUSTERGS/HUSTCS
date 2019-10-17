/*------------------------------------------------------------------------
 * filename - suballoc.cpp
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1991, 1992 by Borland International
 *      All Rights Reserved.
 *
 */

#if !defined(__DLL__)
struct far TSubAllocClientData
{
        void far *MemBlockPtr;
        int MemBlockCount;
};

extern "C"
{
        extern TSubAllocClientData far * far __GetSubAllocClientData();
}

TSubAllocClientData SubAllocClientData;

TSubAllocClientData far * far __GetSubAllocClientData()
{
    return &SubAllocClientData;
}
#endif // !__DLL__
