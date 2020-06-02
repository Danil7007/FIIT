// program vypocita obvod a obsah obdlznika (realne cisla - double)
#include <stdio.h>

int main()
{
	double a, b, o, s;
	
	printf("Zadajte strany obdlznika: ");
	scanf("%lf %lf", &a, &b);
	printf("Stvorec so stranami: %f a %f ma: \n", a, b);
	o = 2 * a + 2 * b;
	s = a * b;
	printf("- obvod %f\n- obsah %f\n", o, s);
	
	return 0;
}
