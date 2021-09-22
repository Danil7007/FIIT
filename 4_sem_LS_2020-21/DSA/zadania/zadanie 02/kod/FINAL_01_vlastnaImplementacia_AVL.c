// Zadanie 2 - Vyhladavanie v dynamickych mnozinah -- Emma Macháčová, 22.3.2021 17:25
// (2 body) Vlastnú implementáciu binárneho vyhľadávacieho stromu (BVS)
// s ľubovoľným algoritmom na vyvažovanie,
// napr. AVL, Červeno-Čierne stromy, (2,3) stromy, (2,3,4) stromy, Splay stromy, ...

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
    struct node *parent;

    int dlzkaPodstromu;
} ZVIERA;


void printOut(struct node *node, int order); // vypis obsahu stromu, order TRUE/FALSE -> vzostupne/zostupne
void test(int velkostTestu); // testovania funkcia

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
        top->dlzkaPodstromu = maxDlzka(top);
        middle->dlzkaPodstromu = maxDlzka(middle);

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
            // podla oci
        else if (pocetOci < node->left->pocetOci) {
            return rotateRight(node);
        } else if (pocetOci > node->left->pocetOci) {
            return leftRight(node);
        }
            // podla nazvu
        else if (strcmp(nazovZvierata, node->nazovZvierata) < 0) {
            return rotateRight(node);
        } else if (strcmp(nazovZvierata, node->nazovZvierata) > 0) {
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
            // podla oci
        else if (pocetOci > node->right->pocetOci) {
            return rotateLeft(node);
        } else if (pocetOci < node->right->pocetOci) {
            return rightLeft(node);
        }
            // podla nazvu
        else if (strcmp(nazovZvierata, node->nazovZvierata) > 0) {
            return rotateLeft(node);
        } else if (strcmp(nazovZvierata, node->nazovZvierata) < 0) {
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

// testovacia funkcia (pocet operacii vkladania/vyhladavania)
void test(int velkostTestu) {

    struct node *node = NULL;
    clock_t begin;
    clock_t end;
    double time_spent;
    double efektivita;

    char *poleZvierat[] = {
            "pes","macka","kacka","chobotnica","lama","jasterica",
            "stonozka","kohut","had","hadica","uhor","slon","nosorozec",
            "ryba","tulen","korytnacka","mravec","mroz","riasa","jelen",
            "srnka","vlk","gorila","lev","tiger","koza","hyena","zirafa",
            "kon","cap","sliepka","orol","husenica","dazdovka","motyl",
            "alpaka","komar","medved","lienka","krokodil","aligator",
            "pstros","delfin","kapor","veleryba","krab","kreveta","rak",
            "mucha","vcela","osa","srsen","holub","cajka","blcha","zebra",
            "antilopa","zralok","hroch","pakon","byvol","varan","lemur",
            "leguan","agama","simpanz","orangutan","makak","vrestan",
            "lenochod","svina","rys","sova","zubor","muflon","srnec","srnka",
            "zaba","stuka","raja","zizala","cervik","los","losos","sob",
            "sobol","ondatra","vydra","bobor","mys","zajac","kralik","skrecok",
            "kacica","hus","labut","pav","sokol","kormoran","cajka","cajnik",
            "albatros","cincila","hranostaj","vtakopysk","vtakopysk Perry",
            "jezura","pasavec","kiwi","klokan","ovecka","mlok","salamander",
            "koala","panda",

    };
    int pocetPrvkov = velkostPola(poleZvierat); // vyratanie velkosti pola zvierat

    // vkladanie
    begin = clock(); // meranie - start
    for (int i = 0; i < velkostTestu; i++) {

        int indexZvierata = (rand() % ((pocetPrvkov - 1) - 0 + 1)) + 0;
        //printf ("%d\n", indexZvierata);
        int randPocetNoh = (rand() % (10000 - 0 + 1)) + 0;
        int randPocetOci = (rand() % (10000 - 2 + 1)) + 2;

        //printf ("%s %d %d\n", poleZvierat[indexZvierata], randPocetNoh, randPocetOci);

        node = insert(node, randPocetNoh, randPocetOci, poleZvierat[indexZvierata]);

    }
    end = clock(); // meranie koniec
    time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
    efektivita = (time_spent / (double) POCET_VLOZENI) * 1000;

    printf("TEST VKLADANIA (%d prvkov) :\n", velkostTestu);
    printf("\t-> pocet vlozenych zvierat: %d,\n\t-> pocet nevlozenych duplikatov: %d,\n\t-> pocet operacii otacania: %d, \n\t\tz toho %d doprava a %d dolava\n",
           POCET_VLOZENI, POCET_DUPLIKATOV, OTOCENIE_DOLAVA + OTOCENIE_DOPRAVA, OTOCENIE_DOPRAVA, OTOCENIE_DOLAVA);
    printf("VYSLEDNY CAS %.3lf s (%lf ms/prvok)\n\n", time_spent, efektivita);
    POCET_VLOZENI = POCET_DUPLIKATOV = OTOCENIE_DOLAVA = OTOCENIE_DOPRAVA = efektivita = 0;

    // hladanie
    begin = clock(); // meranie - start
    for (int i = 0; i < velkostTestu; i++) {
        int randPocetNoh = (rand() % (10000 - 0 + 1)) + 0;
        search(node, randPocetNoh);
    }
    end = clock(); // meranie koniec
    time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
    efektivita = (time_spent / (double) NAJDENYCH) * 1000;

    NENAJDENYCH = velkostTestu - NAJDENYCH;

    printf("TEST HLADANIA (%d prvkov) :\n", velkostTestu);
    printf("\t-> pocet najdenych zvierat: %d,\n\t-> pocet nenajdenych: %d\n", NAJDENYCH, NENAJDENYCH);
    printf("VYSLEDNY CAS %.3lf s (%lf ms/prvok)\n\n", time_spent, efektivita);
    NAJDENYCH = NENAJDENYCH = efektivita = 0;

}

int main() {

    // pre zmenu testov upravit
    int randVelkost;
    int maxPocet = 500000;
    int minPocet = 400000;
    int pocetTestov = 20;

    for (int i = 1; i <= pocetTestov; i++) {
        printf("---------- TEST CISLO %d ---------------------------- \n\n", i);
        randVelkost = (rand() % (maxPocet - minPocet + 1)) + minPocet;
        //randVelkost /= i;
        test(randVelkost);
    }


    printf("end\n");

    return 0;
}
