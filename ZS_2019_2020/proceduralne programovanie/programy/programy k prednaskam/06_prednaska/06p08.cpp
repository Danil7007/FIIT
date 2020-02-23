// vypis pola obratene + obratenie pola
#include <stdio.h>

void vypis(int pole[], int n);
void vypisObratene(int pole[], int n);
void otocPole(int pole[], int n);

int main() {
	
	int x[] = {12,67,56,60,88,34,123};
	int velkost = sizeof(x) / sizeof(int);
	
	vypis(x, velkost);
	vypisObratene(x, velkost);
	otocPole(x, velkost);
	vypis(x, velkost);
   	return 0;
}

void vypis(int pole[], int n) {
	int i;
	printf("\nVypis pola:\n");
	for(i=0; i<n; i++)
		printf("%d, ", pole[i]);
}

void vypisObratene(int pole[], int n) {		// ako nevypisovat poslednu ciarku?
	int i;
	printf("\n\nVypis pola obratene:\n");
	for(i=n-1; i>=0; i--)
		printf("%d, ", pole[i]);
}

void otocPole(int pole[], int n) {
	int i, pom;
	printf("\n\nObratenie pola\n");
	for(i=0; i<=n/2; i++) {		// co ak pojdeme po n-1?
		pom = pole[i];
		pole[i] = pole[n-1-i];
		pole[n-1-i] = pom;
	}
}
