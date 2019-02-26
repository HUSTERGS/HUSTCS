#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
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
	int index; // 变元序号，没有正负
	int positiveCount; // 正的数量
	int negativeCount; // 负的数量
	intListHead positive;
	intListHead negative;
	bool handled; // 表示该变元是否已经被赋值了，用于FindMax时排除变量
};

struct Clause
{
	int length;
	intListHead variables; // 保存着子句中所有变元的位置
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


void addElem(int target, intListHead * head) {
	intListNode * newNode = (intListNode *)calloc(1, sizeof(intListNode));

	assert(newNode != nullptr);
	// old
	newNode->value = target;
	newNode->next = head->first;
	head->first = newNode;
	++head->length;
	
	// new
	/*newNode->value = target;
	if (head->first)
	{
		newNode->next = head->first;
		head->first = newNode;
	}
	else {
		head->first = newNode;
		newNode->next = nullptr;
	}
	head->length++;*/
}

void deleteElem(int target, intListHead * head) {
	// 其实实际上并没有删除，只是将其放到链表的最后一个，并将length减去1
	intListNode * temp = head->first;
	intListNode * pre = temp;
	if (head->first->value == target) {
		while (temp->next)
			temp = temp->next;
		temp->next = head->first;
		head->first = head->first->next;
		temp->next->next = nullptr;
		--head->length;
		return;
	}
	while (temp->next != nullptr)
	{
		if (temp->next->value == target)
			pre = temp;
		temp = temp->next;
	}
	if (pre->next->next == nullptr) {
		--head->length;
	}
	else {
		temp->next = pre->next;
		pre->next = pre->next->next;
		temp->next->next = nullptr;
		--head->length;
	}
	//--head->length;
}

void recoverElem(int target, intListHead * head) {
	// 如果是当前assumption导致的删除的话，必然是最后一个元素,如果最开始是单子句的话，也不可能需要回溯
	intListNode * tempNode = head->first;
	while (tempNode->next->value != target)
		tempNode = tempNode->next;
	tempNode->next->next = head->first;
	head->first = tempNode->next;
	tempNode->next = nullptr;
	++head->length;
}

DecisionTreeNode * addAssumption(int assumption, bool valid, DecisionTreeHead * head) {
	DecisionTreeNode * tempNode = head->firstNode;
	if (tempNode == nullptr) {
		// 此时还没有任何assumption
		head->firstNode = (DecisionTreeNode *)calloc(1, sizeof(DecisionTreeNode));

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
	tempNode->next = (DecisionTreeNode *)calloc(1, sizeof(DecisionTreeNode));

	assert(tempNode->next != nullptr);

	tempNode->next->back = tempNode;
	tempNode->next->next = nullptr;
	tempNode->next->assumption = assumption;
	tempNode->next->valid = valid;
	return tempNode->next;
}

void InitIntListHead(CNF * cnf) {
	cnf->clauses = (Clause *)calloc((cnf->clauseNum + 1), sizeof(Clause));
	cnf->variables = (Var *)calloc((cnf->varNum + 1), sizeof(Var));

	assert(cnf->clauses != nullptr && cnf->variables != nullptr);

	for (int i = cnf->clauseNum; i > 0; --i) {
		cnf->clauses[i].variables.length = 0;
		cnf->clauses[i].hidden = 0;
		cnf->clauses[i].variables.first = nullptr;
	}
	for (int i = cnf->varNum; i > 0; --i) {
		cnf->variables[i].negative.length = 0;
		cnf->variables[i].positive.length = 0;
		cnf->variables[i].negative.first = nullptr;
		cnf->variables[i].positive.first = nullptr;
	}
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
			char * discardBuffer = (char *)calloc(DISCARD_BUFFER_SIZE, sizeof(char));
			fgets(discardBuffer, DISCARD_BUFFER_SIZE, fp);
			firstChar = fgetc(fp);
			free(discardBuffer);
			discardBuffer = nullptr;
		}
		if ('p' == firstChar) {
			char * discardBuffer = (char *)calloc(DISCARD_BUFFER_SIZE, sizeof(char));
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
					cnf->variables[temp].handled = false;
					addElem(i, &cnf->variables[temp].positive);
					addElem(temp, &cnf->clauses[i].variables);
				}
				else {
					cnf->variables[temp].handled = false;
					addElem(i, &cnf->variables[-temp].negative);
					addElem(temp, &cnf->clauses[i].variables);
				}
				++clauseLength;
				fscanf(fp, "%d", &temp);
			}
			cnf->clauses[i].length = clauseLength;
			assert(cnf->clauses[i].length >= 0);
		}
	}
	;
}


void DisplayData(CNF * cnf) {
	int clauseNum = cnf->clauseNum;
	for (int i = 1; i <= clauseNum; ++i) {
		intListNode * temp = cnf->clauses[i].variables.first;
		while (temp)
		{
			printf("%d ", temp->value);
			temp = temp->next;
		}
		printf("length = %d ", cnf->clauses[i].length);
		printf("\n");
	}
}


bool Process(DecisionTreeNode * node, CNF * cnf) {
	bool flag = true; //标志是否出现空子句,true为没有出现，false为出现了

	int assumption = node->assumption;
	int currentClauseIndex = 0;
	intListNode * positiveClauseIndexPtr = nullptr;
	intListNode * negativeClauseIndexPtr = nullptr;

	

	if (assumption > 0) {
		positiveClauseIndexPtr = cnf->variables[assumption].positive.first;
		negativeClauseIndexPtr = cnf->variables[assumption].negative.first;
		cnf->variables[assumption].handled = true;					
	}																
	else {															
		negativeClauseIndexPtr = cnf->variables[-assumption].positive.first;
		positiveClauseIndexPtr = cnf->variables[-assumption].negative.first;
		cnf->variables[-assumption].handled = true;					
	}


	// 先删除子句、再删除文字，可能出现正负同时出现在同一个子句的情况

	while (positiveClauseIndexPtr)
	{
		currentClauseIndex = positiveClauseIndexPtr->value;
		// 取正，则将子句删除
		if (!cnf->clauses[currentClauseIndex].hidden) {
			cnf->clauses[currentClauseIndex].hidden = assumption;
		}
		positiveClauseIndexPtr = positiveClauseIndexPtr->next;
	}
	currentClauseIndex = 0;
	while (negativeClauseIndexPtr)
	{
		currentClauseIndex = negativeClauseIndexPtr->value;
		// 取负，则将子句中的对应文字删除
		if (!cnf->clauses[currentClauseIndex].hidden) {
			assert(cnf->clauses[currentClauseIndex].variables.length > 0);
			deleteElem(-assumption, &cnf->clauses[currentClauseIndex].variables);
			--cnf->clauses[currentClauseIndex].length; // 子句长度减少
			if (0 == cnf->clauses[currentClauseIndex].length) {
				// 说明出现了空子句
				flag = false;
			}
		}
		negativeClauseIndexPtr = negativeClauseIndexPtr->next;
	}
	return flag;
}

void Recover(DecisionTreeNode * node, CNF * cnf) {
	int assumption = node->assumption;
	int currentClauseIndex = 0;
	intListNode * positiveClauseIndexPtr = nullptr;
	intListNode * negativeClauseIndexPtr = nullptr;
	if (assumption > 0) {
		positiveClauseIndexPtr = cnf->variables[assumption].positive.first;
		negativeClauseIndexPtr = cnf->variables[assumption].negative.first;
		cnf->variables[assumption].handled = false; // 恢复状态
	}
	else {
		negativeClauseIndexPtr = cnf->variables[-assumption].positive.first;
		positiveClauseIndexPtr = cnf->variables[-assumption].negative.first;
		cnf->variables[-assumption].handled = false;
	}


	// 与 Process相反，先恢复文字，再恢复删除

	while (negativeClauseIndexPtr)
	{
		currentClauseIndex = negativeClauseIndexPtr->value;
		// 取负，则将子句中的对应文字恢复
		if (!cnf->clauses[currentClauseIndex].hidden) {
			recoverElem(-assumption, &cnf->clauses[currentClauseIndex].variables);
			++cnf->clauses[currentClauseIndex].length;// 子句长度恢复

		}
		negativeClauseIndexPtr = negativeClauseIndexPtr->next;
	}

	while (positiveClauseIndexPtr)
	{
		// 取正,如果子句的删除是由当前assumption导致的，则恢复
		currentClauseIndex = positiveClauseIndexPtr->value;
		if (cnf->clauses[currentClauseIndex].hidden == assumption)
			cnf->clauses[currentClauseIndex].hidden = 0;

		positiveClauseIndexPtr = positiveClauseIndexPtr->next;
	}
	
}

DecisionTreeNode * BackTrack(DecisionTreeNode * node, CNF * cnf) {
	while (node->valid && node->back)
	{
		DecisionTreeNode * tempPtr = node;
		Recover(node, cnf);
		node = node->back;
		node->next = nullptr;
		free(tempPtr);
		tempPtr = nullptr;
	}
	if (!node->valid) {
		// 此时是因为valid为false而跳出循环，说明找到了假设点
		Recover(node, cnf);
		node->assumption = -node->assumption;
		node->valid = true;
		return node;
	}
	else {
		// 此时，即使回溯到最开始也无法使CNF为真，返回NULL
		return nullptr;
	}
}

void updateCountNum(CNF * cnf) {
	int count = 0; 
	intListNode * tempNode = nullptr;
	for (int i = cnf->varNum; i > 0; --i) {
		count = 0;
		tempNode = cnf->variables[i].negative.first;
		while (tempNode)
		{
			if (!cnf->clauses[tempNode->value].hidden)
				++count;
			tempNode = tempNode->next;
		}
		cnf->variables[i].negativeCount = count;

		tempNode = cnf->variables[i].positive.first;

		count = 0;
		while (tempNode)
		{
			if (!cnf->clauses[tempNode->value].hidden)
				++count;
			tempNode = tempNode->next;
		}
		cnf->variables[i].positiveCount = count;
	}
}

void updateCountNum_2(CNF * cnf) {
	int count = 0;
	intListNode * tempNode = nullptr;
	for (int i = cnf->varNum; i > 0; --i) {
		count = 0;
		if (cnf->variables[i].handled) {
			cnf->variables[i].negativeCount = cnf->variables[i].positiveCount = 0;
			continue;
		}
		else {
			tempNode = cnf->variables[i].negative.first;
			while (tempNode)
			{
				if (!cnf->clauses[tempNode->value].hidden && cnf->clauses[tempNode->value].length == 2)
					++count;
				tempNode = tempNode->next;
			}
			cnf->variables[i].negativeCount = count;

			tempNode = cnf->variables[i].positive.first;

			count = 0;
			while (tempNode)
			{
				if (!cnf->clauses[tempNode->value].hidden && cnf->clauses[tempNode->value].length == 2)
					++count;
				tempNode = tempNode->next;
			}
			cnf->variables[i].positiveCount = count;
		}
		
	}
}

int FindMax_2(CNF * cnf) {
	int max = 0;
	updateCountNum_2(cnf);
	int maxCount = cnf->variables[max].positiveCount + cnf->variables[max].negativeCount;
	for (int i = 1; i <= cnf->varNum; ++i) {
		if (!cnf->variables[i].handled) {
			int iCount = cnf->variables[i].positiveCount + cnf->variables[i].negativeCount;
			if (iCount > maxCount) {
				max = i;
				maxCount = iCount;
			}
		}
	}
	if (cnf->variables[max].positiveCount > cnf->variables[max].negativeCount)
		return max;
	else
		return -max;
}

int FindMax(CNF *cnf) {
	int max = 0;
	updateCountNum(cnf);
	int maxCount = cnf->variables[max].positiveCount + cnf->variables[max].negativeCount;
	for (int i = 1; i <= cnf->varNum; ++i) {
		if (!cnf->variables[i].handled) {
			int iCount = cnf->variables[i].positiveCount + cnf->variables[i].negativeCount;
			if (iCount > maxCount) {
				max = i;
				maxCount = iCount;
			}
		}
	}
	if (cnf->variables[max].positiveCount > cnf->variables[max].negativeCount)
		return max;
	else
		return -max;
}


int Findmax_new_2(CNF * cnf) {
	int max = 0;
	int max_2 = 0;

	int max_count_positive = 0;
	int max_count_negative = 0;
	int max_count_2_negative = 0;
	int max_count_2_positive = 0;  



	intListNode * tempNode;
	for (int i = cnf->varNum; i > 0; --i) {
		if (!cnf->variables[i].handled) {
			tempNode = cnf->variables[i].positive.first;
			while (tempNode) {
				if (!cnf->clauses[tempNode->value].hidden) {
					if (cnf->clauses[tempNode->value].length == 2)
						++max_count_2_positive;
					++max_count_positive;
				}
				tempNode = tempNode->next;
			}
			
		}
	}
	return 0;
}



int SelectVar(CNF * cnf) {
	int max_2 = FindMax_2(cnf);
	if (max_2)
		return max_2;
	else
		return FindMax(cnf);
}

bool Satisfied(CNF * cnf) {
	// 检查CNF是否已经满足
	int flag = true;
	// 如果存在还未被删除的子句则说明没有满足
	for (int i = cnf->clauseNum; i > 0; --i) {
		if (!cnf->clauses[i].hidden) {
			flag = false;
			break;
		}
	}
	return flag;
}

int SingleRule(CNF * cnf) {
	// 返回找到的第一个单子句中的变元,0表示不存在单子句
	int result = 0;
	for (int i = cnf->clauseNum; i > 0; --i) {
		if (1 == cnf->clauses[i].length && !cnf->clauses[i].hidden) {
			result = cnf->clauses[i].variables.first->value;
			break;
		}
	}
	return result;
	/*int result = 0;
	intListNode * tempNode = nullptr;
	for (int i = cnf->clauseNum; i > 0; --i) {
		if (1 == cnf->clauses[i].length && !cnf->clauses[i].hidden) {
			tempNode = cnf->clauses[i].variables.first;
			while (cnf->variables[abs(tempNode->value)].handled)
				tempNode = tempNode->next;
			result = tempNode->value;
			break;
		}
	}*/
	return result; 
}

DecisionTreeHead * DPLL(CNF * cnf) {
	DecisionTreeHead * Head = (DecisionTreeHead *)calloc(1, sizeof(DecisionTreeHead));

	assert(Head != nullptr);

	DecisionTreeNode * currentTreeNode = nullptr;
	Head->firstNode = nullptr;
	bool flag = true;
	int singleRuleResult = 0;

	int assumption = 0;

	while (!Satisfied(cnf))
	{
		while (flag && (singleRuleResult = SingleRule(cnf))) {
			currentTreeNode = addAssumption(singleRuleResult, true, Head);
			flag = Process(currentTreeNode, cnf);
			
			printf("proccess the single rule @@ var = %d\n", singleRuleResult);

			if (!flag)
				break;
		}
		
		if (flag) {
			// 由于不再有单子句才退出
			assumption = SelectVar(cnf);
			if (assumption == 0)
				return Head;
			currentTreeNode = addAssumption(assumption, false, Head);
			printf("assumption var = %d\n", assumption);
			flag = Process(currentTreeNode, cnf);
			printf("process the single rule\n");
		}
		else {
			//  由于存在冲突而退出
			printf("BAKETRACK @@ var = %d\n", currentTreeNode->assumption);
			currentTreeNode = BackTrack(currentTreeNode, cnf);
			printf("AFTER backtrack @@ var = %d\n", currentTreeNode->assumption);
			flag = Process(currentTreeNode, cnf);
			printf("process the single rule\n");
		}
		if (nullptr == currentTreeNode)
			return nullptr;
	}
	return Head;
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
		tempNode = cnf->clauses[i].variables.first;
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

int main(int argc, char ** args) {
	CNF * cnf = (CNF *)calloc(1, sizeof(CNF));

	assert(cnf != nullptr);

	if (argc == 2)
		LoadFile(args[1], cnf);
	else {
		const char * filename = "problem11-100.cnf";
		LoadFile(filename, cnf);
	}

	//DisplayData(cnf);
	DecisionTreeHead * result = DPLL(cnf);
	if (result) {
		//DisplayResult(result);
		int * resultArray = TurnToArray(result, cnf);  // 最终的结果数组
		PrintArray(resultArray, cnf->varNum+1);
		CheckFinalResult(resultArray, cnf);
	}
	return 0;
}

