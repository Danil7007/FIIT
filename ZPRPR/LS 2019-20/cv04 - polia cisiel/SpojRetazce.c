/*
Napíšte funkciu char *spojRetazce(char *str1, char *str2), ktorá dostane 2 reťazce
a vytvorí a vráti nový reťazec v dynamicky vytvorenom poli práve tak veľkom, aby sa do neho
spojili reťazce str1 a str2. Reťazce str1 a str2 spojte do vytvoreného poľa tak, že každý
párny znak (na párnom indexe) je zo str1 a každý nepárny znak je zo str2. Ak je jeden
z reťazcov dlhší ako druhý, doplňte nový reťazec zvyšnými znakmi dlhšieho reťazca.
Obmena: na prístup do polí využite pomocný ukazovateľ a ukazovateľovú aritmetiku.
Ukážka vstupu:
*****
FIITSTU
Ukážka výstupu:
*F*I*I*T*STU
*/

#include <stdio.h>      /* printf, scanf, NULL */
#include <string.h>
#include <stdlib.h>     /* malloc, free, rand */

char *spojRetazce(char *str1, char *str2){
    
    int dlzka, i, istr1=0, istr2=0;
    char *buffer;
    
    // zistenie dlzky bufferu
    dlzka = strlen(str1) + strlen(str2);
    // alokovanie pamati pre buffer + 1 na ukoncujuci znak
    buffer = (char*) malloc (i+1);
    
    if (buffer == NULL){
        exit (1);  
    } 

    for (i=0; i<dlzka; i++){
        
        // parne a neprekracuje max index str1
        if (i%2 == 0 && istr1 <= strlen(str1)){
            buffer[i] = str1[istr1];
            istr1++;
        }
        // neparne a neprekracuje max index str2
        if (i%2 == 1 && istr2 <= strlen(str2)){
            buffer[i] = str2[istr2]; 
            istr2++;
        }
        
        // prekrocena dlzka str2 - vloz str1
        if (istr2 > strlen(str2) && istr1 < strlen(str1)){
            buffer[i] = str1[istr1]; 
            istr1++;
        }
        
        // prekrocena dlzka str1 - vloz str2
        if (istr1 > strlen(str1) && istr2 < strlen(str2)){
            buffer[i] = str2[istr2]; 
            istr2++;
        }
          
    }
    buffer[i]='\0';

    printf ("final string: %s\n",buffer);
    free (buffer);

    return 0;
}

int main (){
    char str1[1000], str2[1000];
    
    gets(str1);
    gets(str2);
    
    spojRetazce(str1, str2);
}

