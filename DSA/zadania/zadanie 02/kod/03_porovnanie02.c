// Zadanie 2 - Vyhladavanie v dynamickych mnozinah -- Emma Macháčová, 22.3.2021 17:25
// (2 body) Vlastnú implementáciu binárneho vyhľadávacieho stromu (BVS)
// s ľubovoľným algoritmom na vyvažovanie,
// napr. AVL, Červeno-Čierne stromy, (2,3) stromy, (2,3,4) stromy, Splay stromy, ...

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// pomocne funkcionality - AVL strom
#define compare(a, b) ((a > b) ? a : b)
#define dlzkaPodstromu(node) ((node == NULL) ? 0 : node->dlzkaPodstromu)
#define rozdielHlbok(node) ((node == NULL) ? 0 : (dlzkaPodstromu(node->left) - dlzkaPodstromu(node->right)))
#define maxDlzka(node) (compare(dlzkaPodstromu(node->left), dlzkaPodstromu(node->right)) + 1)
#define velkostPola(pole) (sizeof (pole) / sizeof (char *))

// pre funkciu vypis
#define TRUE 1
#define FALSE 0

// pre RED BLACK strom
#define RED 0
#define BLACK 1

// globalne pre vyhodnotenie
double CELKOVY_CAS_AVL, CELKOVY_CAS_RB;
int CELKOVY_POCET_VLOZENYCH_AVL, CELKOVY_POCET_VLOZENYCH_RB;

// globalne premenne - RED BLACK strom
struct node *ROOT;
struct node *NILL;

// globalne premenne pre vyhodnocovanie testov
int POCET_VLOZENI, POCET_DUPLIKATOV, OTOCENIE_DOPRAVA, OTOCENIE_DOLAVA;
int NAJDENYCH, NENAJDENYCH;

// struktura zvierata
typedef struct node {
    int pocetNoh; // hlavny key
    int pocetOci;
    char nazovZvierata[20];

    int color; // pre red black strom

    struct node *left;
    struct node *right;
    struct node *parent;

    int dlzkaPodstromu;
} ZVIERA;


// AVL funkcie
void printOut(struct node *node, int order); // vypis obsahu stromu, order TRUE/FALSE -> vzostupne/zostupne
void test(int velkostTestu); // testovania funkcia
struct node *search(struct node *node, int pocetNoh); // vyhladavanie podla postu noh
struct node *insert(struct node *node, int pocetNoh, int pocetOci, char *nazovZvierata); // vkladanie
struct node *avl(struct node *node, int pocetNoh, int pocetOci, char *nazovZvierata); // AVL funkcionalita
struct node *rotateRight(struct node *middle); // funkcie otacania pre AVL
struct node *rightLeft(struct node *node);
struct node *rotateLeft(struct node *middle);
struct node *leftRight(struct node *node);

// RED BLACK funkcie
void left_rotate(struct node *x);
void right_rotate(struct node *x);
void tree_print(struct node *x);
void red_black_insert (int key, int key2, char* string);
void red_black_insert_fixup(struct node *z);
struct node *tree_search(int key);
struct node *tree_minimum(struct node *x);


// AVL -------------------------------------------------------------------------------------------------

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
    if (node->pocetNoh == pocetNoh) {
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

// RED BLACK -------------------------------------------------------------------------------------------

// vypis
void tree_print(struct node *x){
    if(x != NILL){
        tree_print(x->left);
        printf("%d %d %s\n", x->pocetNoh, x->pocetOci, x->nazovZvierata); // doplnene key2, string
        tree_print(x->right);
    }
}

// search
struct node *tree_search (int key) {
    struct node *x;

    x = ROOT;
    while (x != NILL && x->pocetNoh != key){
        if (key < x->pocetNoh){
            x = x->left;
        }
        else if (key > x->pocetNoh) { // upravene
            x = x->right;
        }
    }

    if (x != NULL && key == x->pocetNoh) { // doplnene
        NAJDENYCH++;
    }

    return x;
}

// vyhladanie lista
struct node *tree_minimum (struct node *x){
    while(x->left != NILL){
        x = x->left;
    }
    return x;
}

// vkladanie rovnako ako pre BST vkladanie, ale novy uzol je cerveny
// zafarbenie na cerveno moze porusit pravidla -> volanie funkcie fixup
void red_black_insert (int key, int key2, char* string){
    struct node *z, *x, *y;
    z = malloc(sizeof(struct node));

    z->pocetNoh = key; // novy uzol
    z->color = RED;
    z->left = NILL;
    z->right = NILL;

    z->pocetOci = key2; // doplnene
    strcpy(z->nazovZvierata, string);

    x = ROOT;
    y = NILL;


    // prejdi strom kym nenajdes list (NILL)
    // y je pomocny uzol, drzi posledny nie NILL uzol, tento bude rodic noveho uzlu
    while(x != NILL){
        y = x;

        // doplnene - kontrola duplicity
        if (z->pocetNoh == x->pocetNoh) {
            POCET_DUPLIKATOV++;
            return;
        }

        if(z->pocetNoh < x->pocetNoh){
            x = x->left;
        }
        else{
            x = x->right;
        }
    }

    if(y == NILL){
        ROOT = z;
    }
    else if(z->pocetNoh <= y->pocetNoh){
        y->left = z;
    }
    else{
        y->right = z;
    }

    z->parent = y;
    POCET_VLOZENI++;

    red_black_insert_fixup(z);
}

void red_black_insert_fixup(struct node *z){

    if (z->parent == NULL) { // doplnene
        return;
    }

    // kym je rodic noveho uzlu cerveny
    while(z->parent != NULL && z->parent->color == RED ){ // doplnena prva cast podmienky

        // ak je pravy stryko alebo prave dieta stareho rodica noveho uzlu cerveny
        // doplnene (z->right != NULL && z->left != NULL)
        if( (z->right != NULL && z->left != NULL) && z->parent == z->parent->parent->left){
            if(z->parent->parent->right->color == RED){

                // stryko a rodic noveho uzlu -> cierny
                z->parent->color = BLACK;
                z->parent->parent->right->color = BLACK;
                // stary rodic -> cerveny
                z->parent->parent->color = RED;
                // stary rodic noveho uzla bude novy novy uzol, tak while loop pokracuje
                z = z->parent->parent;
            }

                // else if pravy stryko noveho uzlu nie je cerveny
            else{

                // novy uzol je prave dieta
                if(z == z->parent->right){
                    z = z->parent;
                    left_rotate(z); // lava rotacia
                    OTOCENIE_DOLAVA++;
                }

                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                right_rotate(z->parent->parent); // prava rotacia
                OTOCENIE_DOPRAVA++;
            }
        }

            // rodic noveho uzlu je prave dieta stareho rodica
        else{

            // to iste ako hore, len sa vymenia prave a lave rotacie
            // doplnene (z->right != NULL && z->left != NULL)
            if( (z->right != NULL && z->left != NULL) && z->parent->parent->left->color == RED){
                z->parent->color = BLACK;
                z->parent->parent->left->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }

                // lavy stryko nie je cerveny
            else{
                // novy uzol je lave dieta
                if(z == z->parent->left){
                    z = z->parent;
                    right_rotate(z);
                    OTOCENIE_DOPRAVA++;
                }

                // doplnena podmienka
                if (z->parent != NULL) {
                    z->parent->color = BLACK;
                    if (z->parent->parent != NULL) {
                        z->parent->parent->color = RED;
                    }

                    left_rotate(z->parent->parent);
                    OTOCENIE_DOLAVA++;
                }

            }
        }
    }

    ROOT->color = BLACK;
}

// lava rotacia
void left_rotate(struct node *x){
    struct node *y;

    // doplnena podmienka
    if (x == NULL || x->right == NULL || y == NULL || x->left == NULL) {
        return;
    }


    // lave dieta y -> prave dieta x
    y = x->right;
    x->right = y->left;
    if(y->left != NILL){
        y->left->parent = x;
    }

    // vymena rodicov
    y->parent = x->parent;
    if(y->parent == NILL){
        ROOT = y;
    }
    else if(x == x->parent->left){
        x->parent->left = y;
    }
    else{
        x->parent->right = y;
    }

    // x -> lave dieta y, y -> rodic x
    y->left = x;
    x->parent = y;
}

// prava rotacia
void right_rotate(struct node *x){
    struct node *y;

    // doplnena podmienka
    if (x->right == NULL || x->left == NULL) {
        return;
    }

    // prave dieta y -> lave dieta x
    y = x->left;
    x->left = y->right;
    if(y->right != NILL){
        y->right->parent = x;
    }

    // vymena rodicov
    y->parent = x->parent;
    if(y->parent == NILL){
        ROOT = y;
    }
    else if(x == x->parent->left){
        x->parent->left = y;
    }
    else{
        x->parent->right = y;
    }

    // y -> rodic x, x-> dieta y
    y->right = x;
    x->parent = y;
}

// TEST ------------------------------------------------------------------------------------------------

// testovacia funkcia (pocet operacii vkladania/vyhladavania)
void testCompare(int velkostTestu) {

    struct node *node = NULL; // AVL strom

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
        int randPocetNoh = (rand() % (10 - 0 + 1)) + 0;
        int randPocetOci = (rand() % (10 - 2 + 1)) + 2;

        //printf ("%s %d %d\n", poleZvierat[indexZvierata], randPocetNoh, randPocetOci);

        node = insert(node, randPocetNoh, randPocetOci, poleZvierat[indexZvierata]);

    }
    end = clock(); // meranie koniec
    time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
    efektivita = (time_spent / (double) POCET_VLOZENI) * 1000;

    CELKOVY_CAS_AVL += time_spent;
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
        int randPocetNoh = (rand() % (10 - 0 + 1)) + 0;
        int randPocetOci = (rand() % (10 - 2 + 1)) + 2;

        //printf ("%s %d %d\n", poleZvierat[indexZvierata], randPocetNoh, randPocetOci);

        red_black_insert (randPocetNoh, randPocetOci, poleZvierat[indexZvierata]);

    }
    end = clock(); // meranie koniec
    time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
    efektivita = (time_spent / (double) POCET_VLOZENI) * 1000;

    CELKOVY_CAS_RB += time_spent;
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
        int randPocetNoh = (rand() % (10 - 0 + 1)) + 0;
        search(node, randPocetNoh);
    }
    end = clock(); // meranie koniec
    time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
    efektivita = (time_spent / (double) NAJDENYCH) * 1000;

    printf("TEST HLADANIA V AVL STROME (%d prvkov) :\n", velkostTestu);
    printf("\t-> pocet najdenych zvierat: %d,\n\t-> pocet nenajdenych: %d\n", NAJDENYCH, NENAJDENYCH);
    printf("VYSLEDNY CAS %.3lf s (%lf ms/prvok)\n\n", time_spent, efektivita);

    NAJDENYCH = NENAJDENYCH = 0;
    efektivita = 0;

    // hladanie v Red-Black
    begin = clock(); // meranie - start
    for (int i = 0; i < velkostTestu; i++) {
        int randPocetNoh = (rand() % (10 - 0 + 1)) + 0;
        ROOT = tree_search(randPocetNoh);
    }
    end = clock(); // meranie koniec
    time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
    efektivita = (time_spent / (double) NAJDENYCH) * 1000;

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
    int minPocet = 2000;
    int pocetTestov = 20;

    for (int i = 1; i <= pocetTestov; i++) {
        printf("---------- TEST CISLO %d ---------------------------- \n\n", i);
        randVelkost = (rand() % (maxPocet - minPocet + 1)) + minPocet;
        //randVelkost /= i;
        testCompare(randVelkost);
    }


    printf("end\n");

    return 0;
}
