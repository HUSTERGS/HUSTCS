#include<stdio.h>
int main(void)
{
    int n;
    unsigned long int ip;
    scanf("%d", &n);
    for (; n > 0; n--)
    {
        scanf("%lu", &ip);
        unsigned short first = ip&0x000000ff;
        unsigned short second = (ip&0x0000ff00)>>8;
        unsigned short third = (ip&0x00ff0000)>>16;
        unsigned short forth = (ip&0xff000000)>>24;
        printf("%hu.%hu.%hu.%hu\n", first, second, third, forth);
    }
    return 0;
}
