// uloha6-1.c -- Emma Macháčová, 2.11.2019 23:38

#include <stdio.h>
#include <stdlib.h>

int main() 
{ 
    FILE *vstup, *cisla;
    char c;
    int e, pocet;

    vstup = fopen("vstup.txt", "r"); 
    cisla = fopen("cisla.txt", "a"); 

    if (vstup == NULL) { 
        printf("Cannot open file \n"); 
        exit(0); 
    } 
    pocet=0;
    while (c != EOF){
        c = fgetc(vstup);
        e = c;
        if (c =='\n'){
            fprintf(cisla,"\n");
        }
        while (c != '\n') { 
            if (e >= 'a' && e <= 'z' ){
                pocet+=1;
            }
            if (e >= 34 && e <= 126){
                fprintf (cisla,"%c", c);
            }
            c = fgetc(vstup); 
            e = c;
            if (c == EOF){
                break;
            }
        }
        if (pocet>0){
            fprintf(cisla,"\n%d",pocet);
            pocet=0;
        }

    }
    
    
    fclose(vstup); 
    fclose(cisla); 
    return 0; 
}

// uloha6-1.c -- Emma Macháčová, 2.11.2019 23:38

#include <stdio.h>
#include <stdlib.h>

int main() 
{ 
    FILE *vstup, *cisla;
    int pocet,pocet2;

    vstup = fopen("vstup.txt", "r"); 
    cisla = fopen("cisla.txt", "a"); 
 
    pocet=3;
    pocet2=0;
    fprintf(cisla,"\n%d\nble\n%d",pocet2,pocet);
    
    fclose(vstup); 
    fclose(cisla); 
    return 0; 
}