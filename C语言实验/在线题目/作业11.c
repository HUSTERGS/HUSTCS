#include<stdio.h>
int main(void)
{
    unsigned short x, m, n;
    int num;
    scanf("%d", &num);
    for (;num > 0;num--)
    {
        scanf("%hu%hu%hu", &x, &m, &n);
        x >>= m;
        x <<= (16 - n);
        printf("%hu\n", x);
    }
    return 0;
}
