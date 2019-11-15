#include <stdio.h> 
#define N 100

int main() {
	int cisla[N], parne[N], neparne[N]; 
	int n, i, j=0, k=0;
	
	// nacitanie
	printf("Zadajte pocet prvkov pola: ");
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		printf("%d-ty prvok: ", i);
		scanf("%d", &cisla[i]);
	}
	
	// kopirovanie
	for (i = 0; i < n; i++) 
		if (cisla[i] % 2 == 0) {   // zmena: ak rozdelit cisla podla parity pozicie?
			parne[j] = cisla[i]; 
			j++; 
		} 
		else { 
			neparne[k] = cisla[i]; 
			k++; 
		} 
	
	// vypis
	printf("\nParne prvky:\n"); 
	for (i = 0; i < j; i++) 
		printf("%d, ", parne[i]);
		
	printf("\nNeparne prvky:\n"); 
	for (i = 0; i < k; i++)
		printf("%d, ", neparne[i]);
		
	return 0;
}

