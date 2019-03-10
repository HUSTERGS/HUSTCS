#include "dpll.h"

#ifndef _SELECTVAR_H
#define _SELECTVAR_H

void updateCountNum(CNF * cnf);
void updateCountNum_2(CNF * cnf);
int FindMax_2(CNF * cnf);
int FindMax(CNF *cnf);
int Findmax_new_2(CNF * cnf);
int ReverseOrder(CNF * cnf);
int InOrder(CNF * cnf);
int SelectVar(CNF * cnf);


#endif // !_SELECTVAR_H
