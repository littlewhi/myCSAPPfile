#include <stdio.h>

int main()
{
	int i = 0;
	while(++i < 20)
	{
		printf("%d\n", i);
		sleep(2);
	}
	return 0;
}
