#include <stdio.h>
#include <stdlib.h>

typedef struct Polozka {
    int cislo;
    struct Polozka *dalsi;
} POLOZKA;

void vypis (POLOZKA *prvy) {
    if (prvy == NULL)
        printf ("Prazdny zoznam\n");

    else {
        printf("d", prvy -> cislo);
        if (prvy -> dalsi != NULL) {
            printf (" -> ");
            vypis (prvy -> dalsi);
        }
    }    
}

int main () {
    POLOZKA *prvy;
    prvy = nacitaj();
    vypis (prvy);

    return 0;
}