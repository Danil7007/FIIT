// for: vypis parnych cisel od 1 po 20
#include <stdio.h>

int main() 
{
	int i;

	for (i = 1; i<=20; i++)
		if (!(i % 2))
			printf("%d ", i);
	
	return 0;	
} 
