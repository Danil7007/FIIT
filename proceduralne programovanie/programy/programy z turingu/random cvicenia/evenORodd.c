#include <stdio.h>

int main () {
    int a;
    scanf ("%d", &a);

    if (a%2==0) printf ("Cislo : %d je parne", a);
    else printf ("Cislo : %d nie je parne", a);

    return 0;
}