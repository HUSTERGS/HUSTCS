#include<stdio.h>
int main(void)
{
    int nums[1000], temp;
    int count = 0, sum = 0;
    while(scanf("%d%d%d", &nums[count], &nums[count+1], &nums[count+2]) != EOF)
        count += 3;
    for(temp = 0; temp < count;)
    {
        int FEB = ((!(nums[temp]%4) && nums[temp]%100) || !(nums[temp]%400))?  29 : 28;
        switch(nums[temp+1])
        {
            case 1:sum = nums[temp+2];break;
            case 2:sum = 31 + nums[temp+2];break;
            case 3:sum = 31 + nums[temp+2] + FEB;break;
            case 4:sum = 62 + nums[temp+2] + FEB;break;
            case 5:sum = 92+ nums[temp+2] + FEB;break;
            case 6:sum = 123+ nums[temp+2] + FEB;break;
            case 7:sum = 153+ nums[temp+2] + FEB;break;
            case 8:sum = 184+ nums[temp+2] + FEB;break;
            case 9:sum = 215+ nums[temp+2] + FEB;break;
            case 10:sum = 245 + nums[temp+2] + FEB;break;
            case 11:sum = 276+ nums[temp+2] + FEB;break;
            case 12:sum = 306+ nums[temp+2] + FEB;break;
        }
        printf("该日期是这一年中的第%d天\n", sum);
        temp += 3;
    }
    return 0;
}
