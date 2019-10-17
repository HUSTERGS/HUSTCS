/* Copyright (c) 1990, 1992, Borland International */
#include <stdio.h>
#include <dos.h>   /* contains prototype for delay() */
void route66(void); void highway80(void);
void main(void)
{
    printf("Entering main\n");
    route66();
    printf("Back in main\n");
    delay(1000);
    highway80();
    printf("Back in main\n");
    delay(1000);
    printf("Leaving main\n\n");
}

void route66(void)
{
    printf("Entering Route 66\n");
    delay(2000);
    printf("Leaving  Route 66\n");
}

void highway80(void)
{
    printf("Entering Highway 80\n");
    delay(2000);
    printf("Leaving Highway 80\n");
}
