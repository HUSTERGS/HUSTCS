#include <iostream.h>
#include "myfuncs.h"

void main(int argc, char *argv[])
{
	char *s;

	if(argc > 1)
		s=argv[1];
	else
		s="the universe";
	cout << GetString() << s << "\n";
}
