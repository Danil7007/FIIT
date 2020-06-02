// funkcia na najdenie maxima z prvkov pola
#include <stdio.h>
#define N 100

int maximum(int pole[], int n) 
{
    int i, max = pole[0];
    for (i = 1; i < n; i++) {
        if (pole[i] > max)
            max = pole[i];
    }
    return max;
}

int main() {
	int n, i;
	int pole[N];
	
	printf("Zadajte pocet prvkov pola: ");
	scanf("%d", &n);
	if (n>N) return 0;
	printf("Zadajte %d prvkov pola\n", n);
	for(i=0; i<n; i++) 
		scanf("%d", &pole[i]);
		
	printf("Maximum z prvkov pola: %d\n", maximum(pole, n));
	return 0;
}
