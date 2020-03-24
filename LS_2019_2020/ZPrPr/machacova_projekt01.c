#include <stdio.h>
#include <stdlib.h>

#define N 20

char **pole;
int **znaky;
int pocty[26], dlzky[26];

void nacitaj(int *vyska, int *sirka){
    FILE * subor = fopen("osemsmerovka.txt", "r");
    int i=0, r=0, s=0;
    char c;
    
    // nacitanie dvoch celych cisiel zo suboru
    fscanf(subor, "%d %d", vyska, sirka);
    // alokovanie miesta pre pointre pre pismena-pointre
    pole = (char **)malloc(*vyska *sizeof(char *));
    // alokovanie miesta pre pole
    for (i=0; i < *vyska; i++){
        pole[i] = (char *)malloc(*sirka+1 *sizeof(char)); // +1 pre nulovy znak
    }
    
    // nacitanie po riadkoch zo suboru
    for(r=0; r < *vyska; r++){
        fscanf(subor,"%s", pole[r]);
    }
    
    // TABULKA PISMENOK
    znaky = (int **)malloc(26 *sizeof(int *));
    // alokovanie miesta pre pole
    for (i=0; i < 26; i++){
        znaky[i] = (int *)malloc(N *sizeof(int)); 
    }
    
    // vynulovanie poctov a priradenie prvej dlzky N 
    for(i=0; i<26; i++){
        pocty[i] = 0;
        dlzky[i] = N;
    }
}

// hotova funkcia 
void vypis(int *vyska){
    int r;

    for(r=0; r < *vyska; r++){
        printf("%s\n", pole[r]);
    }
}

int main(){
    int m, n, spolu, *pm = &m, *pn = &n;
    int i=0;
    
    nacitaj(pm, pn);
    vypis(pm);

    return 0;
}