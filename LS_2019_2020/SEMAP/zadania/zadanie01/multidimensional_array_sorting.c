// Emma Machacova
// podklad: https://www.sanfoundry.com/c-program-sort-array-ascending-order/

#include <time.h>
#include <stdio.h>

int main(){
    
    int pokus[1000][2] = {
       {2, 19},   
       {1, 25}, 
       {0, 19},   
       {2, 25},
       {0, 10},   
       {1, 22},
       {2, 4}   
    };
    
    int i=0, j=0, k=0, pom=0, vymen=0, pocet_prvkov = 7;
    
    // po jednotlivych prvkoch
    for (i=0; i<pocet_prvkov; i++){
        
        for (j=0; j<pocet_prvkov; j++){
            
            for (k=0; k<pocet_prvkov; k++){
                
                if (pokus[j][1] < pokus[k][1] && pokus[j][0] == pokus[k][0]){
                    
                    pom = pokus[j][1];
                    pokus[j][1] = pokus[k][1];
                    pokus[k][1] = pom;
                }
            }
        }
    }

    for (i=0; i<pocet_prvkov; i++){
        printf("%d %d\n", pokus[i][0], pokus[i][1]);
    }

    return 0;
}
