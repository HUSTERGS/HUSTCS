// Borland C++ - (C) Copyright 1991, 1992 by Borland International

// list.cpp:      Implementation of the List Class

#include <iostream.h>
#include "list2.h"

int List::put_elem(int elem, int pos)
{
   if (0 <= pos && pos < nmax)
   {
      list[pos] = elem;
      return 0;
   }
   else
      return -1;     // non-zero means error
}

int List::get_elem(int& elem, int pos)
{
   if (0 <= pos && pos < nmax)
   {
      elem = list[pos];
      return 0;
   }
   else
      return -1;     // non-zero means error
}

void List::print()
{
   for (int i = 0; i < nelem; ++i)
      cout << list[i] << "\n";
}
