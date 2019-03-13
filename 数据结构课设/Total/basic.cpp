#include "basic.h"

void addElem(int target, intListHead * head) {
	intListNode * newNode = (intListNode *)malloc(sizeof(intListNode));

	assert(newNode != nullptr);
	// old
	newNode->value = target;
	newNode->next = head->first;
	head->first = newNode;
	++head->length;
}


void InitIntListHead(CNF * cnf) {
	cnf->clauses = (Clause *)malloc((cnf->clauseNum + 1) * sizeof(Clause));
	cnf->variables = (Var *)malloc((cnf->varNum + 1) * sizeof(Var));

	assert(cnf->clauses != nullptr && cnf->variables != nullptr);

	for (int i = cnf->clauseNum; i > 0; --i) {

		cnf->clauses[i].length = 0;
		cnf->clauses[i].variables = (intListHead *)malloc(sizeof(intListHead));
		assert(cnf->clauses[i].variables != nullptr);

		cnf->clauses[i].variables->length = 0;
		cnf->clauses[i].hidden = 0;
		cnf->clauses[i].variables->first = nullptr;
	}
	for (int i = cnf->varNum; i > 0; --i) {

		cnf->variables[i].negative = (intListHead *)malloc(sizeof(intListHead));
		cnf->variables[i].positive = (intListHead *)malloc(sizeof(intListHead));
		assert(cnf->variables[i].negative != nullptr);
		assert(cnf->variables[i].positive != nullptr);

		cnf->variables[i].negative->length = 0;
		cnf->variables[i].positive->length = 0;
		cnf->variables[i].negative->first = nullptr;
		cnf->variables[i].positive->first = nullptr;
		cnf->variables[i].handled = false;
	}
}


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

DecisionTreeNode * addAssumption(int assumption, bool valid, DecisionTreeHead * head) {
	DecisionTreeNode * tempNode = head->firstNode;
	if (tempNode == nullptr) {
		// 此时还没有任何assumption
		head->firstNode = (DecisionTreeNode *)malloc(sizeof(DecisionTreeNode));

		assert(head->firstNode != nullptr);

		head->firstNode->back = nullptr;
		head->firstNode->next = nullptr;
		head->firstNode->assumption = assumption;
		head->firstNode->valid = valid;
		return head->firstNode;
	}
	while (tempNode->next)
		tempNode = tempNode->next;
	// 找到最后一个节点
	tempNode->next = (DecisionTreeNode *)malloc(sizeof(DecisionTreeNode));

	assert(tempNode->next != nullptr);

	tempNode->next->back = tempNode;
	tempNode->next->next = nullptr;
	tempNode->next->assumption = assumption;
	tempNode->next->valid = valid;
	return tempNode->next;
}

int LoadFile(const char * filename, CNF * cnf) {
	FILE * fp = fopen(filename, "r");
	if (nullptr == fp) {
		return -1;
	}
	else {
		char firstChar = fgetc(fp);
		while ('c' == firstChar) {
			// 如果是 c 说明是注释，直接跳到下一行
			char * discardBuffer = (char *)malloc(DISCARD_BUFFER_SIZE * sizeof(char));
			fgets(discardBuffer, DISCARD_BUFFER_SIZE, fp);
			firstChar = fgetc(fp);
			free(discardBuffer);
			discardBuffer = nullptr;
		}
		if ('p' == firstChar) {
			char * discardBuffer = (char *)malloc(DISCARD_BUFFER_SIZE * sizeof(char));
			fscanf(fp, "%s", discardBuffer); // 跳过cnf 字符串
			fscanf(fp, "%d", &cnf->varNum); // 读取变元数
			fscanf(fp, "%d", &cnf->clauseNum); // 读取子句数
			free(discardBuffer);
			discardBuffer = nullptr;
		}

		// 多分配一个空间，方便计算

		InitIntListHead(cnf);

		// 替换
		int clauseLength;
		int totalLength = cnf->clauseNum;
		for (int i = 1; i <= totalLength; ++i) {
			clauseLength = 0;
			int temp; // 储存读取到的数字
			fscanf(fp, "%d", &temp);

			while (temp)
			{
				if (temp > 0) {
					addElem(i, cnf->variables[temp].positive);
					addElem(temp, cnf->clauses[i].variables);
				}
				else {
					addElem(i, cnf->variables[-temp].negative);
					addElem(temp, cnf->clauses[i].variables);
				}
				++clauseLength;
				fscanf(fp, "%d", &temp);
			}
			cnf->clauses[i].length = clauseLength;
			assert(cnf->clauses[i].length >= 0);
		}
	}
	fclose(fp);
}


void DisplayResult(DecisionTreeHead * Head) {
	DecisionTreeNode * tempNode = Head->firstNode;
	while (tempNode)
	{
		printf("%d ", tempNode->assumption);
		tempNode = tempNode->next;
	}
}


int * TurnToArray(DecisionTreeHead * result, CNF * cnf) {
	int * resultArray = (int *)calloc((cnf->varNum + 1), sizeof(int));

	assert(resultArray != nullptr);

	DecisionTreeNode * tempNode = result->firstNode;
	while (tempNode)
	{
		resultArray[abs(tempNode->assumption)] = tempNode->assumption;
		tempNode = tempNode->next;
	}
	return resultArray;
}

void PrintArray(int * resultArray, int length) {
	for (int i = 1; i < length; ++i)
		printf("%d ", *(resultArray + i));
}

void CheckFinalResult(int * resultArray, CNF * cnf) {
	intListNode * tempNode = nullptr;
	for (int i = 1; i <= cnf->clauseNum; ++i) {
		bool flag = false;
		tempNode = cnf->clauses[i].variables->first;
		while (tempNode)
		{
			if (resultArray[abs(tempNode->value)] * tempNode->value > 0)
				flag = true;
			tempNode = tempNode->next;
		}
		if (!flag)
			printf("Clause %d gg\n", i);
	}
}

void DestroyList(intListHead * head) {
	if (!head) {
		intListNode * tempNode = head->first;
		intListNode * tempNodeFree = nullptr;
		while (tempNode) {
			tempNodeFree = tempNode;
			tempNode = tempNode->next;
			free(tempNodeFree);
		}
		head->first = nullptr;
		free(head);
		head = nullptr;
		tempNode = tempNodeFree = nullptr;
	}
}

void DestroyCNF(CNF * cnf) {
	for (int i = cnf->varNum - 1; i >= 0; --i) {
		DestroyList(cnf->variables[i].positive);
		DestroyList(cnf->variables[i].negative);
		cnf->variables[i].positive = cnf->variables[i].negative = nullptr;
	}

	free(cnf->variables);
	cnf->variables = nullptr;

	for (int i = cnf->clauseNum - 1; i >= 0; --i) {
		DestroyList(cnf->clauses[i].variables);
		cnf->clauses[i].variables = nullptr;
	}

	free(cnf->clauses);
	cnf->clauses = nullptr;
	free(cnf);
}