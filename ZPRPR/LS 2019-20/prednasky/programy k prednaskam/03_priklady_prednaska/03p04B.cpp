// vytvorenie dynamickeho pola vo funkcii
// vratenie cez navratovu hodnotu 
#include <stdio.h>
#include <stdlib.h>

double *init() {
	double *a;
	int i;
	a = (double *) malloc(5*sizeof(double));

	for(i=0; i<5; i++) {
		printf("Zadaj %d. cislo ", i);
		scanf("%lf", &a[i]);
	}
	return a;
}

int main() { 
	double *p_d;  
	p_d = init();
   
	int i;
	for(i = 0; i < 5; i++) 
		printf("%.2f, ", p_d[i]);
	return 0;
}

