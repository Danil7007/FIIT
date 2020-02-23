
#include <stdio.h>

int main () {
    char a, d, c;
    
    scanf ("%c %c %c", &a, &d, &c) ;

    if ((a == d) && (a == c) && (d == c)) {
        printf ("Vsetky su rovnake") ;
    }

    else {
        if ((a != d) && (a != c) && (d != c)) {
            printf ("Ziadne sa nezhoduju") ;
        }
    else{
        printf ("Dve su rovnake") ;
        }
    }
    return 0;
 
}

