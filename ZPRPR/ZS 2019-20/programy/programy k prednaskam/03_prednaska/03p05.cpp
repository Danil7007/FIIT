// podmieneny vyraz: parne/neparne cislo
#include <stdio.h>

int main()
{
	int x;
	scanf("%d", &x);
	
	x % 2 ? printf("neparne\n") : printf("parne\n");
	//printf("%d\n", x % 2 ? printf("neparne\n") : printf("parne\n"));
	
	printf("%s\n", x % 2 ? "neparne\n" : "parne\n");
	
	return 0;
}
