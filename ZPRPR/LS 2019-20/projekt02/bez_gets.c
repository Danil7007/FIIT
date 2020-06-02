// https://repl.it/languages/c

#pragma GCC ignore
#pragma GCC diagnostic ignored "-Wimplicit-function-declaration"
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct meno {
    char krstne[100];
    char priezv[100];
} MENO;
typedef struct herec {
    MENO meno_herca;
    int narodeniny;
    struct herec *dalsi_herec;
} HEREC; 
typedef struct film {
    char nazov[100];
    int rok;
    MENO reziser;
    HEREC *herci;
    struct film *dalsi_film;
} FILM;

// hlavicka
FILM* nacitaj (FILM *prvy); // nacitanie suboru
void nacitaj_herca_subor (FILE* subor, HEREC *temp_herec); // pomocna funkcia pre funkciu nacitaj
int vypis_filmy (FILM *prvy); // funkcia vypis zo zadania
int vypis_herci (HEREC *prvy); // pomocna funkcia pre vypis_filmy
void odstran_enter (char *pole); // pomocna funkcia na nahradenie \n v stringu --> \0
FILM* pridaj (FILM *prvy); // pridanie dalsieho filmu do zoznamu zo stdin
FILM* vymaz (FILM *prvy); // vymazanie filmu
void filmy (FILM *prvy); // vypis filmov, kde hral dany herec
void herci (FILM *prvy); // vypis hercov ktori hrali v 2 vybranych filmoch
int skontroluj (FILM *prvy); // kontrola nacitania filmov
FILM* uvolni (FILM *prvy); // funkcia koniec zo zadania
FILM* uvolni_filmy (FILM *prvy); // pomocna funkcia k uvolni
void uvolni_hercov (HEREC *prvy); // pomocna funkcia k uvolni
void rok (FILM *prvy); // zo zadania

void rok (FILM *prvy) {
    FILM *prechadzanie;
    HEREC *head_herec, *pole_hercov, *pole_hercov_vymena;
    int dlzka_pola=10, pocet_hercov=0, i, j;
    int hladaj_rok, najdeny=0;
    
    pole_hercov = (struct herec*)calloc(dlzka_pola, sizeof(struct herec));
    pole_hercov_vymena = (struct herec*)calloc(1, sizeof(struct herec));
    if (pole_hercov == NULL || pole_hercov_vymena == NULL) {
      free (pole_hercov);
      free (pole_hercov_vymena);
      printf ("CHYBA PRI ALOKACII\n");
      return;
    }
    
    if (skontroluj (prvy)){
        return;
    }
    
    printf ("ZADAJN ROK:\n  > ");
    assert ((scanf ("%d", &hladaj_rok)) > 0);
    
    prechadzanie = prvy;
    
    // kym nepridem na koniec
    while (prechadzanie != NULL) {
        // ak nie je NULL
        if (prechadzanie != NULL) {
            // spravny rok
            if (prechadzanie->rok == hladaj_rok) {
                najdeny = 1;
                head_herec = prechadzanie->herci;
                // pridanie hercov do zoznamu
                while (head_herec != NULL) {
                    
                    if (pocet_hercov == dlzka_pola) {
                        dlzka_pola += 10;
                        pole_hercov = (struct herec*)realloc(pole_hercov, dlzka_pola *sizeof(struct herec));
                        if (pole_hercov == NULL) {
                          free (pole_hercov);
                          free (pole_hercov_vymena);
                          printf ("CHYBA PRI REALOKACII\n");
                          return;
                        }
                    }
                    // pridanie do pola
                    pole_hercov[pocet_hercov].meno_herca = head_herec->meno_herca;
                    pole_hercov[pocet_hercov].narodeniny = head_herec->narodeniny;
                    pocet_hercov++;
                    
                    head_herec = head_herec->dalsi_herec;
                }
            }
        }
        
        prechadzanie = prechadzanie->dalsi_film;
    }
    
    // ODSTRANENIE DUPLIKATOV
    for (i=0; i < pocet_hercov; i++) {
        for (j = i+1; j < pocet_hercov; j++) {
            // ak zhoda
            if (strcmp (pole_hercov[i].meno_herca.krstne, pole_hercov[j].meno_herca.krstne) == 0 &&
            strcmp (pole_hercov[i].meno_herca.priezv, pole_hercov[j].meno_herca.priezv) == 0 &&
            pole_hercov[i].narodeniny == pole_hercov[j].narodeniny) {
                for (int posun = j; posun < pocet_hercov; posun++) {
                    pole_hercov[posun] = pole_hercov[posun+1];
                }
                pocet_hercov--;
                j--;
            }
        }
    }
    
    // ZORADENIE 
    for (i=0; i < pocet_hercov; i++) {
        for (j = i+1; j < pocet_hercov; j++) {
            // podla priezviska
            if ((strcmp (pole_hercov[i].meno_herca.priezv, pole_hercov[j].meno_herca.priezv) > 0)) {
                pole_hercov_vymena[0] = pole_hercov[i];
                pole_hercov[i] = pole_hercov[j];
                pole_hercov[j] = pole_hercov_vymena[0];
            }
            // podla mena
            else if ((strcmp (pole_hercov[i].meno_herca.priezv, pole_hercov[j].meno_herca.priezv) == 0)) {
                if ((strcmp (pole_hercov[i].meno_herca.krstne, pole_hercov[j].meno_herca.krstne) > 0)) {
                    pole_hercov_vymena[0] = pole_hercov[i];
                    pole_hercov[i] = pole_hercov[j];
                    pole_hercov[j] = pole_hercov_vymena[0];
                }    
            }
            // podla narodenin
            else if ((strcmp (pole_hercov[i].meno_herca.krstne, pole_hercov[j].meno_herca.krstne) == 0)) {
                if (pole_hercov[i].narodeniny > pole_hercov[j].narodeniny) {
                    pole_hercov_vymena[0] = pole_hercov[i];
                    pole_hercov[i] = pole_hercov[j];
                    pole_hercov[j] = pole_hercov_vymena[0];
                }    
            }
        }
    }
    
    // vypis pola
    for (i=0; i < pocet_hercov; i++) {
        printf ("%s %s (%d), ", pole_hercov[i].meno_herca.krstne, pole_hercov[i].meno_herca.priezv, pole_hercov[i].narodeniny);
    }
    
    free (pole_hercov);
    free (pole_hercov_vymena);
    
    if (najdeny == 0) {
        printf ("DANY ROK SA NENASIEL\n");
        return;
    }
    
    printf ("\n");
    
    return;
}

FILM* nacitaj (FILM *prvy) {
    FILE *subor;
    subor = fopen ("osemsmerovka.txt", "r");
    
    // pomocne pole pre nazov filmu
    char pom_nazov[100];
    // c kontroluje vyskyt hviezdicky, po nacitani posledneho herca spolu s c2 drzia nazov dalsieho filmu
    char c[100], c2[100], dalsi_znak_po_nacitani;
    // indexy
    int i, j;
    
    // ak je prazdny subor
    if (subor == NULL) {
        printf ("SUBOR NEBOL NACITANY\n");
        return 0;
    }
    
    // ak uz bolo nieco nacitane
    if (prvy != NULL) {
        uvolni (prvy);
    }    
    
    //printf ("NACITAM\n\n");
    
    // nacitanie prveho nazvy filmu
    fgets (pom_nazov, 100, subor);
    odstran_enter (pom_nazov);
    
    // postupne nacitanie filmov v cykli - head = prvy film, akt = aktualny
    FILM *head = (struct film*)malloc(sizeof(struct film));
    FILM *akt = (struct film*)malloc(sizeof(struct film));
    assert (head != NULL || akt != NULL);
    head = NULL;
    akt = NULL;
    
    // cyklus nacitania sa prerusi pri EOF 
    while (1) {
        
        // vytvorenie docasneho samostatneho filmu
        FILM *temp_film = (struct film*)malloc(sizeof(struct film));
        assert (temp_film != NULL);
        
        // priradenie nazvu filmu
        strcpy(temp_film->nazov, pom_nazov);
        //printf ("NAZOV: %s\n", temp_film->nazov);
        
        // nacitanie roku - ok
        fscanf (subor, "%d", &temp_film->rok);
        //printf ("ROK: %d\n", temp_film->rok);
        
        // nacitanie rezisera - ok
        fscanf (subor, "%s", temp_film->reziser.krstne);
        fscanf (subor, "%s", temp_film->reziser.priezv);
        //printf ("REZISER: %s %s\n", temp_film->reziser.krstne, temp_film->reziser.priezv);
        
        // hviezdicka - ok
        fscanf (subor, "%s", c);
        //printf ("C: %s\n", c);
        
        // nacitanie hercov
        HEREC *head_herec = (struct herec*)malloc(sizeof(struct herec));
        HEREC *akt_herec = (struct herec*)malloc(sizeof(struct herec));
        // ci sa alokovali
        assert (head_herec != NULL && akt_herec != NULL);
        // nech nikam neukazuju
        head_herec = NULL;
        akt_herec = NULL;
        
        // kym je tam hviezdicka
        while (c[0] == '*') {
            
            // vytvorenie docasneho samostatneho herca 
            HEREC *temp_herec = (struct herec*)malloc(sizeof(struct herec));
            assert (temp_herec != NULL);
            
            nacitaj_herca_subor (subor, temp_herec);
            
            // spojenie hercov do zoznamu
            if (head_herec == NULL) {
                head_herec = temp_herec;
                akt_herec = temp_herec;
                
                temp_film->herci = head_herec; // priradenie prveho herca do filmu
            }
            else {
                akt_herec->dalsi_herec = temp_herec;
                temp_herec->dalsi_herec = NULL;
                akt_herec = temp_herec;
            }
            
            // ak po poslednom hercovi je EOF 
            // (inak nacita zaciatok dalsieho nazvu alebo hviezdicku)
            if (fscanf (subor, "%s", c) < 1 ) {
                // pripojenie posledneho filmu
                if (head == NULL) {
                    head = temp_film;
                    akt = temp_film;
                }
                else {
                    temp_film->dalsi_film = NULL;
                    akt->dalsi_film = temp_film;
                    akt = temp_film;
                }
                printf ("NACITANIE USPESNE\n");
                fclose (subor);
                return prvy = head;
            }
            //printf ("-- C: %s \n", c);
        }
        
        // ak nebol EOF zistujem dalej aky mam znak 
        fscanf (subor, "%c", &dalsi_znak_po_nacitani);
        //printf("%c", d);
        
        // ak c obsahuje cely nazov dalsi nenacitany znak je new line
        // inak pokracuje nazov filmu
        if (dalsi_znak_po_nacitani != '\n') {
            // docitaj nazov
            fgets (c2, 100, subor);
            // vypocet dlzky c
            for (i = 1; c[i] != '\0'; i++) {}
            // zhltnuta medzera
            c[i] = ' ';
            i++;
            // zlucenie so zvyskom
            for (j = 0; c2[j] != '\0'; j++, i++) {
                c[i] = c2[j];
            }
            // ukoncenie c
            c[i] = '\0';
        }
        
        // prekopirovanie zvysku nazvu dalsieho filmu 
        // nech sa vo svojom cykli moze priradit
        memset (pom_nazov, '\0', sizeof(pom_nazov));
        strcpy (pom_nazov, c);
        odstran_enter (pom_nazov);
        //printf ("\n");
        
        temp_film->dalsi_film = NULL; // pokus dat to sem

        // spojenie filmov do zoznamu
        if (head == NULL) {
            head = temp_film;
            akt = temp_film;
        }
        else {
            //temp_film->dalsi_film = NULL;
            akt->dalsi_film = temp_film;
            akt = temp_film;
        }    
    }
}

void nacitaj_herca_subor (FILE* subor, HEREC *temp_herec) {
    // krstne, priezvisko - ok
    fscanf (subor, "%s", temp_herec->meno_herca.krstne);
    fscanf (subor, "%s", temp_herec->meno_herca.priezv);
    //printf("HEREC: %s ", temp_herec->meno_herca.krstne);
    //printf("%s ", temp_herec->meno_herca.priezv);
    // narodeniny - ok
    fscanf (subor, "%d", &temp_herec->narodeniny);
    //printf("%d\n", temp_herec->narodeniny);
}

int vypis_herci (HEREC *prvy) {
    
    if (prvy == NULL) {
        printf ("NEBOLI NACITANI HERCI\n");
        return 0;
    }
    else {
        printf ("%s %s (%d), ", prvy->meno_herca.krstne, prvy->meno_herca.priezv, prvy->narodeniny);
        
        if (prvy->dalsi_herec != NULL) {
          vypis_herci (prvy->dalsi_herec);
        }
    }
    return 0;
}

int vypis_filmy (FILM *prvy) {
    
    if (skontroluj (prvy)){
        return 0;
    }
    
    else {
        printf ("\n%s (%d) %s %s\n", prvy->nazov, prvy->rok, prvy->reziser.krstne, prvy->reziser.priezv);
        printf ("\tHRAJU: ");
        vypis_herci(prvy->herci);
        printf("\n");
        
        if (prvy->dalsi_film != NULL) {
          vypis_filmy (prvy->dalsi_film);
        }
    }
    return 0;
}

int skontroluj (FILM *prvy) {
    if (prvy == NULL) {
        printf ("NEBOLI NACITANE FILMY\n");
        return 1;
    }
    else
        return 0;
}

void odstran_enter (char *pole) {
    int i, dlzka = strlen(pole);
    
    for (i=0; i <= dlzka; i++) {
        //printf ("%c", pole[i]);
        if (pole[i] == '\n') {
          pole[i] = '\0';
        }
    }
    
}

FILM* pridaj (FILM *prvy) {
    char c[100];
    FILM *posledny, *prechadzanie;
    // urcuje, ci pridavame film alebo vytvarame novy prvy jediny
    int prazdny=0;
    
    if (skontroluj (prvy)){
      prazdny = 1;
    }
    
    // ak pridavame do nacitaneho zoznamu
    if (prazdny == 0) {
      // zistenie posledneho filmu v zozname
      prechadzanie = prvy;
      while (prechadzanie->dalsi_film != NULL) {
          prechadzanie = prechadzanie->dalsi_film;
      }
      posledny = prechadzanie;
    }
    
    // novy pridavany film
    FILM *novy = (struct film*)malloc(sizeof(struct film));
    assert (novy != NULL);
    
    printf ("ZADAJ NAZOV FILMU: \n  > ");
    fgets (novy->nazov, 100, stdin); // nazov filmu
    odstran_enter(novy->nazov);

    printf ("ZADAJ ROK VZNIKU FILMU: \n  > ");
    assert ((scanf ("%d", &novy->rok)) > 0); // rok
    printf ("ZADAJ MENO A PRIEZVISKO REZISERA: \n  > ");
    assert ((scanf ("%s", novy->reziser.krstne)) > 0); // meno rezisera
    assert ((scanf ("%s", novy->reziser.priezv)) > 0); // priezvisko
    
    // NACITANIE HERCOV
    HEREC *head_herec = (struct herec*)malloc(sizeof(struct herec));
    HEREC *akt_herec = (struct herec*)malloc(sizeof(struct herec));
    assert (head_herec != NULL || akt_herec != NULL);
    head_herec = NULL;
    akt_herec = NULL;
    
    // nacitanie krstneho mena herca
    printf ("ZADAJ MENO, PRIEZVISKO A ROK NARODENIA HERCA: \n  > ");
    assert ((scanf ("%s", c)) > 0);
    // kym to nieje hviezdicka
    while (c[0] != '*') {
        HEREC *temp_herec = (struct herec*)malloc(sizeof(struct herec));
        
        strcpy (temp_herec->meno_herca.krstne, c);
        scanf ("%s", temp_herec->meno_herca.priezv);
        scanf ("%d", &temp_herec->narodeniny);
        
        // spojenie hercov do zoznamu
        if (head_herec == NULL) {
            head_herec = temp_herec;
            akt_herec = temp_herec;
            
            novy->herci = head_herec; // priradenie prveho herca do filmu
        }
        else {
            akt_herec->dalsi_herec = temp_herec;
            temp_herec->dalsi_herec = NULL;
            akt_herec = temp_herec;
        }
        
        // posuvanie sa dalej   
        printf ("ZADAJ MENO, PRIEZVISKO A ROK NARODENIA DALSIEHO HERCA,\n");
        printf ("ALEBO PRE UKONCENIE NACITANIA ZADAJ *\n  > ");
        scanf ("%s", c);
    }
    
    novy->dalsi_film = NULL;

    if (prazdny == 0) {
      posledny->dalsi_film = novy; // ak sme pridali
    }
      
    else {
      prvy = novy; // ak sme vytvorili zoznam
    }
      
    return prvy;
}

FILM* vymaz (FILM *prvy) {
    FILM *temp = prvy, *prev;
    HEREC *tmp_herec, *head_herec;
    char vymaz_film[100];
    
    // ak je prvy NULL
    if (skontroluj (prvy)){
        return prvy;
    }
    
    // ak je co mazat
    printf ("KTORY FILM MAM VYMAZAT?\n  > ");
    fgets (vymaz_film, 100, stdin);
    odstran_enter (vymaz_film);
    
    // ak prvy node obsahuje (ne)zelanu hodnotu
    if (temp != NULL && strcmp(temp->nazov, vymaz_film) == 0) {
        // vymazanie hercov
        head_herec = prvy->herci;
        while (head_herec != NULL) {
            tmp_herec = head_herec;
            head_herec = head_herec->dalsi_herec;
            free (tmp_herec);
        }
        temp->herci = NULL;
        // vymazanie filmu
        prvy = temp->dalsi_film;
        free (temp);
        printf ("\"%s\" VYMAZANY\n", vymaz_film);
        return prvy;
    }
    // ak hodnota nebola najdena v prvom filme
    // hladanie nazvu filmu -- posuvanie; prev aby sme vedeli spojit predchadzajuci s dalsim po temp
    while (temp != NULL && strcmp (temp->nazov, vymaz_film) != 0) {
        prev = temp;
        temp = temp->dalsi_film;
    }
    // ak film nebol vobec najdeny
    if (temp == NULL) {
        printf ("DANY FILM NEBOL NAJDENY\n");
        return prvy;
    }
    // ak sa nedostal po NULL -- bol najdeny
    // vymazanie hercov
    head_herec = temp->herci;
    while (head_herec != NULL) {
        tmp_herec = head_herec;
        head_herec = head_herec->dalsi_herec;
        free (tmp_herec);
    }
    temp->herci = NULL;
    // ak to bol posledny film v zozname
    if (temp->dalsi_film == NULL) {
        prev->dalsi_film = NULL;
    }
    // ak nebol posledny
    else {
        prev->dalsi_film = temp->dalsi_film;
    }
    // uvolnenie pamate
    free (temp);
    printf ("\"%s\" VYMAZANY\n", vymaz_film);
    return prvy;
}

void filmy (FILM *prvy) {
    FILM *prechadzanie;
    HEREC *prechadzanie_hercov;
    char meno[100], priezvisko[100];
    int najdeny = 0;
    
    // ak je prvy NULL
    if (skontroluj (prvy)){
        return;
    }
    
    printf ("ZADAJ MENO A PRIEZVISKO HLADANEHO HERCA\n  > ");
    assert ((scanf ("%s %s", meno, priezvisko)) > 0);
    prechadzanie = prvy;
    
    // kym niesom na konci zoznamu
    while (prechadzanie != NULL) {
        
        prechadzanie_hercov = prechadzanie->herci;
        while (prechadzanie_hercov != NULL) {
            // ak v danom filme hra
            if (strcmp (prechadzanie_hercov->meno_herca.krstne, meno) == 0 && 
            strcmp (prechadzanie_hercov->meno_herca.priezv, priezvisko) == 0) {
                printf ("%s (%d)\n", prechadzanie->nazov, prechadzanie->rok);
                najdeny = 1;
            }
            prechadzanie_hercov = prechadzanie_hercov->dalsi_herec;
        }
        
        prechadzanie = prechadzanie->dalsi_film;
    }
    if (najdeny == 0) {
        printf ("DANY HEREC NEBOL NAJDENY\n");
    }
    return;
}

void herci (FILM *prvy) {
    FILM *prechadzanieA, *prechadzanieB;
    char filmA[100], filmB[100];
    HEREC *herecA, *herecB;
    int najdeny=0;
    
    if (skontroluj (prvy)){
        return;
    }
    
    // nacitanie
    printf ("ZADAJ NAZOV PRVEHO FILMU:\n  > ");
    fgets (filmA, 100, stdin);
    printf ("ZADAJ NAZOV DRUHEHO FILMU:\n  > ");
    fgets (filmB, 100, stdin);
    odstran_enter(filmA);
    odstran_enter(filmB);
    
    prechadzanieA = prvy;
    prechadzanieB = prvy;
    
    // kym nepridem na koniec
    while (prechadzanieA != NULL) {
        // ak najdem film
        if (strcmp(prechadzanieA->nazov, filmA) == 0) {
            break;
        }
        prechadzanieA = prechadzanieA->dalsi_film;
    }
    // ak film nebol najdeny
    if (prechadzanieA == NULL) {
        printf ("FILM \"%s\" NEBOL NAJDENY\n", filmA);
        return;
    }
    
    // kym nepridem na koniec
    while (prechadzanieB != NULL) {
        // ak najdem film
        if (strcmp(prechadzanieB->nazov, filmB) == 0) {
            break;
        }
        prechadzanieB = prechadzanieB->dalsi_film;
    }
    // ak film nebol najdeny
    if (prechadzanieB == NULL) {
        printf ("FILM \"%s\" NEBOL NAJDENY\n", filmB);
        return;
    }
    
    // priradenie hercov
    herecA = prechadzanieA->herci;
    while (herecA != NULL) {
        
        // priradenie hercov
        herecB = prechadzanieB->herci;
        while (herecB != NULL) {
            
            // najdeny 
            if (strcmp(herecA->meno_herca.krstne, herecB->meno_herca.krstne) == 0 &&
            strcmp(herecA->meno_herca.priezv, herecB->meno_herca.priezv) == 0
            && herecA->narodeniny == herecB->narodeniny) {
                najdeny = 1;
                printf ("%s %s (%d)\n", herecA->meno_herca.krstne, herecA->meno_herca.priezv, herecA->narodeniny);
            }
            
            // prechadzanie
            herecB = herecB->dalsi_herec;
        }
        
        // prechadzanie
        herecA = herecA->dalsi_herec;
    }
    if (najdeny == 0) {
        printf ("NEBOLA NAJDENA ZHODA\n");
    }
    return;
}

FILM* uvolni_filmy (FILM *prvy) {
    FILM *tmp;
    HEREC *head_herec;
    
    while (prvy != NULL) {
        tmp = prvy;
        prvy = prvy->dalsi_film;
        head_herec = tmp->herci;
        uvolni_hercov (head_herec);
        free (tmp);
    }
    prvy = NULL;
    return prvy;
}

void uvolni_hercov (HEREC *prvy) {
    HEREC *tmp;
    
    while (prvy != NULL) {
        tmp = prvy;
        prvy = prvy->dalsi_herec;
        free (tmp);
    }
    return;
}

FILM* uvolni (FILM* prvy) {

    if (skontroluj (prvy)){
        printf ("VSETKA PAMAT JE UZ VOLNA\n");
        return prvy;
    } 
    prvy = uvolni_filmy (prvy);  
    printf ("UVOLNENIE PAMATE HOTOVE\n");
    return prvy;
}

int main() {
    FILM *prvy = NULL;
    char funkcia[10];
    
    printf ("\nZADAJ POKYN - nacitaj, vypis, pridaj, vymaz, filmy, herci, rok, koniec:\n  > ");
    
    do {
        // lebo obcas po vykonani inej funkcie sa snazi nacitat cisto enter ako dalsiu funkciu
        if (strlen (funkcia) > 0)
            printf ("\nZADAJ POKYN - nacitaj, vypis, pridaj, vymaz, filmy, herci, rok, koniec:\n  > ");
            
        // nacitanie prikazu    
        fgets (funkcia, 100, stdin);
        odstran_enter(funkcia);
        
        if ((strcmp (funkcia, "nacitaj") == 0))
            prvy = nacitaj (prvy);
        else if ((strcmp (funkcia, "vypis") == 0))
            vypis_filmy (prvy);
        else if ((strcmp (funkcia, "pridaj") == 0))
            prvy = pridaj (prvy); 
        else if ((strcmp (funkcia, "vymaz") == 0)) 
            prvy = vymaz (prvy);
        else if ((strcmp (funkcia, "filmy") == 0)) 
            filmy (prvy);  
        else if ((strcmp (funkcia, "herci") == 0)) 
            herci (prvy);
        else if ((strcmp (funkcia, "rok") == 0)) 
            rok (prvy);
        else if ((strcmp (funkcia, "uvolni") == 0)) 
            prvy = uvolni (prvy); // testovacia funkcia
        else if ((strcmp (funkcia, "koniec") == 0)) {
            prvy = uvolni (prvy);
            printf ("DOVIDENIA\n"); 
        }
        else if (strlen (funkcia) > 0)
            printf ("\"%s\" NIE JE PLATNY VSTUP\n", funkcia); // f > 0 rovnako pre enter
        
    } while ((strcmp (funkcia, "koniec") != 0));
    
    
    return 0;
}