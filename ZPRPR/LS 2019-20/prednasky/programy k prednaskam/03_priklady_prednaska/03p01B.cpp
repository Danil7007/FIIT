// funkcia na najdenie maxima z prvkov pola
// vratenie maxima cez argument
#include <stdio.h>
#define N 100

void maximum(int *pole, int n, int *p_max) 
{
    int *p;
    *p_max = pole[0];
    for (p = pole + 1; p < pole + n; p++) {
        if (*p > *p_max)
            *p_max = *p;
    }
}


int main() {
	int n, i, max;
	int pole[N];
	
	printf("Zadajte pocet prvkov pola: ");
	scanf("%d", &n);
	if (n>N) return 0;
	printf("Zadajte %d prvkov pola\n", n);
	for(i=0; i<n; i++) 
		scanf("%d", &pole[i]);
		
	maximum(pole, n, &max);
	printf("Maximum z prvkov pola: %d\n", max);
	return 0;
}
