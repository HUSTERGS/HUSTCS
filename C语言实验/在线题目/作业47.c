#include <stdio.h>
int main(void)
{
    int n, temp, num, count;
    scanf("%d", &count);
    for (; count > 0; count--)
    {
        scanf("%d", &num);
        int nums[num];
        for (n = 0; n < num; n++)
            scanf("%d", &nums[n]);
        for (n = 0; n < (num/2); n++)
        {
            temp = nums[n];
            nums[n] = nums[num - n - 1];
            nums[num - n - 1] = temp;
        }
        for (n = 0; n < num - 1; n++)
            printf("%d ", nums[n]);
        printf("%d\n", nums[n]);
    }
    return 0;
}
