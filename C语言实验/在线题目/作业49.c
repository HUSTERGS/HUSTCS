#include <stdio.h>
int main(void)
{
    int n, count, count1, count2;
    char result[200];
    char c;
    scanf("%d", &n);
    getchar();
    while(n)
    {
        char string[n][100];
        for (count = 0; count < n; count++)
        {
            count1 = 0;
            while((c = getchar()) != '\n')
            {
                *(*(string+count)+count1) = c;
                count1++;
            }
            *(*(string+count)+count1) = '\0';
        }
        for (count = count2 = 0; count < n; count++)
        {
            count1 = 0;
            while((*(*(string+count)+count1)) != '\0')
            {
                *(result+count2) = *(*(string+count)+count1);
                count1++;
                count2++;
            }
        }
        *(result+count2) = '\0';
        printf("%s\n", result);
        scanf("%d", &n);
        getchar();
    }
    return 0;
}
