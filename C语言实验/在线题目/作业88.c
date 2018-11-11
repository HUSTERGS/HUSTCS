#include<stdio.h>
int f(int n);
int main(void)
{
    int n;
    while(scanf("%d", &n) != EOF)
        printf("%d\n", f(n));
    return 0;
}
int f(int n)
{
    int sum;
    if (n - 2> 0)
        sum=f(n-1) + f(n-2);
    else
        return 1;
    return sum;
}
