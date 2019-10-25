// vypisanie malej nasobilky
#include <stdio.h>

int main() {
	int i, j;
	
	printf("    ");
	for(i=1; i<=10; i++)
		printf("%2d  ", i);
	printf("\n");
	
	for(i=1; i<=10; i++) {
		printf("%2d  ", i);
		for(j=1; j<=i; j++) 
			printf("%2d  ", i*j);
		printf("\n");
	}
	return 0;
}
