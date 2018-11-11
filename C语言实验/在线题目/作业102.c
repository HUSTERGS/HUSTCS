#include<stdio.h>
int main(void)
{
    int sum, n, temp;
    struct date
    {
        int year;
        int month;
        int day;
    };
    struct date data;
    scanf("%d", &n);
    for (temp = 0; temp < n; temp++)
    {
        scanf("%d%d%d", &data.year, &data.month, &data.day);
        int FEB = ((!(data.year%4) && data.year%100) || !(data.year%400))?  29 : 28;
        switch(data.month)
        {
            case 1:sum = data.day;break;
            case 2:sum = 31 + data.day;break;
            case 3:sum = 31 + data.day + FEB;break;
            case 4:sum = 62 + data.day + FEB;break;
            case 5:sum = 92+ data.day + FEB;break;
            case 6:sum = 123+ data.day + FEB;break;
            case 7:sum = 153+ data.day + FEB;break;
            case 8:sum = 184+ data.day + FEB;break;
            case 9:sum = 215+ data.day + FEB;break;
            case 10:sum = 245 + data.day + FEB;break;
            case 11:sum = 276+ data.day + FEB;break;
            case 12:sum = 306+ data.day + FEB;break;
        }
        printf("%d\n", sum);
    }
    return 0;
}
