// znakove konstanty 
#include <stdio.h>

int main()
{

	printf("Zadajte male pismeno: ");
	printf("Velke pismeno: %c\n", getchar() - 'a' + 'A');	

	return 0;
}
