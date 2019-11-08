// typova konverzia vypocet priemeru z celych cisel
#include <stdio.h>

int main() 
{
	int x, y, z;

	printf("Zadajte 3 cele cisla: ");
	scanf("%d %d %d", &x, &y, &z);

	printf("Bez typovej konverzie - priemer: %d\n", (x+y+z) / 3);
	printf("Explicitna typova konverzia - priemer: %.2f\n", (float) (x+y+z) / 3);
	printf("Použitie realnej konstanty: %.2f\n", (x+y+z) / 3.0);
     return 0;
}

