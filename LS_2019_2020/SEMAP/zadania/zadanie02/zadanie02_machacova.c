#include <stdio.h>
#include <stdlib.h>
// N tak akurat na tri slova
#define N 1500

void nacitanie (char *pole, int *ind){
    int velkost, i=0, j=0, k=0, pocet=0;
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
    
    // realokovanie pre zisteny pocet slov (*2 lebo zaciatok-koniec a +1 lebo velkost)
    ind = (int *)realloc(ind, (2*pocet)+1);
    
    // zapis indexov
    // na zaciatku pola dlzka
    *(ind+k) = (2*pocet);
    k++;
    // prve slovo vzdy na indexe 0
    *(ind+k) = 0;
    k++;
    for (j=0; j<i; j++){
        if(*(pole+j) == '\n'){
            *(ind+k) = j;
            k++;
            // zaciatok dalsieho slova
            *(ind+k) = j+1;
            k++;
        }
    }
    // posledny enter
    *(ind+k) = i;
}

// vypisovanie vstupu - hotovo
void vypis (char *pole, int *ind){
    int i=0, dlzka;
    
    while (*(pole+i) != '\0'){
        printf("%c", *(pole+i));
        i++;
    }
    
    dlzka = *ind;
    for (i=1; i <= dlzka; i++){
        printf("%d ", *(ind+i));
    }
}

int main(){
    char *slova;
    int velkost, *indexy;
    velkost = N + 1;
    
    // pole pre slova zo vstupu
    slova = (char *)malloc(velkost *sizeof(char));
    // pole s indexami zaciatkov a koncov slov
    indexy = (int *)malloc(6 *sizeof(int));
    
    nacitanie(slova, indexy);
    vypis(slova, indexy);
    
    return 0;
}