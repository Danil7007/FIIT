// vlozenie cisla do pola
#include<stdio.h>

int vloz(int pole[], int pozicia, int prvok, int n);

int main() {
	int a[50], velkost, cislo, i, poz;

	printf("Zadajte velkost pola: ");
	scanf("%d", &velkost);
	printf("Zadajte %d prvkov pola:\n", velkost);
	for(i=0; i<velkost; i++)
		scanf("%d", &a[i]);

	printf("Zadajte poziciu a cislo na vlozenie: ");
	scanf("%d %d", &poz, &cislo);

	if(poz < 0 || poz > velkost) {
		printf("Pridanie na koniec pola\n");
		poz = velkost;
	}
	velkost = vloz(a, poz, cislo, velkost);
 
	printf("Pole po vlozeni prvku:\n");
	for(i=0; i<velkost; i++)
		printf(" %d",a[i]);

	return 0;
} 

int vloz(int pole[], int pozicia, int prvok, int n) {
	int i = n++;
	while(i > pozicia) {		// co ak neposunieme prvky, ale len pole[pozicia] = prvok;?
		pole[i] = pole[i-1];
		i--;
	}
	pole[i] = prvok;
	return n;
}
