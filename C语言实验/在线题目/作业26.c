#include<stdio.h>
int main(void)
{
    long int number;
    scanf("%ld", &number);
    while(number)
    {
        while(number)
        {
            printf("%ld", number%10);
            number /= 10;
        }
        printf("\n");
        scanf("%ld", &number);
    }
    return 0;
}
