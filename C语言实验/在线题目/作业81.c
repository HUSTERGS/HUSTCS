#include<stdio.h>
#define Swap(x,y) printf("Before Swap:a=%d b=%d\nAfter Swap:a=%d b=%d\n\n", (x), (y), (y), (x))
int main(void)
{
    int a, b;
    int n = 1;
    while(scanf("%d%d", &a, &b) != EOF)
    {
        printf("Case %d:\n", n);
        Swap(a, b);
        n++;
    }
    return 0;
}
