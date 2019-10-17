#include <stdio.h>

extern "C" int _Cdecl show(char *szMsg);
extern "C" int _Cdecl sum(int a,int b);

int main()
{
	int  i;
	i = show("This is a message from main program\n"); /* i=300 */
	/**/
	asm  mov  cx, 100
L1:	asm  inc  i
	asm  loop L1
	/**/
	printf("i = %d\n", i);	/* i=400 */
	return 0;
}

int sum(int a,int b)
{
	return a+b;
}
