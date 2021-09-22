// Napiste prog., kt. nacita cele cislo n predstavujuce pocet vstupov. potom zo vstupu
// nacita n riadkov, kazdy obsahujuci dvojicu realnych cisiel (hodinovu mzdu a pocet hodin)
// Pre kazdu z n dvojic program vypise mzdu a nakoniec spolocnu sumu

#include <stdio.h>

double mzda (double h_mzda, double hod);

int main (){
    int n, i;
    double a, b, spolu = 0, m = 0;

    scanf ("%d", &n);

    for (i=0; i<n; i++){

        scanf (" %lf %lf", &a, &b);
        m = mzda (a, b);
        printf ("Mzda: %lf ", m);
        spolu += m;
    }

    printf ("\nSpolu %lf", spolu);
}

double mzda (double hod, double h_mzda){
    int i;
    double mzda;

    for (i=0; i < hod; i++){
        
        if (i < 40){
            mzda += h_mzda;
        }
        if (i >= 40 && i < 60){
            mzda += h_mzda * 1.5;
        }
        if (i >= 60){
            mzda += h_mzda * 2;
        }
    }

    return mzda;
}