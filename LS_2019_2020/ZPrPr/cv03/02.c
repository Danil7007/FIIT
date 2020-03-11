/*
Napíšte funkciu, ktorá vypíše obsah súboru obsahujúceho vnorené jednoduché zátvorky tak, že
vypíše obsah textu mimo zátvoriek a v každej párnej úrovni vnorenia.
Ukážkový súbor:
V subore su zatvorky (ktore sa nevypisu a (ktore sa vypisu(*(#)*))).
Ukážkový výstup:
V subore su zatvorky (ktore sa vypisu(#)).
*/

#include <stdio.h>

int main()
{
    FILE *subor;
    int zatvorka=0;
    char c;
    
    subor = fopen("subor.txt", "r");
    
    if (subor)
    {
        while ((c = getc(subor)) != EOF)
        {
            if(c == '('){
                zatvorka++;
                //printf("%d", zatvorka);
            }
            if(c == ')'){
                zatvorka--;
                //printf("%d", zatvorka);
            }
        
            if (zatvorka % 2 == 0){
                printf("%c", c);
            }
        }
        fclose(subor);
    
    }

    return 0;
}
