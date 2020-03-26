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
    
    for (r=0; r < *vyska; r++){
        for (s=0; s < *sirka; s++){
            
            i = pole[r][s] - 'A';
            
            pocty[i]++;
            if (pocty[i]*2 > dlzky[i]){
                znaky[i] = (int *)realloc(znaky[i], (dlzky[i]+N) *sizeof(int));
                dlzky[i] += N;
            }
            
            znaky[i][pocty[i] * 2 - 2] = r;
            znaky[i][pocty[i] * 2 - 1] = s;
        }
    }
}

// hotova funkcia 
void vypis(int *vyska, int *sirka){
    int r, s;

    for(r=0; r < *vyska; r++){
        printf("%s\n", pole[r]);
    }
    
    printf("\n");
    
    for (r=0; r < 26; r++){
        printf("%c: ", r+'A');
        for (s=0; s < pocty[r]*2; s++){
            printf("%3d ", znaky[r][s]);
        }
        printf("\n");
    }
    printf("\n");
}

void riesenie(){
    int zmena_r[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
    int zmena_s[8] = {0, 1, 1, 1, 0, -1, -1, -1};
    
}

int main(){
    int m, n, spolu, *pm = &m, *pn = &n;
    int i=0;
    
    nacitaj(pm, pn);
    vypis(pm, pn);

    return 0;
}