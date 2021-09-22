// vrati pocet prvocisel v poli
#include <stdio.h>
#include <math.h>

int jePrvocislo(int x);
int pocetPrvocisel(int pole[], int n);

int main() {
	int x[] = {12,67,5,60,7,34,13};
	int velkost;
	
	velkost = sizeof(x) / sizeof(int);
	printf("Pocet prvocisel v poli: %d\n", pocetPrvocisel(x, velkost));
	return 0;
}

int jePrvocislo(int x) {
	int i, odmocnina;
	
   	odmocnina = (int)pow(x,0.5);
   	for(i=2; i<=odmocnina; i++) 
    	if(x%i==0)
			break; 
   	if(i > odmocnina)
      	return 1;
   	else 
      	return 0;
}

int pocetPrvocisel(int pole[], int n) {
	int i, pocet = 0;
	
	for(i=0; i<n; i++)
		if(jePrvocislo(pole[i]))
			pocet++;
	return pocet;
}
