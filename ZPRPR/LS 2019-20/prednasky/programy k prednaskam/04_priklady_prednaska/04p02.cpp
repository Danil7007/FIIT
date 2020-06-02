// program vytvori dynamicke 2D pole (trojuholnikove: kazdy i-ty riadok ma i prvkov)
// zapise hodnoty, vypise hodnoty a adresy riadkov aj prvkov pola
#include <stdio.h>
#include <stdlib.h>
#define N 3

int main() {
	int *m[N]; 	// staticke pole N ukazovatelov na pole cisel
	int i, j, k=1;
	
	for(i = 0; i < N; i++) {
    	m[i] = (int *) malloc((i+1) * sizeof(int));
		for(j=0; j<i+1; j++)
			m[i][j] = k++;

	}
	
	printf("Vypisy hodnot pola:\n");
	for(i=0; i<N; i++) {
		for(j=0; j<i+1; j++)
			printf("%d ", m[i][j]);
		printf("\n");
	}
	
	printf("\nVypisy adries pola:\n");	
	for(i=0; i<N; i++) {
		printf("riadok %d: %p\n ", i, m[i]);
		for(j=0; j<i+1; j++)
			printf("m[%d][%d]: %p, ", i, j, &m[i][j]);
		printf("\n");
	}

	for(i=0; i<N; i++) {
		free(m[i]);
	}
	return 1;
}

