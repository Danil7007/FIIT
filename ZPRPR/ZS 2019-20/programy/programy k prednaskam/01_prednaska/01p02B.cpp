// program prevedie hodiny a minuty na minuty (s premennou pre vysledok a jednym printf)
#include <stdio.h>

int main()
{
	int hod, min, vys;
	
	hod = 3;
	min = 15;
	
	vys = hod * 60 + min;
	printf("%d %d %d", hod, min, vys);
	
	return 0;
}
