#include <stdio.h>

int main () {
    float r ;
    printf ("Zadaj polomer") ;
    scanf ("%f", &r) ;
    printf ("\nObsah kruhu je %.2f\nObvod kruhu je %.2f", 2*3.14159265358*r, 3.14159265358*r*r) ;
    return 0 ;
}