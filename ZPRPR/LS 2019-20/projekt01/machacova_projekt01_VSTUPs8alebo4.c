#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 20

char **pole;
char **maska;
int **znaky;
int pocty[26], dlzky[26];
FILE * subor;
int smerovka;

// hotovo
void nacitaj (int *vyska, int *sirka) {
    int i=0, r=0, s=0;
    //char c;

    // nacitanie dvoch celych cisiel zo suboru
    fscanf (subor, "%d %d", vyska, sirka);
    // alokovanie miesta pre pointre pre pismena-pointre
    pole = (char **) malloc (*vyska *sizeof (char *));
    // alokovanie miesta pre pole
    for (i=0; i < *vyska; i++){
        pole[i] = (char *) malloc (*sirka+1 *sizeof (char)); // +1 pre nulovy znak
    }

    // maska - pre vypis osemsmerovky s vylustenymi slovami
    maska = (char **) malloc (*vyska *sizeof (char *));
    // alokovanie miesta pre pole
    for (i=0; i < *vyska; i++){
        maska[i] = (char *) calloc (*sirka+1, sizeof (char)); // +1 pre nulovy znak
    }

    // nacitanie po riadkoch zo suboru
    for (r=0; r < *vyska; r++){
        fscanf (subor,"%s", pole[r]);
    }

    // TABULKA PISMENOK
    znaky = (int **) malloc (26 *sizeof (int *));
    // alokovanie miesta pre pole
    for (i=0; i < 26; i++){
        znaky[i] = (int *) malloc (N *sizeof (int));
    }

    // vynulovanie poctov a priradenie prvej dlzky N
    for (i=0; i < 26; i++) {
        pocty[i] = 0;
        dlzky[i] = N;
    }

    for (r=0; r < *vyska; r++) {
        for (s=0; s < *sirka; s++) {

            i = pole[r][s] - 'A';

            pocty[i]++;
            if (pocty[i]*2 > dlzky[i]) {
                znaky[i] = (int *) realloc (znaky[i], (dlzky[i] + N) *sizeof (int));
                dlzky[i] += N;
            }

            znaky[i][pocty[i] * 2 - 2] = r;
            znaky[i][pocty[i] * 2 - 1] = s;
        }
    }
}

// hotova funkcia
void vypis (int *vyska, int *sirka) {
    int r, s, rozdiel = 'a' - 'A';

    // osemsmerovka
    for (r=0; r < *vyska; r++) {
        for (s=0; s < *sirka; s++) {
            if (maska[r][s] == 0)
                printf ("%c", pole[r][s]);
            else printf ("%c", pole[r][s] + rozdiel);
        }
        // za slovom
        printf ("\n");
    }

    // za vypisom
    printf ("\n");

    /*
    // tabulka znakov
    for (r=0; r < 26; r++) {
        printf ("%c: ", r + 'A');
        for (s=0; s < pocty[r] * 2; s++) {
            printf("%3d ", znaky[r][s]);
        }
        printf ("\n");
    }
    printf ("\n");
    */
}

// hotovo
void riesenie (int *vyska, int *sirka) {
    // smery pre dvojrozmerny pohyb v osemsmerovke (dvojice tvoriace osem smerov)
    //int zmena_r[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
    //int zmena_s[8] = {0, 1, 1, 1, 0, -1, -1, -1};

    // 4 smery
    //int zmena_r[4] = {-1, 0, 1, 0};
    //int zmena_s[4] = {0, 1, 0, -1};

    // najskor smery 4 smerovky, potom uhlopriecky
    int zmena_r[8] = {-1, 0, 1, 0, -1, 1, 1, -1};
    int zmena_s[8] = {0, 1, 0, -1, 1, 1, -1, -1};

    int dlzka, i, j, k, z, nasiel, zs, zr, smer, s, r;
    char *slovo = (char*) malloc (sizeof (char));

    if (*sirka >= *vyska) {
        slovo = (char*) malloc ((*sirka + 1) *sizeof (char));
    }
    else {
        slovo = (char*) malloc ((*vyska + 1) *sizeof (char));
    }

    // nove / dalsie slovo
    //printf ("zacinam\n");
    while (fscanf (subor, "%s", slovo) > 0) {
        i = slovo[0] - 'A';
        nasiel = 0;
        dlzka = strlen (slovo);
        //printf ("%s %d %d\n", slovo, i, dlzka);

        // rozne zaciatky
        for (z=0; z < pocty[i]; z++){
            // zaciatocne indexy do osemsmerovky pre prve pismeno pre hadane slovo
            zr = znaky[i][z * 2];
            zs = znaky[i][z * 2 + 1];

            // rozne smery (smerovka je bud 8 alebo 4)
            for (smer = 0; smer < smerovka; smer++) {  
                s = zs;
                r = zr;
                j = 0;

                // porovnavanie pismen slova s osemsmerovkou
                while ((j < dlzka) && (s >= 0) && (s < *sirka) && (r >= 0) && (r < *vyska)) {
                    //printf ("zr %d zs %d r %d s %d j %d smer %d\n", zr, zs, r, s, j, smer);

                    // ak sa nezhoduje
                    if (slovo[j] != pole[r][s]){
                        break;
                    }

                    // ak sa zhoduje
                    if (j >= dlzka - 1) {
                        nasiel = 1;
                        //printf ("NASIEL!!\n");

                        // zmena na male pismenka
                        for (k = 0, s = zs, r = zr;    k < dlzka;    k++, s += zmena_s[smer], r += zmena_r[smer]) {
                            maska[r][s] = 1;
                        }

                        break;
                    }

                    // inkrementacia
                    j++;
                    // posun v smere pohybu pri hladani
                    s += zmena_s[smer];
                    r += zmena_r[smer];
                }

                // ak nema vyskrtat vsetky vyskyty daneho slova
                //if (nasiel == 1) break;
            }

            // ak nema vyskrtat vsetky vyskyty daneho slova
            //if (nasiel == 1) break;
        }

        if (nasiel == 1) vypis (vyska, sirka);
        else printf ("Slovo %s sa nepodarilo najst\n\n", slovo);
    }

    // uvolnenie pamate
    free (slovo);
}

// hotovo
void tajnicka (int *vyska, int *sirka) {
    int i, j, prazdna=0;

    for (i=0; i < *vyska; i++) {
        for (j=0; j < *sirka; j++) {

            if (maska[i][j] == 0) {
                printf ("%c\n", pole[i][j]);
                prazdna++;
            }
        }
    }

    if (prazdna == 0){
        printf ("osemsmerovka neobsahovala tajnicku");
    }
    else {
        //printf ("\n");
    }
}

void uvolni (int *vyska) {
    int i;

    // znaky
    for (i=0; i < 26; i++) {
        free (znaky[i]);
    }
    free (znaky);

    // pole a maska
    for (i=0; i < *vyska; i++) {
        free (pole[i]);
        free (maska[i]);
    }
    free (pole);
    free (maska);

    // subor
    fclose (subor);
}

int main () {
    int m, n, *pm = &m, *pn = &n;
    //int i=0;
    subor = fopen ("osemsmerovka.txt", "r");

    if (subor == NULL) {
        printf ("subor sa nepodarilo nacitat\n");
        return 0;
    }

    fscanf (subor, "%d", &smerovka);

    nacitaj (pm, pn);
    //vypis (pm, pn);
    riesenie (pm, pn);
    tajnicka (pm, pn);
    uvolni (pm);

    return 0;
}