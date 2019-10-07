// priklad na if: nacitanie znaku a ak je to *velke pismeno*, vypisanie ord. cisla
// zmenit podmienky
#include <stdio.h>

int main() {
	int c;
	
	if ((c = getchar()) >= 'A' && c <= 'Z')	
		printf("Velke pismeno %c s ord. cislom %d\n", c, c);
	else
		printf("Znak %c nie je velke pismeno.\n", c);	
			
	return 0;
}
