/*
Napíšte program, ktorý načíta 5 kladných celých čísel oddelených medzerou
a vypíše súčet všetkých čísel okrem najväčšieho z nich. Predpokladajte, že čísla sú
rôzne (nie je potrebné to overovať). Súčet čísel na výstupe je nasledovaný znakom
konca riadku.
Ukážka vstupu:
2 1 5 3 4
Ukážkový výstup:
10
*/

#include <stdio.h>

int main () {
    int a, b, c, d, e, maximum, sucet;

    scanf ("%d %d %d %d %d", &a, &b, &c, &d, &e) ;
    
    if ((a > b ) && (a > c) && (a > d) && (a > e)) {
        maximum = a ;
    }

    if ((b > a ) && (b > c) && (b > d) && (b > e)) {
        maximum = b ;
    }

    if ((c > b ) && (c > a) && (c > d) && (c > e)) {
        maximum = c ;
    }

    if ((d > b ) && (d > c) && (d > a) && (d > e)) {
        maximum = d ;
    }

    if ((e > b ) && (e > c) && (e > d) && (e > a)) {
        maximum = e ;
    }

    sucet = a + b + c + d + e - maximum ;
    printf ("%d", sucet) ;
}

