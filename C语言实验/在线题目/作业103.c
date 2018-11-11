#include <stdio.h>
int main(void)
{
    int n, count, count2;
    struct Student {
        int num;
        char name[19];
        double score;
    };
    struct Student s[3];
    struct Student *p = s;
    scanf("%d", &n);
    for (count = 0; count < n; count++)
    {
        for (count2 = 0; count2 < 3; count2++)
        {
            scanf("%d", &(s[count2].num));
            scanf("%s", s[count2].name);
            scanf("%lf", &(s[count2].score));
        }
        for (count2 = 0; count2 < 3; count2++)
        {
            printf("%d\t", s[count2].num);
            printf("%-20s", s[count2].name);
            printf("%lf\n", s[count2].score);
        }
        for (count2 = 0; count2 < 3; count2++)
        {
            printf("%d\t", (*(p+count2)).num);
            printf("%-20s", (*(p+count2)).name);
            printf("%lf\n", (*(p+count2)).score);
        }
    }
    return 0;
}
