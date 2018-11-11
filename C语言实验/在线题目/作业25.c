#include<stdio.h>
int main(void)
{
    double x;
    scanf("%lf", &x);
    while(x)
    {
        if (x < 1000)
            printf("%lf\n", 0.0);
        else if (x >= 1000 && x < 2000)
            printf("%lf\n", (x -1000)* 0.05);
        else if (x >= 2000 && x < 3000)
            printf("%lf\n", (x-2000) * 0.1 + 50);
        else if (x >= 3000 && x < 4000)
            printf("%lf\n", (x -3000)* 0.15 + 100+ 50);
        else if (x >= 4000 && x <=5000)
            printf("%lf\n", (x-4000) * 0.2 + 150 + 100 + 50);
        else
            printf("%lf\n", (x -5000)* 0.25 + 200 + 150 + 100 + 50);
        scanf("%lf", &x);
    }
    return 0;
}
