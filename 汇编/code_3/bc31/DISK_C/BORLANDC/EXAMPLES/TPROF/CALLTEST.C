/* Program CALLTEST */
/* Copyright (c) 1990, 1992, Borland International */
void a(void); void b1(void); void b2(void); void c(void);

void main(void)
{
  c();
  b2();
  b1();
  a();
}

void a(void)
{
  int i;

  for (i=0; i<100; i++)
    b2();
  b1();
}

void b1(void)
{
  int i;

  for (i=0; i<33; i++)
    c();
}

void b2(void)
{
  int i;

  for (i=0; i<77; i++)
    c();
}

void c(void)
{
  int i;

  for (i=0; i<3; i++)
    ;
}
