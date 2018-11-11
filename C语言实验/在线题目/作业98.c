#define CHANGE c%2
#include <stdio.h>
int main(void)
{
    char c;
    int num, n;
    scanf("%d", &num);
    getchar();
    for (n = 0; n < num; n++)
    {
        c = getchar();
#if CHANGE == 0
        do
        {
            putchar(c);
        }
        while((c = getchar) != '\n');
#elif CHANGE == 1
        do
        {
            if (c >= 'A' && c <= 'Z')
                putchar(c+32);
            else if (c >= 'a' && c <= 'z')
                putchar(c-32);
            else
                putchar(c);
        }while((c = getchar()) != '\n');
#endif // CHANGE
        }
    return 0;
}
