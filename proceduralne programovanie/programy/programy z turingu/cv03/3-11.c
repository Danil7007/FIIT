/*Napíšte program, ktorý načíta tri písmená nasledované znakom konca riadku.
Výstupom je jeden riadok obsahujúci jednu zo správ: Vsetky pismena su
rozne, Dve pismena su rovnake alebo Vsetky pismena su rovnake, v
závislosti od pravdivosti danej správy. Riadok je ukončený znakom konca riadku.
Ukážka vstupu:
p v p
Ukážkový výstup:
Dve pismena su rovnake
*/

#include <stdio.h>

int main () {
    char a, b, c;
    
    scanf ("%c %c %c", &a, &b, &c) ;

    if ((a == b) && (a == c) && (b == c)) {
        printf ("Vsetky su rovnake") ;
    }

    else {
        if ((a != b) && (a != c) && (b != c)) {
            printf ("Ziadne sa nezhoduju") ;
        }
        else {
            printf ("Dve su rovnake") ;
        }
    }

}

