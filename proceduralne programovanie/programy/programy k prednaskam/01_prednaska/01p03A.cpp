// program vypocita obvod a obsah obdlznika
#include <stdio.h>

int main()
{
	int a, b, o, s;
	
	scanf("%d", &a);
	scanf("%d", &b);
	printf("Stvorec so stranami: %d a %d ma: \n", a, b);
	o = 2 * a + 2 * b;
	s = a * b;
	printf("- obvod %d\n- obsah %d\n", o, s);
	
	return 0;
}
