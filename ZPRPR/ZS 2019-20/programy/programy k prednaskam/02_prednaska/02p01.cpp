// celociselne konstanty: desiatkova a sestnastkova sustava + unsigned
#include <stdio.h>

int main()
{
	int vyska = 0xAA;
	unsigned int u;
	
	printf("vyska: %d (%x)\n", vyska, vyska);
	u = vyska = vyska * (-1);
	printf("vyska: %d, u: %u (%d)\n", vyska, u, u);
	//u = 145u;	// 	u = 4000000000u;
	//printf("u: %u (%d)\n", u, u);
	
	//printf("Najvyssia hodnota premennej unsigned: %u\n", (unsigned) -1);
	
	return 0;
}
