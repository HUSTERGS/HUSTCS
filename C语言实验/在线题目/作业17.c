#include<stdio.h>
void nums(int a, int b);
int main(void)
{
    int a[1000], b[1000];
    int count = 0, i = 0;
    scanf("%d%d", &a[count], &b[count]);
    while(a[count] || b[count])
    {
        count++;
        scanf("%d%d", &a[count], &b[count]);
    }
    for (i = 0; i < count; i++)
        nums(a[i], b[i]);
    return 0;
}
void nums(int a, int b)
{
    int max, min;
    max = a > b? b : a;
    min = a > b? a : b;
    while (a % max != 0 || b % max != 0)
        max--;
    while (min % a != 0 || min % b != 0)
        min++;
    printf("%d %d\n", max, min);
}
