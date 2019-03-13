#ifndef DPLL_H
#define DPLL_H
#include "basic.h"
#include "selectvar.h"

bool Process(DecisionTreeNode * node, CNF * cnf);
void Recover(DecisionTreeNode * node, CNF * cnf);
DecisionTreeNode * BackTrack(DecisionTreeNode * node, CNF * cnf);
DecisionTreeHead * DPLL(CNF * cnf);
bool Satisfied(CNF * cnf);
int SingleRule(CNF * cnf);
#endif // !DPLL_H
