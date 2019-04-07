#include "dpll.h"
#include "selectvar.h"

bool Process(DecisionTreeNode * node, CNF * cnf) {
	bool flag = true; //标志是否出现空子句,true为没有出现，false为出现了

	int assumption = node->assumption;
	int currentClauseIndex = 0;
	intListNode * positiveClauseIndexPtr = nullptr;
	intListNode * negativeClauseIndexPtr = nullptr;



	if (assumption > 0) {
		positiveClauseIndexPtr = cnf->variables[assumption].positive->first;
		negativeClauseIndexPtr = cnf->variables[assumption].negative->first;
		cnf->variables[assumption].handled = true;
	}
	else {
		negativeClauseIndexPtr = cnf->variables[-assumption].positive->first;
		positiveClauseIndexPtr = cnf->variables[-assumption].negative->first;
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
			assert(cnf->clauses[currentClauseIndex].variables->length >= 0);
			deleteElem(-assumption, cnf->clauses[currentClauseIndex].variables);
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
		positiveClauseIndexPtr = cnf->variables[assumption].positive->first;
		negativeClauseIndexPtr = cnf->variables[assumption].negative->first;
		cnf->variables[assumption].handled = false; // 恢复状态
	}
	else {
		negativeClauseIndexPtr = cnf->variables[-assumption].positive->first;
		positiveClauseIndexPtr = cnf->variables[-assumption].negative->first;
		cnf->variables[-assumption].handled = false;
	}


	// 与 Process相反，先恢复文字，再恢复删除

	while (negativeClauseIndexPtr)
	{
		currentClauseIndex = negativeClauseIndexPtr->value;
		// 取负，则将子句中的对应文字恢复
		if (!cnf->clauses[currentClauseIndex].hidden) {
			recoverElem(-assumption, cnf->clauses[currentClauseIndex].variables);
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
	int result = 0;
	intListNode * tempNode = nullptr;
	for (int i = cnf->clauseNum; i > 0; --i) {
		if (1 == cnf->clauses[i].length && !cnf->clauses[i].hidden) {
			tempNode = cnf->clauses[i].variables->first;
			while (cnf->variables[abs(tempNode->value)].handled)
				tempNode = tempNode->next;
			result = tempNode->value;
			break;
		}
	}
	return result;
}

DecisionTreeHead * DPLL(CNF * cnf) {
	DecisionTreeHead * Head = (DecisionTreeHead *)malloc(sizeof(DecisionTreeHead));

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
			//clock_t start = clock();
			flag = Process(currentTreeNode, cnf);
			//clock_t end = clock();
			//printf("Processtime: %f\n", (double)(end - start));
			// 测试
			//printAssumptions(Head);

			//printf("proccess the single rule @@ var = %d\n", singleRuleResult);

			if (!flag)
				break;
		}
		if (flag) {
			// 由于不再有单子句才退出
			//clock_t start = clock();
			assumption = SelectVar(cnf);
			//clock_t end = clock();
			//printf("SelectVar : %f\n ", (double)(end - start));
			if (assumption == 0)
				return Head;
			currentTreeNode = addAssumption(assumption, false, Head);
			//printf("assumption var = %d\n", assumption);

			// 测试


			//start = clock();
			flag = Process(currentTreeNode, cnf);
			//end = clock();
			//printf("Processtime: %f\n", (double)(end - start));
			//printAssumptions(Head);
			//printf("process the single rule\n");
		}
		else {
			//  由于存在冲突而退出
			//printf("BAKETRACK @@ var = %d\n", currentTreeNode->assumption);
			//clock_t start = clock();
			currentTreeNode = BackTrack(currentTreeNode, cnf);
			if (nullptr == currentTreeNode)
				return nullptr;
			//clock_t end = clock();
			//printf("BackTrackTime: %f\n", (double)(end - start));
			//printf("AFTER backtrack @@ var = %d\n", currentTreeNode->assumption);
			//start = clock();
			flag = Process(currentTreeNode, cnf);
			//end = clock();
			//printf("Processtime: %f\n", (double)(end - start));

			// 测试
			//printAssumptions(Head);

			//printf("process the single rule\n");
		}

	}
	return Head;
}