#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// pre testy
char VYSLEDKY[2][200000];
int Z=0, Y=0, NEZHOD=0, POCETTESTOV=0, POVODNYCHUZLOV=0, ODSTRANENYCHUZLOV=0, T=0, F=0;

// funkcia
typedef struct binaryFunction {
    char vektor[200000];
} BF;

typedef struct binaryDecisionDiagram {
    int pocetPremennych;
    int pocetUzlov;
    struct diagramNode* koren;
} BDD;

// uzol
typedef struct diagramNode {
    BF funkcia;
    struct diagramNode* false;
    struct  diagramNode* true;
} node;

BDD *BDD_create(BF *bfunkcia); // vytvorenie binarneho diagramu
char BDD_use(BDD *bdd, char *vstupy); // vyuzitie binarneho diagramu
int BDD_reduce(BDD *bdd); // redukovanie uzlov

int getPocetPremennych(BF bfunkcia); // pomocne funkcie
void rozdel(node *uzol, BDD *diagram);
char* leftHalf(char* vektor);
char* rightHalf(char* vektor);
void printOut(node *uzol);
node* trasa (node* uzol, char *vstupy, int index);
void najdiPrebytocne(node* uzol, BDD *bdd);
void spojKonce (node* uzol, BDD *bdd, node* true, node* false);
BF *vytvorFunkciu (int premenne);
void uvolni (node* node);
int malyTest();
int velkyTest();

// free
void uvolni (node* node) {
    if (node == NULL) {
        return;
    }
    uvolni(node->false);
    uvolni(node->true);

    free (node);
}

// vytvorenie diagramu
BDD *BDD_create(BF *bfunkcia) {
    // alokovanie rootu a diagramu
    node *root = (struct diagramNode*)malloc(sizeof(struct diagramNode));
    BDD *diagram = malloc(sizeof(struct binaryDecisionDiagram));

    root->funkcia = *bfunkcia; // vstupny vektor
    diagram->pocetPremennych = getPocetPremennych(root->funkcia); // pocet premennych
    // todo: co vsetko sa rata ako uzol? aj tie posledne co maju hodnotu 0/1?
    // momentalne sa nerata root, a rataju sa aj listy
    diagram->pocetUzlov = 1; // pociatocny pocet uzlov (ak ratame aj root tak 1)
    diagram->koren = root; // koren


    rozdel(root, diagram);

    return diagram;
}

// use
char BDD_use(BDD *bdd, char *vstupy) {
    char vysledok = '\0';
    node* temp = NULL;

    // ak doslo k nejakej chybe
    if (bdd == NULL) {
        return 'x';
    }

    temp = trasa(bdd->koren, vstupy, 0);

    //printf("%s", temp->funkcia.vektor);

    if (strcmp(temp->funkcia.vektor, "0") == 0) {
        vysledok = '0';
    }
    else {
        vysledok = '1';
    }

    return vysledok;
}

// pomocna rekurzivna funkcia pre pouzitie stromu
node* trasa (node* uzol, char *vstupy, int index) {
    if (uzol != NULL) {
        char lr = vstupy[index];
        //printf("%c", lr);

        if (lr == '0' && uzol->false != NULL) {
            uzol = trasa (uzol->false, vstupy, index+1);
        }
        else if (lr == '1' && uzol->true != NULL) {
            uzol = trasa (uzol->true, vstupy, index+1);
        }
    }

    return uzol;
}

// rekurzivna funkcia na rozvetvenie
void rozdel(node *uzol, BDD *diagram) {
    char* vektor = uzol->funkcia.vektor;

    // ak sa da rozdelit
    if (strlen(vektor) % 2 == 0)
    {

        // vytvorenie uzlov
        node *leftChild = (node *) malloc(sizeof(node));
        node *rightChild = (node *) malloc(sizeof(node));
        while(leftChild==NULL){
            leftChild = (node *) malloc(sizeof(node));
        }
        while (rightChild==NULL){
            rightChild = (node *) malloc(sizeof(node));
        }

        leftChild->true=leftChild->false=NULL;
        rightChild->false=rightChild->true=NULL;

        diagram->pocetUzlov += 2; // tu sa pocita pocet uzlov stromu

        // rozdelenie vektora
        char* tempL = leftHalf(vektor);
        char* tempR = rightHalf(vektor);

        // priradenie vektorov uzlom
        strcpy(leftChild->funkcia.vektor, tempL);
        strcpy(rightChild->funkcia.vektor, tempR);
        //printf("%s\n", leftChild->funkcia.vektor);
        //printf("%s\n", rightChild->funkcia.vektor);

        /*
        // pocet premennych vo funkcii
        leftChild->funkcia.pocetPremennych = getPocetPremennych(leftChild->funkcia);
        rightChild->funkcia.pocetPremennych = getPocetPremennych((rightChild->funkcia));
        */

        // priradenie uzlov k rodicovi
        uzol->false = leftChild;
        uzol->true = rightChild;

        // dalsie delenie
        rozdel(leftChild, diagram);
        rozdel(rightChild, diagram);
    }
}

// ziska lavu polku vektora
char* leftHalf(char* vektor) {
    int velkost = (strlen(vektor) / 2);
    //printf("velkost: %d\n", velkost);

    char* temp = (char*)calloc(velkost+1, sizeof(char));

    for (int i = 0; i < velkost; i++) {
        temp[i] = vektor[i];
    }

    //printf("Left: %s\n", temp);

    return temp;
}

// ziska pravu polku vekora
char* rightHalf(char* vektor) {
    int velkost = (strlen(vektor) / 2);
    //printf("velkost: %d\n", velkost);

    char* temp = (char*)calloc(velkost+1, sizeof(char));

    int j = 0;
    for (int i = velkost; i < (strlen(vektor)); i++) {
        temp[j] = vektor[i];
        j++;
    }

    //printf("Right: %s\n", temp);

    return temp;
}

// zisti pocet premennych vektora
int getPocetPremennych(BF bfunkcia) {
    // logaritmus so zakladom dva z poctu outputov
    int pocetOutputov = strlen(bfunkcia.vektor);
    float vysledok = log(pocetOutputov) / log(2);

    //printf("Pocet outputov: %d\n", pocetOutputov);
    //printf("Log: %.0lf\n", vysledok);

    return (int)vysledok;
}

// vypis
void printOut(node* uzol) {
    char* vektor = uzol->funkcia.vektor;

    // ak sa da rozdelit
    if (strlen(vektor) % 2 == 0 || strlen(vektor) == 1) {

        // vypis
        if (strlen(vektor) == 1) {
            printf("%s ", uzol->funkcia.vektor);
        }

        // priradenie
        node *leftChild = uzol->false;
        node *rightChild = uzol->true;

        // dalej
        if (strlen(vektor) / 2 != 0) {
            printOut(leftChild);
            printOut(rightChild);
        }
    }
}

// velkost stromu zavisi od vytvorenej funkcie
BF *vytvorFunkciu (int premenne) {
    BF *funkcia = (struct binaryFunction*) malloc (sizeof (struct binaryFunction));

    int dlzka = 2;
    dlzka = pow(2,premenne);
    char *vektor = (char*)calloc(dlzka, sizeof (char));

    int j=0;
    for (int i = 0; i < dlzka; i++) {
        int randInt = (rand() % (200 - 2 + 1)) + 2;
        // nahodne vygenerovanie 0 / 1 do vektora
        if (randInt % 5 == 0) {
            *(vektor+j) = '0';
        }
        else {
            vektor[j] = '1';
        }

        j++;
    }

    strcpy(funkcia->vektor, vektor);

    return funkcia;
}

// vytvorenie nahodneho inputu pre funkciu
char* vytvorVstup (BDD *diagram) {
    char* vstup = (char*)calloc(20, sizeof (char)); // viac ako 20 premennych je celkom dost uz

    for (int i = 0; i < diagram->pocetPremennych; i++) {
        int randInt = (rand() % (200 - 2 + 1)) + 2;
        // nahodne vygenerovanie 0 / 1
        if (randInt % 5 == 0) {
            *(vstup+i) = '0';
        }
        else {
            vstup[i] = '1';
        }
    }
    // vstup pre presny pocet premennych funkcie
    return vstup;
}

int BDD_reduce(BDD *bdd) {

    if (bdd == NULL) {
        return -1;
    }

    node* root = bdd->koren;
    int pocetUzlov = bdd->pocetUzlov;
    int vymazanych;

    najdiPrebytocne(root, bdd);

    // vytvorenie uzlov
    node *false = (node *) calloc(1, sizeof(node));
    node *true = (node *) calloc(1, sizeof(node));
    strcpy(false->funkcia.vektor, "0");
    strcpy(true->funkcia.vektor, "1");
    false->false = false->true = NULL;
    true->false = true->true = NULL;


    printf ("%d\n", bdd->pocetUzlov);

    spojKonce(root, bdd, true, false);
    bdd->pocetUzlov += (T + F);
    T = F = 0;

    printf ("%d\n", bdd->pocetUzlov);

    vymazanych = pocetUzlov - bdd->pocetUzlov;
    //printf ("pocet odstranenych uzlov: %d\n" , vymazanych);

    return vymazanych;
}

// zisti ci je vektor same 0 alebo same 1
int jeZbytocny (char* vektor) {
    int dlzka = strlen(vektor);

    // list nie je zbytocny
    if (dlzka == 1) {
        return 0;
    }

    char porovnaj = vektor[0];

    for (int i = 0; i < dlzka; i++) {
        if (vektor[i] != porovnaj) {
            return 0;
        }
    }

    return 1;
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
                bdd->pocetUzlov--;
                uzol->false = false;
                F = 1;
            } else { // ak ma hodnotu 1
                free(uzol->false); // odstranenie uzlu
                leftChild = NULL;
                bdd->pocetUzlov--;
                uzol->false = true;
                T = 1;
            }
        }

        // ak je v pravo list
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
void najdiPrebytocne(node* uzol, BDD *bdd) {
    // ziskanie vektora
    char* vektor = uzol->funkcia.vektor;

    // ak sa da rozdelit
    if (strlen(vektor) % 2 == 0) {

        // je zbytocny? (sklada sa len z 0 / 1 ?)
        if (jeZbytocny(uzol->funkcia.vektor) == 1) {

            int dlzkaVektora = strlen(uzol->funkcia.vektor);
            int vymazat = 0;

            while (dlzkaVektora > 0) { // vypocet poctu uzlov co z neho pochadzaju
                vymazat += dlzkaVektora;
                dlzkaVektora -= 2;
            }

            // zmena hodnoty v diagrame
            bdd->pocetUzlov -= vymazat;

            if (uzol->funkcia.vektor[0] == '0') { // zmena vektora uzla na 0
                memset(uzol->funkcia.vektor, 0, sizeof (uzol->funkcia.vektor));
                uzol->funkcia.vektor[0] = '0';
            }
            else { // zmena vektora uzla na 1
                memset(uzol->funkcia.vektor, 0, sizeof (uzol->funkcia.vektor));
                uzol->funkcia.vektor[0] = '1';
            }

            // odpojenie dalsich uzlov
            uvolni(uzol->false);
            uvolni(uzol->true);
            uzol->false = NULL;
            uzol->true = NULL;
        }

        else { // pokracuj v prechadzani vetvy

            // priradenie
            node *leftChild = uzol->false;
            node *rightChild = uzol->true;

            // dalej
            if (strlen(vektor) / 2 != 0) {
                najdiPrebytocne(leftChild, bdd);
                najdiPrebytocne(rightChild, bdd);
            }
        }
    }
}

int malyTest() {

    printf ("\n------------------ MALE TESTOVANIE ------------------------------------------------------\n");

    BF *funkcia = (struct binaryFunction*) malloc (sizeof (struct binaryFunction));
    strcpy(funkcia->vektor, "11000000");
    BDD *diagram = BDD_create(funkcia);
    printf("Pocet outputov funkcie: %d\n", (int)strlen(funkcia->vektor));
    printf("Pocet premennych pre diagram: %d\n\n", diagram->pocetPremennych);

    printf("Korene: ");
    printOut(diagram->koren);
    printf("\nPocet uzlov diagramu: %d\n", diagram->pocetUzlov);

    char vstup[20];
    strcpy (vstup, "000");
    printf("Vstup: %s\n", vstup);

    // use
    char vysledok = BDD_use(diagram, vstup);
    printf("Vysledna boolean hodnota je: %c\n", vysledok);

    // --------------------------------------------------------- reduced
    BDD_reduce(diagram);

    printf("\nPO REDUKCII:\nKorene: ");
    printOut(diagram->koren);
    printf("\nPocet uzlov diagramu: %d\n", diagram->pocetUzlov);

    printf("Vstup: %s\n", vstup);

    // use
    vysledok = BDD_use(diagram, vstup);
    printf("Vysledna boolean hodnota je: %c\n", vysledok);

    return 0;
}

void otestujVsetkyMoznosti(int n, char arr[], int i, BDD* diagram, int redukovany, FILE *f) {

    if (i == n) {

        VYSLEDKY[Y][Z] = BDD_use(diagram, arr);

        /*/ vypis

        printf("Vstup: %s, ", arr);

        redukovany > 0 ?
        printf("Vystup redukovany: %c\n", VYSLEDKY[Y][Z]) :
        printf("Vystup: %c\n", VYSLEDKY[Y][Z]);
        */

        if(f != NULL){
            fprintf(f,"Vstup: %s, ", arr);
            redukovany > 0 ?
            fprintf(f,"Vystup redukovany: %c\n", VYSLEDKY[Y][Z]):
            fprintf(f,"Vystup: %c\n", VYSLEDKY[Y][Z]);
        }

        Z++;
        POCETTESTOV++;
        return;
    }

    arr[i] = '0';
    otestujVsetkyMoznosti(n, arr, i + 1, diagram, redukovany,f);

    arr[i] = '1';
    otestujVsetkyMoznosti(n, arr, i + 1, diagram, redukovany,f);
}

int velkyTest() {
    FILE *f = NULL;
    int subor = 0;
    char vstup;
    int pocetHlavnychTestov = 2000;
    nacitanie:
    printf("Kolko testov chcete vykonat? (zo zadania 2000+) \n");
    scanf("%d", &pocetHlavnychTestov);
    if (pocetHlavnychTestov > 10){
        if(pocetHlavnychTestov>2000){
            printf("To sa už musíte inak nudiť!");
        }
        printf("Ste si isty ze mate tolko casu? (y/n) ");
        getchar();
        scanf("%c",&vstup);
        if(vstup == 'y' || vstup == 'Y'){
            printf("Na vasom mieste by som to este prehodnotila\n\tISTO? (y/n) ");
            getchar();
            scanf("%c",&vstup);
            if(vstup == 'y' || vstup == 'Y'){
                printf("Tak si aspon vezmite popcorn\n");
            }
            else{
                goto nacitanie;
            }
        }
        else{
            goto nacitanie;
        }
    }
    printf("Prajete si vystup ulozit aj do \"output.txt\" suboru?(y/n)\n");
    getchar();
    scanf("%c", &vstup);
    if(vstup == 'y' || vstup == 'Y'){
        f = fopen("output.txt","w");
    }
    else{
        f = NULL;
    }
    int pocetPremennych = 14; // pocet premennych A B C D
    char *poleVstupov = (char*)calloc(pocetPremennych,sizeof(char));

    printf ("------------------ VELKE TESTOVANIE ------------------------------------------------------\n");

    for (int j = 0; j < pocetHlavnychTestov; j++) {

        printf ("\n --------------------- TEST %d/%d ---------------------\n", j+1,pocetHlavnychTestov);
        if(f != NULL){
            fprintf (f,"\n --------------------- TEST %d/%d ---------------------\n", j+1,pocetHlavnychTestov);
        }
        // root funkcia
        BF *funkcia = vytvorFunkciu(pocetPremennych); // velkost stromu zavisi od vytvorenej funkcie

        //printf("Vektor: %s\n", funkcia->vektor);

        // diagram
        BDD *diagram = BDD_create(funkcia);
        //printf("Pocet outputov funkcie: %d\n", strlen(funkcia->vektor));
        printf("Pocet premennych pre diagram: %d\n", diagram->pocetPremennych);
        //printf("Korene: ");
        //printOut(diagram->koren);
        printf("Pocet uzlov diagramu: %d\n", diagram->pocetUzlov);
        printf("\n");

        if(f != NULL){
            fprintf(f,"Pocet premennych pre diagram: %d\n", diagram->pocetPremennych);
            fprintf(f,"Pocet uzlov diagramu: %d\n", diagram->pocetUzlov);
            fprintf(f,"\n");
        }

        Y = 0;
        Z = 0;
        otestujVsetkyMoznosti(pocetPremennych, poleVstupov, 0, diagram, 0,f);
        POVODNYCHUZLOV += diagram->pocetUzlov;


        // REDUKOVANIE -------------------------------------------------------------
        int odstranenych = BDD_reduce(diagram);
        ODSTRANENYCHUZLOV += odstranenych;
        printf("\nPO REDUKCII:\nPocet zredukovanych uzlov %d\n", odstranenych);

        //printf("Pocet outputov funkcie: %d\n", strlen(funkcia->vektor));
        printf("Pocet premennych pre diagram: %d\n", diagram->pocetPremennych);
        //printf("Korene: ");
        //printOut(diagram->koren);
        printf("Pocet uzlov diagramu: %d\n", diagram->pocetUzlov);
        printf("\n");
        if(f != NULL){
            fprintf(f,"\nPO REDUKCII:\nPocet zredukovanych uzlov %d\n", odstranenych);

            //printf("Pocet outputov funkcie: %d\n", strlen(funkcia->vektor));
            fprintf(f,"Pocet premennych pre diagram: %d\n", diagram->pocetPremennych);
            //printf("Korene: ");
            //printOut(diagram->koren);
            fprintf(f,"Pocet uzlov diagramu: %d\n", diagram->pocetUzlov);
            fprintf(f,"\n");
        }

        Y = 1;
        Z = 0;
        otestujVsetkyMoznosti(pocetPremennych, poleVstupov, 0, diagram, 1,f);


        // KONTROLA VYSLEDKOV
        for (int i = 0; i < Z; i++) {
            if (VYSLEDKY[0][i] != VYSLEDKY[1][i]) {
                NEZHOD++;
            }
        }
        printf("\nPOCET NEZHODNYCH VYSLEDKOV TESTOV: %d\n", NEZHOD);
        if(f != NULL){
            fprintf(f,"\nPOCET NEZHODNYCH VYSLEDKOV TESTOV: %d\n", NEZHOD);
        }
        // uvolnovanie pamate
        //uvolni(diagram->koren);
        free(diagram);
    }
    free(poleVstupov);

    float uspesnost = (((float)ODSTRANENYCHUZLOV) / ((float)POVODNYCHUZLOV))*100;
    printf("\nPERCENTUALNA MIERA ZREDUKOVANIA BDD: %.2lf %%\n", uspesnost);
    printf("Pocet povodnych uzlov: %d, pocet odstranenych uzlov: %d\n", POVODNYCHUZLOV, ODSTRANENYCHUZLOV);
    printf("Pocet testov: %d\n", POCETTESTOV);
    if(f != NULL){
        fprintf(f,"\nPERCENTUALNA MIERA ZREDUKOVANIA BDD: %.2lf %%\n", uspesnost);
        fprintf(f,"Pocet povodnych uzlov: %d, pocet odstranenych uzlov: %d\n", POVODNYCHUZLOV, ODSTRANENYCHUZLOV);
        fprintf(f,"Pocet testov: %d\n", POCETTESTOV);
    }
    ODSTRANENYCHUZLOV = POVODNYCHUZLOV = POCETTESTOV = 0;
    if(f != NULL){
        fclose(f);
    }
    return 0;
}

int main () {

    //malyTest();

    velkyTest();

    //system("pause");
    return 0;
}