// realne a celociselne delenie
#include <stdio.h>

int main()
{
	double f, g, vys;
	int i, j;
	
	printf("Zadajte 2 realne cisla: ");
	scanf("%lf %lf", &f, &g);
	vys = f/g;
	printf("%f / %f = %f", f, g, vys);
	
	printf("\n\nZadajte 2 cele cisla: ");
	scanf("%d %d", &i, &j);
	vys = i/j;
	printf("%d / %d = %f", i, j, vys);
	
	return 0;
}
