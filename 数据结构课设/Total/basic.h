#ifndef BASIC_H
#define BASIC_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>
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
	//int index; // ��Ԫ��ţ�û������
	int positiveCount; // ��������
	int negativeCount; // ��������
	intListHead * positive;
	intListHead * negative;
	bool handled; // ��ʾ�ñ�Ԫ�Ƿ��Ѿ�����ֵ�ˣ�����FindMaxʱ�ų�����
};

struct Clause
{
	int length;
	intListHead * variables; // �������Ӿ������б�Ԫ��λ��
	int hidden;  // ָʾ�Ƿ�ɾ�����Լ���ɾ����ԭ��
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



inline void deleteElem(int target, intListHead * head) {
	--head->length;
}

inline void recoverElem(int target, intListHead * head) {
	++head->length;
}
void addElem(int target, intListHead * head);
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
void DisplayData(CNF * cnf);
void writeFile(int * resultArray, int length, float runtime, const char *filename);
#endif 





