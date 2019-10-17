// Turbo Assembler    Copyright (c) 1988, 1991 By Borland International, Inc.

/* SHOWTOT.CPP
   The program provides external data to DOTOTAL.ASM
*/

// From the Turbo Assembler Users Guide - Interfacing Turbo Assembler
//                                         with Borland C++


extern "C" {
extern int DoTotal(void);
}

extern int StartingValue;

int Repetitions;
main()
{
   int i;
   Repetitions = 10;
   StartingValue = 2;
   printf("%d\n", DoTotal());
}
