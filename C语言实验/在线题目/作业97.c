#include <stdio.h>
#include <math.h>
#define S(a, b, c) (((a)+(b)+(c))/2)
#define AREA(a, b, c) (sqrt(((S(a,b,c))-(a))*((S(a,b,c))-b)*((S(a,b,c))-c)*(S(a,b,c))))
int main (void)
{
    float a,b,c;
    while(scanf("%f%f%f", &a, &b, &c) != EOF)
        printf("%d %f\n",(int)S(a,b,c), AREA(a,b,c));
    return 0;
}
