#include<stdio.h>
#include<math.h>
int nums(unsigned int num, int k);
int main(void)
{
    unsigned int num;
    int k;
    while(scanf("%u%d", &num, &k) != EOF)
        printf("%d\n", nums(num, k));
    return 0;
}
int nums(unsigned int num, int k)
{
    int temp;
    int count = (int)log10(num) + 1;
    int nums[count];
    for (temp = 0; temp < count; temp++)
    {
        nums[temp] = num%10;
        num /= 10;
    }
    if (k > count)
        return -1;
    else
        return nums[k-1];
}
