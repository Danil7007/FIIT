#include <stdio.h>

int main(){
    
    char vstup[3000], y[1000];
    
    int i=0, k=0, a=0, b=0, x[1000], ia=0, ib=0, iy=0, ix=0, desA=10, desB=10;
    int pa[1000], pb[1000], zorA[1000], zorB[1000]; 
    int maxA, maxB, iMax, izA=0, izB=0;

    gets (vstup);
    
    while (vstup[i] != '\0'){
        
        // ---------------------- nastavenie prepinacov ----------------------
        
        // ak je vstup A alebo a
        if (vstup[i] == 97 || vstup[i] == 65){
            // pridaj do pola A 
            y[iy] += 65;
            a = 1;
            b = 0;
            iy++;
            desA = 10;
        }
        // ak je vstup B alebo b
        if (vstup[i] == 98 || vstup[i] == 66){
            // pridaj do pola A 
            y[iy] += 66;
            a = 0;
            b = 1;
            iy++;
            desB = 10;
        }
        
        // ak je vstup ine pismeno
        if ((vstup[i] > 66 && vstup[i] < 97) || (vstup[i] > 98 && vstup[i] < 123)){
            a = 0;
            b = 0;
            desA = 10;
            desB = 10;
        }
        
        // -------------------------- skusenosti --------------------------
        
        // ak je vstup cislo nasledujuce za A
        if (vstup[i] < 58 && a == 1 && vstup[i] != 32){
            //printf ("v poli A skusenosti: %c\n", vstup[i]);
            
            // nasleduje medzera
            if (vstup[i+1] < 48){
                pa[ia] += vstup[i]-48; 
                x[ix] += vstup[i]-48;
            }
            // nenasleduje medzera
            if (vstup[i+1] > 48){
                pa[ia] += (vstup[i]-48)*desA;
                x[ix] += (vstup[i]-48)*desA;
                desA /= 10;
            }
        }
        
        if (a == 1 && (vstup[i] == 32 || vstup[i+1] == '\0')){
            ia++;
            ix++;
        }
        
        // ak je vstup cislo nasledujuce za B
        if (vstup[i] < 58 && b == 1 && vstup[i] != 32){
            //printf ("v poli B skusenosti: %c\n", vstup[i]);
            
            // nasleduje medzera
            if (vstup[i+1] < 48){
                pb[ib] += vstup[i]-48; 
                x[ix] += vstup[i]-48;
            }
            // nenasleduje medzera
            if (vstup[i+1] > 48){
                pb[ib] += (vstup[i]-48)*desB;
                x[ix] += (vstup[i]-48)*desB;
                desB /= 10;
            }
        }
        
        if (b == 1 && (vstup[i] == 32 || vstup[i+1] == '\0')){
            ib++;
            ix++;
        }
        
        i++;
    }
    
    for (i=0; i<ia; i++){
        //printf ("%d\n", pa[i]);
    }
    for (i=0; i<ib; i++){
        //printf ("%d\n", pb[i]);
    }
    
    // -------------------------- triedenie --------------------------
    
    // triedenie A --------------------------
    
    maxA = 0;
    for (k=0; k<ia; k++){
        
        i=0;
        while (pa[i+1] != '\0'){
            // najdenie maxima
            if (pa[i] > maxA){
                maxA = pa[i];
                //printf ("zatial najvacsie cislo je cislo: %d s indexom %d\n", maxA, i);
                iMax = i;
            }
            i++;
        }
        
        printf("najvacsie cislo A najdene bolo: %d na indexe: %d\n", maxA, iMax);
        // vynulovanie najvacsieho cisla
        pa[iMax] = 0;
        // pridanie do zoradeneho pola A
        zorA[izA] = maxA;
        izA++;
        // vynulovanie maxima
        maxA = 0;
        // vynulovanie indexov
        i = 0;
        iMax = 0;
        
    }
    
    // triedenie B --------------------------
    
    maxB = 0;
    for (k=0; k<ib; k++){
        
        i=0;
        while (pb[i] != '\0'){
            // najdenie maxima
            if (pb[i] > maxB){
                maxB = pb[i];
                //printf ("zatial najvacsie cislo je cislo: %d s indexom %d\n", maxB, i);
                iMax = i;
            }
            i++;
        }
        
        //printf("najvacsie cislo B najdene bolo: %d na indexe: %d\n", maxB, iMax);
        // vynulovanie najvacsieho cisla
        pb[iMax] = 0;
        // pridanie do zoradeneho pola A
        zorB[izB] = maxB;
        izB++;
        // vynulovanie maxima
        maxB = 0;
        // vynulovanie indexov
        i = 0;
        iMax = 0;
        
    }
    
    // -------------------------- otocenie a vypis --------------------------
   
   printf("IX %d IA %d IB %d\n", ix, ia, ib);
   
   for (i=0; i<ib; i++){
       printf("ZOR B %d\n", zorB[i]);
   }
   for (i=0; i<ia; i++){
       printf("ZOR a %d\n", zorA[i]);
   }
   
   --ia; 
   --ib;
   
   for (i=0; i<ix; i++){
       printf("%c", y[i]);
       // ak A
       if (y[i] == 65){
           printf("%d ", zorA[ia]);
           ia--;
       }
       // ak B
       if (y[i] == 66){
           printf("%d ", zorB[ib]);
           ib--;
       }
   }
    
    return 0;
}
