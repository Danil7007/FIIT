#include <stdio.h>
#include <stdlib.h>

int porovnaj_vzost(const void *a, const void *b) {
   return (*(int *)a - *(int *)b);
}

int porovnaj_zost(const void *a, const void *b) {
   return (*(int *)b - *(int *)a);
}

void vypis(int x[], int n) {
	int i;
	
	for(i=0; i<n; i++) 
		printf("%d, ", x[i]);
	printf("\n");	
}

int main() {
   int x[] = {5,7,8,-2,4};
   vypis(x, 5);
   qsort(x, 5, sizeof(int), porovnaj_vzost);
   vypis(x, 5);
   qsort(x, 5, sizeof(int), porovnaj_zost);
   vypis(x, 5);
   return 0;
}


