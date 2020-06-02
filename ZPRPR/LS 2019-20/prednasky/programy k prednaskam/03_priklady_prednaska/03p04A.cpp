// vytvorenie dynamickeho pola vo funkcii 
// vratenie ukazovatela cez argument - preto treba ukazovatel na ukazovatel
#include <stdio.h>
#include <stdlib.h>

void init(double **p_f) {
    double *a;
	int i;

	a = (double *) malloc(5 * sizeof(double));

    for(i = 0; i < 5; i++) {
        scanf("%lf", &a[i]);
    }
    *p_f = a;
}

int main() { 
	double *p_d;  
	init(&p_d);
   
	int i;
	for(i = 0; i < 5; i++) 
		printf("%.2f, ", p_d[i]);
	return 0;
}

