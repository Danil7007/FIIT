#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main() {
	char slovo[100], maska[100], s[100], p, volba, pom;
	FILE *subor;
	int pocet, nahod, i, dlzka, uhadol = 0;
	int rozdiel = 0;

    // iniciacia random
    srand((unsigned)time(NULL));

    // otvorenie suboru a nacitanie poctu slov + posunutie kurzora \n na prve slovo
	subor = fopen("slova.txt", "r");
	fscanf(subor, "%d\n", &pocet);
    
    // vytvorenie nahodneho cisla
    nahod = rand()%(pocet) + 1;
    
    // nacitanie nahodneho slova
    for (i=0; i < nahod; i++){
        fgets(slovo, 100, subor);
    }
    
    
    // zistenie dlzky slova
    dlzka = strlen(slovo);
    dlzka--;
    slovo[dlzka] = '\0';
    
    
    // vytvorenie masky
    for (i=0; i<(dlzka); i++){
        maska[i]='-';
    }
    
    maska[dlzka] = '\0';
    printf("%s\n", maska);
    printf("%s\n%d\n", slovo, dlzka);
    
    while (uhadol==0){
        printf("Hadanie po pismenkach (p) alebo po slovach(s)?\n");
        volba = getc(stdin);
        pom = getc(stdin);
        
        // hadanie pismenka
        if (volba == 'p'){
            printf("Hadanie po pismenkach: ");
            p = getc(stdin);
            pom = getc(stdin);
            for (i=0; i <= dlzka; i++){
                if (slovo[i] == p){
                    maska[i] = p;
                }
            }
            // if(strcmp(maska,slovo)==0){
            // if (maska[0] == slovo[0]){
            //    uhadol = 1;
            //    printf("uhadol\n");
            // }
            printf("%s\n", maska);
            
            // zistenie zhody
            rozdiel = 0;
            for (i=0; i<dlzka; i++){
                if (slovo[i] != maska[i])
                rozdiel++;
            }
            if (rozdiel == 0){
                uhadol = 1;
            }
        }
        
        // hadanie slova
        else if (volba == 's'){
            rozdiel = 0;
            gets(s);
            // if(strcmp(s,slovo)==0){
            // if (s[0] == slovo[0]){
            //    uhadol = 1;
            //    printf("uhadol\n");
            //}
            
            // zistenie zhody
            rozdiel = 0;
            for (i=0; i<dlzka; i++){
                if (slovo[i] != s[i])
                rozdiel++;
                }
                if (strlen(s) != dlzka){
                    rozdiel++;
                }
            if (rozdiel == 0){
                uhadol = 1;
            }
        }
    }
    
    
    printf("Uhadol!");
	return 0;
}