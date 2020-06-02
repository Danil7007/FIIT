// priklad na if: nacitanie znaku a ak je to *velke pismeno*, vypisanie ord. cisla
// zmenit podmienky
#include <stdio.h>

int main() {
	int c;
	c = getchar();
	
	if (c >= 'A' && c <= 'Z' || c >= 'a' && c >= 'z')
		printf("Pismeno %c s ord. cislom %d\n", c, c);
	else
		printf("Znak %c nie je pismeno.\n", c);	
			
	return 0;
}
