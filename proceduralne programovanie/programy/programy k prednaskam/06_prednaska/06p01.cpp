// vypocet priemeru znamok
#include<stdio.h>
#define MAX 5

int main() {
	int i; 
	double znamky[MAX]; 
	double priemer = 0; 

	for (i = 0 ; i < MAX; i++) { 
		printf("Aka je znamka z %d-teho predmetu?", i+1); 
    	scanf("%lf", &znamky[i]); 

		priemer += znamky[i]; 
	} 
	priemer /= MAX;

	printf("Znamky: ");
	for (i = 0 ; i < MAX; i++) 
      printf("%.2f, ", znamky[i]); 
	//printf("->%.2f<-, ", znamky[500]);

	printf("priemer: %.2f\n", priemer); 

	return 0;
}

