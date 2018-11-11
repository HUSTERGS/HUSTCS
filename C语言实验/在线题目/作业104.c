#include <stdio.h>

int myStrcmp(char *s, char *t);
int main(void)
{
    int n, count, count2;
    scanf("%d", &n);
    struct Web {
        char name1[100];
        char name2[100];
        char URL[100];
    };
    struct Web p[n];
    struct Web temp;
    for (count = 0; count < n; count++)
    {
        scanf("%s", (p+count)->name1);
        scanf("%s", (p+count)->name2);
        scanf("%s", (p+count)->URL);
    }
    for (count = 0; count < n; count++)
    {
        printf("%-20s", (p+count)->name1);
        printf("%-40s", (p+count)->name2);
        printf("%s\n", (p+count)->URL);
    }
    printf("\n");
    for (count = 0; count < n - 1; count++)
    {
        for (count2 = 0; count2 < n - count - 1; count2++)
        {
            if (myStrcmp(((p+count2)->name1), (p+count2+1)->name1))
            {
                temp = p[count2];
                p[count2] = p[count2+1];
                p[count2+1] = temp;
            }
        }
    }
    for (count = 0; count < n; count++)
    {
        printf("%-20s", (p+count)->name1);
        printf("%-40s", (p+count)->name2);
        printf("%s\n", (p+count)->URL);
    }
    return 0;
}
int myStrcmp(char *s, char *t)
{
    if (*s > *t)
        return 1;
    if (*s < *t)
        return 0;
    if (*s == *t)
        myStrcmp(s+1, t+1);
}
