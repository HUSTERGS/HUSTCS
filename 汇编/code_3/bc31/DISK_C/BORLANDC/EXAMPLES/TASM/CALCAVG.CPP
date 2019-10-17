// Turbo Assembler    Copyright (c) 1991 By Borland International, Inc.

/* CALCAVG.CPP
   The C++ portion of an example of assembler code that calls
   a Borland C++ function in order to get a floating-point
   calculation performed.

*/

// From the Turbo Assembler Users Guide - Interfacing Turbo Assembler
//                                         with Borland C++

extern float Average(int far * ValuePtr, int NumberOfValues);
#define NUMBER_OF_TEST_VALUES 10
int TestValues[NUMBER_OF_TEST_VALUES] = {
   1, 2, 3, 4, 5, 6, 7, 8, 9, 10
};

main()
{
   printf("The average value is: %f\n",
          Average(TestValues, NUMBER_OF_TEST_VALUES));
}
float IntDivide(int Dividend, int Divisor)
{
   return( (float) Dividend / (float) Divisor );
}
