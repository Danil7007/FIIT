#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

// pre testy
char VYSLEDKY[2][200000];
char VSTUPY[40000][20];

int X=0, Z=0, Y=0, NEZHOD=0, POCETTESTOV=0, POVODNYCHUZLOV=0, ODSTRANENYCHUZLOV=0, T=0, F=0, POM_VYMAZ=0;

// funkcia
typedef struct binaryFunction {
    char vektor[200000]; // vektor
} BF;

// diagram
typedef struct binaryDecisionDiagram {
    int pocetPremennych; // pocet premennych (A B C D) diagramu
    int pocetUzlov; // pocet uzlov
    struct diagramNode* koren; // root, prvy uzol
    struct  diagramNode* listTrue; // po redukcii jediny list s hodnotou 1
    struct diagramNode* listFalse; //    ----- || -----       s hodnotou 0
} BDD;

// uzol
typedef struct diagramNode {
    BF funkcia;
    int mark; // udava, ci je to jeden z dvoch samostatnych listov (redukcia) (0 = uvolnit, 1 = neuvolnit)
    struct diagramNode* false; // lavy child
    struct  diagramNode* true; // pravy child
} node;

// hlavne funkcie
BDD *BDD_create(BF *bfunkcia); // vytvorenie binarneho diagramu
char BDD_use(BDD *bdd, char *vstupy); // vyuzitie binarneho diagramu
int BDD_reduce(BDD *bdd); // redukovanie uzlov

// pomocne funkcie
int getPocetPremennych (BF bfunkcia); // ziska pocet premennych diagramu
int jeSymetricky (char* vektor);
int jeZbytocny (char* vektor); // posudi ci sa ma uzol zredukovat
char* leftHalf (char* vektor); // ziska lavu polku vektora
int malyTest (); // test na ukazku
void najdiPrebytocne (node* uzol, BDD *bdd); // pomocna funkcia pre reduce, pouziva jeZbytocny
void najdiSymetricke (node* uzol, BDD *bdd);
void otestujVsetkyMoznosti (int n, char arr[], int i);
void printOut (node *uzol); // vypis korenov (listov)
char* rightHalf (char* vektor); // ziska pravu polku vektora
void rozdel(node *uzol, BDD *diagram); // vetvenie diagramu
node* trasa (node* uzol, char *vstupy, int index); // pomocna funkcia pre use
void spojKonce (node* uzol, BDD *bdd, node* true, node* false); // pomocna funkia pre reduce
void uvolni (node* node); // uvolnovanie uzlov
int velkyTest (); // velky test, pouziva otestujVsetkyMoznosti
BF *vytvorFunkciu (int premenne); // vytvara nahodnu funkciu
char* vytvorVstup (BDD *diagram); // vytvara nahodne vstupy


// free
void uvolni (node* node) {
    // ak neexistuje,
    // alebo ak je to jeden z dvoch uzlov do ktorych ustia vsetky vetvy po redukcii
    // vtedy sa musia uvolnit samostatne
    if (node == NULL || node->mark == 1) {
        return;
    }

    // ak neukazuju na ten isty uzol
    if (node->false != node->true) {
        uvolni (node->false);
        uvolni (node->true);
    } else {
        uvolni (node->true);
    }

    POM_VYMAZ++;
    free (node);
}

// vytvorenie diagramu
BDD *BDD_create (BF *bfunkcia) {
    // alokovanie rootu a diagramu
    node *root = (struct diagramNode*) malloc (sizeof (struct diagramNode));
    BDD *diagram = malloc (sizeof (struct binaryDecisionDiagram));

    root->funkcia = *bfunkcia; // vstupny vektor
    diagram->pocetPremennych = getPocetPremennych (root->funkcia); // pocet premennych
    diagram->pocetUzlov = 1; // pociatocny pocet uzlov (ak ratame aj root tak 1)
    diagram->koren = root; // koren
    diagram->koren->mark = 0;

    // rekurzivna funkcia na vetvenie
    rozdel (root, diagram);

    return diagram;
}

// use
char BDD_use (BDD *bdd, char *vstupy) {
    char vysledok = '\0';
    node* temp = NULL;

    // ak doslo k nejakej chybe
    if (bdd == NULL) {
        return 'x';
    }

    // rekurzivna funkcia co prejde diagram
    // temp je list na ktorom skonci po prejdeni diagramu
    temp = trasa (bdd->koren, vstupy, 0);

    // zistenie hodnoty listu
    if (strcmp (temp->funkcia.vektor, "0") == 0) {
        vysledok = '0';
    } else {
        vysledok = '1';
    }

    return vysledok;
}

// pomocna rekurzivna funkcia pre pouzitie stromu
node* trasa (node* uzol, char *vstupy, int index) {
    if (uzol != NULL) {
        char lr = vstupy[index]; // lr = left / right

        // 0 -> left (false), 1 -> right (true)
        if (lr == '0' && uzol->false != NULL) {
            uzol = trasa (uzol->false, vstupy, index+1);
        } else if (lr == '1' && uzol->true != NULL) {
            uzol = trasa (uzol->true, vstupy, index+1);
        }
        // po redukcii mozu byt uzol->false alebo uzol->true = NULL
        // diagram uz nemusi mat tolko urovni co vstup
    }

    return uzol;
}

// rekurzivna funkcia na rozvetvenie
void rozdel(node *uzol, BDD *diagram) {
    char* vektor = uzol->funkcia.vektor;

    // ak sa da rozdelit
    if (strlen(vektor) % 2 == 0) {

        // vytvorenie dalsich uzlov
        node *leftChild = (node *) malloc (sizeof (node));
        node *rightChild = (node *) malloc (sizeof (node));
        while (leftChild == NULL) { // pre istotu, keby doslo k chybe
            leftChild = (node *) malloc (sizeof (node));
        }
        while (rightChild == NULL) {
            rightChild = (node *) malloc (sizeof (node));
        }

        // su to bezne uzly, pri uvolnovani sa maju uvolnit
        leftChild->mark = 0;
        rightChild->mark = 0;

        // pre istotu
        leftChild->true = leftChild->false = NULL;
        rightChild->false = rightChild->true = NULL;

        diagram->pocetUzlov += 2; // tu sa pocita pocet uzlov stromu

        // rozdelenie vektora
        char* tempL = leftHalf (vektor);
        char* tempR = rightHalf (vektor);

        // priradenie vektorov uzlom
        strcpy (leftChild->funkcia.vektor, tempL);
        strcpy (rightChild->funkcia.vektor, tempR);

        // uvolnenie pomocnych poli
        free (tempL);
        free (tempR);

        // priradenie uzlov k rodicovi
        uzol->false = leftChild;
        uzol->true = rightChild;

        // dalsie delenie
        rozdel (leftChild, diagram);
        rozdel (rightChild, diagram);
    }
}

// ziska lavu polku vektora
char* leftHalf (char* vektor) {
    // dlzka vektora
    int velkost = (strlen (vektor) / 2);

    // pre novy vektor (jeho polku) - uvolnuje sa vo funkcii rozdel
    char* temp = (char*) calloc (velkost + 1, sizeof (char));

    // prekopirovanie
    for (int i = 0; i < velkost; i++) {
        temp[i] = vektor[i];
    }

    return temp;
}

// ziska pravu polku vekora
char* rightHalf (char* vektor) {
    // dlzka vektora
    int velkost = (strlen(vektor) / 2);

    // pre novy vektor (jeho polku) - uvolnuje sa vo funkcii rozdel
    char* temp = (char*) calloc (velkost + 1, sizeof (char));

    // prekopirovanie od polky povodneho vektora
    int j = 0;
    for (int i = velkost; i < (strlen (vektor)); i++) {
        temp[j] = vektor[i];
        j++;
    }

    return temp;
}

// zisti pocet premennych vektora
int getPocetPremennych (BF bfunkcia) {
    // logaritmus so zakladom dva z poctu outputov
    int pocetOutputov = strlen (bfunkcia.vektor);
    float vysledok = log(pocetOutputov) / log(2);

    return (int)vysledok;
}

// vypis
void printOut (node* uzol) {
    char* vektor = uzol->funkcia.vektor;

    // ak sa da rozdelit
    if (strlen(vektor) % 2 == 0 || strlen(vektor) == 1) {

        // vypis - len korene
        //if (strlen (vektor) == 1) {
            printf ("%s ", uzol->funkcia.vektor);
        //}

        // priradenie
        node *leftChild = uzol->false;
        node *rightChild = uzol->true;

        // dalej (kontrola taka keby nieco)
        if (strlen(vektor) / 2 != 0) {
            printOut (leftChild);
            printOut (rightChild);
        }
    }
}

// velkost stromu zavisi od vytvorenej funkcie
BF *vytvorFunkciu (int premenne) {
    BF *funkcia = (struct binaryFunction*) malloc (sizeof (struct binaryFunction));

    // dlzka funkcie musi byt mocnina 2 nech to vychadza rozvetvit
    int dlzka;
    dlzka = pow (2, premenne);
    char *vektor = (char*) calloc (dlzka, sizeof (char));

    int j=0;
    for (int i = 0; i < dlzka; i++) {
        int randInt = (rand() % (200 - 2 + 1)) + 2;
        // nahodne vygenerovanie 0 / 1 do vektora
        if (randInt % 5 == 0) {
            *(vektor+j) = '0';
        } else { vektor[j] = '1'; }
        j++;
    }

    strcpy (funkcia->vektor, vektor);

    return funkcia;
}

// vytvorenie nahodneho inputu pre funkciu
char* vytvorVstup (BDD *diagram) {
    char* vstup = (char*) calloc (20, sizeof (char)); // viac ako 20 premennych je celkom dost uz

    for (int i = 0; i < diagram->pocetPremennych; i++) {
        int randInt = (rand() % (200 - 2 + 1)) + 2;
        // nahodne vygenerovanie 0 / 1
        if (randInt % 5 == 0) {
            *(vstup+i) = '0';
        } else { vstup[i] = '1'; }
    }
    // vstup pre presny pocet premennych funkcie
    return vstup;
}

int BDD_reduce (BDD *bdd) {
    // ak nebol vytvoreny
    if (bdd == NULL) {
        return -1;
    }
    // ziskanie korena
    node* root = bdd->koren;
    int pocetUzlov = bdd->pocetUzlov;
    int vymazanych; // pocet zredukovanych uzlov


    // pomocna rekurzivna funkcia
    najdiPrebytocne (root, bdd);

    //vymazanych = pocetUzlov - bdd->pocetUzlov;
    //printf ("1: po prebytocnych: %d\n", vymazanych);

    // alokovanie specialnych koncovych uzlov
    bdd->listFalse = (node *) calloc(1, sizeof(node));
    bdd->listTrue = (node *) calloc(1, sizeof(node));
    // nastavenie ich hodnoty
    strcpy(bdd->listFalse->funkcia.vektor, "0");
    strcpy(bdd->listTrue->funkcia.vektor, "1");
    // pri uvolnovani sa nemaju uvolnit
    bdd->listFalse->mark = 1;
    bdd->listTrue->mark = 1;
    // pre istotu
    bdd->listFalse->false = bdd->listFalse->true = NULL;
    bdd->listTrue->false = bdd->listTrue->true = NULL;

    // fukncia vsetky listy zredukuje na dva
    spojKonce (root, bdd, bdd->listTrue, bdd->listFalse);
    // ak sa listTrue pouzije tak T = 1 (rovnako listFalse)
    // aby sa do poctu uzlov diagramu nezaratali ak sa nepouziju
    bdd->pocetUzlov += (T + F);
    T = F = 0;

    //vymazanych = pocetUzlov - bdd->pocetUzlov;
    //printf ("2: po spojeni: %d\n", vymazanych);

    // vymazanie symetrickych uzlov

    najdiSymetricke (root, bdd);
    //vymazanych = pocetUzlov - bdd->pocetUzlov;
    //printf ("3: po symetrii: %d\n", vymazanych);


    // pocet uzlov pred reduce - pocet uzlov po reduce
    vymazanych = pocetUzlov - bdd->pocetUzlov;

    return vymazanych;
}

// zisti ci je vektor same 0 alebo same 1
int jeZbytocny (char* vektor) {
    int dlzka = strlen (vektor);

    // list nie je zbytocny
    // tie sa redukuju az vo funkcii spojKonce
    if (dlzka == 1) {
        return 0; // -> nevymazat uzol
    }

    char porovnaj = vektor[0];
    // zistenie ci su vsetky chary pola rovnake ako ten prvy
    for (int i = 0; i < dlzka; i++) {
        if (vektor[i] != porovnaj) {
            return 0; // nie su to same zhodne chary -> nevymazat uzol
        }
    }

    return 1; // -> vymazat uzol
}

// zisti ci je vektor napr 00110011
int jeSymetricky (char* vektor) {
    int dlzka = strlen (vektor);
    int polovica = dlzka / 2;

    // list nie je zbytocny
    // tie sa redukuju az vo funkcii spojKonce
    if (dlzka == 1) {
        return 0; // -> nevymazat uzol
    }

    // zistenie ci je symetricky
    int j = polovica;
    for (int i = 0; i < polovica; i++) {
        if (vektor[i] != vektor[j]) {
            return 0; // polky nie su zhodne -> nevymazat uzol
        }
        j++;
    }

    return 1; // -> vymazat uzol
}

// rekurzivne prejdenie uzlov, spojenie rovnakych listov
void spojKonce (node* uzol, BDD *bdd, node* true, node* false) {
    // ziskanie vektora
    char* vektor = uzol->funkcia.vektor;

    // ak sa da rozdelit
    if (strlen(vektor) % 2 == 0) {

        // priradenie
        node *leftChild = uzol->false;
        node *rightChild = uzol->true;
        char* vektorLeft = uzol->false->funkcia.vektor;
        char* vektorRight = uzol->true->funkcia.vektor;

        // ak je v lavo list
        if (strlen(vektorLeft) == 1) {
            // ak ma hodnotu 0
            if (vektorLeft[0] == '0') {
                free(uzol->false); // odstranenie uzlu
                leftChild = NULL;
                bdd->pocetUzlov--; // odpocitanie uzlov stromu
                uzol->false = false; // pripojenie k specialnemu uzlu
                F = 1; // specialny uzol sa pouzil -> zarata sa do diagramu (1x)
            } else { // ak ma hodnotu 1
                free(uzol->false); // odstranenie uzlu
                leftChild = NULL;
                bdd->pocetUzlov--; // odpocitanie uzlov stromu
                uzol->false = true; // pripojenie k specialnemu uzlu
                T = 1; // specialny uzol sa pouzil -> zarata sa do diagramu (1x)
            }
        }

        // ak je v pravo list ( vpodstate to iste ale do druhej strany)
        if (strlen(vektorRight) == 1) {
            // ak ma hodnotu 0
            if (vektorRight[0] == '0') {
                free(uzol->true); // odstranenie uzlu
                rightChild = NULL;
                bdd->pocetUzlov--;
                uzol->true = false;
                F = 1;
            } else { // ak ma hodnotu 1
                free(uzol->true); // odstranenie uzlu
                rightChild = NULL;
                bdd->pocetUzlov--;
                uzol->true = true;
                T = 1;
            }
        }

        // dalej
        if (leftChild != NULL && strlen(vektor) / 2 != 0) {
            spojKonce(leftChild, bdd, true, false);
        }
        if (rightChild != NULL && strlen(vektor) / 2 != 0) {
            spojKonce(rightChild, bdd, true, false);
        }
    }
}

// rekurzivne prejdenie uzlov, hladanie prebytocnych
void najdiPrebytocne (node* uzol, BDD *bdd) {
    // ziskanie vektora
    char* vektor = uzol->funkcia.vektor;

    // ak sa da rozdelit
    if (strlen(vektor) % 2 == 0) {


        // je zbytocny? (sklada sa len z 0 / 1 ?)
        if (jeZbytocny (uzol->funkcia.vektor) == 1) {

            int dlzkaVektora = strlen (uzol->funkcia.vektor);
            int vymazat = 0;

            while (dlzkaVektora > 1) { // vypocet poctu uzlov co z neho pochadzaju
                vymazat += dlzkaVektora;
                dlzkaVektora /= 2;
                //                    A                        (dlzka 1 -> koniec )
                //        B                         B          (dlzka 2 -> vymazat 14 -> dlzka 1)
                //    C       C                 C       C      (dlzka 4 -> vymazat 12 -> dlzka 2)
                //  D   D   D   D             D   D   D   D    (dlzka 8 -> vymazat  8 -> dlzka 4)
            }

            // zmena hodnoty v diagrame
            bdd->pocetUzlov -= vymazat;

            if (uzol->funkcia.vektor[0] == '0') { // zmena vektora uzla 00000000 -> 0
                memset (uzol->funkcia.vektor, 0, sizeof (uzol->funkcia.vektor));
                uzol->funkcia.vektor[0] = '0';
            }
            else { // zmena vektora uzla 11111111 -> 1
                memset (uzol->funkcia.vektor, 0, sizeof (uzol->funkcia.vektor));
                uzol->funkcia.vektor[0] = '1';
            }

            // uvolnenie a odpojenie dalsich uzlov
            uvolni (uzol->false);
            uvolni (uzol->true);
            uzol->false = NULL;
            uzol->true = NULL;
        }

        else { // ak nie je zbytocny pokracuj v prechadzani vetvy

            // priradenie
            node *leftChild = uzol->false;
            node *rightChild = uzol->true;

            // dalej
            if (strlen(vektor) / 2 != 0) {
                najdiPrebytocne (leftChild, bdd);
                najdiPrebytocne (rightChild, bdd);
            }
        }
    }
}

void najdiSymetricke (node* uzol, BDD *bdd) {
    // ziskanie vektora
    char* vektor = uzol->funkcia.vektor;

    // ak sa da rozdelit
    if (strlen(vektor) % 2 == 0) {

        // je symetricky? (00110011 ?)
        if (jeSymetricky (uzol->funkcia.vektor) == 1 && uzol->mark == 0) {

            POM_VYMAZ = 0;

            // oba ukazovatele ukazuju na jeden chld
            uvolni (uzol->false);
            uzol->false = uzol->true;

            // zmena hodnoty v diagrame
            bdd->pocetUzlov -= POM_VYMAZ;
            }

        else { // ak nie je symetricky pokracuj v prechadzani vetvy

            // priradenie
            node *leftChild = uzol->false;
            node *rightChild = uzol->true;

            // dalej
            if (strlen(vektor) / 2 != 0) {
                najdiPrebytocne (leftChild, bdd);
                najdiPrebytocne (rightChild, bdd);
            }
        }
    }
}

int malyTest() {

    printf ("\n------------------ MALE TESTOVANIE ------------------------------------------------------\n");

    BF *funkcia = (struct binaryFunction*) malloc (sizeof (struct binaryFunction));
    strcpy(funkcia->vektor, "1000110010001100");
    BDD *diagram = BDD_create(funkcia);
    printf("Pocet outputov funkcie: %d\n", (int)strlen(funkcia->vektor));
    printf("Pocet premennych pre diagram: %d\n", diagram->pocetPremennych);

    //printf("\nKorene: ");
    //printOut(diagram->koren);

    printf("\nPocet uzlov diagramu: %d\n", diagram->pocetUzlov);

    char vstup[20];
    strcpy (vstup, "000");
    printf("Vstup: %s\n", vstup);

    // use
    char vysledok = BDD_use(diagram, vstup);
    printf("Vysledna boolean hodnota je: %c\n", vysledok);

    // --------------------------------------------------------- reduced
    BDD_reduce(diagram);

    printf("\nPO REDUKCII:");
    //printf("\nKorene: ");
    //printOut(diagram->koren);
    printf("\nPocet uzlov diagramu: %d\n", diagram->pocetUzlov);

    printf("Vstup: %s\n", vstup);

    // use
    vysledok = BDD_use(diagram, vstup);
    printf("Vysledna boolean hodnota je: %c\n", vysledok);


    uvolni(diagram->koren);

    free(diagram->listFalse);
    free(diagram->listTrue);
    free(diagram);

    return 0;
}

void otestujVsetkyMoznosti(int n, char arr[], int i) {

    if (i == n) {
        strcpy(VSTUPY[X],arr);
        X++;
        return;
    }

    arr[i] = '0';
    otestujVsetkyMoznosti(n, arr, i + 1);

    arr[i] = '1';
    otestujVsetkyMoznosti(n, arr, i + 1);
}

int velkyTest() {
    FILE *f = NULL; // ZAPIS VYSLEDKOV TESTU DO SUBORU
    int subor = 0;

    int pocetHlavnychTestov = 2000; // kolkokrat prebehne test (kolko funkcii otestuje)

    int pocetPremennych = 14; // pocet premennych A B C D
    char *poleVstupov = (char*) calloc (pocetPremennych+1, sizeof(char));

    // ----------------------------------------------------------------------------- sranda xD
    char vstup;
    nacitanie:
    printf("Kolko testov chcete vykonat? (zo zadania 2000+) \n");
    scanf("%d", &pocetHlavnychTestov);
    if (pocetHlavnychTestov > 10){
        if (pocetHlavnychTestov > 2000) { printf("To sa už musíte inak nudiť xD"); }
        printf("Ste si isty ze mate tolko casu? (y/n)\n ");
        getchar();
        scanf("%c",&vstup);
        if (vstup == 'y' || vstup == 'Y') {
            printf("Na vasom mieste by som to este prehodnotila\n\tISTO? (y/n)\n ");
            getchar();
            scanf("%c",&vstup);
            if (vstup == 'y' || vstup == 'Y') {
                printf("Tak si aspon vezmite popcorn\n");
            } else { goto nacitanie; }
        } else { goto nacitanie; }
    } // ---------------------------------------------------------------------------------- end of sranda

    // UKLADANIE DO SUBORU ANO / NIE
    printf("Prajete si vystup ulozit aj do \"output.txt\" suboru? (y/n)\n");
    getchar();
    scanf("%c", &vstup);
    if (vstup == 'y' || vstup == 'Y'){
        f = fopen("output.txt","w");
    } else {
        f = NULL;
    }

    // ZACIATOK TESTOV

    printf ("------------------ VELKE TESTOVANIE ------------------------------------------------------\n");

    for (int j = 0; j < pocetHlavnychTestov; j++) {

        printf ("\n --------------------- TEST %d/%d ---------------------\n", j+1,pocetHlavnychTestov);

        // do suboru
        if (f != NULL) { fprintf (f,"\n --------------------- TEST %d/%d ---------------------\n", j+1,pocetHlavnychTestov); }

        // root funkcia
        BF *funkcia = vytvorFunkciu(pocetPremennych); // velkost stromu zavisi od vytvorenej funkcie

        //printf("Vektor: %s\n", funkcia->vektor);

        // diagram
        BDD *diagram = BDD_create(funkcia);

        // vypisy
        //printf("Pocet outputov funkcie: %d\n", strlen(funkcia->vektor));
        //printf("Pocet premennych pre diagram: %d\n", diagram->pocetPremennych);
        //printf("Korene: ");
        //printOut(diagram->koren);
        //printf("Pocet uzlov diagramu: %d\n", diagram->pocetUzlov);
        //printf("\n");

        // do suboru
        if (f != NULL) {
            fprintf(f,"Pocet premennych pre diagram: %d\n", diagram->pocetPremennych);
            fprintf(f,"Pocet uzlov diagramu: %d\n", diagram->pocetUzlov);
            fprintf(f,"\n");
        }

        Y = 0; // pre pole vysledkov
        Z = 0;

        for (int i = 0; i < X; i++) {


            VYSLEDKY[Y][Z] = BDD_use(diagram, VSTUPY[i]);

            /*/ vypis

            printf("Vstup: %s, ", VSTUPY[i]);
            printf("Vystup: %c\n", VYSLEDKY[Y][Z]);
            */

            if (f != NULL){
                fprintf(f,"Vstup: %s, ", VSTUPY[i]);
                fprintf(f,"Vystup: %c\n", VYSLEDKY[Y][Z]);
            }

            Z++;
            POCETTESTOV++;
        }


        POVODNYCHUZLOV += diagram->pocetUzlov;


        // REDUKOVANIE -------------------------------------------------------------
        int odstranenych = BDD_reduce(diagram);
        ODSTRANENYCHUZLOV += odstranenych;

        // vypisy
        //printf("\nPO REDUKCII:\nPocet zredukovanych uzlov %d\n", odstranenych);
        //printf("Pocet outputov funkcie: %d\n", strlen(funkcia->vektor));
        //printf("Pocet premennych pre diagram: %d\n", diagram->pocetPremennych);
        //printf("Korene: ");
        //printOut(diagram->koren);
        //printf("Pocet uzlov diagramu: %d\n", diagram->pocetUzlov);
        //printf("\n");

        // do suboru
        if (f != NULL){
            fprintf(f,"\nPO REDUKCII:\nPocet zredukovanych uzlov %d\n", odstranenych);
            //printf("Pocet outputov funkcie: %d\n", strlen(funkcia->vektor));
            fprintf(f,"Pocet premennych pre diagram: %d\n", diagram->pocetPremennych);
            //printf("Korene: ");
            //printOut(diagram->koren);
            fprintf(f,"Pocet uzlov diagramu: %d\n", diagram->pocetUzlov);
            fprintf(f,"\n");
        }

        Y = 1; // pre pole vysledkov
        Z = 0;

        for (int i = 0; i < X; i++) {


            VYSLEDKY[Y][Z] = BDD_use(diagram, VSTUPY[i]);

            /*/ vypis

            printf("Vstup: %s, ", VSTUPY[i]);
            printf("Vystup redukovany: %c\n", VYSLEDKY[Y][Z]);
            */

            if (f != NULL){
                fprintf(f,"Vstup: %s, ", VSTUPY[i]);
                fprintf(f,"Vystup redukovany: %c\n", VYSLEDKY[Y][Z]);
            }

            Z++;
            POCETTESTOV++;
        }

        // KONTROLA VYSLEDKOV
        for (int i = 0; i < Z; i++) {
            if (VYSLEDKY[0][i] != VYSLEDKY[1][i]) {
                NEZHOD++;
            }
        }

        // vypis
        //printf("\nPOCET NEZHODNYCH VYSLEDKOV TESTOV: %d\n", NEZHOD);
        if (f != NULL) { fprintf(f,"\nPOCET NEZHODNYCH VYSLEDKOV TESTOV: %d\n", NEZHOD);}

        // uvolnovanie pamate
        uvolni (diagram->koren);
        free (diagram->listTrue);
        free (diagram->listFalse);
        free (diagram);
    }
    free (poleVstupov);

    // KONIEC TESTOV ------------------------------------------------------------------------------

    // vypis
    float uspesnost = (((float)ODSTRANENYCHUZLOV) / ((float)POVODNYCHUZLOV))*100;
    printf("\nPERCENTUALNA MIERA ZREDUKOVANIA BDD: %.2lf %%\n", uspesnost);
    printf("POCET NEZHODNYCH TESTOV %d\n", NEZHOD);
    printf("Pocet premennych testovanych funkcii: %d\n", pocetPremennych);
    printf("Pocet povodnych uzlov: %d, pocet odstranenych uzlov: %d\n", POVODNYCHUZLOV, ODSTRANENYCHUZLOV);
    printf("Pocet testov: %d\n\n", POCETTESTOV);

    // do suboru
    if (f != NULL) {
        fprintf(f,"\nPERCENTUALNA MIERA ZREDUKOVANIA BDD: %.2lf %%\n", uspesnost);
        fprintf(f, "POCET NEZHODNYCH TESTOV %d\n", NEZHOD);
        fprintf(f, "Pocet premennych testovanych funkcii: %d\n", pocetPremennych);
        fprintf(f,"Pocet povodnych uzlov: %d, pocet odstranenych uzlov: %d\n", POVODNYCHUZLOV, ODSTRANENYCHUZLOV);
        fprintf(f,"Pocet testov: %d\n", POCETTESTOV);
    }
    if (f != NULL) { fclose(f);}

    ODSTRANENYCHUZLOV = POVODNYCHUZLOV = POCETTESTOV = 0;

    return 0;
}

int main () {

    X = 0;
    int pocetPremennych = 14; // pocet premennych A B C D
    char *poleVstupov = (char*) calloc (pocetPremennych+1, sizeof(char));

    clock_t c = clock();

    otestujVsetkyMoznosti(14, poleVstupov, 0);

    //malyTest();

    velkyTest();

    clock_t ce = clock();

    printf ("Cas vykonania %f", (double)(ce - c)/CLOCKS_PER_SEC);

    //system("pause");
    return 0;
}