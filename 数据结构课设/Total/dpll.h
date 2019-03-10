#include "basic.h"

#ifndef _DPLL_H
#define _DPLL_H

inline void deleteElem(int target, intListHead * head);
inline void recoverElem(int target, intListHead * head);
DecisionTreeNode * addAssumption(int assumption, BOOL valid, DecisionTreeHead * head);
bool Process(DecisionTreeNode * node, CNF * cnf);
void Recover(DecisionTreeNode * node, CNF * cnf);
DecisionTreeNode * BackTrack(DecisionTreeNode * node, CNF * cnf);
bool Satisfied(CNF * cnf);
int SingleRule(CNF * cnf);
DecisionTreeHead * DPLL(CNF * cnf);

#endif // !_DPLL_H

