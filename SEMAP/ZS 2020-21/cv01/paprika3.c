// uloha1-1.c -- Emma Macháčová, 23.9.2020 23:46

#include <stdio.h>

int t, n;

int max () {
    int a=0, b=0, c=0, zisk=0;
    int dni=0;

    scanf ("%d", &n); // pocet dni
    //printf ("DNI BUDE: %d\n", n);

    if (n == 0 || n == 1) {
        return 0;
    }

    dni = 2;
    zisk = 0;

    scanf ("%d %d", &a, &b);

    // zaciatok -----------------------------------------
    while (dni < n) {

        printf ("(0) %d %d %d\n", a, b, c);

        // klesanie
        while ((a >= b) && (dni < n)) {
            
            printf ("klesam z %d na %d\n", a, b);
            a = b; // klesnutie z a na b 

            printf ("(1) %d %d %d\n", a, b, c);
            if (dni <= n) { 
                scanf ("%d", &b); 
                //printf ("a skenujem %d\n", b);
                dni++;
                printf ("(1.2) %d %d %d\n", a, b, c);
                //printf ("naskenovanych %d z %d\n", dni, n);
            } // posunutie b

        }

        // stupanie 
        if ((a < b) && (dni < n)) {
            c = b;
            while ((c <= b)  && (dni < n)) {
                c = b; // pomocna hodnota na lokalne maximum

                printf ("(2) %d %d %d\n", a, b, c);
                if (dni <= n) { 
                    scanf ("%d", &b);
                    //printf ("skenujem %d\n", b);
                    dni++;
                    printf ("(2.2) %d %d %d\n", a, b, c);
                    //printf ("naskenovanych %d z %d ", dni, n);
                } // posunutie b

                printf ("stupam z %d na %d\n", a, c);
            }

            // ked stupanie skonci
            zisk += c - a;
            //printf ("LOKALNE MAXIMUM %d, zisk %d, naskenovanych %d \n", c, zisk, dni);
            a = b;

            printf ("(3) %d %d %d\n", a, b, c);
            if (dni <= n) { 
                scanf ("%d", &b);
                dni++;
                printf ("(3.3) %d %d %d\n", a, b, c);
            } 
        }
    }
    
    if (b > a) {
        zisk += b - a;
    }
    printf ("%d\n", zisk);
    return 0;
}

int main () {
    int i;
    scanf ("%d", &t); // pocet variant

    for (i=0; i<t; i++) {
        max ();
    }

}