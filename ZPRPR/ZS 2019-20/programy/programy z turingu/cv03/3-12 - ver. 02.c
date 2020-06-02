/*
Napíšte program, ktorý načíta 5 kladných celých čísel oddelených medzerou
a vypíše súčet všetkých čísel okrem najväčšieho z nich. Predpokladajte, že čísla sú
rôzne (nie je potrebné to overovať). Súčet čísel na výstupe je nasledovaný znakom
konca riadku.
Ukážka vstupu:
2 1 5 3 4
Ukážkový výstup:
10
*/

#include <stdio.h>

int main () {

    int a[5],i,sum=0,max;
    scanf("%d %d %d %d %d",&a[0],&a[1],&a[2],&a[3],&a[4]);
    for(i=0;i<5;i++)
    {
        if(max<a[i])
        {
            max=a[i];
        }
    }
    for(i=0;i<5;i++)
    {
        sum+=a[i];
    }
    sum-=max;
    printf("%d\n",sum);

}

