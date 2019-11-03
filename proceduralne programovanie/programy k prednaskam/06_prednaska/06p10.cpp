// vymazanie cisla z pola
#include<stdio.h>

int vymaz(int pole[], int pozicia, int n);

int main() {
	int a[50], velkost, cislo, i, poz;

	printf("Zadajte velkost pola: ");
	scanf("%d", &velkost);
	printf("Zadajte %d prvkov pola:\n", velkost);
	for(i=0; i<velkost; i++)
		scanf("%d", &a[i]);

	printf("Zadajte poziciu z ktorej vymazeme prvok: ");
	scanf("%d", &poz);

	if(poz >=0 && poz <velkost)
 		velkost = vymaz(a, poz, velkost);
	printf("Pole po vymazani prvku:\n");
	for(i=0; i<velkost; i++)
		printf(" %d",a[i]);
	return 0;
} 

int vymaz(int pole[], int pozicia, int n) {
	int i = pozicia+1;
	while(i < n) {
		pole[i-1] = pole[i];
		i++;
	}
	n--;
	return n;
}
