#include "selectvar.h"

void updateCountNum(CNF * cnf) {
	int count = 0;
	intListNode * tempNode = nullptr;
	for (int i = cnf->varNum; i > 0; --i) {
		count = 0;
		tempNode = cnf->variables[i].negative->first;
		while (tempNode)
		{
			if (!cnf->clauses[tempNode->value].hidden)
				++count;
			tempNode = tempNode->next;
		}
		cnf->variables[i].negativeCount = count;

		tempNode = cnf->variables[i].positive->first;

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
			tempNode = cnf->variables[i].negative->first;
			while (tempNode)
			{
				if (!cnf->clauses[tempNode->value].hidden && cnf->clauses[tempNode->value].length == 2)
					++count;
				tempNode = tempNode->next;
			}
			cnf->variables[i].negativeCount = count;

			tempNode = cnf->variables[i].positive->first;

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
	int maxCount = 0;
	//int maxCount = cnf->variables[max].positiveCount + cnf->variables[max].negativeCount;
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
	int maxCount = 0;
	//int maxCount = cnf->variables[max].positiveCount + cnf->variables[max].negativeCount;
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
	int max = 0;  // 所有子句中出现最多的元素的序号
	int max_2 = 0; // 所有长度为2的子句中出现最多的元素的序号

	int max_count_positive = 0;
	int max_count_negative = 0;
	int max_count_2_negative = 0;
	int max_count_2_positive = 0;

	int currentMax_count = 0;
	int currentMax_count_2 = 0;

	intListNode * tempNode;
	for (int i = cnf->varNum; i > 0; --i) {
		//  清零
		max_count_2_negative = max_count_2_positive = max_count_negative = max_count_positive = 0;

		if (!cnf->variables[i].handled) {
			// positive 
			tempNode = cnf->variables[i].positive->first;
			while (tempNode) {
				if (!cnf->clauses[tempNode->value].hidden) {
					if (cnf->clauses[tempNode->value].length == 2)
						++max_count_2_positive;
					++max_count_positive;
				}
				tempNode = tempNode->next;
			}
			// negative
			tempNode = cnf->variables[i].negative->first;
			while (tempNode) {
				if (!cnf->clauses[tempNode->value].hidden) {
					if (cnf->clauses[tempNode->value].length == 2)
						++max_count_2_negative;
					++max_count_negative;
				}
				tempNode = tempNode->next;
			}

			// length >= 2
			if (max_count_negative + max_count_positive > currentMax_count) {
				max = i;
				currentMax_count = max_count_negative + max_count_positive;
			}

			// length == 2
			if (max_count_2_negative + max_count_2_positive > currentMax_count) {
				max_2 = i;
				currentMax_count_2 = max_count_2_negative + max_count_2_positive;
			}
		}
	}

	// 优先选择长度为2的子句中出现次数最多的元素
	// 其中选择出现次数最多的取值为真
	if (currentMax_count_2) {
		if (max_count_2_negative > max_count_2_positive)
			return -max_2;
		else
			return max_2;
	}

	if (max_count_negative > max_count_positive)
		return -max;
	else
		return max;

	return 0;
}

int ReverseOrder(CNF * cnf) {
	int i = cnf->varNum;
	while (cnf->variables[i].handled)
		--i;
	return i;
}

int InOrder(CNF * cnf) {
	int i = 1;
	while (cnf->variables[i].handled)
		++i;
	if (i > cnf->varNum)
		return 0;
	else
		return i;
}
int SelectVar(CNF * cnf) {
	/*int max_2 = FindMax_2(cnf);
	if (max_2)
		return -max_2;
	else
		return -FindMax(cnf);*/
		//return InOrder(cnf);
		//return Findmax_new_2(cnf);
	return FindMax(cnf);
	//return InOrder(cnf);
}
