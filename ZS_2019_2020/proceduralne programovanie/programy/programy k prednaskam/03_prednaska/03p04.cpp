// podmienky + skratene vyhodnocovanie logickych operatorov
#include <stdio.h>

int main()
{
    double delenec = 5, delitel = 0, podiel;  // delitel = 1
	
	if (delitel == 0)		// ekvivalentne if (!delitel)
		printf("Delenie nulou!\n");
	else if ((podiel = delenec/delitel) > 1)
		printf("Podiel je vacsi ako 1 (%.2f)\n", podiel);
		
	if (delitel != 0 && (podiel = delenec/delitel) > 1)
//	if ((podiel = delenec/delitel) > 1)  // chyba osetrenie delenia nulou
		printf("Podiel je vacsi ako 1 (%.2lf)\n", podiel);
		
	return 0;
}
