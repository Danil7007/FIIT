#include <stdio.h>
int main(){
    char vstup[4000], y[1000], pa[1000], pb[1000], zorA[1000], zorB[1000], minA, minB, maxA, maxB;
    int i=0, k=0, a=0, b=0, x[1000], ia=0, ib=0, iy=0, ix=0, izA=0, izB=0, iMax=0;
    gets (vstup);
    while (vstup[i] != '\0'){
        if (vstup[i] < 58 && a == 1 && vstup[i] != 32){
            pa[ia] += vstup[i];
            ia++;
            x[ix] += vstup[i];
            ix++;
        }
        if (vstup[i] < 58 && b == 1 && vstup[i] != 32){
            pb[ib] += vstup[i];
            ib++;
            x[ix] += vstup[i];
            ix++;
        }
        if (vstup[i] == 97 || vstup[i] == 65){
            y[iy] += 65;
            a = 1;
            b = 0;
            iy++;
        }
        if (vstup[i] == 98 || vstup[i] == 66){
            y[iy] += 66;
            a = 0;
            b = 1;
            iy++;
        }
        if ((vstup[i] > 66 && vstup[i] < 97) || (vstup[i] > 98 && vstup[i] < 123)){
            a = 0;
            b = 0;
        }
        i++;
    }
    maxA = 0;
    for (k=0; k<ia; k++){
        i=0;
        while (pa[i] != '\0'){
            if (pa[i] > maxA){
                maxA = pa[i];
                iMax = i;
            }
            i++;
        }
        pa[iMax] = 48;
        zorA[izA] = maxA;
        izA++;
        maxA = 0;
        i = 0;
        iMax = 0;
    }
    maxB = 0;
    for (k=0; k<ib; k++){
        i=0;
        while (pb[i] != '\0'){
            if (pb[i] > maxB){
                maxB = pb[i];
                iMax = i;
            }
            i++;
        }
        pb[iMax] = 48;
        zorB[izB] = maxB;
        izB++;
        maxB = 0;
        i = 0;
        iMax = 0;
    }
   --ia; 
   --ib;
    for (i=0; i<ix; i++){
       printf("%c", y[i]);
       if (y[i] == 65){
           printf("%c ", zorA[ia]);
           ia--;
       }
       if (y[i] == 66){
           printf("%c ", zorB[ib]);
           ib--;
       }
    }
    return 0;
}
