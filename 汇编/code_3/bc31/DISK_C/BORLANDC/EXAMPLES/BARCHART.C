// Borland C++ - (C) Copyright 1991, 1992 by Borland International

// BARCHART Example Program

#include           <stdio.h>
#include           <stdlib.h>
#include           <float.h>
#include           <graphics.h>
#include           <math.h>
#include           <conio.h>

#define            MAX        50
#define            ARRAYMAX   10

void makegraph(float p[]);

void main(void)
{
  int              i;
  int              scores[ARRAYMAX];
  float            percents[ARRAYMAX];

  for (i = 0; i < ARRAYMAX; i++)
    {
    printf("\nEnter score between 0 and %d:  ", MAX);
    scanf("%d", &scores[i]);
    }
  for (i = 0; i < ARRAYMAX; i++)
    percents[i] = ((float) scores[i]) / MAX;

  printf("\n\n\n\tSCORE\tPERCENT");
  for (i = 0; i < ARRAYMAX; i++)
    printf("\n%d. \t%d\t%3.0f", i + 1, scores[i], (percents[i] * 100));
  getch();
  makegraph(percents);
}

void makegraph(float p[])
{
  int              g_driver, g_mode;
  int              i, left, top, wide, bottom, deep;

  detectgraph(&g_driver, &g_mode);
  initgraph(&g_driver, &g_mode, "..\\bgi");
  wide = (int)((getmaxx()) / ((ARRAYMAX * 2 ) + 1));
  bottom = getmaxy() - 20;
  deep = (int) (wide / 4);
  left = wide;
  for (i = 0; i < ARRAYMAX; i++)
    {
    top = (bottom) - ((int)(p[i] * 300));
    bar3d(left, top, (left + wide), bottom, deep, 1);
    left += (wide * 2);
    }
  getch();
  closegraph();
  return;
}

