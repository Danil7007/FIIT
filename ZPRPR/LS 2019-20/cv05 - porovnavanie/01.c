/*
Predpokladajte definíciu celočíselnej konštanty K. Napíšte funkciu
int porovnaj_mod(const void *a, const void *b), ktorá porovná hodnoty, na ktoré
ukazujú ukazovatele a a b podľa modulo K. Ak je prvý atribút je menší podľa modulo K,
funkcia vráti záporné číslo. Ak je prvý atribút väčší podľa modulo K, funkcia vráti kladné číslo.
Ak sú rovnaké, vráti 0.
Porovnanie podľa modulo K: Ak dve čísla majú rôzny zvyšok po delení K, číslo s menším
zvyškom je považované za menšie podľa modulo K. Ak majú rovnaké zvyšky po delení K, za
menšie podľa modulo K sa považuje to číslo, ktoré je menšie (porovnávajú sa pôvodné čísla,
nie ich zvyšky). Napr. pre čísla 10, 3, 2, 6, 12 a K = 4, sú čísla usporiadané podľa modulo
K: 12, 2, 6, 10, 3, pričom ich zvyšky po delení K = 4 sú 0, 2, 2, 2, 3.
Ukazovateľ na funkciu porovnaj_mod() použite v programe na usporiadanie pomocou
qsort() (z knižnice stdlib.h) na usporiadanie načítaných čísel podľa modulo K.
Ukážka vstupu:
10 3 2 6 12
Ukážka výstupu pre K = 4:
12 2 6 10 3
*/

#include <stdlib.h>
#include <stdio.h>

#define K 7
#define MAX 10

int porovnaj_mod(const void *a, const void *b){
    // ak je modulo a % K < b % K
	if ( ( *(int *)a % K) < ( *(int *)b % K) ){
		return -1;
    }

    // ak je modulo a % K > b % K
	else if ( ( *(int *)a % K) > ( *(int *)b % K) ){
		return 1;
    }

	else {
        return 0;
    }    
}                
                
int main(){
	int pole[MAX], i; 
	
	for (i=0; i < MAX; i++) {
		scanf("%d", &pole[i]);
    }
	
    // pointer na prvy element pola, pocet prvkov, velkost prvkov v bytoch, funkcia na porovnanie
	qsort(pole, MAX, sizeof(int), porovnaj_mod);
	
	for (i=0; i < MAX; i++) {
		printf("%d ", pole[i]);
    } 
	
	return 0;
}
