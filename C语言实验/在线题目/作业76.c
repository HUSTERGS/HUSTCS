#include<stdio.h>
#include<math.h>
int main(void)
{
    int n, rem, sum;
    scanf("%d", &n);
    int start1[n], start2[n];
    int temp = 0;
    while(scanf("%d%d", &start1[temp], &start2[temp]) != EOF)
    {
        sum = f(start1[temp])%6+1 + f(start2[temp])%6+1;
        rem = sum;
        if(sum == 7 || sum == 11)
            printf("success!\n");
        else if(sum == 2 || sum == 3 || sum == 12)
            printf("fail!\n");
        else
        {
            do
            {
                start1[temp] += 1;
                start2[temp] += 1;
                sum = f(start1[temp])%6+1 + f(start2[temp])%6+1;
            }while(sum != rem && sum != 7);
            if(sum == rem)
                printf("success!\n");
            if(sum == 7)
                printf("fail!\n");
        }
        temp++;
    }
    return 0;
}
int f(int n)
{
    int count, sum, temp;
    count = (int)log10(n)+1;
    for(temp = 0, sum = 0; temp < count; temp++)
    {
        sum += n%10;
        n /= 10;
    }
    return sum;
}
