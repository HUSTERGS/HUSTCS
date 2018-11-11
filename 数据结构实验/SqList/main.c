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
status DestroyList(SqList * L);
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

bool checkList(SqList L)
{
    if (L.elem)
    {
        printf("List doesn't exist\n");
        return false;
    }
    else
        return true;
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
    printf("|    13. Locate Elem                                 |\n");
    printf("|                                                    |\n");
    printf("|            CopyRight GS from HUST CS1703           |\n");
    printf("|                                                    |\n");
    printf("|----------------------------------------------------|\n");
    printf("    Please Choose Your Operation from Options above   \n");
}

int main(void)
{
    SqList L;
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
            if (InitaList(&L) == OK)
                printf("List successfully created\n");
            else
                printf("Failed to create a List\n");
            getchar();
            break;
        case 2:
            if (checkList(L) && DestroyList(&L) == OK)
                printf("List successfully destroyed\n");
            else
                printf("Failed to destroy List\n");
            getchar();
            break;
        case 3:
            if(checkList(L) && ClearList(&L) == OK)
                printf("List successfully cleared\n");
            else if (InitaList(&L) == ERROR)
                printf("Failed to clear List\n");
            getchar();
            break;
        case 4:
            if (checkList(L) && ListEmpty(L) == false)
                printf("List is not empty\n");
            else if (ListEmpty(L) == true)
                printf(("List is empty\n"));
            getchar();
            break;
        case 5:
            if (checkList(L))
            {
                printf("The length of the list is %d\n", ListLength(L));
            }
            getchar();
            break;
        case 6:
            if (checkList(L))
                printf("Please enter the position you want to query:(between 1 to %d)\n", ListLength(L));
            int queryPosition;
            ElemType queryResult;
            scanf("%d", &queryPosition);
            if (GetElem(L, queryPosition, &queryResult) != ERROR)
                printf("Element of position %d is %d\n", queryPosition, queryResult);
            getchar();
            break;
        case 7:
            printf("Please enter the elem you want to query:\n");
            ElemType queryElem_prior;
            ElemType queryResult_prior;
            scanf("%d", &queryElem_prior);
            if (checkList(L) && PriorElem(L, queryElem_prior, & queryResult_prior) != ERROR)
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
            if (checkList(L) && NextElem(L, queryElem_next, & queryResult_next) != ERROR)
                printf("The next element of %d is %d\n", queryElem_next, queryResult_next);
            else
                printf("failed to find\n");
            getchar();
            break;

            break;
        case 9:

            printf("Please enter the element you want to insert, and the position of it(spaced by space):\n");
            if (checkList(L))
                printf("Position: (between 1 to %d)\n", ListLength(L)+1);
            ElemType insertElem;
            int insertPosition;
            scanf("%d %d", &insertElem, &insertPosition);
            if (checkList(L) && ListInsert(&L, insertPosition, insertElem) != ERROR)
                printf("Successfully inserted\n");
            else
                printf("failed to insert\n");
            getchar();
            break;
        case 10:
            if (checkList(L))
                printf("Please enter the position of the element you want to delete(between 1 to %d):\n", ListLength(L));
            ElemType deleteElem;
            int deletePosition;
            scanf("%d %d", &deleteElem, &deletePosition);
            if (checkList(L) && ListInsert(&L, deleteElem, deletePosition) != ERROR)
                printf("Successfully deleted\n");
            else
                printf("failed to deleted\n");
            getchar();
            break;
        case 11:
            if (checkList(L) && ListTrabverse(L, visit) == OK)
                printf("successfully traveled all elements\n");
            else
                printf("failed to travel all element\n");
            getchar();
            break;
        case 12:
            if (checkList(L))
                printf("List length = %d, ListSize = %d\n", L.length, L.listsize);
            break;
        case 13:
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

status DestroyList(SqList * L)
{
    free(L->elem);
    L->elem = NULL;
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
        printf("Target Position doesn't exist\n");
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
                    * next_e = L.elem[literate_time - 1];
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









