#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char palindrom[1000];
// tabulka pre ciastocne vypocty - lebo rekurzivna funkcia sa velakrat dostane k rovnakym pod usekom ktore rata
int min[1000][1000];
int n;

int riesenie_minimum (int z, int k) {

    // minimum je uz vypocitane v tabulke
    if (min[z][k] > -1){
        return min[z][k];
    }   

    // hranicny pripad - slovo = jedno pismeno
    if (z == k){   
        min[z][k] = 0;
        return 0;
    }

    // hranicny pripad - 2 pismenkove slovo
    if (z == k-1){   
        // ak sa zhoduju
        if (palindrom[z] == palindrom[k]){
        min[z][k] = 0;
        return 0;      
        }
        // ak nie, minimum je 1
        else {
            return min[z][k] = 1;
        }
      
    }
  
    // z zaciatok slova, k koniec --> P podla toho, ci je doplnena dvojica pismenu vpravo alebo v lavo, 
    // mozu byt rozdielne vysledne dlzky
    //
    //         |  k - 1  |   k
    // --------|---------|--------
    //    z    |   P2    |  
    // --------|---------|--------
    //  z + 1  |   P0    |   P1


    // zhoda krajnych pismen
    if (palindrom[z] == palindrom[k]) {
        return min[z][k] = riesenie_minimum(z+1, k-1);   // P0
    } 
        
    // nezhoda krajnych pismen
    if (palindrom[z] != palindrom[k]){ 

        // zisti, do ktorej strany je vyhodnejsie pridavat pismeno (+1)
        int poc1 = riesenie_minimum(z+1, k);   // P1
        int poc2 = riesenie_minimum(z, k-1);   // P2

        if (poc1 <= poc2) {
            return min[z][k] = poc1 + 1;
        }
        
        else {
            return min[z][k] = poc2 + 1;
        }  
    }
}

// AbCxCbAxxCxxA 

int main() {
  int r, s, i;

    while ( scanf ("%s", palindrom) > 0 ) {

        // dlzka palindromu
        n = strlen(palindrom);

        // vyminusovanie tabulky, nemaju v nej byt este vysledky
        for (r = 0; r < n; r++) {
            for (s = 0; s < n; s++) {
                min[r][s] = -1;
                }    
            }
            

        printf ("%s, minimalny pocet: %d\n", palindrom, riesenie_minimum(0, n-1));

    }

  return 0;
}
