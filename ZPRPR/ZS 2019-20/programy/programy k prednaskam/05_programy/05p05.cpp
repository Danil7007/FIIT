#include <stdio.h>

int maximum(int a, int b) {
	//printf("Volanie funkcie maximum (%d, %d)\n", a, b);
	return (a > b ? a : b);
}

int main() {
	int i, x, max, n;	

	scanf("%d", &n);
	printf("zadajte 1. cislo: ");
	scanf("%d", &max);

	for (i=2; i<=n; i++) {
      	printf("zadajte %d. cislo: ", i);
      	scanf("%d", &x);
      	max = maximum(x, max);
   	}	 
   	printf("Maximum: %d\n", max);

   	return 0;
}

