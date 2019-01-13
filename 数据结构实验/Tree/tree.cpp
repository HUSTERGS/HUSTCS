#include <stdio.h>
#include <iostream>
#include <stdlib.h>

#define MAX_TREE_NUM 10
#define OK 1
#define ERROR -1
#define true 1
#define false 0
#define bool int

typedef int status;
typedef int ElemType;

using namespace std;

struct TreeNode
{
	ElemType elem;
	TreeNode * LChild;
	TreeNode * RChild;
};


struct Quene
{
	TreeNode  * elem;
	Quene * next;
};


struct HeadNode
{
	TreeNode * Tree;
};

class myQuene {
public:
	Quene * ListHead = nullptr;
	int listlength = 0;
	void push(TreeNode * tarelem) {
		if (ListHead) {
			Quene * temp = ListHead;
			while (temp->next)
				temp = temp->next;
			temp->next = (Quene *)malloc(sizeof(Quene));
			temp->next->elem = tarelem;
			temp->next->next = NULL;
		}
		else {
			ListHead = (Quene *)malloc(sizeof(Quene));
			ListHead->elem = tarelem;
			ListHead->next = nullptr;
		}
		listlength++;
	}
	TreeNode * pop() {
		Quene * temp = ListHead;
		TreeNode * tempValue = temp->elem;
		ListHead = temp->next;
		free(temp);
		listlength--;
		return tempValue;
	}
	void clearAll() {
		ListHead = nullptr;
	}
};


status InitBiTree();
status ClearBiTree(HeadNode * currentHead);
void ClearFromRoot(TreeNode * root);
bool BiTreeEmpty(HeadNode * currentHead);
status CreateBiTree(TreeNode * & currentPtr);
status DestroyBiTree(HeadNode * currentHead);
TreeNode * Root();
TreeNode * getElem();
TreeNode * Parent(TreeNode * root, TreeNode * e);
TreeNode * LeftChild(TreeNode * e);
TreeNode * RightChild(TreeNode * e);
int depth(TreeNode * currentHead);
status PreOrderTraverse(TreeNode * root, void(*Visit)(ElemType));
status InOrderTraverse(TreeNode * root, void(*Visit)(ElemType));
status PostOrderTraverse(TreeNode * root, void(*Visit)(ElemType));
status LevelOrderTraverse(TreeNode * root, void(*Visit)(ElemType));
status DeleteChild(TreeNode * p, int LR);
TreeNode * LeftSibling(TreeNode * root, TreeNode * e);
TreeNode * RightSibling(TreeNode * root, TreeNode * e);
status InsertChild(TreeNode * p, int LR, TreeNode * targetTree);
void iterSave(FILE * fp, TreeNode * ptr);
void SaveData();
status iterLoad(FILE * fp, TreeNode * & currentPtr);
status LoadData();
void printTree(TreeNode * currentTree, int h);


HeadNode * currentHead; //用于存放当指向当前树的头节点的指针
HeadNode * TreeTracker[MAX_TREE_NUM];  //头指针数组
int currentIndex; //指示当前树的序号
myQuene quene;
myQuene quene_for_select;
int getElemConst;
int getElemTarget;
TreeNode * tempTarget;


void clearTracker() {
	int i = 0;
	for (; i < MAX_TREE_NUM; i++)
		TreeTracker[i] = NULL;
}
void Visit(ElemType elem) {
	cout << elem << " ";
}

void printListInfo() {
	int i = 0;
	for (; i < MAX_TREE_NUM; i++) {
		if (TreeTracker[i])
			cout << "树 " << i << " 已被占用" << endl;
		else
			cout << "树 " << i << "可用" << endl;
	}
}

void printMenu(void) {
	cout << "|--------------------B Tree Experiment Menu--------------------|" << endl;
	cout << "|            1. 初始化当前树            2. 销毁当前树            |" << endl;
	cout << "|            3. 清空当前树              4. 判断当前树是否为空     |" << endl;
	cout << "|            5. 利用前序创建一颗树       6. 获取根节点            |" << endl;
	cout << "|            7. 获取一个节点            8. 查询当前树深度         |" << endl;
	cout << "|            9. 赋值                   10. 获取父节点            |" << endl;
	cout << "|            11. 获取左孩子             12. 获取右孩子           |" << endl;
	cout << "|            13. 获取左邻元素           14. 获取右邻节点         |" << endl;
	cout << "|            15. 插入一颗树             16. 删除子树             |" << endl;
	cout << "|            17. 前序遍历               18. 中序遍历             |" << endl;
	cout << "|            19. 后序遍历               20. 按层遍历             |" << endl;
	cout << "|            21. 切换树                 22. 保存数据            |" << endl;
	cout << "|            23. 导入数据               24. 打印树（横向）       |" << endl;
}

void main(void) {
	//先清空所有空间
	clearTracker();
	printMenu();
	int op = 1;
	while (op) {
		cin >> op;
		system("cls");
		printMenu();
		switch (op) {
		case 1:
			if (InitBiTree() == OK) {
				cout << "初始化成功" << endl;
			}
			else {
				cout << "初始化失败" << endl;
			}
			break;
		case 2:
			if (DestroyBiTree(currentHead) == OK) {
				cout << "成功销毁" << endl;
			}
			else {
				cout << "销毁失败" << endl;
			}
			break;
		case 3:
			if (ClearBiTree(currentHead) == OK) {
				cout << "清空成功" << endl;
			}
			else {
				cout << "清空失败" << endl;
			}
			break;

		case 4:
			if (BiTreeEmpty(currentHead) == ERROR) {
				cout << "判断失败" << endl;
			}
			else {
				if (BiTreeEmpty(currentHead))
					cout << "当前树为空" << endl;
				else
					cout << "当前树不为空" << endl;
			}
			break;
		case 5:
			if (currentHead) {
				cout << "请输入先序遍历的数字，其中空节点用#表示, 使其成为一个二叉树" << endl;
				cout << "请输入正确的遍历结果，否则输入可能会一直进行" << endl;
				cout << "   1   " << endl;
				cout << "  / \\   " << endl;
				cout << "2     3" << endl;
				cout << "     /" << endl;
				cout << "    4" << endl;
				cout << "样例序列为 1 2 # # 3 4 # # #" << endl;
				if (CreateBiTree(currentHead->Tree) == OK) {
					cout << "成功创建" << endl;
				}
				else
					cout << "创建失败" << endl;
			}
			else {
				cout << "请先初始化" << endl;
			}
			
			break;
		case 6:
			if (currentHead && currentHead->Tree) {
				if (Root()) {
					cout << "根节点的值为 " << Root()->elem << endl;
				}
				else
					cout << "获取失败" << endl;
				
			}
			else {
				cout << "请先选择一棵树或者初始化当前树" << endl;
			}
			
			break;
		case 7:
			cout << "请输入目标节点在按层遍历过程中的次序并选择删除左子树或右子树" << endl;
			cout << "   1   " << endl;
			cout << "  / \\   " << endl;
			cout << "2     5" << endl;
			cout << "     /" << endl;
			cout << "    4" << endl;
			cout << "样例中若要取元素5所在位置的元素则输入3" << endl;
			getElemConst = 0;
			quene_for_select.push(currentHead->Tree);
			if (cin >> getElemTarget) {
				if (tempTarget = getElem()) {
					cout << "你选择的元素为" <<  tempTarget->elem << endl;
				}
				else
					cout << "查找失败" << endl;
			}
			else
				cout << "请输入正确的元素位置" << endl;
			quene_for_select.clearAll();
			break;
		case 8:
			if (currentHead)
				cout << "当前树的深度为 " << depth(currentHead->Tree) << endl;
			else if (!currentHead)
				cout << "当前树已被销毁，若要继续操作请重新选择一颗树" << endl;
			break;
		case 9:
			cout << "请输入目标节点在按层遍历过程中的次序" << endl;
			cout << "   1   " << endl;
			cout << "  / \\   " << endl;
			cout << "2     5" << endl;
			cout << "     /" << endl;
			cout << "    4" << endl;
			cout << "样例中若要取元素5所在位置的元素则输入3" << endl;
			getElemConst = 0;
			quene_for_select.push(currentHead->Tree);
			if (cin >> getElemTarget) {
				if (tempTarget = getElem()) {
					cout << "你选择的元素为" << tempTarget->elem << endl;
					cout << "请输入要为其赋的新值" << endl;
					if (cin >> tempTarget->elem) {
						cout << "成功将其赋值为" << tempTarget->elem << endl;
					}
					else
						cout << "赋值失败" << endl;
				}
				else
					cout << "查找失败" << endl;
			}
			else
				cout << "请输入正确的元素位置" << endl;
			quene_for_select.clearAll();
			break;
		case 10:
			if (currentHead->Tree) {
				cout << "请输入目标节点在按层遍历过程中的次序" << endl;
				cout << "   1   " << endl;
				cout << "  / \\   " << endl;
				cout << "2     5" << endl;
				cout << "     /" << endl;
				cout << "    4" << endl;
				cout << "样例中若要取元素5所在位置的元素则输入3" << endl;
				getElemConst = 0;
				quene_for_select.push(currentHead->Tree);
				if (cin >> getElemTarget) {
					if (tempTarget = getElem()) {
						cout << "你选择的元素为" << tempTarget->elem << endl;
						if (Parent(currentHead->Tree, tempTarget)) {
							cout << "其父元素为" << Parent(currentHead->Tree, tempTarget)->elem << endl;
						}
						else
							cout << "查找失败" << endl;
					}
					else
						cout << "查找失败" << endl;
				}
				else
					cout << "请输入正确的元素位置" << endl;
				quene_for_select.clearAll();
			}
			else
				cout << "请先初始化" << endl;
			break;
		case 11:
			if (currentHead->Tree) {
				cout << "请输入目标节点在按层遍历过程中的次序" << endl;
				cout << "   1   " << endl;
				cout << "  / \\   " << endl;
				cout << "2     5" << endl;
				cout << "     /" << endl;
				cout << "    4" << endl;
				cout << "样例中若要取元素5所在位置的元素则输入3" << endl;
				getElemConst = 0;
				quene_for_select.push(currentHead->Tree);
				if (cin >> getElemTarget) {
					if (tempTarget = getElem()) {
						cout << "你选择的元素为" << tempTarget->elem << endl;
						if (LeftChild(tempTarget)) {
							cout << "其左子元素为" << LeftChild(tempTarget)->elem << endl;
						}
						else
							cout << "查找失败" << endl;
					}
					else
						cout << "查找失败" << endl;
				}
				else
					cout << "请输入正确的元素位置" << endl;
				quene_for_select.clearAll();
			}
			else
				cout << "请先初始化" << endl;
			break;
		case 12:
			if (currentHead->Tree) {
				cout << "请输入目标节点在按层遍历过程中的次序" << endl;
				cout << "   1   " << endl;
				cout << "  / \\   " << endl;
				cout << "2     5" << endl;
				cout << "     /" << endl;
				cout << "    4" << endl;
				cout << "样例中若要取元素5所在位置的元素则输入3" << endl;
				getElemConst = 0;
				quene_for_select.push(currentHead->Tree);
				if (cin >> getElemTarget) {
					if (tempTarget = getElem()) {
						cout << "你选择的元素为" << tempTarget->elem << endl;
						if (RightChild(tempTarget)) {
							cout << "其右子元素为" << RightChild(tempTarget)->elem << endl;
						}
						else
							cout << "查找失败" << endl;
					}
					else
						cout << "查找失败" << endl;
				}
				else
					cout << "请输入正确的元素位置" << endl;
				quene_for_select.clearAll();
			}
			else
				cout << "请先初始化" << endl;
			break;
		case 13:
			if (currentHead->Tree) {
				cout << "请输入目标节点在按层遍历过程中的次序" << endl;
				cout << "   1   " << endl;
				cout << "  / \\   " << endl;
				cout << "2     5" << endl;
				cout << "     /" << endl;
				cout << "    4" << endl;
				cout << "样例中若要取元素5所在位置的元素则输入3" << endl;
				getElemConst = 0;
				quene_for_select.push(currentHead->Tree);
				if (cin >> getElemTarget) {
					if (tempTarget = getElem()) {
						cout << "你选择的元素为" << tempTarget->elem << endl;
						if (LeftSibling(currentHead->Tree, tempTarget)) {
							cout << "其左临元素为" <<  LeftSibling(currentHead->Tree, tempTarget)->elem << endl;
						}
						else
							cout << "查找失败" << endl;
					}
					else
						cout << "查找失败" << endl;
				}
				else
					cout << "请输入正确的元素位置" << endl;
				quene_for_select.clearAll();
			}
			else
				cout << "请先初始化" << endl;
			break;
		case 14:
			if (currentHead->Tree) {
				cout << "请输入目标节点在按层遍历过程中的次序" << endl;
				cout << "   1   " << endl;
				cout << "  / \\   " << endl;
				cout << "2     5" << endl;
				cout << "     /" << endl;
				cout << "    4" << endl;
				cout << "样例中若要取元素5所在位置的元素则输入3" << endl;
				getElemConst = 0;
				quene_for_select.push(currentHead->Tree);
				if (cin >> getElemTarget) {
					if (tempTarget = getElem()) {
						cout << "你选择的元素为" << tempTarget->elem << endl;
						if (RightSibling(currentHead->Tree, tempTarget)) {
							cout << "其右临元素为" <<  RightSibling(currentHead->Tree, tempTarget)->elem << endl;
						}
						else
							cout << "查找失败" << endl;
					}
					else
						cout << "查找失败" << endl;
				}
				else
					cout << "请输入正确的元素位置" << endl;
				quene_for_select.clearAll();
			}
			else
				cout << "请先初始化" << endl;
			break;
		case 15:
			cout << "请选择要插入当前树的的目标:" << endl;
			printListInfo();
			int op_index;
			cin >> op_index;
			getchar();
			if ((op_index < 0) || (op_index > MAX_TREE_NUM) || (TreeTracker[op_index] == NULL))
			{
				cout << "编号" << op_index << "不能使用" << endl;
				break;
			}

			cout << "请输入插入的目标节点在当前树中按层遍历过程中的次序" << endl;
			cout << "   1   " << endl;
			cout << "  / \\   " << endl;
			cout << "2     5" << endl;
			cout << "     /" << endl;
			cout << "    4" << endl;
			cout << "样例中若要取元素5所在位置的元素则输入3" << endl;
			getElemConst = 0;
			quene_for_select.push(currentHead->Tree);
			if (cin >> getElemTarget) {
				if (tempTarget = getElem()) {
					cout << "你选择的元素为" << tempTarget->elem << endl;
				}
				else
					cout << "查找失败" << endl;
			}
			else
				cout << "请输入正确的元素位置" << endl;
			quene_for_select.clearAll();
			cout << "请选择想要插在左边还是右边：" << endl;
			int choice;
			cin >> choice;
			getchar();

			if (InsertChild(tempTarget, choice, TreeTracker[op_index]->Tree) == OK)
				cout << "插入成功" << endl;
			break;
		case 16:
			cout << "请输入目标节点在按层遍历过程中的次序并选择删除左子树或右子树" << endl;
			cout << "   1   " << endl;
			cout << "  / \\   " << endl;
			cout << "2     5" << endl;
			cout << "     /" << endl;
			cout << "    4" << endl;
			cout << "样例中若要取元素5所在位置的元素则输入3" << endl;
			getElemConst = 0;
			quene_for_select.push(currentHead->Tree);
			if (cin >> getElemTarget) {
				if (tempTarget = getElem()) {
					int choice;
					cin >> choice;
					if (DeleteChild(tempTarget, choice) != ERROR)
						cout << "删除成功" << endl;
					else
						cout << "删除失败" << endl;
				}
				else
					cout << "查找失败" << endl;
			}
			else
				cout << "请输入正确的元素位置" << endl;
			quene_for_select.clearAll();
			break;
		case 17:
			if (currentHead) {
				if (PreOrderTraverse(currentHead->Tree, Visit) == ERROR)
					cout << "遍历失败" << endl;
				else
					cout << "\n遍历成功" << endl;
			}
			else {
				cout << "当前树已被销毁，请重新选择一棵树" << endl;
			}
			break;
		case 18:
			if (currentHead) {
				if (InOrderTraverse(currentHead->Tree, Visit) == ERROR)
					cout << "遍历失败" << endl;
				else
					cout << "\n遍历成功" << endl;
			}
			else {
				cout << "当前树已被销毁，请重新选择一棵树" << endl;
			}
			break;
		case 19:
			if (currentHead) {
				if (PostOrderTraverse(currentHead->Tree, Visit) == ERROR)
					cout << "遍历失败" << endl;
				else
					cout << "\n遍历成功" << endl;
			}
			else {
				cout << "当前树已被销毁，请重新选择一棵树" << endl;
			}
			break;
		case 20:
			if (currentHead) {
				if (LevelOrderTraverse(currentHead->Tree, Visit) == ERROR)
					cout << "遍历失败" << endl;
				else
					cout << "\n遍历成功" << endl;
			}
			else {
				cout << "当前树已被销毁，请重新选择一棵树" << endl;
			}
			break;
		case 21:
			printListInfo();
			cout << "请输入目标树的序号" << endl;
			cin >> currentIndex;
			currentHead = TreeTracker[currentIndex];
			cout << "切换成功，当前树的序号为" <<  currentIndex << endl;
			break;
		case 22:
			SaveData();
			break;
		case 23:
			LoadData();
			cout << "导入成功" << endl;
			break;
		case 24:
			printTree(currentHead->Tree, depth(currentHead->Tree));
			break;
		}
	}


}


status InitBiTree() {
	if (TreeTracker[currentIndex]) {
		//如果当前树已经被初始化，那么提示错误
		cout << "不能重复初始化同一棵树" << endl;
		return ERROR;
	}
	else {
		//否则初始化头节点，并处理头节点中的相关数据
		TreeTracker[currentIndex] = (HeadNode *)malloc(sizeof(HeadNode));
		TreeTracker[currentIndex]->Tree = NULL;
		currentHead = TreeTracker[currentIndex];
		return OK;
	}
}

status DestroyBiTree(HeadNode * currentHead) {
	if (!currentHead) {
		cout << "请先初始化" << endl;
		return ERROR;
	}
	if (ClearBiTree(currentHead) == ERROR){
		return ERROR;
	}
	free(currentHead);
	TreeTracker[currentIndex] = NULL;
	currentHead = NULL;
	return OK;
}

status ClearBiTree(HeadNode * currentHead) {
	if (!currentHead) {
		cout << "请先初始化" << endl;
		return ERROR;
	}
	else if (BiTreeEmpty(currentHead)) {
		cout << "树已空" << endl;
		return ERROR;
	}
	else {
		ClearFromRoot(currentHead->Tree);
		free(currentHead->Tree);
		currentHead->Tree = NULL;
		return OK;
	}
}

void ClearFromRoot(TreeNode * root) {
	if (root->LChild) {
		ClearFromRoot(root->LChild);
	}
	if (root->RChild) {
		ClearFromRoot(root->RChild);
	}
	free(root->RChild);
	free(root->LChild);
	root->RChild = NULL;
	root->LChild = NULL;
}

status CreateBiTree(TreeNode * & currentPtr) {
	int temp;
	int returnValue = scanf("%d", &temp);
	if (returnValue > 0) {
		currentPtr = (TreeNode *)malloc(sizeof(TreeNode));
		currentPtr->elem = temp;
		if (CreateBiTree(currentPtr->LChild) == ERROR)
			return ERROR;
		if (CreateBiTree(currentPtr->RChild) == ERROR)
			return ERROR;
		return OK;
	}
	else if (returnValue == 0){
		currentPtr = nullptr;
		getchar();
		return OK;
	}
	else if (returnValue == -1) {
		currentPtr = nullptr;
		return OK;
	}
	
}


bool BiTreeEmpty(HeadNode * currentHead) {
	if (!currentHead) {
		cout << "请先初始化" << endl;
		return ERROR;
	}
	else {
		if (depth(currentHead->Tree))
			return false;
		else
			return true;
	}
}

int depth(TreeNode * currentHead) {
	if (currentHead == NULL)
		return 0;
	else
	{
		int LeftDepth = depth(currentHead->LChild);
		int RightDepth = depth(currentHead->RChild);
		if (LeftDepth > RightDepth)
			return LeftDepth + 1;
		else
			return RightDepth + 1;
	}
}

TreeNode * Root() {
	return currentHead->Tree;
}

ElemType Value(TreeNode * e) {
	return e->elem;
}

status Assign(TreeNode * e, ElemType value) {
	e->elem = value;
	return OK;
}
//如果找到了就返回对应节点的父节点，如果没有找到，返回NULL
TreeNode * Parent(TreeNode * root, TreeNode * e) {
	if (root->LChild == e)
		return root;
	else if (root->RChild == e)
		return root;
	else {
		if (root->LChild) {
			TreeNode * temp = Parent(root->LChild, e);
			//如果在左子树没有找到，就在右子树查找
			if (temp) {
				return temp;
			}
			else {
				//不论temp是否为NULL，都进行返回
				temp = Parent(root->RChild, e);
				return temp;
			}
		}
	}
}

TreeNode * LeftChild(TreeNode * e) {
	return e->LChild;
}

TreeNode * RightChild(TreeNode * e) {
	return e->RChild;
}

TreeNode * LeftSibling(TreeNode * root, TreeNode * e) {
	TreeNode * temp = Parent(root, e);
	if (temp && temp->RChild == e)
			return temp->LChild;
	return NULL;
}

TreeNode * RightSibling(TreeNode * root, TreeNode * e) {
	TreeNode * temp = Parent(root, e);
	if (temp && temp->LChild == e) {
		return temp->RChild;
	}
	return NULL;
}

status InsertChild(TreeNode * p, int LR, TreeNode * targetTree) {
	if (targetTree->RChild) {
		cout << "The right subtree is not empty" << endl;
		return ERROR;
	}
	else {
		if (LR) {
			targetTree->RChild = p->RChild;
			p->RChild = targetTree;
		}
		else {
			targetTree->RChild = p->LChild;
			p->LChild = targetTree;
		}
		return OK;
	}
}

status DeleteChild(TreeNode * p, int LR) {
	if (p) {
		if (LR) {
			if (p->RChild) {
				ClearFromRoot(p->RChild);
				free(p->RChild);
				p->RChild = nullptr;
			}
		}
		else {
			if (p->LChild) {
				ClearFromRoot(p->LChild);
				free(p->LChild);
				p->LChild = nullptr;
			}

		}
	}
	else {
		return ERROR;
	}
	return OK;
}

status PreOrderTraverse(TreeNode * root, void(*Visit)(ElemType)) {
	if (root == NULL)
		return ERROR;
	Visit(root->elem);
	PreOrderTraverse(root->LChild, Visit);
	PreOrderTraverse(root->RChild, Visit);
	return OK;
}
status InOrderTraverse(TreeNode * root, void(*Visit)(ElemType)) {
	if (root == NULL)
		return ERROR;
	InOrderTraverse(root->LChild, Visit);
	Visit(root->elem);
	InOrderTraverse(root->RChild, Visit);
	return OK;
}
status PostOrderTraverse(TreeNode * root, void(*Visit)(ElemType)) {
	if (root == NULL)
		return ERROR;
	PostOrderTraverse(root->LChild, Visit);
	PostOrderTraverse(root->RChild, Visit);
	Visit(root->elem);
	return OK;
}

status LevelOrderTraverse(TreeNode * root, void(*Visit)(ElemType)) {
	quene.push(root);
	TreeNode * cur;
	while (quene.listlength > 0) {
		cur = quene.pop();
		Visit(cur->elem);
		if (cur->LChild)
			quene.push(cur->LChild);
		if (cur->RChild)
			quene.push(cur->RChild);
	}
	return OK;
}

void printTree(TreeNode * currentTree, int h) {
	int i;
	if (currentTree != NULL) {
		printTree(currentTree->RChild, h+1);
		for (i = 0; i < h; i++)
			putchar('/t');
		cout << currentTree->elem << endl;
		putchar('\n');
		printTree(currentTree->LChild, h+1);
	}
}

TreeNode * getElem() {
	while (quene_for_select.listlength) {
		if (getElemConst == getElemTarget - 1) {
			return quene_for_select.pop();
		}
		TreeNode * temp = quene_for_select.pop();
		if (!temp) {
			return nullptr;
		}
		else {
			if (temp->LChild) {
				quene_for_select.push(temp->LChild);
			}
			if (temp->RChild) {
				quene_for_select.push(temp->RChild);
			}
		}
		getElemConst++;
	}
}

void SaveData() {
	FILE * fp = fopen("data.txt", "w");
	if (fp == NULL) {
		fp = fopen("data.txt", "wb");
	}
	for (int i = 0; i < MAX_TREE_NUM; i++) {
		if (TreeTracker[i] && TreeTracker[i]->Tree) {
			fprintf(fp, "%d\n", i);
			iterSave(fp, TreeTracker[i]->Tree);
		}
		fprintf(fp, "/n");
	}
	fclose(fp);
}

void iterSave(FILE * fp, TreeNode * ptr) {
	if (ptr) {
		fprintf(fp, "%d ", ptr->elem);
		iterSave(fp, ptr->LChild);
		iterSave(fp, ptr->RChild);
	}
	else {
		fprintf(fp, "# ");
	}	
}

status LoadData() {
	FILE * fp = fopen("data.txt", "r");
	if (fp == nullptr) {
		cout << "文件不存在" << endl;
		return ERROR;
	}
	else {
		int temp;
		while (fscanf(fp, "%d\n", &temp) != EOF) {
			TreeTracker[temp] = (HeadNode *)malloc(sizeof(HeadNode));
			iterLoad(fp, TreeTracker[temp]->Tree);
		}
	}
	fclose(fp);
}

status iterLoad(FILE * fp, TreeNode * & currentPtr) {
	ElemType temp;
	int returnValue = fscanf(fp, "%d ", &temp);
	if (returnValue > 0) {
		currentPtr = (TreeNode *)malloc(sizeof(TreeNode));
		currentPtr->elem = temp;
		if (iterLoad(fp, currentPtr->LChild) == ERROR)
			return ERROR;
		if (iterLoad(fp, currentPtr->RChild) == ERROR)
			return ERROR;
		return OK;
	}
	else if (returnValue == 0) {
		currentPtr = nullptr;
		fgetc(fp);
		return OK;
	}
	else if (returnValue == -1) {
		currentPtr = nullptr;
		return OK;
	}
}


