// Borland C++ - (C) Copyright 1991, 1992 by Borland International

// def2.h:   A word definition class
// from Getting Started
#include <string.h>

const int Maxmeans = 5;

class Definition
{
   char *word;                      // Word being defined
   char *meanings[Maxmeans];        // Various meanings of this word
   int nmeanings;

public:
   void put_word(char *);
   char *get_word(char *s) {return strcpy(s,word);};
   void add_meaning(char *);
   char *get_meaning(int, char *);
   friend class Dictionary;         // line 18
};

