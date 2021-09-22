// najdenie prveho zaporneho prvku pola a jeho indexu: vratenie hodnoty cez argumenty
#include <stdio.h>
#define N 10

int prveZaporne(int pole[], int n, int *index);

int main() {
	int index, zaporne, pole[N] = {1, 2, 3, 4, -5, 6, 7, 8, 9, 10};
	
	zaporne = prveZaporne(pole, N, &index);
	if(zaporne != 0)
		printf("zaporne cislo %d je na indexe: %d\n", zaporne, index);
	else
		printf("zaporne cislo sa v poli nenachadza\n");
	return 0;
}

int prveZaporne(int pole[], int n, int *index){ 
    int i;

	*index = -1;
    for(i=0; i<n; i++)
    	if(pole[i] <0)
    		break;
    if(i<n) {
    	*index = i;
    	return pole[i];
	}
    else
		return 0;
} 

