#include<stdio.h>
int main(void)
{
    int down = 3, x = 1;
    double pi = 1.0;
    while(1.0 / (down-2) > 1e-5)
    {
        x = -x;
        pi += 1.0/down * x;
        down += 2;
    }
    printf("%.9f\n", 4 * pi);
    return 0;
}
