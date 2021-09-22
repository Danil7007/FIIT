// Zadanie 2 - Vyhladavanie v dynamickych mnozinah -- Emma Macháčová, 22.3.2021 17:25
// (1 bod) Prevzatú (nie vlastnú!) implementáciu BVS s iným algoritmom na vyvažovanie ako
// v predchádzajúcom bode. Zdroj musí byť uvedený.

// kod prevzaty z Programiz
// https://www.programiz.com/dsa/red-black-tree
// search funkcia z https://www.codesdope.com/blog/article/binary-search-tree-in-c/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// VLASTNA IMPLEMENTACIA ----------------------------------------------------------------------------------

// pomocne funkcionality
#define compare(a, b) ((a > b) ? a : b)
#define dlzkaPodstromu(node) ((node == NULL) ? 0 : node->dlzkaPodstromu)
#define rozdielHlbok(node) ((node == NULL) ? 0 : (dlzkaPodstromu(node->left) - dlzkaPodstromu(node->right)))
#define maxDlzka(node) (compare(dlzkaPodstromu(node->left), dlzkaPodstromu(node->right)) + 1)
#define velkostPola(pole) (sizeof (pole) / sizeof (char *))

// pre funkciu vypis
#define TRUE 1
#define FALSE 0

// struktura zvierata
typedef struct node {
    int pocetNoh; // hlavny key
    int pocetOci;
    char nazovZvierata[20];

    struct node *left;
    struct node *right;

    int dlzkaPodstromu;
} ZVIERA;


void printOut(struct node *node, int order); // vypis obsahu stromu, order TRUE/FALSE -> vzostupne/zostupne
void testCompare(int velkostTestu); // testovania funkcia
struct node *search(struct node *node, int pocetNoh); // vyhladavanie podla postu noh
struct node *insert(struct node *node, int pocetNoh, int pocetOci, char *nazovZvierata); // vkladanie
struct node *avl(struct node *node, int pocetNoh, int pocetOci, char *nazovZvierata); // AVL funkcionalita
struct node *rotateRight(struct node *middle); // funkcie otacania pre AVL
struct node *rightLeft(struct node *node);
struct node *rotateLeft(struct node *middle);
struct node *leftRight(struct node *node);

// globalne premenne pre vyhodnocovanie testov
int POCET_VLOZENI, POCET_DUPLIKATOV, OTOCENIE_DOPRAVA, OTOCENIE_DOLAVA;
int NAJDENYCH, NENAJDENYCH;

// pre vyhodnotenie
double CELKOVY_CAS_AVL_INSERT, CELKOVY_CAS_RB_INSERT;
double CELKOVY_CAS_AVL_SEARCH, CELKOVY_CAS_RB_SEARCH;
int CELKOVY_POCET_VLOZENYCH_AVL, CELKOVY_POCET_VLOZENYCH_RB;
int CELKOVY_POCET_NAJDENYCH_AVL, CELKOVY_POCET_NAJDENYCH_RB;

// otocenie doprava
struct node *rotateRight(struct node *middle) {

    if (middle->left != NULL) { // potrebna podmienka

        struct node *top;
        struct node *bottom;

        // otocenie

        top = middle->left;
        bottom = top->right;

        middle->left = bottom;
        top->right = middle;

        // aktualizacia dlzok
        middle->dlzkaPodstromu = maxDlzka(middle);
        top->dlzkaPodstromu = maxDlzka(top);

        OTOCENIE_DOPRAVA++; // pre test

        return top;
    }

    return middle; // ak nedojde k otoceniu
}

// otocenie dolava
struct node *rotateLeft(struct node *middle) {

    if (middle->right != NULL) { // potrebna podmienka
        struct node *top;
        struct node *bottom;

        // otocenie

        top = middle->right;
        bottom = top->left;

        top->left = middle;
        middle->right = bottom;

        // aktualizacia dlzok
        middle->dlzkaPodstromu = maxDlzka(middle);
        top->dlzkaPodstromu = maxDlzka(top);

        OTOCENIE_DOLAVA++; // pre test

        return top;
    }

    return middle; // ak nedojde k otoceniu
}

// kombinacia otoceni doprava-dolava
struct node *rightLeft(struct node *node) {
    if (node->right != NULL) {
        node->right = rotateRight(node->right);
        node = rotateLeft(node);
        return node;
    }
    return node; // ak nepride k otoceniu
}

// kombinacia otoceni dolava-doprava
struct node *leftRight(struct node *node) {
    if (node->left != NULL) {
        node->left = rotateLeft(node->left);
        node = rotateRight(node);
        return node;
    }
    return node; // ak nepride k otoceniu
}


// vyhladavanie podla poctu noh
struct node *search(struct node *node, int pocetNoh) {

    if (node == NULL) { // nenajdene
        //printf("Nebol vytvoreny strom alebo zviera nebolo najdene\n\n");
        NENAJDENYCH++; // pre test
        return node;
    } else if (node->pocetNoh == pocetNoh) { // najdene
        //printf("Najdene zviera s poctom noh %d - je to %s\n", pocetNoh, node->nazovZvierata);
        NAJDENYCH++; // pre test
        return node;
    } else if (node->pocetNoh > pocetNoh) { // pokracovanie hladania v lavo
        return search(node->left, pocetNoh);
    } else { // (root->pocetNoh < pocetNoh) // pokracovanie hladania v pravo
        return search(node->right, pocetNoh);
    }
}

// insert
struct node *insert(struct node *node, int pocetNoh, int pocetOci, char *nazovZvierata) {

    // volne miesto pre uzol
    if (node == NULL) {
        // alokovanie noveho uzlu
        struct node *newNode = (struct node *) malloc(sizeof(struct node));
        newNode->pocetNoh = pocetNoh; // vlozenie udajov
        newNode->pocetOci = pocetOci;
        strcpy(newNode->nazovZvierata, nazovZvierata);

        // nastavenie
        newNode->left = NULL;
        newNode->right = NULL;

        newNode->dlzkaPodstromu = 1;

        //printf ("-> %s\n", newNode->nazovZvierata);

        POCET_VLOZENI++; // pre test
        //return (newNode);
        node = newNode;
    }


        // ak je duplikat:
        /*if ((node->pocetNoh == pocetNoh) && (node->pocetOci == pocetOci) && (strcmp(node->nazovZvierata, nazovZvierata) == 0)) {
            POCET_DUPLIKATOV++;
        }*/
    else if (node->pocetNoh == pocetNoh) {
        POCET_DUPLIKATOV++;
    }

        // inak hladanie miesta pre uzol podla kriterii:

        // PODLA NOH -------------------------------------------------
    else if (node->pocetNoh > pocetNoh) {
        node->left = insert(node->left, pocetNoh, pocetOci, nazovZvierata);
    } else { // if (node->pocetNoh < pocetNoh) // mensie aj rovne
        node->right = insert(node->right, pocetNoh, pocetOci, nazovZvierata);
    }

    /* // teoreticke mozne verzie

    // ZORADENIE PODLA OCI -------------------------------------------------
    else if (node->pocetOci > pocetOci) {
        node->left = insert(node->left, pocetNoh, pocetOci, nazovZvierata);
    } else { // if (node->pocetOci < pocetOci) // mensie aj rovne
        node->right = insert(node->right, pocetNoh, pocetOci, nazovZvierata);
    }

    // ZORADENIE PODLA NAZVU -----------------------------------------------
    else if (strcmp(node->nazovZvierata, nazovZvierata) > 0) {
        node->left = insert(node->left, pocetNoh, pocetOci, nazovZvierata);
    } else { // if (strcmp(node->nazovZvierata, nazovZvierata) < 0) // mensie aj rovne
        node->right = insert(node->right, pocetNoh, pocetOci, nazovZvierata);

    }

    */

    // preusporiadanie uzlov (vyvazovanie)
    node = avl(node, pocetNoh, pocetOci, nazovZvierata);

    return node;
}

// vyvazovanie
struct node *avl(struct node *node, int pocetNoh, int pocetOci, char *nazovZvierata) {
    int rozdiel; // pre zistenie scenara vyvazovania

    // zistenie najvacsej dlzky podstromu daneho uzlu
    node->dlzkaPodstromu = compare(dlzkaPodstromu(node->left), dlzkaPodstromu(node->right));
    node->dlzkaPodstromu++; // lebo je o uroven vyssie

    rozdiel = rozdielHlbok(node);

    // vyvazovanie z lava --------------------------------------------
    if (rozdiel > 1) {
        // podla noh
        if (pocetNoh < node->left->pocetNoh) {
            return rotateRight(node);
        } else if (pocetNoh > node->left->pocetNoh) {
            return leftRight(node);
        }
    }
        // vyvazovanie z prava -------------------------------------------
    else if (rozdiel < -1) {
        // podla noh
        if (pocetNoh > node->right->pocetNoh) {
            return rotateLeft(node);
        } else if (pocetNoh < node->right->pocetNoh) {
            return rightLeft(node);
        }
    }


    return node;
}


// vypis
void printOut(struct node *node, int order) {

    if (node != NULL) {

        if (order) { // zostupne
            printOut(node->left, TRUE);
            printf("\tzviera: %s, pocet noh: %d, pocet oci: %d, dlzka (pod)stromu: %d\n", node->nazovZvierata,
                   node->pocetNoh, node->pocetOci, node->dlzkaPodstromu);
            printOut(node->right, TRUE);
        } else {
            // vzostupne
            printOut(node->right, FALSE);
            printf("\tzviera: %s, pocet noh: %d, pocet oci: %d, dlzka (pod)stromu: %d\n", node->nazovZvierata,
                   node->pocetNoh, node->pocetOci, node->dlzkaPodstromu);
            printOut(node->left, FALSE);
        }
    }
}

// PREVZATA IMPLEMENTACIA ---------------------------------------------------------------------------------
// kod prevzaty z Programiz
// https://www.programiz.com/dsa/red-black-tree
// search funkcia z https://www.codesdope.com/blog/article/binary-search-tree-in-c/

// pre rozlisovanie medzi druhmi uzlov
enum nodeColor {
    RED,
    BLACK
};

// uzol
struct rbNode {
    int data, data2, color;
    char string[20];
    struct rbNode *link[2];
};

// vytvorenie noveho uzlu
struct rbNode *createNode(int data, int data2, char *string) {
    struct rbNode *newnode;
    newnode = (struct rbNode *) malloc(sizeof(struct rbNode)); // alokovanie noveho uzla

    newnode->data = data; // vlozenie dat
    newnode->data2 = data2;
    strcpy(newnode->string, string);

    newnode->color = RED; // na zaciatku je kazdy uzol "cerveny"
    newnode->link[0] = newnode->link[1] = NULL; // ukazovatele na potomkov

    POCET_VLOZENI++;
    return newnode;
}

// vlozenie do stromu
struct rbNode *insertion(struct rbNode *root, int data, int data2, char *string) {
    // y je list
    struct rbNode *stack[98], *ptr, *newnode, *xPtr, *yPtr;
    int dir[98], ht = 0, index;
    ptr = root;
    if (!root) { // ak neexistuje root -> vytvor
        root = createNode(data, data2, string);
        return root;
    }

    stack[ht] = root;
    dir[ht++] = 0;
    // kontrola ci je strom prazdny
    // ak hej, vlozi sa novy uzol a prefarbi sa na cierno
    while (ptr != NULL) {
        //if (ptr->data == data && ptr->data2 == data2 && strcmp(ptr->string, string) == 0) { // ak narazi na duplikat
        if (ptr->data == data) {
            //printf("Duplicates Not Allowed!!\n");
            POCET_DUPLIKATOV++;
            return root;
        }
        index = (data - ptr->data) > 0 ? 1 : 0;
        stack[ht] = ptr;
        ptr = ptr->link[index];
        dir[ht++] = index;
    }
    stack[ht - 1]->link[index] = newnode = createNode(data, data2, string);

    // algoritmus na udrziavanie vlastnosti red black stromu
    // ak vlozenie noveho  uzla porusi farebnostne pravidla
    while ((ht >= 3) && (stack[ht - 1]->color == RED)) { // kym rodic noveho uzlu je cerveny
        // case A.
        // ak je uzol lavym potomkom stareho rodica Z-tka
        if (dir[ht - 2] == 0) {
            yPtr = stack[ht - 2]->link[1];
            // ak farba praveho dietata stareho rodica je cervena
            if (yPtr != NULL && yPtr->color == RED) {
                // stary rodic sa nastavi na cervenu
                stack[ht - 2]->color = RED;
                // obe jeho deti budu cierne
                stack[ht - 1]->color = yPtr->color = BLACK;
                ht = ht - 2;
            }
                // inak prirad stareho rodica novemu uzlu
            else {
                // ak je novy uzol pravym dietatom p, prirad ich
                if (dir[ht - 1] == 0) {
                    yPtr = stack[ht - 1];
                }
                    // nastavenie farby uzlu na ciernu
                    // stary rodic -> cerveny
                    // rotacia doprava
                else {
                    xPtr = stack[ht - 1];
                    yPtr = xPtr->link[1];
                    xPtr->link[1] = yPtr->link[0];
                    yPtr->link[0] = xPtr;
                    stack[ht - 2]->link[0] = yPtr;
                }
                xPtr = stack[ht - 2];
                xPtr->color = RED;
                yPtr->color = BLACK;
                xPtr->link[0] = yPtr->link[1];
                yPtr->link[1] = xPtr;
                if (xPtr == root) {
                    root = yPtr;
                } else {
                    stack[ht - 3]->link[dir[ht - 3]] = yPtr;
                }
                break;
            }
        }
            // case B.
        else {
            yPtr = stack[ht - 2]->link[0];
            // ak je lave dieta stareho rodica cervene,
            // nastavi sa farba oboch deti stareho rodica na ciernu a on sam na cervenu
            if ((yPtr != NULL) && (yPtr->color == RED)) {
                stack[ht - 2]->color = RED;
                stack[ht - 1]->color = yPtr->color = BLACK;
                ht = ht - 2;
            } else {
                // inak ak je novy uzol lavym dietatom p, tak prirad
                // otocenie doprava noveho uzla
                if (dir[ht - 1] == 1) {
                    yPtr = stack[ht - 1];
                } else {
                    xPtr = stack[ht - 1];
                    yPtr = xPtr->link[0];
                    xPtr->link[0] = yPtr->link[1];
                    yPtr->link[1] = xPtr;
                    stack[ht - 2]->link[1] = yPtr;
                }
                xPtr = stack[ht - 2];
                yPtr->color = BLACK;
                xPtr->color = RED;
                xPtr->link[1] = yPtr->link[0];
                yPtr->link[0] = xPtr;
                if (xPtr == root) {
                    root = yPtr;
                } else {
                    stack[ht - 3]->link[dir[ht - 3]] = yPtr;
                }
                break;
            }
        }
    }
    root->color = BLACK; // nastavenie korena na ciernu
    return root;
}

// vypis
void inorderTraversal(struct rbNode *node) {
    if (node) {
        inorderTraversal(node->link[0]);
        printf("%d %d  %s\n", node->data, node->data2, node->string);
        inorderTraversal(node->link[1]);
    }
    return;
}

// search - https://www.codesdope.com/blog/article/binary-search-tree-in-c/
void searchRedBlack(struct rbNode *node, int key) {

    if (node == NULL) {
        NENAJDENYCH++;
        return;
    }
    else {

        if (node->data == key) {
            NAJDENYCH++;
        } else if (key > node->data) {
            searchRedBlack(node->link[1], key); // 0 alebo 1?
        } else if (key < node->data) {
            searchRedBlack(node->link[0], key);
        }
    }

    return;
}


// TEST ----------------------------------------------------------------------------------------------------

// testovacia funkcia (pocet operacii vkladania/vyhladavania)
void testCompare(int velkostTestu) {

    struct node *node = NULL; // AVL strom
    struct rbNode *rbNode = NULL; // Red-Black strom

    clock_t begin;
    clock_t end;
    double time_spent;
    double efektivita;

    char *poleZvierat[] = {
            "pes", "macka", "kacka", "chobotnica", "lama", "jasterica",
            "stonozka", "kohut", "had", "hadica", "uhor", "slon", "nosorozec",
            "ryba", "tulen", "korytnacka", "mravec", "mroz", "riasa", "jelen",
            "srnka", "vlk", "gorila", "lev", "tiger", "koza", "hyena", "zirafa",
            "kon", "cap", "sliepka", "orol", "husenica", "dazdovka", "motyl",
            "alpaka", "komar", "medved", "lienka", "krokodil", "aligator",
            "pstros", "delfin", "kapor", "veleryba", "krab", "kreveta", "rak",
            "mucha", "vcela", "osa", "srsen", "holub", "cajka", "blcha", "zebra",
            "antilopa", "zralok", "hroch", "pakon", "byvol", "varan", "lemur",
            "leguan", "agama", "simpanz", "orangutan", "makak", "vrestan",
            "lenochod", "svina", "rys", "sova", "zubor", "muflon", "srnec", "srnka",
            "zaba", "stuka", "raja", "zizala", "cervik", "los", "losos", "sob",
            "sobol", "ondatra", "vydra", "bobor", "mys", "zajac", "kralik", "skrecok",
            "kacica", "hus", "labut", "pav", "sokol", "kormoran", "cajka", "cajnik",
            "albatros", "cincila", "hranostaj", "vtakopysk", "vtakopysk Perry",
            "jezura", "pasavec", "kiwi", "klokan", "ovecka", "mlok", "salamander",
            "koala", "panda",

    };
    int pocetPrvkov = velkostPola(poleZvierat); // vyratanie velkosti pola zvierat

    // VKLADANIE -----------------------------------------------------------------------------

    // vkladanie AVL
    begin = clock(); // meranie - start
    for (int i = 0; i < velkostTestu; i++) {

        int indexZvierata = (rand() % ((pocetPrvkov - 1) - 0 + 1)) + 0;
        //printf ("%d\n", indexZvierata);
        int randPocetNoh = (rand() % (100000 - 0 + 1)) + 0;
        int randPocetOci = (rand() % (100000 - 2 + 1)) + 2;

        //printf ("%s %d %d\n", poleZvierat[indexZvierata], randPocetNoh, randPocetOci);

        node = insert(node, randPocetNoh, randPocetOci, poleZvierat[indexZvierata]);

    }
    end = clock(); // meranie koniec
    time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
    efektivita = (time_spent / (double) POCET_VLOZENI) * 1000;

    CELKOVY_CAS_AVL_INSERT += time_spent;
    CELKOVY_POCET_VLOZENYCH_AVL += POCET_VLOZENI;

    printf("TEST VKLADANIA DO AVL STROMU (%d prvkov) :\n", velkostTestu);
    printf("\t-> pocet vlozenych zvierat: %d,\n\t-> pocet nevlozenych duplikatov: %d,\n\t-> pocet operacii otacania: %d, \n\t\tz toho %d doprava a %d dolava\n",
           POCET_VLOZENI, POCET_DUPLIKATOV, OTOCENIE_DOLAVA + OTOCENIE_DOPRAVA, OTOCENIE_DOPRAVA, OTOCENIE_DOLAVA);
    printf("VYSLEDNY CAS %.3lf s (%lf ms/prvok)\n\n", time_spent, efektivita);

    POCET_VLOZENI = POCET_DUPLIKATOV = OTOCENIE_DOLAVA = OTOCENIE_DOPRAVA = 0;
    efektivita = 0;

    // vkladanie RED-BLACK
    begin = clock(); // meranie - start
    for (int i = 0; i < velkostTestu; i++) {

        int indexZvierata = (rand() % ((pocetPrvkov - 1) - 0 + 1)) + 0;
        int randPocetNoh = (rand() % (100000 - 0 + 1)) + 0;
        int randPocetOci = (rand() % (100000 - 2 + 1)) + 2;

        //printf ("%s %d %d\n", poleZvierat[indexZvierata], randPocetNoh, randPocetOci);

        rbNode = insertion(rbNode, randPocetNoh, randPocetOci, poleZvierat[indexZvierata]);

    }
    end = clock(); // meranie koniec
    time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
    efektivita = (time_spent / (double) POCET_VLOZENI) * 1000;

    CELKOVY_CAS_RB_INSERT += time_spent;
    CELKOVY_POCET_VLOZENYCH_RB += POCET_VLOZENI;

    printf("TEST VKLADANIA DO RED-BLACK STROMU (%d prvkov) :\n", velkostTestu);
    printf("\t-> pocet vlozenych zvierat: %d,\n\t-> pocet nevlozenych duplikatov: %d\n",
           POCET_VLOZENI, POCET_DUPLIKATOV);
    printf("VYSLEDNY CAS %.3lf s (%lf ms/prvok)\n\n", time_spent, efektivita);

    POCET_VLOZENI = POCET_DUPLIKATOV = OTOCENIE_DOLAVA = OTOCENIE_DOPRAVA = 0;
    efektivita = 0;


    // HLADANIE ----------------------------------------------------------------------------------

    // hladanie v AVL
    begin = clock(); // meranie - start
    for (int i = 0; i < velkostTestu; i++) {
        int randPocetNoh = (rand() % (100000 - 0 + 1)) + 0;
        search(node, randPocetNoh);
    }
    end = clock(); // meranie koniec
    time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
    efektivita = (time_spent / (double) NAJDENYCH) * 1000;

    CELKOVY_CAS_AVL_SEARCH += time_spent;
    CELKOVY_POCET_NAJDENYCH_AVL += NAJDENYCH;

    printf("TEST HLADANIA V AVL STROME (%d prvkov) :\n", velkostTestu);
    printf("\t-> pocet najdenych zvierat: %d,\n\t-> pocet nenajdenych: %d\n", NAJDENYCH, NENAJDENYCH);
    printf("VYSLEDNY CAS %.3lf s (%lf ms/prvok)\n\n", time_spent, efektivita);

    NAJDENYCH = NENAJDENYCH = 0;
    efektivita = 0;

    // hladanie v Red-Black
    begin = clock(); // meranie - start
    for (int i = 0; i < velkostTestu; i++) {
        int randPocetNoh = (rand() % (100000 - 0 + 1)) + 0;
        searchRedBlack(rbNode, randPocetNoh);
    }
    end = clock(); // meranie koniec
    time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
    efektivita = (time_spent / (double) NAJDENYCH) * 1000;

    CELKOVY_CAS_RB_SEARCH += time_spent;
    CELKOVY_POCET_NAJDENYCH_RB += NAJDENYCH;

    NENAJDENYCH = velkostTestu - NAJDENYCH;

    printf("TEST HLADANIA V RED-BLACK STROME (%d prvkov) :\n", velkostTestu);
    printf("\t-> pocet najdenych zvierat: %d,\n\t-> pocet nenajdenych: %d\n", NAJDENYCH, NENAJDENYCH);
    printf("VYSLEDNY CAS %.3lf s (%lf ms/prvok)\n\n", time_spent, efektivita);

    NAJDENYCH = NENAJDENYCH = 0;
    efektivita = 0;
}


int main() {

    // pre zmenu testov upravit
    int randVelkost;
    int maxPocet = 500000;
    int minPocet = 200000;
    int pocetTestov = 20;

    double efektivitaAVL, efektivitaRB;

    for (int i = 1; i <= pocetTestov; i++) {
        printf("---------- TEST CISLO %d ---------------------------- \n\n", i);
        randVelkost = (rand() % (maxPocet - minPocet + 1)) + minPocet;
        //randVelkost /= i;
        testCompare(randVelkost);
    }

    efektivitaAVL = (CELKOVY_POCET_VLOZENYCH_AVL / CELKOVY_CAS_AVL_INSERT);
    efektivitaRB = (CELKOVY_POCET_VLOZENYCH_RB / CELKOVY_CAS_RB_INSERT);

    printf ("VYSLEDOK VKLADANIE:\npocet vlozenych prvkov:\n\tAVL: %d,\n\tRB:  %d,\n", CELKOVY_POCET_VLOZENYCH_AVL, CELKOVY_POCET_VLOZENYCH_RB);
    printf ("cas potrebny na beh:\n\tAVL: %.3lf sekund,\n\tRB:   %.3lf sekund,\n", CELKOVY_CAS_AVL_INSERT, CELKOVY_CAS_RB_INSERT);
    printf ("pomer vlozeny prvok / sekundu:\n\tAVL: %lf,\n\tRB:   %lf,\n", efektivitaAVL, efektivitaRB);

    efektivitaAVL = (CELKOVY_POCET_NAJDENYCH_AVL / CELKOVY_CAS_AVL_SEARCH);
    efektivitaRB = (CELKOVY_POCET_NAJDENYCH_RB / CELKOVY_CAS_RB_SEARCH);

    printf ("\nVYSLEDOK HLADANIE:\npocet najdenych prvkov:\n\tAVL: %d,\n\tRB:  %d,\n", CELKOVY_POCET_NAJDENYCH_AVL, CELKOVY_POCET_NAJDENYCH_RB);
    printf ("cas potrebny na beh:\n\tAVL: %.3lf sekund,\n\tRB:   %.3lf sekund,\n", CELKOVY_CAS_AVL_SEARCH, CELKOVY_CAS_RB_SEARCH);
    printf ("pomer najdeny prvok / sekundu:\n\tAVL: %lf,\n\tRB:   %lf,\n", efektivitaAVL, efektivitaRB);

    printf("end\n");

    return 0;
}
