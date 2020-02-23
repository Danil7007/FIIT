// program prevedie hodiny a minuty na minuty (bez premennej pre vysledok)
#include <stdio.h>

int main()
{
	int hod, min;
	
	hod = 3;
	min = 15;
	
	printf("%d hodin a %d minut je %d minut.\n", hod, min, hod * 60 + min);
	
	return 0;
}
