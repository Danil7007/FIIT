// Emma Machacova
// podklad: https://www.sanfoundry.com/c-program-sort-array-ascending-order/

#include <time.h>
#include <stdio.h>

int main(){
    // meranie casu
	double cas = 0.0;

    // pole na vstup, [index][0] pre vojaka, [index][1] pre skusenosti (lepsie sa mi s tym robi ako s polom x[] a polom y[])
    int pole[1000][2];
    
    // skeny (lebo skenovat to priamo do pola robilo chyby)
    int skenD;
    char skenC;
    
    // indexy i, j, k, pom; pomocna premenna pri sortovani vymen; pocet zadanych prvkov
    int i=0, j=0, k=0, pom=0, vymen=0, pocet_prvkov=0;
    
    // prepnutie medzi cislami a pismenami (vstup zacina pismenom --> pismena = 1)
    int cisla = 0, pismena = 1;
    
    // meranie casu
    clock_t begin = clock();

    do {
        // ----------------------------------------- ak ocakava pismeno 
        if (pismena == 1){
            scanf("%c", &skenC);
            pole[pom][0] = skenC;
            
            // prepinanie pismena / cisla
            pismena = 0;
            cisla = 1;
        }
        
        // ----------------------------------------- ak ocakava cislo
        if (cisla == 1){
            scanf("%d", &skenD);
            pole[pom][1] = skenD;
            
            // prepinanie pismena / cisla
            pismena = 1;
            cisla = 0;
        }
        // inkrementacia indexu pre zadanie dalsieho vojaka
        pom++;
    }
    // kym berie medzery nie enter, podmienka na konci aby nehltal prve pismenko
    while (getc(stdin) != '\n');
    
    
    //  ----------------------------------------- zoradenie vsetkych vstupov
    pocet_prvkov = pom;
    
    for (i=0; i < pocet_prvkov; i++){
        
        for (j=0; j < pocet_prvkov; j++){
            
            for (k=0; k < pocet_prvkov; k++){
                
                // ak je hodnota mensia a "pismeno" sa zhoduje
                if (pole[j][1] < pole[k][1] && pole[j][0] == pole[k][0]){
                    // vymen prvky
                    vymen = pole[j][1];
                    pole[j][1] = pole[k][1];
                    pole[k][1] = vymen;
                }
            }
        }
    }

    // vypis zoradeneho pola 
    for (i=0; i < pocet_prvkov; i++){
        printf("%c%d ", pole[i][0], pole[i][1]);
    }
    
    // stop cas
    clock_t end = clock();
	cas += (double)(end - begin) / CLOCKS_PER_SEC;
	printf("\nCas na exekuciu %f sekund", cas);

    return 0;
}
