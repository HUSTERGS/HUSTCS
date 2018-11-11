#include<stdio.h>
void exchange(int *nums, int n, int k);
int main(void)
{
    int n, k, j;
    while(scanf("%d%d", &n, &k) != EOF)
    {
        int nums[n];
        for (j = 0; j < n; j++)
            scanf("%d", &nums[j]);
        exchange(nums, n, k);
        for (j = 0; j < n; j++)
            if (j != n-1)
                printf("%d ", nums[j]);
            else
                printf("%d\n", nums[j]);
    }
    return 0;
}
void exchange(int *nums, int n, int k)
{
    int m, j, temp;
    for (m = k; m > 0; m--)
    {
        for (j = 0; j < n-k; j++)
        {
            temp = *(nums+m-1+j);
            *(nums+m+j-1) = *(nums+m+j);
            *(nums+m+j) = temp;
        }
    }
}
