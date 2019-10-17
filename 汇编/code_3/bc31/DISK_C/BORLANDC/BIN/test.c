#include <stdio.h>
#pragma inline

extern void lulala(void);
extern char temp;

int main(void){
    printf("%d\n", temp);
    asm push ds
    lulala();
    asm pop ds
    printf("%d", temp);
    return 0;
}