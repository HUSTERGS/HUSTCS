/* Copyright (c) 1990, 1992, Borland International */
/*  Program for generating prime numbers using Euclid's method */
#include <stdio.h>
int primes[1000];
#define MAXPRIMES 1000

void main(void)
{
   int j;
   int lastprime, curprime;

   primes[0] = 2;
   primes[1] = 3;
   lastprime = 1;
   curprime  = 3;

   printf("prime %d = %d\n", 0, primes[0]);
   printf("prime %d = %d\n", 1, primes[1]);
   while(curprime < MAXPRIMES)
   {
      for(j = 0; j <= lastprime; j++)
         if((curprime % primes[j]) == 0)
         {
            curprime += 2;

            break;
         }
      if(j <= lastprime)
         continue;
      lastprime++;
      printf("prime %d = %d\n", lastprime, curprime);
      primes[lastprime] = curprime;
      curprime += 2;
   }
}
