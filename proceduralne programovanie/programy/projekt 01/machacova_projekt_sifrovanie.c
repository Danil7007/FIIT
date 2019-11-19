#include <stdio.h>
#include <ctype.h>

int main (){
    int vstup_prikaz, povodny[1000], upraveny[1000], *povodny_pointer, *upraveny_pointer, a;
    povodny_pointer = &povodny[0];
    upraveny_pointer = &upraveny[0];
    
    do {
        vstup_prikaz = getchar();
        switch (vstup_prikaz){
            case 'n' : a = nacitaj (povodny_pointer);
                        break;
            case 'v' : a = vypis_povodny (povodny_pointer);
                        break;
            case 'u' : a = uprav (povodny_pointer, upraveny_pointer);
                        break;
            case 's' : a = vypis_upraveny (upraveny_pointer);
                        break;
            case 'd' : a = vypis_danej_dlzky (povodny_pointer);
                        break;
            case 'h' :  a = histogram(int* upraveny)
						break;
            case 'c' : break;
            case 'k' : break;
            default : break;
        }
    }
    while (vstup_prikaz != 'k');

    return 0;
}

//vypisanie slova zelanej dlzky
int vypis_danej_dlzky (int *povodny){
    int i, j=0, k, counter;
    scanf("\n%d", &k);
    int slovo[100];

    if (k < 1 || k > 100){
        return 0;
    }

    if (*povodny == NULL){
        printf ("Sprava nie je nacitana\n");
    }

    else {
        for (i=0; i<1000; ++i){
            //ak nie je biely znak
            if (*(povodny + i) != ' ' || *(povodny + i) != '\n'){
                slovo[j] = *(povodny + i);
                ++j;
            }
            //ak je biely znak a dlzka citaneho slova > 1
            else if ((*(povodny + i) == ' ' || *(povodny + i) == '\n') && j > 0){
                //ak je vyhovujuca dlzka
                if (j + 1 == k){
                    for (j=0; j<k; ++j){
                        printf("%c", slovo[j]);
                        slovo[j] = 0;
                    }
                    j = 0;
                    printf("\n");
                }
            }
        }
        printf("\n");
    }

    return 0;
}

// vypisanie upraveneho pola
int vypis_upraveny (int *upraveny){
    int i;

    if (*upraveny == NULL){
        printf ("Nie je k dispozicii upravena sprava\n");
    }
    else {
        for (i=0; i<1000; ++i){
            printf ("%d", *(upraveny + i));
        }
        printf("\n");
    }

    return 0;
}

// uprava povodneho pola
int uprav (int *povodny, int *upraveny){
    int i, j=0;

    if (*povodny == NULL){
        printf ("Sprava nie je nacitana\n");
    }
    else {
        for (i=0; i<1000; ++i){
            if (*(povodny + i) >= 'A' && *(povodny + i) <= 'z'){
                if (*(povodny + i) >= 'a' && *(povodny + i) <= 'z'){
                    *(upraveny + j) = *(povodny + i) - 32;
                }
                else {
                    *(upraveny + j) = *(povodny + i);
                }
                ++j;
            }
        }
    }

    return 0;
}

// vypisanie povodneho pola
int vypis_povodny (int *povodny){
    int i;

    if (*povodny == NULL){
        printf ("Sprava nie je nacitana\n");
    }
    else {
        for (i=0; i<1000; ++i){
            printf ("%d", *(povodny + i));
        }
        printf("\n");
    }

    return 0;
}

// nacitanie do pola povodny
int nacitaj (int *povodny){
    FILE *subor;
    int c, i=0;

    if ((subor = fopen ("sifra.txt", "r")) == NULL){
		printf ("Spravu sa nepodarilo nacitat\n");
		return 0;
	}

    while ((c = getc (subor)) != EOF) {
		if (i < 1000) {
			*(povodny + i) = c;
            ++i;
		}
        else {
            break;
        }
	}

    if (fclose (subor) == EOF){
        printf ("Subor sa nepodarilo zatvorit\n");
    }
		
	return 0;
}

