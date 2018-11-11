#include<stdio.h>
int main(void)
{
    int n, temp1, temp2, count, sum, temp;
    scanf("%d", &n);
    int nums[n][11];
    for (temp1 = 0; temp1 < n; temp1++)
        for(temp2 = 0; temp2 < 11; temp2++)
            scanf("%d", &nums[temp1][temp2]);
    for(temp1 = 0; temp1 < n; temp1++)
    {

        if(nums[temp1][0])
        {
            for(count = sum = 0, temp = 1; temp < 11; temp++)
            {
                if(nums[temp1][temp] > 0)
                {
                    sum += nums[temp1][temp];
                    count++;
                }
            }
            if (count)
                printf("In \"no continue\" way,numbers=%d,average=%.6f\n", count, (double)sum / count);
        }
        else
        {
            for(count = sum = 0, temp = 1; temp < 11; temp++)
            {
                if(nums[temp1][temp] <= 0)
                    continue;
                sum += nums[temp1][temp];
                count++;
            }
            if (count)
                printf("In \"continue\" way,numbers=%d,average=%.6f\n", count, (double)sum / count);
        }
    }
    return 0;
}
