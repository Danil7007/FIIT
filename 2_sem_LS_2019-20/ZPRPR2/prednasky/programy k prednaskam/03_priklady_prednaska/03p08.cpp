// vypocet zvolenej aritmetickej operacie
// pole ukazovatelov na funkcie
#include <stdio.h>
int sucet(int x, int y) {return(x + y);}
int rozdiel(int x, int y) {return(x - y);}
int sucin(int x, int y) {return(x * y);}
int podiel(int x, int y) {if (y != 0) return (x / y); else  return 0;}

int main() {
	int x, y, volba, vysledok;
	int (*operacia[4])(int, int);
	operacia[0] = sucet;
	operacia[1] = rozdiel;
	operacia[2] = sucin;
	operacia[3] = podiel;
	
	printf("Zadajte 2 cele cisla: ");
	scanf("%d%d", &x, &y);
	printf("Zadajte 0 pre sucet, 1 pre rozdiel, 2 pre sucin, alebo 3 pre podiel: ");
	scanf("%d", &volba);
	vysledok = operacia[volba](x, y);
	printf("%d", vysledok);
	return 0;
}



