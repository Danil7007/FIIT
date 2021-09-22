// zistenie, ci sa dane cislo da napisat ako sucet dvoch prvocisel
#include <stdio.h>
#include <math.h>

int jePrvocislo(int x) {
	int i, odmocnina;
	
	printf("- Volanie funkcie prvocislo (%d)\n", x);
   	odmocnina = (int)pow(x,0.5);
   	for(i=2; i<=odmocnina; i++) 
    	if(x%i==0)
			break; 
   	if(i > odmocnina)
      	return 1;
   	else 
      	return 0;
}

int main() {
	int i, n;
	scanf("%d", &n);
	for(i=2; i<=n/2; i++) {
		printf("Rozdelenie na sumu: %d + %d\n", i, n-i);
		if(jePrvocislo(i) && jePrvocislo(n-i))
			break;
	}
	if(i<=n/2) 
		printf("%d je sucet prvocisel %d a %d\n", n, i, n-i); 
	else
		printf("%d nie je suctom ziadnych dvoch prvocisel", n);
	return 0;
}

