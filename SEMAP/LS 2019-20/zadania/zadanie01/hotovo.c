// Emma Machacova
// podklad: https://www.sanfoundry.com/c-program-sort-array-ascending-order/

#include <time.h>
#include <stdio.h>

int main(){
    // meranie casu
	double cas = 0.0;

    // vsetky cisla c[], cisla A a[], cisla B b[]
    int c[1000], a[1000], b[1000];
    // vsetky pismena p[]
    char p[1000];
    // indexy, pomocna premenna pri sortovani pom
    int i=0, j=0, ic=0, ip=0, ia=0, ib=0, pom;
    // prepnutie medzi cislami a pismenami (vstup zacina pismenom --> pismena = 1); prepinac medzi A a B pA
    int cisla = 0, pismena = 1, pA;
    
    // meranie casu
    clock_t begin = clock();

    do {
        // ak ocakava pismeno 
        if (pismena = 1){
            // naskenuj do pola pismen
            scanf("%c", &p[ip]);
            
            // zistenie ci je A alebo B
            if (p[ip] == 'A' || p[ip] == 'a'){
                pA = 1;
            }
            if (p[ip] == 'B' || p[ip] == 'b'){
                pA = 0;
            }
            
            // index pismena
            ip++;
            // prepinanie pismena / cisla
            pismena = 0;
            cisla = 1;
        }
        
        if (cisla = 1){
            scanf("%d", &c[ic]);
            
            // ak ide cislo za A zapis do pola A
            if (pA == 1){
                a[ia] = c[ic];
                //printf("a[ia] %d, ia %d,\n", a[ia], ia);
                ia++;
            }
            
            // ak ide cislo za B zapis do pola B
            if (pA == 0){
                b[ib] = c[ic];
                //printf("b[ib] %d, ib %d\n", b[ib], ib);
                ib++;
            }
            
            // index cisla
            ic++;
            // prepinanie pismena / cisla
            pismena = 1;
            cisla = 0;
        }
        
        //printf("p[i] %c, c[i] %d\n", p[i], c[i]);
        i++;
    }
    // kym berie medzery nie enter, na konci aby nehltal prve pismenko
    while (getc(stdin) != '\n');
    
    // zoradenie A
    for (i = 0; i < ia; ++i){
        for (j = i + 1; j < ia; ++j){
            // ak je cislo na indexe i vacsie ako na indexe j
            if (a[i] > a[j]){
                // vymenenie pomocou premennej
                pom =  a[i];
                a[i] = a[j];
                a[j] = pom;
            }
        }
    }
    // zoradenie B
    for (i = 0; i < ib; ++i){
        for (j = i + 1; j < ib; ++j){
            // ak je cislo na indexe i vacsie ako na indexe j
            if (b[i] > b[j]){
                // vymenenie pomocou premennej
                pom =  b[i];
                b[i] = b[j];
                b[j] = pom;
            }
        }
    }
    
    // vypis
    ia = 0;
    ib = 0;
    
    // ic = index vsetkych cisiel spolu
    for (i = 0; i < ic; ++i){
        // ak ma ist v povodnom poradi A
        if (p[i] == 'A' || p[i] == 'a'){
            printf("A%d ", a[ia]);
            ia++;
        }
        // ak ma ist v povodnom poradi B  
        if (p[i] == 'B' || p[i] == 'b'){
            printf("B%d ", b[ib]);
            ib++;
        }  
    }
    
    // stop
    clock_t end = clock();
	cas += (double)(end - begin) / CLOCKS_PER_SEC;
	printf("\nCas na exekuciu %f sekund", cas);

    return 0;
}
