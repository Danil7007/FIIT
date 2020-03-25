#include <stdio.h>
#include <stdlib.h>
// N tak akurat na tri slova
#define N 1500

int nacitanie (char *pole){
    int velkost, i=0, j=0, pocet=0;
    char c;
    
    velkost = N + 1;
    
    // nacitanie celeho vstupu
    while (scanf("%c", &c) == 1){
        
        // realokovanie velkosti pola
        if (i == velkost){
            // add miesto na dalsie slovo
            velkost += N;
            pole = (char *)realloc(pole, velkost);
        }
        
        *(pole+i) = c;
        //printf("%c", *(pole+i));
        
        i++;
    }
    
    // zistenie poctu slov
    for (j=0; j<i; j++){
        if(*(pole+j) == '\n'){
            pocet++;
        }
    }
    //printf("\n%d", pocet);
    
    return pocet;
}

// vypisovanie vstupu - hotovo
void vypis (char *pole){
    int i=0;
    while (*(pole+i) != '\0'){
        printf("%c", *(pole+i));
        i++;
    }
}

int main(){
    char *slova;
    int velkost;
    velkost = N + 1;
    
    slova = (char *)malloc(velkost *sizeof(char));
    
    nacitanie(slova);
    vypis(slova);
    
    return 0;
}