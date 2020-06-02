// znakove konstanty 
#include <stdio.h>

int main()
{
	int c;
	
	printf("Zadajte male pismeno: ");
	c = getchar();
	c = c - 'a' + 'A';			// vyskusajte zmenit velke pismeno na male
	printf("Velke pismeno: %c\n", c);	

	return 0;
}
