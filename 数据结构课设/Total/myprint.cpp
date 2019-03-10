#include "myprint.h"


void printAssumptions(DecisionTreeHead * head) {
	system("cls");
	DecisionTreeNode * tempNode = head->firstNode;
	while (tempNode)
	{
		printf("%d", tempNode->assumption);
		if (!tempNode->valid)
			printf(" false");
		else
			printf(" true ");
		printf("\t");
		tempNode = tempNode->next;
	}
}

void DisplayData(CNF * cnf) {
	int clauseNum = cnf->clauseNum;
	for (int i = 1; i <= clauseNum; ++i) {
		intListNode * temp = cnf->clauses[i].variables->first;
		while (temp)
		{
			printf("%d ", temp->value);
			temp = temp->next;
		}
		printf("length = %d ", cnf->clauses[i].length);
		printf("\n");
	}
}

void DisplayResult(DecisionTreeHead * Head) {
	DecisionTreeNode * tempNode = Head->firstNode;
	while (tempNode)
	{
		printf("%d ", tempNode->assumption);
		tempNode = tempNode->next;
	}
}

void PrintArray(int * resultArray, int length) {
	for (int i = 1; i < length; ++i)
		printf("%d ", *(resultArray + i));
}