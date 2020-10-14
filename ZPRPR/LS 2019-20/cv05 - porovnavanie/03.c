/*
Vytvorte program, ktorý zistí, či je daný štvorec magický. Štvorec je magický vtedy, keď súčet
prvkov vo všetkých riadkoch, stĺpcoch a uhlopriečkach je rovnaký.
Program vytvorí staticky pole N x N prvkov (napr. N = 20). Potom zo štandardného vstupu
načíta rozmer štvorca n (pričom n <= N) a do statického poľa načíta prvky štvorca. Ak bude n
< N, nevyužije sa celý štvorec, ale len jeho časť. Ak je n > N, program skončí s chybovou
hláškou. Potom program vo funkcii int magicky(int pole[][N], int n) zistí, či je štvorec
magický. Nakoniec program na obrazovku vypíše správu magicky alebo nie magicky.
2 príklady magických štvorcov:

8 1 6
3 5 7
4 9 2

16   5   9   4
 3  10   6  15
 2  13  11   8
 7  12  14   1

*/

#include <stdio.h>

#define N 10
#define M 22 // 2N + 2

int main() {
    int pole[N][N], n, i, j;
    int sucty[M], im=0;
    
    // vynulovanie pola
    for (i=0; i<M; i++){
        sucty[i] = 0;
    }
    
    scanf ("%d", &n);
    if (n>N){
        return 0;
    }
    
    // NEVSIMLA SOM SI ZE TAM MA BYT FUNKCIA MAGICKY, AZ KED SOM TO MALA HOTOVE - tak to mam len v maine
    
    // skenovanie po riadkoch
    for (i=0; i<n; i++){
        for (j=0; j<n; j++){
            
            scanf("%d", &pole[i][j]);
        }
    }
    
    // vypis pola
    for (i=0; i<n; i++){
        for (j=0; j<n; j++){
            
            printf("%d ", pole[i][j]);
        }
        printf("\n");
    }
    
    // uhlopriecka 1
    for (i=0; i<n; i++){
        sucty[im] += pole[i][i];
    }
    //printf("sucet uhlopriecky 1: %d\n", sucty[im]);
    im++;
    
    // uhlopriecka 2
    j = n-1;
    for (i=0; i<n; i++){
        sucty[im] += pole[i][j-i];
    }
    //printf("sucet uhlopriecky 2: %d\n", sucty[im]);
    im++;
    
    // riadky 
    for (i=0; i<n; i++){
        
        for (j=0; j<n; j++){
            sucty[im] += pole[i][j];
        }
        
        //printf("sucet riadku %d: %d\n", i+1, sucty[im]);
        im++;
    }
    
    // stlpce
    for (j=0; j<n; j++){
        
        for (i=0; i<n; i++){
            sucty[im] += pole[i][j];
        }
        
        //printf("sucet stlpca %d: %d\n", j+1, sucty[im]);
        im++;
    }
    
    // porovnanie
    for (i=0; i<im-1; i++){
        if (sucty[i] == sucty[i+1]){
            //printf("true, ");
        }
        else {
            printf("NIE JE TO MAGICKY STVOREC");
            return 0;
        }
    }
    
    printf("JE TO MAGICKY STVOREC");
    
    return 0;
}