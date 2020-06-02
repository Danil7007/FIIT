/*
Napíšte rekurzívnu funkciu void nahrad(char str[], int n) na nahradenie všetkých
nepísmenkových znakov v reťazci str za znak '*'. Argument n predstavuje index meneného
znaku. Využite, že reťazec vstupuje do funkcie len ako ukazovateľ na jeho začiatok (nevytvára
sa jeho lokálna kópia) a preto zmena (prepísanie znaku) vo funkcii je trvalá, ted a zostáva aj po
skončení volania funkcie.
*/

#include <stdio.h>
#include <string.h>

int main()
{
    char vstup[100];
    gets(vstup);
    
    //printf("%s\n", vstup);
    nahrad(vstup, strlen(vstup)-1);
    printf("%s\n", vstup);
    
    return 0;
}

// char str[] = char *str
void nahrad(char str[], int n)
{
    if (n <= -1){
        return;
    }
    
    if (str[n] < 'A' || str[n] > 'z' || ( str[n] > 'Z' && str[n] < 'a')){
        str[n] = '*';
    }
    
    nahrad(str, n-1);
}
