// Napiste funkciu najdlhsie_opakvanie(char x [], int pocet), ktora vrati dlyku najdlhsieho useku v poli znakov,
// obsahujuceho ten isty opakujuci sa znak. X predstavuje najviav 30 znakov, pocet vyjadruje pocet platnych znakov v poli. 
// Vstup obsahuje najviac 3Oznakove slovo, vystupom je jeden riadok obs. cele cislo predstavujuce dlzku
// najdlhsieho useku z nacitaneho slova

#include <stdio.h>

int main()
{
    char pole[29];
    int i = 0;
    
    scanf ("%[^\n]s", pole);
    
    while (pole[i] != '\0'){
        printf ("%c", pole[i]);
        i++;
    }

    return 0;
}