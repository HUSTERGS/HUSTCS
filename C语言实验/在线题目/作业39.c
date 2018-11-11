#include<stdio.h>
#include<string.h>
int judge(char * chars, int lenth);
int main(void)
{
    int n;
    char chars[1000];
    scanf("%d", &n);
    getchar();
    for (; n > 0; n--)
    {
        fgets(chars, 1000, stdin);
        if(judge(chars, strlen(chars)))
            printf("Yes!\n");
        else
            printf("No!\n");
    }
    return 0;
}
int judge(char * chars, int lenth)
{
    if (lenth <= 1)
        return 1;
    else if (*chars != *(chars+lenth-2))
        return 0;
    else if (*chars == *(chars+lenth-2))
        return judge(chars+1, lenth-2);
}
