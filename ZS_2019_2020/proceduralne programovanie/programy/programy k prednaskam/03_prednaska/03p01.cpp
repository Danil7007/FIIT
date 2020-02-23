// podmienky
#include <stdio.h>

int main()
{
    int i = 1, j = 1, l =-1, k;
	
	k = i && (j == 3);
//	k = !i && j;
//	k = (i = 2) || j;			// meni sa hodnota i
//	k = !i || (j = j - 1);  	// meni sa hodnota j
//	k = i || (j = j - 1);   	// hodnota j sa nemeni
//	k = i < 0 && --i % 2;		// hodnota i sa nemeni
//	k = i >= 0 && --i % 2;		// meni sa hodnota i
//	k = l++ || (-1)*i; 			// meni sa hodnota l
	
	printf("i: %d j: %d k: %d\n", i, j, k);


	return 0;
}
