// spocitanie suctu prvkov pola - 4 funkcie
#include <stdio.h>

// sucet v cykle, pristup cez indexy
double sum0(double *a, int n) {     
   double vys = 0.0;
   int i;
   for(i = 0; i < n; i++) 
      vys += a[i];
   return vys;
}

// sucet v cykle, pristup cez ukazovatelovu aritmetiku
double sum1(double *a, int n) {     
   double vys = 0.0;
   int i;
   for(i = 0; i < n; i++) 
      vys += *(a + i);
   return vys;
}

// sucet v cykle, pristup cez pomocny ukazovatel s vyuzitim ukazovatelovej aritmetiky
double sum2(double *a, int n) {     
   double vys = 0.0, *p;
   for(p = a; p < a+n; p++) 
      vys += *p;
   return vys;
}

// rekurzivna funkcia, pristup cez indexy
double sum3(double *a, int n) {     
   double vys = 0.0;
   if(n == 0)
      return 0;
   return a[0] + sum3(a+1, n-1);
}

int main() {
	double x[8] = {0,1,2,3,4,5,6,7};
	double s0_7 = sum0(&x[0], 7); 
	double s1_6 = sum1(&x[1], 6); 
	double s2_3 = sum2(&x[2], 3); 
	double s0_5 = sum3(x, 5);
	double s3_2 = sum0(x+3, 2);
	
	printf("Sucet %d prvkov od indexu %d: %.1f\n", 7, 0, s0_7);
	printf("Sucet %d prvkov od indexu %d: %.1f\n", 6, 1, s1_6);
	printf("Sucet %d prvkov od indexu %d: %.1f\n", 3, 2, s2_3);
	printf("Sucet %d prvkov od indexu %d: %.1f\n", 5, 0, s0_5);
	printf("Sucet %d prvkov od indexu %d: %.1f\n", 2, 3, s3_2);

	return 0;
}


