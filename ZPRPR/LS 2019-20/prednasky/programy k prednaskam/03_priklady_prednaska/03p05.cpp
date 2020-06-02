// vypis hodnot polynomov (x2 + 3, x + 8) pre zadanú hornu, dolnu hranicu a krok 
// pouzitie ukazovatel na funkciu
#include <stdio.h>

double pol1(double x) {
    return  (x * x + 3);
}

double pol2(double x) {
    return  (x + 8);
}

// vypis hodnoty polynomu pre rozne hodnoty x
void vypis(double d, double h, double k, double (*p_f)(double x)) {
    double x;
    for(x=d; x<=h; x+=k) 
        printf("%lf, %lf \n", x, (*p_f)(x));
}  

int main() {
	
	printf("Polynom 1:\n");
	vypis(-1.0, 1.0, 0.1, pol1);
	printf("Polynom 2:\n");
	vypis(-2.0, 2.0, 0.2, pol2);

	return 0;
}
