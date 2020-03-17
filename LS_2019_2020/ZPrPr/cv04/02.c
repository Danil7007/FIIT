/*
Dané je dynamicky vytvorené pole pole s dĺžkou m obsahujúce n celých čísel usporiadaných
od najmenšieho po najväčšie a celé číslo cislo, ktoré do poľa vkladáme. Napíšte funkciu
int *vloz(int cislo, int *pole, int *m, int *n), ktorá vloží prvok cislo do poľa
pole tak, že výsledné pole zostane usporiadané a cez argument n sa vráti aktuálny počet
platných čísel zapísaných v poli. Ak pole nie je dostatočné veľké na vloženie ďalšieho čísla,
zväčšite ho o konštantu N, ktorú si definujete. Prostredníctvom argumentu m funkcia vráti dĺžku
poľa.
Správnosť doplnenia funkcie overte v programe, kde postupne vkladáte hodnoty.
Ukážka vstupu:
-45 -15 0 28 56 685
45 12
Ukážka výstupu:
-45 -15 0 12 28 45 56 685
*/

#define N 10
#include <stdio.h>
#include <stdlib.h>
int *vloz(int cislo , int *pole , int *m , int *n);
int main() {
    
    int *pole, m, n;
    m = 5;
    n = 5;
    
    pole = (int *)malloc(m);
    
    pole[0] = 12;
    pole[1] = 13;
    pole[2] = 14;
    pole[3] = 16;
    pole[4] = 18;
    vloz(10,pole,&m,&n);
    
    return 0;
}
int *vloz(int cislo , int *pole , int *m , int *n) {
    int m2 = *m;
    int n2 = *n;
    int i;
    
    if (cislo >= pole[n2]){
        pole[n2+1] = cislo;
        return 0;
    }
    
    else {
        
        if (m2 == n2){
            m2 += N;
            pole = (int *)realloc(pole,m2);
        }
    
        pole[n2+1] = pole[n2];
        
        if (n2 == 0){
            pole[0] = cislo;
            return 0;
        }
        
        vloz(cislo, pole, m2, n2-1);
    }
    return pole;
}
