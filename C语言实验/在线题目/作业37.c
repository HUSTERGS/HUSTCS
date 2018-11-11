#include<stdio.h>
#include<string.h>
void mycpy(char *s, char *t, int n);
void getstring(char * s);
int main(void)
{
    int n, k;
    scanf("%d", &n);
    for (; n > 0; n--)
    {
        char s[1000], t[1000];
        getchar();
        fgets(t,1000,stdin);
        *(t+strlen(t)-1) = '\0';
        scanf("%d", &k);
        mycpy(s, t, k);
        printf("%s\n", s);
    }
    return 0;
}
void mycpy(char *s, char *t, int n)
{
    *(t+n) = '\0';
    strcpy(s, t);
}
