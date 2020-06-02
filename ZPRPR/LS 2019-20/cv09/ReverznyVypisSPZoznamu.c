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
        
        if (prvy -> dalsi != NULL) { 
            vypis (prvy -> dalsi);
            printf (" -> ");
        }
        printf("d", prvy -> cislo);
    }    
}

int main () {
    POLOZKA *prvy;
    prvy = nacitaj();
    vypis (prvy);

    return 0;
}