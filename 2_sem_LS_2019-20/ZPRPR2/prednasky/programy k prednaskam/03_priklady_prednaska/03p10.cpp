// vlozenie cisla do usporiadaneho pola 
// rekurzivna funkcia
#include <stdio.h>

void vloz(int pole[], int n, int cislo) {
	if (n == -1) {
		pole[0] = cislo;
	}	
	else if (cislo < pole[n-1]) {
		pole[n] = pole[n-1];
		vloz(pole, n-1, cislo);
	}
	else if (cislo >= pole[n-1]) {
		pole[n] = cislo;
	}	
}

void vypis(int pole[], int n) {
	int i;
	
	for(i=0; i<n; i++)
		printf("%d ", pole[i]);
	printf("\n");
}

int main() {
	
	int a[10] = {-45, -15, 9, 10, 17, 80, 342};
	int cislo, n = 7;
	
	vypis(a, n);
	printf("Zadajte cislo, ktore sa vlozi do pola: ");
	scanf("%d", &cislo);	// nacitanie vkladaneho cisla
	
	vloz(a, n, 45);			// vloz
	n++;					// zvysil sa pocet prvkov pola o 1
	vypis(a, n);

	return 0;
}
