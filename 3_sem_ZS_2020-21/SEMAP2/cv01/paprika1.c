// uloha1-1.c -- Emma Macháčová, 23.9.2020 23:46

#include <stdio.h>

int ceny[100], bol[100], t, n;

int nacitanie () {
    int i;
    for (i=0; i<100; i++) {
        ceny[i] = 0; // vynulovanie
        bol[i] = 0;
    }
    
    scanf ("%d", &n); // pocet dni

    for (i=0; i<n; i++) {
        scanf ("%d", &ceny[i]);
    }

    return 0;
}

int maxZisk (int start, int end) {
    int aktZisk=0, zisk=0, i, j;

    if (start >= end) { // max 1 prvkove pole
        return 0;
    }

    for (i=start; i<end; i++) {
        for (j=i+1; j<end; j++) {
            if (bol[i] > -1) {
                if (ceny[j] > ceny[i]) {

                      aktZisk = ceny[j] - ceny[i] + maxZisk(start, i-1) + maxZisk(j+1, end);

                      if (aktZisk > zisk) {
                          zisk += aktZisk;
                          bol[i] = -1;
                          bol[j] = -1;
                      }          
                }
            }
            
        }
    }
    return zisk;
    
}

int main () {
    int i, print;
    scanf ("%d", &t); // pocet variant

    for (i=0; i<t; i++) {
        nacitanie ();
        print = maxZisk (0, n);
        printf ("%d\n", print);
    }

    return 0;
}