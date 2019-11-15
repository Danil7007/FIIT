// vymena obsahu premennych: vratenie hodnoty cez argumenty
#include <stdio.h>

void vymen(int *p_x, int *p_y){ 
    int pom;

    pom = *p_x;
    *p_x = *p_y;
    *p_y = pom;
} 

int main() {
	int i = 5, j = 7;
	
	printf("i: %d, j: %d\n", i, j);
	vymen(&i, &j);
	printf("i: %d, j: %d\n", i, j);
	return 0;
}
