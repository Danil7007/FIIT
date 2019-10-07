// program prevedie hodiny a minuty na minuty (s premennou pre vysledok)
#include <stdio.h>

int main()
{
	int hod, min, vys;
	
	hod = 3;
	printf("%d", hod);
	min = 15;
	printf("%d", min);
	
	vys = hod * 60 + min;
	printf("%d", vys);
	
	return 0;
}
