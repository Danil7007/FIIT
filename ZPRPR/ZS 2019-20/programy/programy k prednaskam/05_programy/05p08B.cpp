// faktorial - iterativne
#include <stdio.h>

long fakt(long n) {
	long i, f=1;

	for(i=1; i<=n; i++)
		f *= i;
	return f;
}

int main() {
	long i, f=0;

	printf("Zadajte cele cislo: ");
	scanf("%ld", &i);
	f = fakt(i);
	printf("Fakrotial je %ld\n", f);
	return 0;
}
