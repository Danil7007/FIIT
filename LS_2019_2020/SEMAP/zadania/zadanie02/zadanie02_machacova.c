#include <stdio.h>
#include <stdlib.h>
#define N 1500

void nacitanie (char *pole, int *pocet){
    int velkost, i=0;
    char c;
    
    velkost = N + 1;
    
    // citanie vstupu
    while (scanf("%c", &c) == 1){
        
        // realokovanie velkosti pola
        if (i == velkost){
            // add miesto na dalsie slovo
            velkost += N;
            pole = (char *)realloc(pole, velkost);
        }
        
        *(pole+i) = c;
        
        printf("%c", *(pole+i));
        
        i++;
    }
    
}

void vypis (char *pole){
    
}

int main(){
    char *slova;
    int *pocet, velkost;
    velkost = N + 1;
    *pocet = 0;
    
    slova = (char *)malloc(velkost *sizeof(char));
    
    nacitanie(slova, pocet);
    //vypis(slova);
    
    printf("\n%d", *pocet);
    
    return 0;
}