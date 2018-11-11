#include <stdio.h>
#include <math.h>
int main(void)
{
    int begin, end;
    scanf("%d%d", &begin, &end);
    int num = begin%2 ? begin+1 : begin, i;
    while(begin)
    {
        while(num <= end)
        {
            i = 2;
            while(!(f(i) && f(num-i)))
                i++;
            printf("%d=%d+%d\n", num, i, num - i);
            num += 2;
        }
        printf("\n");
        scanf("%d%d", &begin, &end);
        num = begin%2 ? begin+1 : begin;
    }
    return 0;
}
int f(int n)
{
    int i, j;
    for (i = 2, j = (int)sqrt(n); i <= j; i++)
        if (n % i)
            continue;
        else
            return 0;
    return 1;
}
