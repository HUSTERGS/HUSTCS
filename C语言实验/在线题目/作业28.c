#include <stdio.h>
#include <math.h>
#define f(x) (3*(x)*(x)*(x)-4*(x)*(x)-5*(x)+13)
#define f1(x) (9*(x)*(x)-8*(x)-5)
#define A 1
int main(void)
{
    double x1 = A, x2, result;
    x2 = x1 - f(x1)/f1(x1);
    while(fabs(x2-x1) > 1e-6)
    {
        x1 = x2;
        x2 = x1 - f(x1)/f1(x1);
    }
    printf("%lf\n", x2);
    return 0;
}
