// Sucin dvoch cisel pomocou scitania - rekurzivna funkcia
#include <stdio.h>

int sucin(int a, int b) {
	printf("Volanie funkcie sucin() - a: %d, b: %d\n", a, b);
	if (b == 1) {
		printf("Koniec rekurzivneho vnarania\n");
		return a;
	}
	else {
		int v;
		v = sucin(a, b-1); 
		printf("Vysledok rekurzivneho volania sucin() - a: %d, b: %d -> %d\n", a, b-1, v);
		return a + v; 
	}		 
}

int main() {
	int x, y;

	printf("Zadajte 2 cele cisla: ");
	scanf("%d %d", &x, &y);
	printf("Sucin: %d * %d = %d\n", x, y, sucin(x, y));
	return 0;
}



