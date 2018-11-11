#include <stdio.h>
int main(void)
{
    int num[10], n, m, temp;
    while(scanf("%d%d%d%d%d%d%d%d%d%d", &num[0], &num[1], &num[2], &num[3], &num[4], &num[5], &num[6], &num[7], &num[8], &num[9]) != EOF)
    {
        for (n = 0; n < 9; n++)
        {
            for (m = 0; m < 10 - n - 1; m++)
            {
                if (*(num+m) > *(num+m+1))
                {
                    temp = *(num+m);
                    *(num+m) = *(num+m+1);
                    *(num+m+1) = temp;
                }
            }
        }
        for (m = 0; m < 9; m++)
        {
            printf("%d->", *(num+m));
        }
        printf("%d\n", *(num+m));
    }
    return 0;
}
