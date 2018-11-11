#include<stdio.h>
int main(void)
{
    int x, y, z, mid;
    while (scanf("%d%d%d", &x, &y, &z) != EOF)
    {
        if ((x > z && z > y) || (x < z && z < y))
            printf("C:%d\n", z);
        else if ((x > y && y >= z) || (x < y && y <= z))
            printf("B:%d\n", y);
        else
            printf("A:%d\n", x);
    }
    return 0;
}
