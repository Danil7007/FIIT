// program vypocita obvod a obsah obdlznika (realne cisla - float)
#include <stdio.h>

int main()
{
	float a, b, o, s;
	
	printf("Zadajte strany obdlznika: ");
	scanf("%f %f", &a, &b);
	printf("Stvorec so stranami: %g a %g ma: \n", a, b);
	o = 2 * a + 2 * b;
	s = a * b;
	printf("- obvod %f\n- obsah %f\n", o, s);
	
	return 0;
}
