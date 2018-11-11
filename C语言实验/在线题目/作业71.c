#include<stdio.h>
void useif(double x, double y, char n);
void useswitch(double x, double y, char n);
int main(void)
{
    double x, y;
    int t;
    char n;
    while(scanf("%d %lf %lf %c", &t, &x, &y, &n) != EOF)
    {
        if (t == 0)
            useif(x, y, n);
        else if (t == 1)
            useswitch(x, y, n);
        else
        {
            useif(x, y, n);
            useswitch(x, y, n);
        }
        printf("\n");
    }
    return 0;
}
void useif(double x, double y, char n)
{
    double result;
    if (n == '+')
        result = x + y;
    else if (n == '-')
        result = x - y;
    else if (n == '*')
        result = x * y;
    else if (n == '/')
        result = x / y;
    else
        ;
    printf("After if-else processing,the result is : %.2f\n", result);
}
void useswitch(double x, double y, char n)
{
    double result;
    switch(n)
    {
        case '+':result = x + y;break;
        case '-':result = x - y;break;
        case '*':result = x * y;break;
        case '/':result = x / y;break;
        default : break;
    }
    printf("After switch processing,the result is : %.2f\n", result);
}
