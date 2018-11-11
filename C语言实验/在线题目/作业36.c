#include<stdio.h>
#include<ctype.h>
int main(void)
{
    char c;
    int i;
    int nums[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
    while((c = getchar()) != '#')
    {
        if (c == '0')
            nums[0]++;
        else if (c == '1')
            nums[1]++;
        else if (c == '2')
            nums[2]++;
        else if (c == '3')
            nums[3]++;
        else if (c == '4')
            nums[4]++;
        else if (c == '5')
            nums[5]++;
        else if (c == '6')
            nums[6]++;
        else if (c == '7')
            nums[7]++;
        else if (c == '8')
            nums[8]++;
        else if (c == '9')
            nums[9]++;
        else if (isalpha(c))
            nums[10]++;
        else
            nums[11]++;
    }
    for(i = 0; i < 10; i++)
        printf("Number %d: %d\n", i ,nums[i]);
    printf("characters: %d\n", nums[10]);
    printf("others: %d\n", nums[11]);
    return 0;
}
