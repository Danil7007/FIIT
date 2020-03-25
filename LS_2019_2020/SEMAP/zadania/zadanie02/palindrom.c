#include <stdio.h>
#include <stdlib.h>

int main(){
    char pole[] = {'a','b','e','c','e','d','a','z','j','e','d','l','a','d','e','d','a','\n'}, palindromy[167][500];
    int zaciatok = 0, koniec = 17, zaznam[3];
    int flag = 0, i, j, n, max=0, dlzka, a, indPal=0, indPal2=0, indSlovoZac, indSlovoKon, vypis; 
    
    a = zaciatok;

    //     ----> vzdy o jednu tym smerom a potom :
    while (a < koniec){
        n = koniec;
    
        //      <-------      porovnavanie postupne tym smerom
        while (n > a){
            // dlzka toho co moze byt palindrom a momentalne to posudzuje (koniec - zaciatok intervalu)
            dlzka = n - a;
            // zvlast index pre koniec intervalu lebo nemoze byt i (odpocitavalo by to vacsiu hodnotu ako 1)
            j=0;
            
            //     -----> <-----     porovnavanie vzdy celeho intervalu
            for (i = a; i <= n / 2 && n != 0; i++) { 
                
                // porovnava pole[i] a pole[n-j-1]
                
                if (pole[i] != pole[n - j -1]) { 
                    flag = 1; 
                    break; 
                } 
                // inkrementacia indexu pre koniec intervalu
                j++;
            } 
          
            // ak nebol palindrom, vynuluj hodnotu na dalsie porovnavanie
            if (flag == 1){
                flag = 0;
            }
            
            // ak bol palindrom
            else {
                // najdlhsi palindrom 
                if (dlzka >= max){
                    max = dlzka;
                    // ulozenie informacii o najdlhsom palindrome do pola
                    zaznam[0] = max;
                    zaznam[1] = a;
                    zaznam[2] = n-1;
                    printf("MAX dlzka %d od %d po %d\n", max, a, n-1);
                }
            } 
            
            // posun smerom     <-----
            n--;
        }
        
        // zapis palindromu
        if (max > 0){
            
            indSlovoZac = zaznam[1];
            indSlovoKon = zaznam[2];
            
            indPal = 0;
            while (indSlovoZac <= indSlovoKon){
                
                palindromy[indPal2][indPal] = pole[indSlovoZac];

                indSlovoZac++;
                indPal++;
            }
            
            indPal2++;
        }
        
        // posun smerom   ----->   po vykonani cyklu
        a++;    
    }
    
    vypis = 0;
    printf("%d ", max);
    for (j=0; j<indPal2; j++){
        
        for(i=0; i<max; i++){
            
           if (palindromy[j][i] == palindromy[j+1][i]){
               vypis++;
           } 
        }

        if (vypis % max != 0){
            vypis = 0;
        }
        
        if (vypis == 0){
            for(i=0; i<max; i++){
              printf("%c", palindromy[j][i]);  
           }
           printf(" ");
        }
        vypis = 0;
        
    }
    
    return 0;
}