#include <stdio.h>
extern  void  convert(void);
extern  char BUFA;
int INVAL;

void main(void)
{
printf("Please  input a number:");
scanf("%d",&INVAL);
convert();
printf("%s", &BUFA);
}