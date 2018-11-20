#include "pch.h"

#include <stdio.h>
#include <stdlib.h>
#define MAX_LIST_NUM 10
#define OK 1
#define ERROR -1
#define true 1
#define false 0
#define bool int



typedef int status;
typedef int ElemType;

typedef struct List
{
	ElemType elem;
	struct List * next;
}List;



status InitaList();
status DestroyList(List * L);
status ClearList(List *L);
bool ListEmpty(List * L);
int ListLength(List * L);
status GetElem(List *L, int i, ElemType * e);
int LocateElem(List *L, ElemType e, bool compare(ElemType, ElemType));
status PriorElem(List * L, ElemType cur_e, ElemType * pre_e);
status NextElem(List * L, ElemType cur_e, ElemType * next_e);
status ListInsert(List * L, int i, ElemType e);
status ListDelete(List * L, int i, ElemType * e);
status ListTraverse(List * L, void visit(ElemType));
status SaveData();
status LoadData();

List ListTracker[MAX_LIST_NUM];
List * currentList = &ListTracker[0];
int currentIndex = 0;

void clearAllList() {
	int i = 0;
	for (; i < MAX_LIST_NUM; i++) {
		ListTracker[i].next = NULL;
	}
}

bool compare(ElemType a , ElemType b) {
	if (a == b)
		return true;
	else
		return false;
}

void visit(ElemType e) {
	printf("%d ", e);
}

void printMenu()
{
	printf("|-------------List Experiment Menu-------------------|\n");
	printf("|                                                    |\n");
	printf("|                                                    |\n");
	printf("|    1. Init a List          2. Destroy List         |\n");
	printf("|    3. Clear List           4. Empty or Not         |\n");
	printf("|    5. Show List Length     6. Get Element          |\n");
	printf("|    7. Get Prior Element    8. Get Next Element     |\n");
	printf("|    9. Insert Element       10. Delete Element      |\n");
	printf("|    11. Travel List         12. Describe List       |\n");
	printf("|    13. Locate Elem         14. Change List         |\n");
	printf("|    15. Save Data           16. Load Data           |\n");
	printf("|                                                    |\n");
	printf("|            CopyRight GS from HUST CS1703           |\n");
	printf("|                                                    |\n");
	printf("|----------------------------------------------------|\n");
	printf("    Please Choose Your Operation from Options above   \n");
}

void printListInfo() {
	int i = 0;
	for (; i < MAX_LIST_NUM; i++) {
		if (ListTracker[i].next) 
			printf("List %d is occupied\n", i);
		else
			printf("List %d is available\n", i);
	}
}

status changeList(int target) {
	if (target >= 0 && target < MAX_LIST_NUM) {
		currentIndex = target;
		if (ListTracker[currentIndex].next) 
			currentList = &ListTracker[currentIndex];
		else 
			currentList = NULL;
		return OK;
	}
	else {
		printf("length illegal\n");
		return ERROR;
	}
}


int main(void) {
	clearAllList();
	printMenu();
	int op = 1;
	while (op)
	{
		scanf("%d", &op);
		system("cls");
		printMenu();
		switch (op)
		{
		case 1:
			if (InitaList() == OK)
				printf("Successfully initialized\n");
			else
				printf("Failed to initialize\n");
			getchar();
			break;
		case 2:
			if (currentList) {
				if (DestroyList(currentList) == OK) {
					printf("Successfully destroyed\n");
				}
			}
			else {
				printf("You need to inite a list first\n");
			}
			getchar();
			break;
		case 3:
			if (currentList) {
				if (ClearList(currentList) == OK) {
					printf("Successfully cleared list\n");
				}
				else {
					printf("Failed to clear");
				}
				if (currentList == NULL) {
					printf("fuck\n");
				}
			}
			else {
				printf("You need to inite a list first\n");
			}
			getchar();
			break;
		case 4:
			if (currentList) {
				if (ListEmpty(currentList))
					printf("List is empty\n");
				else
					printf("List is not empty\n");
			}
			else {
				printf("You need to inite list first\n");
			}
			getchar();
			break;
		case 5:
			if (currentList) {
				printf("List length is %d\n", ListLength(currentList));
			}
			else {
				printf("You need to inite a list first\n");
			}
			getchar();
			break;
		case 6:
			if (currentList) {
				if (ListEmpty(currentList))
					printf("List is still empty\n");
				else {
					ElemType elem_get;
					int position_get;
					printf("Please enter the position you want to get (from 1 to %d)", ListLength(currentList));
					scanf("%d", &position_get);
					if (GetElem(currentList, position_get, &elem_get) == OK)
						printf("Element of position %d is %d", position_get, elem_get);
					else
						printf("Failed to get Element\n");
				}
			}
			else {
				printf("You need to inite a list first\n");
			}
			getchar();
			break;
		case 7:
			if (currentList) {
				printf("Please enter the elem you want to query:\n");
				ElemType elem_prior;
				ElemType input_prior;
				//用户输入元素
				scanf("%d", &input_prior);
				if (PriorElem(currentList, input_prior, &elem_prior) != ERROR)
					printf("The prior element of %d is %d\n", input_prior, elem_prior);
				else
					printf("failed to find\n");
			}
			else {
				printf("You need to inite a list first\n");
			}
			getchar();
			break;
		case 8:
			if (currentList) {
				printf("Please enter the elem you want to query:\n");
				ElemType elem_next;
				ElemType input_next;
				scanf("%d", &input_next);
				if (NextElem(currentList, input_next, &elem_next) != ERROR)
					printf("The next element of %d is %d\n", input_next, elem_next);
				else
					printf("failed to find\n");
			}
			else {
				printf("You need to inite a list first\n");
			}
			getchar();
			break;
		case 9:
			if (currentList) {
				printf("Position: (between 1 to %d)\n", ListLength(currentList) + 1);
				printf("Please enter the element you want to insert, and the position of it(spaced by space):\n");
				ElemType insertElem;
				int insertPosition;
				//用户输入
				scanf("%d %d", &insertElem, &insertPosition);
				if (ListInsert(currentList, insertPosition, insertElem) != ERROR)
					printf("Successfully inserted\n");
				else
					printf("failed to insert\n");
			}
			else
				printf("You need to init a list first\n");
			getchar();
			break;
		case 10:
			if (currentList) {
				printf("Please enter the position of the element you want to delete(between 1 to %d):\n", ListLength(currentList));
				ElemType deleteElem;
				int deletePosition;
				scanf("%d", &deletePosition);
				if (ListDelete(currentList, deletePosition, &deleteElem) != ERROR)
					printf("Successfully deleted %d in position %d\n", deleteElem, deletePosition);
				else
					printf("failed to deleted\n");
			}
			getchar();
			break;
		case 11:
			if (currentList)
			{
				if (ListTraverse(currentList, visit) == OK)
					printf("\nsuccessfully traveled all elements\n");
				else
					printf("\nList is still empty, failed to travel all element\n");
			}
			else {
				printf("You need to init a list first\n");
			}
			getchar();
			break;
		case 12:
			if (currentList) {
				printf("List length = %d, currentIndex = %d\n", ListLength(currentList), currentIndex);
			}
			else {
				printf("current index = %d, not inite\n", currentIndex);
			}
			getchar();
			break;
		case 13:
			if (currentList)
			{
				printf("Please enter the elem you want to locate with function compare\n");
				ElemType queryElem_locate;
				int queryResult_locate;
				scanf("%d", &queryElem_locate);
				if (queryResult_locate = LocateElem(currentList, queryElem_locate, compare))
				{
					printf("The position of %d is %d\n", queryElem_locate, queryResult_locate);
				}
			}
			else {
				printf("You need to inite a list first\n");
			}
			getchar();
			break;
		case 14:
			printf("You have chose to change list\n");
			printListInfo();
			printf("Please enter the index you want to change to\n");
			int tempIndex;
			scanf("%d", &tempIndex);
			if (changeList(tempIndex) == OK)
				printf("Successfully changed, current index is %d\n", currentIndex);
			else
				printf("Failed to change list");
			getchar();
			break;
		case 15:
			SaveData();
			printf("Successfully Saved\n");
			getchar();
			break;
		case 16:
			LoadData();
			printf("Successfully Loaded\n");
			getchar();
			break;
		default://当输入其他字符的时候默认退出
			op = 0;
			break;
		}
	}
	return 0;
}



status InitaList() {
	if (currentList) {
		printf("Can't repeatedly initialize the same list\n");
		return ERROR;
	}
	else {
		currentList = &ListTracker[currentIndex];
		return OK;
	}
}
//destroy 之后需要手动将currentList 置空
status DestroyList(List * L) {
	ClearList(L);
	currentList = NULL;
	return OK;
}

status ClearList(List *L) {
	if (L->next == NULL) {
		return OK;
	}
	else {
		ClearList(L->next);
		free(&L->next->elem);
		L->next = NULL;
		return OK;
	}
}

bool ListEmpty(List * L) {
	if (L->next)
		return false;
	else
		return true;
}

int ListLength(List * L) {
	int length = 0;
	while (L->next) {
		length++;
		L = L->next;
	}
	return length;
}

status GetElem(List *L, int i, ElemType * e) {
	if (ListLength(L) >= i && i > 0) {
		while (i) {
			L = L->next;
			i--;
		}
		*e = L->elem;
		return OK;
	}
	else {
		printf("Length illigal\n");
		return ERROR;
	}
}

int LocateElem(List *L, ElemType e, bool compare(ElemType, ElemType)) {
	int position = 0;
	L = L->next;
	while (L) {
		position += 1;
		if (compare(e, L->elem)) {
			return position;
		}
		L = L->next;
	}
	return 0;
}

status PriorElem(List * L, ElemType cur_e, ElemType * pre_e) {
	if (L->next->elem == cur_e) {
		printf("The target element is the first element\n");
		return ERROR;
	}
	while (L->next) {
		if (L->next->elem == cur_e) {
			*pre_e = L->elem;
			return OK;
		}
		L = L->next;
	}
	return ERROR;
}


status NextElem(List * L, ElemType cur_e, ElemType * next_e) {
	while (L->next) {
		if (L->elem == cur_e) {
			*next_e = L->next->elem;
			return OK;
		}
		L = L->next;
	}
	if (L->elem == cur_e)
		printf("The target element is the last element\n");
	return ERROR;
}

status ListInsert(List * L, int i, ElemType e) {
	if (i <= ListLength(L) + 1 && i >= 1) {
		if (i == 1) {
			List * temp = L->next;
			ListTracker[currentIndex].next = (List *)malloc(sizeof(List));
			currentList = &ListTracker[currentIndex];
			currentList->next->next = temp;
			currentList->next->elem = e;
		}
		else {
			List * TempPointer = L;
			while (i-1) {
				TempPointer = TempPointer->next;
				i--;
			}
			List * temp = TempPointer->next;
			TempPointer->next = (List *)malloc(sizeof(List));
			TempPointer->next->elem = e;
			TempPointer->next->next = temp;
		}
		return OK;
	}
	else {
		printf("Position illigal\n");
		return ERROR;
	}
}

status ListDelete(List * L, int i, ElemType * e) {
	if (ListLength(L) >= i && i >= 1) {
		if (i == 1) {
			List *temp = L->next;
			*e = L->next->elem;
			L->next = L->next->next;
			free(temp);
		}
		else {
			List * TempPointer = L;
			while (i-1) {
				TempPointer = TempPointer->next;
				i--;
			}
			List * temp = TempPointer->next;
			*e = TempPointer->next->elem;
			TempPointer->next = TempPointer->next->next;
			free(temp);
		}
		return OK;
	}
	else {
		printf("Position illigal\n");
		return ERROR;
	}
}

status ListTraverse(List * L, void visit(ElemType)) {
	if (!L->next)
		return ERROR;
	while (L->next) {
		visit(L->next->elem);
		L = L->next;
	}
	return OK;
}

status SaveData() {
	FILE * fp = fopen("data.txt", "w");
	if (fp == NULL) {
		fp = fopen("data.txt", "wb");
	}
	int literateTime = 0;
	for (; literateTime < MAX_LIST_NUM; literateTime++) {
		List * temp = &ListTracker[literateTime];
		if (!ListEmpty(temp)) {
			printf("List should write %d %d", literateTime, ListLength(temp));
			fprintf(fp, "%d %d\n\n", literateTime, ListLength(temp));
			while (temp->next) {
				printf("%d List is writing %d\n", literateTime, temp->next->elem);
				fprintf(fp, "%d\n", temp->next->elem);
				temp = temp->next;
			}
		}
	}
	fclose(fp);
	return OK;
}

status LoadData() {
	FILE * fp = fopen("data.txt", "r");
	if (fp == NULL) {
		printf("File doesn't exist\n");
		return ERROR;
	}
	else {
		int current_list_num;
		int list_length;
		ElemType current_elem;
		while (fscanf(fp, "%d %d\n\n", &current_list_num, &list_length) != EOF) {
			printf("Loading the %dth list\n", current_list_num);
			printf("current list num = %d, list length = %d\n", current_list_num, list_length);
			fscanf(fp, "%d\n", &current_elem);
			printf("Reading %d\n", current_elem);
			ListTracker[current_list_num].next = (List *)malloc(sizeof(List));
			List * temp = &ListTracker[current_list_num];
			temp->next->elem = current_elem;
			temp->next->next = NULL;
			temp = temp->next;
			while (list_length-1) {
				temp->next = (List *)malloc(sizeof(List));
				temp = temp->next;
				fscanf(fp, "%d\n", &current_elem);
				temp->elem = current_elem;
				temp->next = NULL;
				list_length--;
			}
		}
	}
	fclose(fp);
	return OK;
}
