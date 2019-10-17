// Borland C++ - (C) Copyright 1991, 1992 by Borland International

// list2.h:   A Integer List Class
// from Getting Started
const int Max_elem = 10;

class List
{
protected:     // The protected keyword gives subclasses
               // direct access to inherited members
   int *list;        // An array of integers
   int nmax;         // The dimension of the array
   int nelem;        // The number of elements

public:
   List(int n = Max_elem) {list = new int[n]; nmax = n; nelem = 0;};
   ~List() {delete list;};
   int put_elem(int, int);
   int get_elem(int&, int);
   void setn(int n) {nelem = n;};
   int getn() {return nelem;};
   void incn() {if (nelem < nmax) ++nelem;};
   int getmax() {return nmax;};
   virtual void print();                   // line 22
};
