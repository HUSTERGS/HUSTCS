/* Copyright (c) 1990, 1992, Borland International */
#include <stdio.h>

int prime(int n)
{
        int i;

        if (n % 2 == 0)
                return (n==2);
        if (n % 3 == 0)
                return (n==3);
        if (n % 5 == 0)
                return (n==5);
        for (i=7; i*i <= n; i+=2)
                if (n % i == 0)
                        return 0;
        return 1;
}

void main(void)
{
        int i, n;

        n = 1000;
        for (i=2; i<=n; i++)
                if (prime(i))
                        printf("%d\n", i);
}
