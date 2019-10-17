#include <stdio.h>
#pragma inline
int main(void){
    int i;
    asm mov i, 5
    printf("%d",i);
    return 0;
}