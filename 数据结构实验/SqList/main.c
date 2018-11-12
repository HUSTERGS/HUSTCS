#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR -1
#define INFEASTABLE -1
#define OVERFLOW -2

#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
#define MAX_LIST_NUM 10

#define bool int
#define true 1
#define false 0

typedef int status;
typedef int ElemType;


typedef struct
{
    ElemType * elem;
    int length;
    int listsize;
} SqList;




status IntiaList(SqList * L);
status DestroyList(SqList * ListTracker[MAX_LIST_NUM], int currentIndex);
status ClearList(SqList * L);
bool ListEmpty(SqList L);
int ListLength(SqList L);
status GetElem(SqList L,int i,ElemType * e);
int LocateElem(SqList L,ElemType e, bool (* compare)(ElemType, ElemType));
status PriorElem(SqList L,ElemType cur_e,ElemType * pre_e);
status NextElem(SqList L,ElemType cur_e,ElemType * next_e);
status ListInsert(SqList * L,int i,ElemType e);
status ListDelete(SqList * L,int i,ElemType * e);
status ListTrabverse(SqList L, void (* visite)(ElemType));
status LoadData(SqList * ListTracker[MAX_LIST_NUM]);

void visit(ElemType item)
{
    printf("%d ", item);
}

bool compare(ElemType elem1, ElemType elem2)
{
    if (elem1 == elem2)
        return true;
    else
        return false;
}

bool checkList(SqList * L)
{
    if (!L)
    {
        printf("List doesn't exist\n");
        return false;
    }
    else if (!L->elem)
    {
        printf("You need to initialize first\n");
        return false;
    }
    else
        return true;
}

int countListNum(SqList * ListTracker[MAX_LIST_NUM])
{
    int count = 0;
    int i = 0;
    for (; i < MAX_LIST_NUM; i++)
        if (ListTracker[i])
            count++;
    return count;
}

void clearAllList(SqList * ListTracker[MAX_LIST_NUM])
{
    int i = 0;
    for (; i < MAX_LIST_NUM; i ++)
        ListTracker[i] = NULL;
}

void printListInfo(SqList * ListTracker[MAX_LIST_NUM])
{
    int i = 0;
    for (; i < MAX_LIST_NUM; i++)
    {
        if (ListTracker[i])
            printf("List %d is occupied\n", i);
        else
            printf("List %d is available\n", i);
    }
}

void printMenu()
{
    printf("|-------------SqList Experiment Menu-----------------|\n");
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

int main(void)
{
    SqList * ListTracker[MAX_LIST_NUM];
    clearAllList(ListTracker);
    ListTracker[0] = (SqList *)malloc(sizeof(SqList));
    ListTracker[0]->elem = NULL;
    SqList * L = ListTracker[0];


    int currentIndex = 0;



    printMenu();
    int op = 1;
    while (op)
    {
        scanf("%d", &op);
        system("cls");
        printMenu();
        switch(op)
        {
        case 1:
            if (L->elem)
                printf("You can't repeatedly initialize the same List\n");
            else
            {
                if (InitaList(L) == OK)
                    printf("List successfully initialized\n");
                else
                    printf("Failed to create a List\n");
            }
            getchar();
            break;
        case 2:
            if (checkList(L) && DestroyList(ListTracker, currentIndex) == OK){
                L = NULL;
                printf("List successfully destroyed\n");
            }
            else
                printf("Failed to destroy List\n");
            getchar();
            break;
        case 3:
            if(checkList(L) && ClearList(L) == OK)
                printf("List successfully cleared\n");
            else if (InitaList(L) == ERROR)
                printf("Failed to clear List\n");
            getchar();
            break;
        case 4:
            if (checkList(L) && ListEmpty(*L) == false)
                printf("List is not empty\n");
            else if (ListEmpty(*L) == true)
                printf(("List is empty\n"));
            getchar();
            break;
        case 5:
            if (checkList(L))
            {
                printf("The length of the list is %d\n", ListLength(*L));
            }
            getchar();
            break;
        case 6:
            if (checkList(L))
                printf("Please enter the position you want to query:(between 1 to %d)\n", ListLength(*L));
            int queryPosition;
            ElemType queryResult;
            scanf("%d", &queryPosition);
            if (GetElem(*L, queryPosition, &queryResult) != ERROR)
                printf("Element of position %d is %d\n", queryPosition, queryResult);
            getchar();
            break;
        case 7:
            printf("Please enter the elem you want to query:\n");
            ElemType queryElem_prior;
            ElemType queryResult_prior;
            scanf("%d", &queryElem_prior);
            if (checkList(L) && PriorElem(*L, queryElem_prior, & queryResult_prior) != ERROR)
                printf("The prior element of %d is %d\n", queryElem_prior, queryResult_prior);
            else
                printf("failed to find\n");
            getchar();
            break;
        case 8:
            printf("Please enter the elem you want to query:\n");
            ElemType queryElem_next;
            ElemType queryResult_next;
            scanf("%d", &queryElem_next);
            if (checkList(L) && NextElem(*L, queryElem_next, & queryResult_next) != ERROR)
                printf("The next element of %d is %d\n", queryElem_next, queryResult_next);
            else
                printf("failed to find\n");
            getchar();
            break;
        case 9:
            if (checkList(L))
            {
                printf("Position: (between 1 to %d)\n", ListLength(*L)+1);
                printf("Please enter the element you want to insert, and the position of it(spaced by space):\n");
                ElemType insertElem;
                int insertPosition;
                scanf("%d %d", &insertElem, &insertPosition);
                if (checkList(L) && ListInsert(L, insertPosition, insertElem) != ERROR)
                    printf("Successfully inserted\n");
                else
                    printf("failed to insert\n");
            }

            getchar();
            break;
        case 10:
            if (checkList(L))
                printf("Please enter the position of the element you want to delete(between 1 to %d):\n", ListLength(*L));
            ElemType deleteElem;
            int deletePosition;
            scanf("%d %d", &deleteElem, &deletePosition);
            if (checkList(L) && ListInsert(L, deleteElem, deletePosition) != ERROR)
                printf("Successfully deleted\n");
            else
                printf("failed to deleted\n");
            getchar();
            break;
        case 11:
            if (checkList(L) && ListTrabverse(*L, visit) == OK)
                printf("successfully traveled all elements\n");
            else
                printf("failed to travel all element\n");
            getchar();
            break;
        case 12:
            if (checkList(L))
                printf("List length = %d, ListSize = %d, ListNum = %d\n", L->length, L->listsize, currentIndex);
            else
                printf("ListNUM = %d", currentIndex);
            break;
        case 13:
            printf("Please enter the elem you want to locate with function compare\n");
            ElemType queryElem_locate;
            int queryResult_locate;
            scanf("%d", &queryElem_locate);

            if (queryResult_locate = LocateElem(*L, queryElem_locate, compare))
            {
                printf("The position of %d is %d\n", queryElem_locate, queryResult_locate);
            }
            break;
        case 14:
            printf("You have chose to change list\n");
            printListInfo(ListTracker);
            printf("Please enter the index you want to change to\n");
            int tempIndex;
            scanf("%d", &tempIndex);
            if (tempIndex >= 0 && tempIndex < MAX_LIST_NUM)
            {
                currentIndex = tempIndex;
                if (!ListTracker[currentIndex])
                {
                    ListTracker[currentIndex] = (SqList *)malloc(sizeof(SqList));
                    ListTracker[currentIndex]->elem = NULL;
                }
                L = ListTracker[currentIndex];
                printf("Successfully changed\n");
            }
            else
                printf("Number illegal\n");
            break;
        case 15:
            SaveData(ListTracker);
            printf("Successfully Saved\n");
            getchar();
            break;
        case 16:
            LoadData(ListTracker);
            printf("Successfully Loaded\n");
            getchar();
            break;
        default:
            op = 0;
            break;
        }
    }
    return 0;
}


status InitaList(SqList * L)
{
    L->elem = (ElemType *)malloc( LIST_INIT_SIZE * sizeof (ElemType));
    if(!L->elem)
        exit(OVERFLOW);
    L->length=0;
    L->listsize=LIST_INIT_SIZE;
    return OK;
}

status DestroyList(SqList * ListTracker[MAX_LIST_NUM], int currentIndex)
{
    free(ListTracker[currentIndex]->elem);
    ListTracker[currentIndex]->elem = NULL;
    free(ListTracker[currentIndex]);
    ListTracker[currentIndex] = NULL;
    return OK;
}

status ClearList(SqList * L)
{

    L->length = 0;
    return OK;

}

bool ListEmpty(SqList L)
{

    if (L.length)
        return false;
    else
        return true;

}

int ListLength(SqList L)
{
    return L.length;
}

status GetElem(SqList L,int i,ElemType * e)
{
    if (ListEmpty(L))
    {
        printf("The List is still empty\n");
        return ERROR;
    }
    else if (i <= 0 || i > L.length)
    {
        printf("Target position doesn't exist\n");
        return ERROR;
    }
    else
    {
        *e = L.elem[i-1];
        return OK;
    }
}

int LocateElem(SqList L,ElemType e, bool (* compare)(ElemType, ElemType))
{
    if (!ListEmpty(L))
    {
        int literate_time = 0;
        for (; literate_time < L.length; literate_time ++)
        {
            if (compare(L.elem[literate_time], e))
                return literate_time + 1;
        }
        printf("Can't find the target element\n");
        return 0;
    }
    else
    {
        printf("List is empty\n");
        return ERROR;
    }
}

status PriorElem(SqList L,ElemType cur_e,ElemType * pre_e)
{
    if (L.length)
    {
        int literate_time = 0;
        for (; literate_time < L.length; literate_time++)
        {
            if (L.elem[literate_time] == cur_e)
            {
                if (literate_time)
                {
                    * pre_e = L.elem[literate_time - 1];
                    return OK;
                }

                else
                    printf("The target element is the first element\n");
                return ERROR;
            }
        }
        printf("Can't find Target Element\n");
        return ERROR;
    }
    else
    {
        printf("List is empty\n");
        return ERROR;
    }
}

status NextElem(SqList L,ElemType cur_e,ElemType * next_e)
{
    if (L.length)
    {
        int literate_time = 0;
        for (; literate_time < L.length; literate_time++)
        {
            if (L.elem[literate_time] == cur_e)
            {
                if (literate_time != L.length - 1)
                {
                    * next_e = L.elem[literate_time + 1];
                    return OK;
                }

                else
                    printf("The target element is the last element\n");
                return ERROR;
            }
        }
        printf("Can't find Target Element\n");
        return ERROR;
    }
    else
    {
        printf("List is empty\n");
        return ERROR;
    }
}


status ListInsert(SqList * L,int i,ElemType e)
{
    if (i < 1 || i > L->length + 1)
    {
        printf("Target Position illegal\n");
        return ERROR;
    }

    if (L->length > L->listsize)
    {
        ElemType * newbase = (ElemType *)realloc(L->elem, (L->listsize + LISTINCREMENT) * sizeof(ElemType));
        if (!newbase)
            exit(OVERFLOW);
        L->elem = newbase;
        L->listsize += LISTINCREMENT;
    }
    ElemType * p, * q;
    q = &(L->elem[i-1]);

    for (p = &(L->elem[L->length-1]); p >= q; --p)
        * (p+1) = * p;
    * q = e;
    L->length++;
    return OK;
}

status ListDelete(SqList *L,int i,ElemType * e)
{
    if (i < 1 || i > (*L).length)
        return ERROR;
    ElemType * p, * q;
    p = &(L->elem[i-1]);
    *e = *p;
    q = L->elem + L->length - 1;
    for (++p; p <= q; ++p)
        *(p-1) = *p;
    --L->length;
    return OK;
}

status ListTrabverse(SqList L, void (* visit)(ElemType))
{
    if (L.length)
    {
        int literate_time = 0;
        for (; literate_time < L.length; literate_time++)
        {
            visit(L.elem[literate_time]);
        }
        printf("\n");
        return OK;
    }
    else
    {
        printf("List length = 0, failed to travel\n");
        return ERROR;
    }
}

status LoadData(SqList * ListTracker[MAX_LIST_NUM])
{
    FILE * fp = fopen("data.txt", "r");
    if (fp == NULL)
    {
        printf("File doesn't exist\n");
        return ERROR;
    }
    int literate_time = 0;
    int current_list_num;
    ElemType current_elem;
    int list_length;

    while(literate_time < MAX_LIST_NUM && fscanf(fp, "%d %d\n\n", &current_list_num, &list_length) != EOF)
    {
        printf("current_list_num = %d, list_length = %d\n", current_list_num, list_length);
        printf("正在进行表%d的读取\n", current_list_num);
        int i = 0;
        //free(ListTracker[current_list_num]);
        ListTracker[current_list_num] = (SqList *)malloc(sizeof(SqList));
        ListTracker[current_list_num]->length = list_length;
        ListTracker[current_list_num]->listsize = LIST_INIT_SIZE;
        ListTracker[current_list_num]->elem = (ElemType *)malloc(sizeof(ElemType) * LIST_INIT_SIZE);
        for (; i < list_length; i++)
        {
            fscanf(fp, "%d\n", &current_elem);
            printf("正在读取第%d个元素\n", i);
            (ListTracker[current_list_num]->elem)[i] = current_elem;
        }
        literate_time++;
    }
    return OK;
}

status SaveData(SqList * ListTracker[MAX_LIST_NUM])
{
    FILE * fp = fopen("data.txt", "w");
    if (fp == NULL)
        fp = fopen("data.txt", "wb");
    int literate_time = 0;
    for (; literate_time < MAX_LIST_NUM; literate_time++)
    {
        if (ListTracker[literate_time] && ListTracker[literate_time]->length)
        {
            fprintf(fp, "%d %d\n\n", literate_time, ListTracker[literate_time]->length);
            int i = 0;
            for(; i < ListTracker[literate_time]->length; i++)
                fprintf(fp, "%d\n", ListTracker[literate_time]->elem[i]);
        }
    }
    fclose(fp);
    return OK;
}
