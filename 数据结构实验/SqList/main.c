#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR -1 //为了与FALSE区分开来，改为了-1
#define INFEASTABLE -1
#define OVERFLOW -2

#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
#define MAX_LIST_NUM 10

#define bool int  //使用bool表意更为明确
#define true 1
#define false 0

typedef int status;
typedef int ElemType;   //此处为了简化难度而直接使用了int而不是结构体

//定义结构体
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


//用于遍历时的测试函数
void visit(ElemType item)
{
    printf("%d ", item);
}
//用于locate时的测试函数
bool compare(ElemType elem1, ElemType elem2)
{
    if (elem1 == elem2)
        return true;
    else
        return false;
}
//用于在每次基本操作时检查当前表是否符合操作所需要求
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
//用于管理多表，返回所有表的个数
int countListNum(SqList * ListTracker[MAX_LIST_NUM])
{
    int count = 0;
    int i = 0;
    for (; i < MAX_LIST_NUM; i++)
        if (ListTracker[i])
            count++;
    return count;
}
//用于管理多表，将每个指针先初始化为NULL
void clearAllList(SqList * ListTracker[MAX_LIST_NUM])
{
    int i = 0;
    for (; i < MAX_LIST_NUM; i ++)
        ListTracker[i] = NULL;
}
//用于管理多表时给出信息，供用户参考选择
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
//用于打印菜单
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
//主函数
int main(void)
{

    SqList * ListTracker[MAX_LIST_NUM];
    clearAllList(ListTracker);
    //首次使用时默认使用位置0处的表
    ListTracker[0] = (SqList *)malloc(sizeof(SqList));
    ListTracker[0]->elem = NULL;
    //指定当前表
    SqList * L = ListTracker[0];

    //用于指示当前表的位置
    int currentIndex = 0;



    printMenu();
    int op = 1;
    while (op)
    {
        scanf("%d", &op);
        //Windows下起到清屏作用
        system("cls");
        printMenu();
        switch(op)
        {//以下基本上所有操作都需要利用checkList()先进行检查检查
        case 1:
            //初始话表的时候需要检查是否处于刚刚执行过destroy操作
            if (L == NULL)
            {   //如果是，则需要用户冲洗选择一个表
                printf("You need to chose a List first\n");
            }
            else
            {   //如果不是，则再进行检查，当前表是否已经初始化过
                if (L->elem)//如果是，则提示不不能重复初始化
                    printf("You can't repeatedly initialize the same List\n");
                else
                {   //否则则进行正常初始化操作
                    if (InitaList(L) == OK)
                        printf("List successfully initialized\n");
                    else
                        printf("Failed to create a List\n");
                }
            }
            getchar();
            break;
        case 2:
            if (checkList(L) && DestroyList(ListTracker, currentIndex) == OK)
            {
                L = NULL;
                printf("List successfully destroyed\n");
            }
            else
                printf("Failed to destroy List\n");
            getchar();
            break;
        case 3:
            if (checkList(L)){
                if (ClearList(L) == OK)
                    printf("List successfully cleared\n");
                else if (InitaList(L) == ERROR)
                    printf("Failed to clear List\n");
            }
            getchar();
            break;
        case 4:
            if (checkList(L))
            {
                if (ListEmpty(*L))
                    printf("List is empty\n");
                else
                    printf("List is not empty\n");
            }
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
            //用户输入位置
            scanf("%d", &queryPosition);
            if (GetElem(*L, queryPosition, &queryResult) != ERROR)
                printf("Element of position %d is %d\n", queryPosition, queryResult);
            getchar();
            break;
        case 7:
            if (checkList(L))
            {
                printf("Please enter the elem you want to query:\n");
                ElemType queryElem_prior;
                ElemType queryResult_prior;
                //用户输入元素
                scanf("%d", &queryElem_prior);
                if (PriorElem(*L, queryElem_prior, & queryResult_prior) != ERROR)
                    printf("The prior element of %d is %d\n", queryElem_prior, queryResult_prior);
                else
                    printf("failed to find\n");
            }

            getchar();
            break;
        case 8:
            if (checkList(L))
            {
                printf("Please enter the elem you want to query:\n");
                ElemType queryElem_next;
                ElemType queryResult_next;
                //用户输入元素
                scanf("%d", &queryElem_next);
                if (NextElem(*L, queryElem_next, & queryResult_next) != ERROR)
                    printf("The next element of %d is %d\n", queryElem_next, queryResult_next);
                else
                    printf("failed to find\n");
            }

            getchar();
            break;
        case 9:
            if (checkList(L))
            {
                printf("Position: (between 1 to %d)\n", ListLength(*L)+1);
                printf("Please enter the element you want to insert, and the position of it(spaced by space):\n");
                ElemType insertElem;
                int insertPosition;
                //用户输入
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
            //用户输入
            scanf("%d", &deletePosition);
            if (checkList(L) && ListDelete(L, deletePosition, &deleteElem) != ERROR)
                printf("Successfully deleted %d in position %d\n", deleteElem, deletePosition);
            else
                printf("failed to deleted\n");
            getchar();
            break;
        case 11:
            if (checkList(L))
            {
                if (ListTrabverse(*L, visit) == OK)
                    printf("successfully traveled all elements\n");
                else
                    printf("failed to travel all element\n");

            }
            getchar();
            break;
        case 12:
            if (checkList(L))
                printf("List length = %d, ListSize = %d, ListNum = %d\n", L->length, L->listsize, currentIndex);
            else
                printf("ListNUM = %d\n", currentIndex);
            break;
        case 13:
            if (checkList(L))
            {
                printf("Please enter the elem you want to locate with function compare\n");
                ElemType queryElem_locate;
                int queryResult_locate;
                //用户输入
                scanf("%d", &queryElem_locate);
                if (queryResult_locate = LocateElem(*L, queryElem_locate, compare))
                {
                    printf("The position of %d is %d\n", queryElem_locate, queryResult_locate);
                }
            }
            getchar();
            break;
        case 14:
            printf("You have chose to change list\n");
            //打印出每个位置的占用信息，供用户选择
            printListInfo(ListTracker);
            printf("Please enter the index you want to change to\n");
            int tempIndex;
            scanf("%d", &tempIndex);
            if (tempIndex >= 0 && tempIndex < MAX_LIST_NUM)
            {   //如果用户的选择再规定范围之中
                currentIndex = tempIndex;
                if (!ListTracker[currentIndex])
                {   //如果用户所选的位置还没有分配空间。则分配
                    ListTracker[currentIndex] = (SqList *)malloc(sizeof(SqList));
                    ListTracker[currentIndex]->elem = NULL;
                }//否则则正常切换
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
            L = ListTracker[0];
            currentIndex = 0;
            getchar();
            break;
        default://当输入其他字符的时候默认退出
            op = 0;
            break;
        }
    }
    return 0;
}

//由于在所有操作之前均进行了检查表的操作，所以以下操作均假设输入为正常输入，不含有异常处理
status InitaList(SqList * L)
{
    //为表中的elem分配区域
    L->elem = (ElemType *)malloc( LIST_INIT_SIZE * sizeof (ElemType));
    if(!L->elem)
        exit(OVERFLOW);
    //同时初始化表厂为0
    L->length=0;
    L->listsize=LIST_INIT_SIZE;
    return OK;
}

status DestroyList(SqList * ListTracker[MAX_LIST_NUM], int currentIndex)
{
    //首先free掉elem所指向的空间
    free(ListTracker[currentIndex]->elem);
    //再令其为NULL
    ListTracker[currentIndex]->elem = NULL;
    //同时free掉整个表结构
    free(ListTracker[currentIndex]);
    //然后将ListTracker中对应的表赋值为NULL，以表明状态
    ListTracker[currentIndex] = NULL;
    return OK;
}

status ClearList(SqList * L)
{
    //直接令表长为0，表明其元素个数为0，亦即元素可以被覆盖
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
        int literate_time = 0;//迭代次数
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
        int literate_time = 0;//迭代次数
        for (; literate_time < L.length; literate_time++)
        {
            if (L.elem[literate_time] == cur_e)
            {
                if (literate_time)
                {   //如果找到的元素不是第一个
                    * pre_e = L.elem[literate_time - 1];
                    //就将找到的元素赋值给pre_e
                    return OK;
                }

                else//否则提示找到的元素为第一个元素，没有前驱
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
                {   //如果找到的元素为最后一个元素
                    * next_e = L.elem[literate_time + 1];
                    //则将找打的元素赋值给next_e
                    return OK;
                }

                else//否则提示找到的是最后一元素，没有后继
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
    {   //如果储存空间不够，则尝试增加空间分配
        ElemType * newbase = (ElemType *)realloc(L->elem, (L->listsize + LISTINCREMENT) * sizeof(ElemType));
        if (!newbase)
            exit(OVERFLOW);
        L->elem = newbase;
        L->listsize += LISTINCREMENT;
    }
    ElemType * p, * q;
    q = &(L->elem[i-1]);
    //如果空间足够，就先将元素向后挪出位置
    for (p = &(L->elem[L->length-1]); p >= q; --p)
        * (p+1) = * p;
    //然后将元素插入
    * q = e;
    //同时更新表长
    L->length++;
    return OK;
}

status ListDelete(SqList *L,int i,ElemType * e)
{
    if (i < 1 || i > L->length)
        return ERROR;
    ElemType * p, * q;
    p = &(L->elem[i-1]);
    *e = *p;
    q = L->elem + L->length - 1;
    //直接将元素前移
    for (++p; p <= q; ++p)
        *(p-1) = *p;
    //同时修改更新表长
    --L->length;
    return OK;
}

status ListTrabverse(SqList L, void (* visit)(ElemType))
{
    if (L.length)
    {   //迭代次数
        int literate_time = 0;
        for (; literate_time < L.length; literate_time++)
        {   //对每一个元素执行visit函数，此处visit函数的作用是打印元素
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
{   //尝试打开文件
    FILE * fp = fopen("data.txt", "r");
    if (fp == NULL)
    {   //如果文件不存在
        printf("File doesn't exist\n");
        return ERROR;
    }
    int literate_time = 0;
    int current_list_num;
    ElemType current_elem;
    int list_length;
    //不断读取直到文件尾，即EOF
    while(literate_time < MAX_LIST_NUM && fscanf(fp, "%d %d\n\n", &current_list_num, &list_length) != EOF)
    {   //打印log
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
    //尝试打开，如果文件不存在，则创建文件
    if (fp == NULL)
        fp = fopen("data.txt", "wb");
    int literate_time = 0;
    for (; literate_time < MAX_LIST_NUM; literate_time++)
    {
        if (ListTracker[literate_time] && ListTracker[literate_time]->length)
        {   //按照一定格式将数据保存到文件中
            fprintf(fp, "%d %d\n\n", literate_time, ListTracker[literate_time]->length);
            int i = 0;
            for(; i < ListTracker[literate_time]->length; i++)
                fprintf(fp, "%d\n", ListTracker[literate_time]->elem[i]);
        }
    }
    fclose(fp);
    return OK;
}
