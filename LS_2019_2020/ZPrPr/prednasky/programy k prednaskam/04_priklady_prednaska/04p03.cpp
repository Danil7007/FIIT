// program vytvori plne dynamicke 2D pole, naplni hodnotami a vypise
#include <stdio.h>
#include <stdlib.h>

int **create(int riadky, int stlpce) {
	int **p, i;

	p = (int **) malloc(riadky * sizeof(int *));
	for(i = 0; i < riadky; i++)
		p[i] = (int *) malloc(stlpce * sizeof(int));

	return p;
}

int main() {
	int **a;
	a = create(3, 5);

	// priradenie hodnot: cez indexy
	int i, j;
	for(i=0; i<3; i++) 
		for(j=0; j<5; j++) 
			a[i][j] = 10 * i + j;
	
	// vypis hodnot: cez ukazovatele	
	for(i=0; i<3; i++) {
		for(j=0; j<5; j++) 
			printf("%2d ", *(*(a+i) + j));
		printf("\n");	
	}
		
	// uvolnenie pamate
	for(i=0; i<3; i++) {
		free(a[i]);
	}
	free(a);
	
	return 0;
}

