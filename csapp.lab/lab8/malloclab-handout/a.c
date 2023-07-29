#include <stdio.h>

int main()
{
	int b = 0;
	void * a = &b;
	a += 1;
	printf("%ld", sizeof(a));
	return 0;

}
