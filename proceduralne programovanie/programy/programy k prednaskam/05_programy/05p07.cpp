// zmena hodnoty premennej vo funkcii - volanie hodnotou
// hodnota mimo funkcie nie je zmenena
#include <stdio.h>

void nacitaj(int i);

int main() {
	int i;
	
	nacitaj(i);
	printf("main() - i: %d\n", i);		// hodnota i sa nezmenila
	//printf("main() / a: %d, b: %d\n", a, b);	// nemame pristup k premennym definovanym v inej funkcii
	return 0;
}

void nacitaj(int i) {
	int a, b;
	
	printf("Zadajte 2 cele cisla: \n");
	scanf("%d %d", &a, &b);
	i = a + b;
	printf("nacitaj() - i: %d, a: %d, b: %d\n", i, a, b);
}

