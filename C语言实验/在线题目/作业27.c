#include<stdio.h>
int number(int i, int j);
int main(void)
{
    int i, j, m, n;
    scanf("%d", &n);
    while (n)
    {
        for(i = 0; i < n; i++)
        {
            for(m = n-i-1; m > 1; m--)
                if (m == n-i-1)
                    printf(" ");
                else
                    printf("  ");
            for(j = 0; j <= i; j++)
                if (i == n-1 && j == 0)
                    printf("%d", number(i, j));
                else if (i == n-2 && j==0)
                    printf("  %d", number(i, j));
                else
                    printf("%4d", number(i, j));
            printf("\n");
        }
        printf("\n");
        scanf("%d", &n);
    }
    return 0;
}
int number(int i, int j)
{
    int sum;
    if (!j)
        sum = 1;
    else
        sum = number(i, j-1)*(i - j + 1)/j;
    return sum;
}
