#include<stdio.h>
int main(void)
{
    int n, count, next, a1, a2;
    int nums[1000], temp = 0;
    scanf("%d", &nums[temp]);
    while(nums[temp])
    {
        temp++;
        scanf("%d", &nums[temp]);
    }
    for (n = 0; n <= temp; n++)
    {
        if (nums[n] == 0)
            break;
        else if(nums[n] >= 3)
        {
            for (count = a1 = a2 = 1; count <= nums[n]; count++)
            {
                printf("%10d", a1);
                if(count % 8 == 0)
                    printf("\n");
                next = a1 + a2;
                a1 = a2;
                a2 = next;
            }
                printf("\n");
                if(nums[n] % 8)
                    printf("\n");
        }
        else
            printf("Error!\n\n");
    }
    return 0;
}







