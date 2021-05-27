#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define log2(x) (log(x) / log(2))

// funkcia
typedef struct binaryFunction {
    char vektor[16384];
    //int pocetPremennych;
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
void traverse(node* uzol, BDD *bdd);
void uvolni (node* node);
int malyTest();
int velkyTest();

// free
void uvolni (node* node) {
    if (node == NULL) {
        return;
    }
    uvolni (node->false);
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
    diagram->pocetUzlov = 0; // pociatocny pocet uzlov (ak ratame aj root tak 1)
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
BF *vytvorFunkciu () {
    BF *funkcia = (struct binaryFunction*) malloc (sizeof (struct binaryFunction));
    //int mocnina = (rand() % (13 - 1 + 1)) + 1; // viac ako 13 je celkom vela uz
    int mocnina = 12;
    int dlzka = 2;
    char *vektor = (char*)calloc(16384, sizeof (char)); // 2 na 15 myslim

    for (int i=0; i < mocnina; i++) {
        dlzka *= 2; // vytvori mocninu 2ky
        // funkcia musi mat dlzku mocniny 2 aby vychadzal pocet korenov (listov)
    }

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

    traverse(root, bdd);

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

// rekurzivne prejdenie uzlov, hladanie prebytocnych
void traverse(node* uzol, BDD *bdd) {
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
                traverse(leftChild, bdd);
                traverse(rightChild, bdd);
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

void generateAllBinaryStrings(int n, char arr[], int i) {

    if (i == n) {
        return;
    }

    arr[i] = '0';
    generateAllBinaryStrings(n, arr, i + 1);

    arr[i] = '1';
    generateAllBinaryStrings(n, arr, i + 1);
}

int velkyTest() {

    int pocetHlavnychTestov = 2000;
    int pocetPodtestov = 100;
    int i = 13;
    char *pole = NULL;
    pole = (char*)calloc(i,sizeof (char));
    generateAllBinaryStrings(i, pole, 0);

    char vstupy[pocetPodtestov][20];  // vstupy testov
    char vysledky[2][pocetPodtestov]; // vysledky pre dane vstupy

    printf ("------------------ VELKE TESTOVANIE ------------------------------------------------------\n");

    for (int j = 0; j < pocetHlavnychTestov; j++) {

        printf ("\n --------------------- TEST %d ---------------------\n", j+1);

        // root funkcia
        BF *funkcia = vytvorFunkciu(); // velkost stromu zavisi od vytvorenej funkcie

        //printf("Vektor: %s\n", funkcia->vektor);

        // diagram
        BDD *diagram = BDD_create(funkcia);
        //printf("Pocet outputov funkcie: %d\n", strlen(funkcia->vektor));
        printf("Pocet premennych pre diagram: %d\n", diagram->pocetPremennych);
        //printf("Korene: ");
        //printOut(diagram->koren);
        printf("Pocet uzlov diagramu: %d\n", diagram->pocetUzlov);
        printf("\n");

        // test vstupov v neredukovanom diagrame
        for (int i = 0; i < pocetPodtestov; i++) {
            printf("----- test %d ------\n", i+1);

            // vstupy
            char vstup[20];
            strcpy (vstup, vytvorVstup(diagram)); // vytvorenie vstupu
            strcpy (vstupy[i], vstup); // pridanie do pola vstupov

            printf("Vstup: %s\n", vstup);

            // use
            char vysledok = BDD_use(diagram, vstup);
            printf("Vysledna boolean hodnota je: %c\n", vysledok);
            vysledky[0][i] = vysledok;
        }

        // REDUKOVANIE -------------------------------------------------------------
        printf("\nPO REDUKCII:\nPocet zredukovanych uzlov %d\n", BDD_reduce(diagram));

        //printf("Pocet outputov funkcie: %d\n", strlen(funkcia->vektor));
        printf("Pocet premennych pre diagram: %d\n", diagram->pocetPremennych);
        //printf("Korene: ");
        //printOut(diagram->koren);
        printf("Pocet uzlov diagramu: %d\n", diagram->pocetUzlov);
        printf("\n");

        // test vstupov v redukovanom diagrame
        for (int i = 0; i < pocetPodtestov; i++) {
            printf("----- test %d ------\n", i+1);

            // vstupy - rovnake ako v predchadzajucom teste
            char vstup[20];
            strcpy (vstup, vstupy[i]); // vybranie vstupu z pola pouzitych vstupov

            printf("Vstup: %s\n", vstupy[i]);

            // use
            char vysledok = BDD_use(diagram, vstup);
            printf("Vysledna boolean hodnota je: %c\n", vysledok);
            vysledky[1][i] = vysledok;
        }

        // KONTROLA VYSLEDKOV
        int pocetNezhod = 0;
        for (int i = 0; i < pocetPodtestov; i++) {
            if (vysledky[0][i] != vysledky[1][i]) {
                pocetNezhod++;
            }
        }
        printf("\nPOCET NEZHODNYCH VYSLEDKOV TESTOV: %d\n", pocetNezhod);

        // uvolnovanie pamate
        uvolni(diagram->koren);
        free(diagram);
    }

    return 0;
}

int main () {

    // TODO:
    // použijete postupne všetky ????? možné kombinácie vstupných premenných.
    // Počet premenných v rámci testovania BDD by mal byť minimálne 13.
    // Počet Booleovských funkcií / BDD diagramov by mal byť minimálne 2000.
    // V rámci testovania tiež vyhodnocujte percentuálnu mieru zredukovania BDD
    // (t.j. počet odstránených uzlov / pôvodný počet uzlov).

    //malyTest();
    velkyTest();

    //TODO: megaVelkyTest()



    return 0;
}""