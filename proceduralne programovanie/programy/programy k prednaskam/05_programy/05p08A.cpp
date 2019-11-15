// faktorial - rekurzivne
#include <stdio.h>

int fakt(int n) {
	return ((n <= 0) ? 1 : n * fakt(n - 1));	
}

int fakt1(int n) {
	if(n <= 0)
		return 1;
	else
		return n * fakt1(n-1);	
}

int main() {
	long i, f=0;

	printf("Zadajte cele cislo: ");
	scanf("%ld", &i);
	f = fakt(i);	
	// f = fakt1(i);
	printf("Fakrotial je %ld\n", f);
	return 0;
}

