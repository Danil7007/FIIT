/*

Napíšte program, ktorý do poľa načíta dopredu nešpecifikovaný počet celých čísel zo súboru,
pričom súbor budete čítať práve raz. Súbor obsahuje len celé čísla oddelené bielymi znakmi.
Veľkosť poľa meňte podľa potreby tak, aby po načítaní všetkých čísel zo súboru pole
obsahovalo najviac o N viac prvkov, ako bolo načítaných čísel. N definujte ako konštantu.
Ak súčet čísel v poli nie je prvočíslo, nájdite a vložte na koniec poľa najmenšie také číslo, aby
súčet všetkých čísel v poli bolo prvočíslo.
Nakoniec vypíšte všetky prvky poľa do nového riadku aj ich súčet.
Ukážkový súbor:
2 4 6 8
12
Ukážkový výstup:
2 4 12 8 6 5
37

*/

#define N 10

#include <stdio.h>
#include <stdlib.h>

int main() {
	int sucet=0, sucet2, j=0, i = 0, velkost = 10, prvocislo=1, pom;
	int c,blank;

	FILE* subor = fopen("subor.txt", "r");
	int* pole = (int*)calloc(velkost, sizeof(int));

	if (subor == NULL){
		printf("chyba");
	}

	while (c!=EOF && blank!=EOF) {
	    fscanf(subor,"%d%1c", &c,&blank);


			if (i == velkost) {
				velkost += N;
				pole = (int*)realloc(pole, velkost);
			}

			*(pole + i) = c;
			sucet+=c;
			i++;
	}

	// sucet v poli ci je prvocislo
	for (j=2; j <= sucet/2; j++){
	    if (sucet % j == 0){
	        prvocislo = 0;
	        break;
	    }
	}

	sucet2 = sucet;
	// ked pom = 0 je prvocislo
	pom = 0;
	while (prvocislo == 0){
	    sucet2++;
	    // zistuje ci sucet je prvocislo
	    for (j=2; j <= sucet2/2; j++){
	        if(sucet2 % j == 0){
	            pom++;
	        }
	    }
	    if (pom == 0){
	        prvocislo = 1;
	    }
	    else {
            pom = 0;
        }
	}
	sucet2 -= sucet;
	sucet += sucet2;

	if (sucet2 > 0){
	    if(i==velkost){
            velkost += N;
            pole = (int*)realloc(pole, velkost);
	    }
	    *(pole+i+1) = sucet2;
	}
	for(i=0;i<velkost;i++)
	{
	    printf("%d ",*(pole+i));
	}
	printf("\n%d",sucet);

	free(pole);
	return 0;

}

