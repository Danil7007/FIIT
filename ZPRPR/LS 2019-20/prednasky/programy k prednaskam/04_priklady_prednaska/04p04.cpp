// funkcia pre najdenie maxima statickeho a dynamickeho pola rovnakych rozmerov (5x4)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double **create(int riadky, int stlpce) {
	double **p;
	int i;

	p = (double **) malloc(riadky * sizeof(double *));
	for(i = 0; i < riadky; i++)
		p[i] = (double *) malloc(stlpce * sizeof(double));

	return p;
}

// parameter pre staticke pole: double pole[][4]
double maximumStat(double pole[][4], int riadky) {
    double pom = pole[0][0];
    int i, j;

    for (i = 0; i < riadky; i++) {
        for (j = 0; j < 4; j++) 
            if (pole[i][j] > pom) 
                pom = pole[i][j];
    }
    return (pom);
 }

// parameter pre plne dynamicke pole: double **pole
double maximumDyn(double **pole, int riadky, int stlpce) {
    double pom = pole[0][0];
    int i, j;

    for (i = 0; i < riadky; i++) {
        for (j = 0; j < stlpce; j++) 
            if (pole[i][j] > pom) 
                pom = pole[i][j];
    }
    return (pom);
 }

int main() {
	double p1[5][4], **p2;	
	srand(time(0));
	
	p2 = create(5,4);
	
	int i, j;
	// naplnenie oboch poli nahodnymi cislami od 1 po 100
	for(i=0; i<5; i++) 
		for(j=0; j<4; j++) {
			p1[i][j] = rand() % 100 + 1;
			p2[i][j] = rand() % 100 + 1;
	}
			
	printf("Max (staticke pole): %f\n", maximumStat(p1, 5));
	printf("Max (dynamicke pole): %f\n", maximumDyn(p2, 5, 4));
	
	for(i=0; i<5; i++) {
		free(p2[i]);
	}
	free(p2);
	
	return 0;
}
