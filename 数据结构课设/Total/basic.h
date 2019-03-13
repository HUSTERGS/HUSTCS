#ifndef BASIC_H
#define BASIC_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <string.h>

#define DISCARD_BUFFER_SIZE 100

struct intListNode {
	int value;
	intListNode * next;
};

struct intListHead
{
	intListNode * first;
	int length = 0;
};

struct Var
{
	//int index; // 变元序号，没有正负
	int positiveCount; // 正的数量
	int negativeCount; // 负的数量
	intListHead * positive;
	intListHead * negative;
	bool handled; // 表示该变元是否已经被赋值了，用于FindMax时排除变量
};

struct Clause
{
	int length;
	intListHead * variables; // 保存着子句中所有变元的位置
	int hidden;  // 指示是否被删除，以及被删除的原因
};

struct CNF {
	int varNum;
	int clauseNum;
	Var * variables;
	Clause * clauses;
};

struct DecisionTreeNode
{
	int assumption;
	bool valid;
	DecisionTreeNode * next;
	DecisionTreeNode * back;
};

struct DecisionTreeHead
{
	DecisionTreeNode * firstNode;
};



void addElem(int target, intListHead * head);
inline void deleteElem(int target, intListHead * head) {
	--head->length;
}

inline void recoverElem(int target, intListHead * head) {
	++head->length;
}

void printAssumptions(DecisionTreeHead * head);
DecisionTreeNode * addAssumption(int assumption, bool valid, DecisionTreeHead * head);
void InitIntListHead(CNF * cnf);
int LoadFile(const char * filename, CNF * cnf);
void DisplayResult(DecisionTreeHead * Head);
int * TurnToArray(DecisionTreeHead * result, CNF * cnf);
void PrintArray(int * resultArray, int length);
void CheckFinalResult(int * resultArray, CNF * cnf);
void DestroyList(intListHead * head);
void DestroyCNF(CNF * cnf);
#endif 





