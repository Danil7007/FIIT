#include <stdio.h>

int main(){
    // "vstup" = max 1000 vojakov, 1000 znakov pre mesiac a 999 medzier plus 1 rezerva
    // pa[], pb[] skusenosti v skupine
    char vstup[3000], y[1000];
    char pa[1000], pb[1000];
    char zorA[1000], zorB[1000];
    char maxA, maxB;
    
    // a, b = prepinace, ia, ib, iy, ix indexy
    int i=0, k=0, a=0, b=0, x[1000], ia=0, ib=0, iy=0, ix=0;
    int izA=0, izB=0;
    int iMax=0;
    
    gets (vstup);
    
    while (vstup[i] != '\0'){
        //printf ("ASCI: %d, char: %c, v poli: %d\n", vstup[i], vstup[i], i);
        
        // -------------------------- skusenosti --------------------------
        
        // ak je vstup cislo nasledujuce za A
        if (vstup[i] < 58 && a == 1 && vstup[i] != 32){
            //printf ("v poli A skusenosti: %c\n", vstup[i]);
            // pridaj skusenosti
            pa[ia] += vstup[i];
            ia++;
            x[ix] += vstup[i];
            ix++;
        }
        // ak je vstup cislo nasledujuce za B
        if (vstup[i] < 58 && b == 1 && vstup[i] != 32){
            //printf ("v poli B skusenosti: %c\n", vstup[i]);
            // pridaj skusenosti
            pb[ib] += vstup[i];
            ib++;
            x[ix] += vstup[i];
            ix++;
        }
        
        // ---------------------- nastavenie prepinacov ----------------------
        
        // ak je vstup A alebo a
        if (vstup[i] == 97 || vstup[i] == 65){
            // pridaj do pola A 
            y[iy] += 65;
            a = 1;
            b = 0;
            iy++;
        }
        // ak je vstup B alebo b
        if (vstup[i] == 98 || vstup[i] == 66){
            // pridaj do pola B
            y[iy] += 66;
            a = 0;
            b = 1;
            iy++;
        }
        // ak je vstup ine pismeno
        if ((vstup[i] == 32 || vstup[i] > 66 && vstup[i] < 97) || (vstup[i] > 98 && vstup[i] < 123)){
            a = 0;
            b = 0;
        }
        
        i++;
    }
    
    //printf ("poradie tried: %s skusenosti A: %s skusenosti B: %s\n", y, pa, pb);
    //printf ("pocet A: %d pocet B: %d\n", ia, ib);
    
    // -------------------------- triedenie --------------------------
    
    // triedenie A --------------------------
    
    maxA = 0;
    // ia = pocet cisiel v pa
    for (k=0; k<ia; k++){
        
        // prejdenie radu cisiel 
        i=0;
        while (pa[i] != '\0'){
            //printf("som na: %c s indexom: %d\n", pa[i], i);
            // najdenie maxima
            if (pa[i] > maxA){
                maxA = pa[i];
                //printf ("zatial najvacsie cislo je cislo: %c s indexom %d\n", maxA, i);
                iMax = i;
            }
            i++;
        }
        
        //printf("najvacsie cislo A najdene bolo: %c na indexe: %d\n", maxA, iMax);
        // vynulovanie najvacsieho cisla
        pa[iMax] = 48;
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
    // ib = pocet cisiel v pb
    for (k=0; k<ib; k++){
        
        // prejdenie radu cisiel
        i=0;
        while (pb[i] != '\0'){
            //printf("som na: %c s indexom: %d\n", pb[i], i);
            // najdenie maxima
            if (pb[i] > maxB){
                maxB = pb[i];
                //printf ("zatial najvacsie cislo je cislo: %c s indexom %d\n", maxB, i);
                iMax = i;
            }
            i++;
        }
 
        //printf("najvacsie cislo B najdene bolo: %c na indexe: %d\n", maxB, iMax);
        // vynulovanie najvacsieho cisla
        pb[iMax] = 48;
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
   
   --ia; 
   --ib;
   
    for (i=0; i<ix; i++){
        printf("%c", y[i]);
        // ak A
       if (y[i] == 65){
           printf("%c ", zorA[ia]);
           ia--;
       }
       // ak B
       if (y[i] == 66){
           printf("%c ", zorB[ib]);
           ib--;
       }
    }
    
    
    return 0;
}
