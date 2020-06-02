// znakove konstanty 
#include <stdio.h>

int main()
{
	int c;
	
	printf("Zadajte male pismeno: ");
	c = getchar() - 'a' + 'A';
	printf("Velke pismeno: %c\n", c);	

	return 0;
}
