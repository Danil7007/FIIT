// priemer 3 cisel 
#include <stdio.h>

int main()
{
	double k, l, m;
	
	printf("Zadajte 3 realne cisla: ");
	scanf("%lf %lf %lf", &k, &l); // chyba nacitanie premennej m
	printf("\nPriemer cisel %f %f %f je %f.\n", k, l, m, (k+l+m)/3);
	
	return 0;
}
