// priklad na if: nacitanie znaku a ak je to *velke pismeno*, vypisanie ord. cisla
// zmenit podmienky
#include <stdio.h>

int main() {
	int c;
	
	if ((c = getchar()) >= 'A' && c <= 'Z')	
		printf("Velke pismeno %c s ord. cislom %d\n", c, c);
	
	if (c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z')	
		printf("Pismeno %c s ord. cislom %d\n", c, c);
		
	//	doplnit podmienku pre Nepismenovy znak
	//	printf("Nepismenovy znak %c s ord. cislom %d\n", c, c);
		
	if (c >= '0' && c <= '9')	
		printf("Cislica %c s ord. cislom %d\n", c, c);
		
	if (c < '0' && c > '9')	
		printf("Necislicovy znak %c s ord. cislom %d\n", c, c);
		
	if (!(c % 2))	// zapisat bez negacie
		printf("%d je parne cislo\n", c);
		
	if (c == '*') 
		printf("%c je hviezdicka\n", c);
	return 0;
}
