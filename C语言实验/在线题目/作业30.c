#include <stdio.h>
int f(int m, int n);
int main(void)
{
    int a, b;
    scanf("%d%d", &a, &b);
    while (a)
    {
        a > b ? printf("%d\n", f(a, b)) : printf("%d\n", f(b, a));
        scanf("%d%d", &a, &b);
    }
    return 0;
}
int f(int m, int n)
{
    m %= n;
    if(m)
        f(n, m);
    else
        return n;
}
