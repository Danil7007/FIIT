// vypocet dane z prijmu
#include <stdio.h>

int main() 
{
	double prijem;
	
	printf("Zadajte prijem: ");
	scanf("%lf", &prijem);
	
	if (prijem >= 1000000) 
		printf("Milionarska dan: %lf\n", prijem * 0.3);
	else if (prijem >= 500)
		printf("Bezna dan: %lf\n", prijem * 0.2);
	else 
		printf("Z prijmu sa dan neplati\n");
	return 0;
}
