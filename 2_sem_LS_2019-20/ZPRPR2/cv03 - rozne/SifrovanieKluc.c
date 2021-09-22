/*
Napíšte program na šifrovanie správy pomocou kľúča. Správa sa šifruje tak, že sa k jej
písmenám pripočítavajú písmená kľúča, ak je správa dlhšia, kľúč sa opakuje.
Napr. pre správu: TAJNASPRAVA a kľúč HESLO sa správa zašifruje:
TAJNASPRAVA
HESLOHESLOH
*/

#include <stdio.h>
#include <string.h>

int main(){
    char slovo[100], heslo[100], sifra[100];
    int i, ih=0;
    
    gets(slovo);
    gets(heslo);

    
    for (i=0; slovo[i] != '\0'; i++){
        // ked je index ih vacsi ako moze maximalne byt
        if (ih > strlen(heslo) - 1){
            ih=0;
        }
        // A-Z hodnota 0-25, 26 pismen, potom % 26 zisti ktore pismeno a + 'A' to posunie do abecedy 
        sifra[i] = (((slovo[i] - 'A' + heslo[ih] - 'A') % 26) + 'A');
        ih++;
    }
    
    printf("%s", sifra);
    
    return 0;
}
