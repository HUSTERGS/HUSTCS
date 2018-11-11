#include<stdio.h>
int main(void)
{
    int len, i;
    scanf("%d", &len);
    while(len)
    {
        int nums[len];
        for (i = 0; i < len; i++)
            scanf("%d", &nums[i]);
        for (i = 0; i < len; i++)
        {
            int max = i;
            int j = i;
            while (j < len)
            {
                max = nums[j] > nums[max]? j : max;
                j++;
            }
            int temp = nums[i];
            nums[i] = nums[max];
            nums[max] = temp;
        }
        for (; len > 0; len--)
            if (len != 1)
                printf("%d ", nums[len-1]);
            else
                printf("%d\n", nums[0]);
        scanf("%d", &len);
    }
    return 0;
}
