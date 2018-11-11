#include<stdio.h>
#include<string.h>
#include<math.h>
int main(void)
{
    int i, n, sum, j;
    char chars[20];
    scanf("%d", &j);
    for (i = 0; i < j; i++)
    {
        scanf("%s", chars);
        int lenth = strlen(chars);
        for (n = 2, sum = 0; n < lenth; n++)
        {
            if (chars[n] >= '0' && chars[n] <= '9')
                sum += (chars[n] - 48)*(int)pow(16, lenth-n-1);
            else if (chars[n] >= 'a' && chars[n] <= 'z')
                sum += (chars[n] - 87)*(int)pow(16, lenth-n-1);
            else if (chars[n] >= 'A' && chars[n] <= 'Z')
                sum += (chars[n] - 55)*(int)pow(16, lenth-n-1);
        }
        printf("%d\n", sum);
    }
    return 0;
}
