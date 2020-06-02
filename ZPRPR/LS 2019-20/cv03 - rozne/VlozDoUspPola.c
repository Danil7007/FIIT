/*
Dané je pole a obsahujúce n celých čísel usporiadaných od najmenšieho po najväčšie a celé
číslo cislo, ktoré do poľa vkladáme. Napíšte rekurzívnu funkciu void vloz(int cislo,
int pole[], int n), ktorá vloží prvok cislo do poľa pole[] tak, že výsledné pole zostane
usporiadané. Pole pole[] je dostatočné veľké aj pre ďalšie číslo.
Správnosť doplnenia funkcie overte v programe.
*/

#include <stdio.h>
#include <string.h>

// char str[] = char *str
void vloz(int x, int p[], int k)
{
    /*
    if(k < 0){
        p[0] = x;
        return;
    }
    */
    
    if (x >= p[k]){
        p[k+1] = x;
        return;
    }
    else {
        p[k+1] = p[k];
        
        if (k == 0){
            p[0] = x;
            return;
        }
        
        vloz(x, p, k-1);
    }
}


int main()
{
    int pole[20];
    int x, i, n=10;
    
    for(i=0; i<10; i++){
        pole[i] = 2*i-5;
    }
    
    for (i = 0; i < n; i++){
        printf("%d ", pole[i]);
    }
    printf("\n");
    
    scanf("%d", &x);
    
    
    vloz(x, pole, n-1);
    n++;
    
    for (i = 0; i < n; i++){
        printf("%d ", pole[i]);
    }
    printf("\n");
    
    return 0;
}

