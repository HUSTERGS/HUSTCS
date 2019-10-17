#include <stdio.h>
//#pragma inline
extern "C" void _Cdecl printstring(void);

int main()
{
	printstring();
	return 0;
}