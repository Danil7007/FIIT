/*
Napíšte program na zistenie počtu rôznych typov znakov v súbore znaky.txt. Podľa voľby zo
vstupu program zisťuje počet:
- bielych znakov (medzera, tabulátor, znak konca riadku),
- veľkých písmen,
- malých písmen,
- číslic.

Na zistenie, 
    či je znak číslica vytvorte funkciu int cislica(char c), 
    či je malé písmeno – int male_pismeno(char c), 
    veľké písmeno – int velke_pismeno(char c),
    alebo biely znak – int biely(char c). 

Funkcie majú vrátiť hodnotu 1, ak znak je toho typu, ktorý testuje funkcia, inak vrátia 0. 

Ďalej vytvorte funkciu zisti(), ktorá bude ako argument obsahovať ukazovateľ
na funkciu a ukazovateľ na súbor. 

Tá spočíta všetky výskyty znakov v súbore, pre ktoré vráti funkcia 
(ktorá bola argumentom funkcie zisti()) hodnotu 1.)

Prvý riadok vstupu bude obsahovať celé číslo n, ktoré vyjadruje počet zisťovaní. Pre každé z n
zisťovaní bude na vstupe jeden riadok obsahujúci znak 'b', 'v', 'm' alebo 'c', ktorý vyjadruje,
či sa zisťuje počet bielych znakov, resp. veľkých písmen, resp. malých písmen, resp. číslic.
Každý, t.j. aj posledný riadok vstupu je ukončený znakom konca riadku. Výstupom je n riadkov,
každý pre jedno zisťovanie. Pre príslušné zisťovanie bude riadok obsahovať počet zvoleného
typu znakov v súbore. Každý riadok výstupu je ukončený znakom konca riadku.

Ukážka súboru znaky.txt:
AhOj Ferko,
Ako sa mas?

Ukážka vstupu:
2
v
b

Ukážka výstupu:
4
5
*/

#include <stdio.h>
#include <stdlib.h>

int male(char c){
    if (c >= 'a' && c <= 'z'){
        return 1;
    }
    else {
        return 0;
    }   
}

int velke(char c){
    if (c >= 'A' && c <= 'Z'){
        return 1;
    }
    else {
        return 0;
    }  
}

int biely(char c){
    if (c == ' ' || c == '\n' || c == 9){
        return 1;
    }
    else {
        return 0;
    }  
}

int cislo(char c){
    if (c >= '0' && c <= '9'){
        return 1;
    }
    else {
        return 0;
    }  
}

int zisti(int funkcia){
    
    FILE * subor = fopen("subor.txt", "r");
    char c = fgetc(subor), pism;
    int pocet=0;
    
    while (c != EOF){
        if (funkcia == 'm'){
            pocet += male(c);
        }
        if (funkcia == 'v'){
            pocet += velke(c);
        }
        if (funkcia == 'c'){
            pocet += cislo(c);
        }
        if (funkcia == 'b'){
            pocet += biely(c);
        }
        c = fgetc(subor);
    }
    return pocet;
}

int main() {
    int i, n;
    char pole[10], enter;
    
    scanf("%d", &n);
    
    for (i=0; i<n; i++){
        enter = getc(stdin);
        pole[i] = getc(stdin);
        
    }
    
    for (i=0; i<n; i++){
        printf("znak: %c funkcia zisti: %d\n", pole[i], zisti(pole[i]));
    }
    
}
