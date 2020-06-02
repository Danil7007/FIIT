// funkcia na vymenu premennych - cez parametre funkcie
#include <stdio.h>

void vymen(int *p_x, int *p_y)
{
    int pom;

    pom = *p_x;
    *p_x = *p_y;
    *p_y = pom;
} 

int main() {
	int i, j;
	
	printf("Zadajte 2 cele cisla: ");
	scanf("%d %d", &i, &j);
	
	vymen(&i, &j);
	printf("Vymenene cisla: %d, %d\n", i, j);
	return 0;
}
