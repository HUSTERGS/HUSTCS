class count_add {
     // Private member variables:
     int access_count;  // Number of times this is accessed
     int count;         // The ongoing count
   public:
        count_add(void){ access_count=0;
                        count=0;
                      }
        int  get_count(void){return count;}

        // Two functions that will actually be written 
        // in assembler: 
        void increment(void);
        void add(int what_to_add=-1); 
         // Note that the default value only
         // affects calls to add, it does not
         // affect the code for add.
}

extern "C" {
  // To create some unique, meaningful names for the 
  // assembler routines, prepend the name of the class 
  // to the assembler routine. Unlike some assemblers, 
  // Turbo Assembler has no problem with long names.
  void count_add_increment(int *count);  // We will pass a 
                                         // pointer to the
                                         // count variable. 
                                         // Assembler will
                                         // do the incrementing.
  void count_add_add(int *count,int what_to_add);
}

void count_add::increment(void)
{
  count_add_increment(&count);
}

void count_add::add(int what_to_add)
{
  count_add(&count,int what_to_add);
}
