// Turbo Assembler    Copyright (c) 1991 By Borland International, Inc.

// CALLCT.CPP
// Program to invoke the LineCount function in COUNT.ASM.

// From the Turbo Assembler Users Guide - Interfacing Turbo Assembler
//                                         with Borland C++

#include <stdio.h>

char * TestString="Line 1\nline 2\nline 3";
extern "C" {
extern unsigned int LineCount(char * StringToCount,
       unsigned int * CharacterCountPtr);
}

main()
{
   unsigned int LCount;
   unsigned int CCount;
   LCount = LineCount(TestString, &CCount);
   printf("Lines: %d\nCharacters: %d\n", LCount, CCount);
}
