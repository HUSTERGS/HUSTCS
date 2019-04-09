#include "dpll.h"
#include "selectvar.h"

bool Process(DecisionTreeNode * node, CNF * cnf) {
	bool flag = true; //��־�Ƿ���ֿ��Ӿ�,trueΪû�г��֣�falseΪ������

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


	// ��ɾ���Ӿ䡢��ɾ�����֣����ܳ�������ͬʱ������ͬһ���Ӿ�����

	while (positiveClauseIndexPtr)
	{
		currentClauseIndex = positiveClauseIndexPtr->value;
		// ȡ�������Ӿ�ɾ��
		if (!cnf->clauses[currentClauseIndex].hidden) {
			cnf->clauses[currentClauseIndex].hidden = assumption;
		}
		positiveClauseIndexPtr = positiveClauseIndexPtr->next;
	}
	currentClauseIndex = 0;
	while (negativeClauseIndexPtr)
	{
		currentClauseIndex = negativeClauseIndexPtr->value;
		// ȡ�������Ӿ��еĶ�Ӧ����ɾ��
		if (!cnf->clauses[currentClauseIndex].hidden) {
			assert(cnf->clauses[currentClauseIndex].variables->length >= 0);
			deleteElem(-assumption, cnf->clauses[currentClauseIndex].variables);
			--cnf->clauses[currentClauseIndex].length; // �Ӿ䳤�ȼ���
			if (0 == cnf->clauses[currentClauseIndex].length) {
				// ˵�������˿��Ӿ�
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
		cnf->variables[assumption].handled = false; // �ָ�״̬
	}
	else {
		negativeClauseIndexPtr = cnf->variables[-assumption].positive->first;
		positiveClauseIndexPtr = cnf->variables[-assumption].negative->first;
		cnf->variables[-assumption].handled = false;
	}


	// �� Process�෴���Ȼָ����֣��ٻָ�ɾ��

	while (negativeClauseIndexPtr)
	{
		currentClauseIndex = negativeClauseIndexPtr->value;
		// ȡ�������Ӿ��еĶ�Ӧ���ָֻ�
		if (!cnf->clauses[currentClauseIndex].hidden) {
			recoverElem(-assumption, cnf->clauses[currentClauseIndex].variables);
			++cnf->clauses[currentClauseIndex].length;// �Ӿ䳤�Ȼָ�

		}
		negativeClauseIndexPtr = negativeClauseIndexPtr->next;
	}

	while (positiveClauseIndexPtr)
	{
		// ȡ��,����Ӿ��ɾ�����ɵ�ǰassumption���µģ���ָ�
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
		// ��ʱ����ΪvalidΪfalse������ѭ����˵���ҵ��˼����
		Recover(node, cnf);
		node->assumption = -node->assumption;
		node->valid = true;
		return node;
	}
	else {
		// ��ʱ����ʹ���ݵ��ʼҲ�޷�ʹCNFΪ�棬����NULL
		return nullptr;
	}
}


bool Satisfied(CNF * cnf) {
	// ���CNF�Ƿ��Ѿ�����
	int flag = true;
	// ������ڻ�δ��ɾ�����Ӿ���˵��û������
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
			flag = Process(currentTreeNode, cnf);
			if (!flag)
				break;
		}
		if (flag) {
			// ���ڲ����е��Ӿ���˳�
			assumption = SelectVar(cnf);
			if (assumption == 0)
				return Head;
			currentTreeNode = addAssumption(assumption, false, Head);

			// ����


			flag = Process(currentTreeNode, cnf);
		}
		else {
			//  ���ڴ��ڳ�ͻ���˳�
			currentTreeNode = BackTrack(currentTreeNode, cnf);
			if (nullptr == currentTreeNode)
				return nullptr;
			flag = Process(currentTreeNode, cnf);
		}
	}
	return Head;
}