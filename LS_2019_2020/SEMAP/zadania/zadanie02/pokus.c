#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// N tak akurat na tri slova
#define N 1500

void nacitanie (char *pole, int *ind){
    int velkost, i=0, j=0, k=0, pocet=0;
    char c;
    
    velkost = N + 1;
    
    // nacitanie celeho vstupu -------------------------------------------------
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
    
    // zistenie poctu slov -----------------------------------------------------
    for (j=0; j<i; j++){
        if(*(pole+j) == '\n'){
            pocet++;
        }
    }
    
    // realokovanie pre zisteny pocet slov -------------------------------------
    // *2 lebo ukladam zaciatok aj koniec, a +1 lebo ukladam velkost
    pocet = (2*pocet)+1;
    ind = (int *)realloc(ind, pocet);
    
    // zapis indexov - pomoc pre orientaciu v poli -----------------------------
    // na zaciatku pola jeho dlzka
    *(ind+k) = pocet;
    k++;
    // prve slovo vzdy na indexe 0
    *(ind+k) = 0;
    k++;
    for (j=0; j<i; j++){
        if(*(pole+j) == '\n'){
            // zaznamenania pozicie enteru
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
    
    // vypis slov
    while (*(pole+i) != '\0'){
        printf("%c", *(pole+i));
        i++;
    }
    
    // vypis indexov
    dlzka = *ind;
    for (i=1; i < dlzka; i++){
        printf("%d ", *(ind+i));
    }
}

void printSubStr(char *pole, int low, int high) { 
    for ( int i = low; i <= high; ++i ) { 
        printf("%c", pole[i]); 
    }    
}

int palindrom(char *str, int start, int len) { 
    
    int maxLength = 1;  // The result (length of LPS) 
    int low, high; 

    for (int i = 1; i < len; ++i) { 
   
        low = i - 1; 
        high = i; 
        
        while (low >= 0 && high < len && str[low] == str[high]) { 
            
            if (high - low + 1 > maxLength) { 
                start = low; 
                maxLength = high - low + 1; 
            } 
            --low; 
            ++high; 
        } 
  
        low = i - 1; 
        high = i + 1; 
        
        while (low >= 0 && high < len && str[low] == str[high]) { 
            
            if (high - low + 1 > maxLength) { 
                start = low; 
                maxLength = high - low + 1; 
            } 
            --low; 
            ++high; 
        } 
    } 
  
    printf("\n%d ", maxLength); 
    printSubStr(str, start, start + maxLength - 1); 
  
    return maxLength; 
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
    palindrom(slova, 0, 4);
    
    return 0;
}