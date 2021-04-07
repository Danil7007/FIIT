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
double CELKOVY_CAS_AVL_INSERT, CELKOVY_CAS_HASH_INSERT;
double CELKOVY_CAS_AVL_SEARCH, CELKOVY_CAS_HASH_SEARCH;
int CELKOVY_POCET_VLOZENYCH_AVL, CELKOVY_POCET_VLOZENYCH_HASH;
int CELKOVY_POCET_NAJDENYCH_AVL, CELKOVY_POCET_HASH_NAJDENYCH;

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
// kód prevzatý zo stránky https://www.journaldev.com/35238/hash-table-in-c-plus-plus#conclusion

#define CAPACITY 50000 // velkost HASH tabulky

// pre testovanie
int POCET_VLOZENI, POCET_DUPLIKATOV, NAJDENYCH, NENAJDENYCH;
int CELKOVY_POCET_NAJDENYCH, CELKOVY_POCET_VLOZENYCH;
double CELKOVY_CAS_HLADANIA = 0, CELKOVY_CAS_VKLADANIA = 0;

// hash funkcia
unsigned long hash_function(char* str) {
    unsigned long i = 0;
    for (int j=0; str[j]; j++)
        i += str[j];
    return i % CAPACITY;
}

typedef struct Ht_item Ht_item;
typedef struct LinkedList LinkedList;
typedef struct HashTable HashTable;

// polozka hash table
struct Ht_item {
    int pocetNoh;
    int pocetOci;
    char* nazovZvierata;
};

// spajany zoznam
struct LinkedList {
    Ht_item* item;
    LinkedList* next;
};

// hash tabulka
struct HashTable {
    // obsahuje pole ukazovatelov na polozky
    Ht_item** items;
    LinkedList** overflow_buckets;
    int size;
    int count;
};

// alokovanie pamate pre ukazovatel spajaneho zoznamu
static LinkedList* allocate_list () {
    LinkedList* list = (LinkedList*) malloc (sizeof(LinkedList));
    return list;
}

// insert
static LinkedList* linkedlist_insert(LinkedList* list, Ht_item* item) {
    // vlozenie do spajaneho zoznamu
    if (list == NULL) {
        LinkedList* head = allocate_list();
        head->item = item;
        head->next = NULL;
        list = head;
        return list;
    }

    else if (list->next == NULL) {
        LinkedList* node = allocate_list();
        node->item = item;
        node->next = NULL;
        list->next = node;
        return list;
    }

    LinkedList* node = allocate_list();
    node->item = item;
    node->next = NULL;

    return list;
}

static Ht_item* linkedlist_remove(LinkedList* list) {
    if (!list)
        return NULL;
    if (!list->next)
        return NULL;
    LinkedList* node = list->next;
    LinkedList* temp = list;
    temp->next = NULL;
    list = node;
    Ht_item* it = NULL;
    memcpy(temp->item, it, sizeof(Ht_item));
    free(temp->item->nazovZvierata);
    free(temp->item);
    free(temp);
    return it;
}

static void free_linkedlist(LinkedList* list) {
    LinkedList* temp = list;
    while (list) {
        temp = list;
        list = list->next;
        free(temp->item->nazovZvierata);
        free(temp->item);
        free(temp);
    }
}

// vytvori "overflow buckets" = pole zpajanych zoznamov
static LinkedList** create_overflow_buckets(HashTable* table) {
    LinkedList** buckets = (LinkedList**) calloc (table->size, sizeof(LinkedList*));
    for (int i=0; i<table->size; i++)
        buckets[i] = NULL;
    return buckets;
}

// uvolnenie "overflow bucket-ov"
static void free_overflow_buckets(HashTable* table) {
    LinkedList** buckets = table->overflow_buckets;
    for (int i=0; i<table->size; i++)
        free_linkedlist(buckets[i]);
    free(buckets);
}

// vytvorenie polozky
Ht_item* create_item(char* nazovZvierata, int pocetNoh, int pocetOci) {
    // vytvori pointer na novu polozku hash tabulky
    Ht_item* item = (Ht_item*) malloc (sizeof(Ht_item));
    item->nazovZvierata = (char*) malloc (strlen(nazovZvierata) + 1);

    item->pocetNoh = (int) malloc (sizeof(int));
    item->pocetOci = (int) malloc (sizeof(int));

    strcpy(item->nazovZvierata, nazovZvierata);

    item->pocetNoh = pocetNoh;
    item->pocetOci = pocetOci;

    return item;
}

// vytvorenie novej hash tabulky
HashTable* create_table(int size) {
    HashTable* table = (HashTable*) malloc (sizeof(HashTable));
    table->size = size;
    table->count = 0;
    table->items = (Ht_item**) calloc (table->size, sizeof(Ht_item*));
    for (int i=0; i<table->size; i++)
        table->items[i] = NULL;
    table->overflow_buckets = create_overflow_buckets(table);

    return table;
}

// uvolnenie polozky
void free_item(Ht_item* item) {
    free(item->nazovZvierata);
    free(item);
}

// uvolnenie tabulky
void free_table(HashTable* table) {
    for (int i=0; i<table->size; i++) {
        Ht_item* item = table->items[i];
        if (item != NULL)
            free_item(item);
    }
    free_overflow_buckets(table);
    free(table->items);
    free(table);
}

// sprava kolizii
void handle_collision(HashTable* table, unsigned long index, Ht_item* item) {
    LinkedList* head = table->overflow_buckets[index];

    if (head == NULL) {
        // nie je treba robit zoznam
        head = allocate_list();
        head->item = item;
        table->overflow_buckets[index] = head;
        return;
    }
    else {
        // vlozenie do zoznamu
        table->overflow_buckets[index] = linkedlist_insert(head, item);
        return;
    }
}

// insert
void ht_insert(HashTable* table, char* nazovZvierata, int pocetNoh, int pocetOci) {
    // vytvorenie polozky
    Ht_item* item = create_item(nazovZvierata, pocetNoh, pocetOci);

    // vypocitanie indexu
    unsigned long index = hash_function(nazovZvierata);

    Ht_item* current_item = table->items[index];

    if (current_item == NULL) {

        // kluc neexistuje

        if (table->count == table->size) {
            // hash tabulka je plna
            printf("Insert Error: Hash Table is full\n");
            // odstranenie vytvorenej polozky
            free_item(item);
            return;
        }

        // priame vlozenie
        table->items[index] = item;
        table->count++;
    }

    else {
        // Scenar 1: treba aktualizovat len hodnotu
        // rovnaky nazovZvierata
        if (strcmp(current_item->nazovZvierata, nazovZvierata) == 0) {
            //strcpy(table->items[index]->value, value);
            table->items[index]->pocetNoh = pocetNoh;
            table->items[index]->pocetOci = pocetOci;
            POCET_DUPLIKATOV++;
            return;
        }

        else {
            // Scenar 2: kolizia
            handle_collision(table, index, item);
            return;
        }
    }
}

// search
char* ht_search(HashTable* table, char* nazovZvierata) {
    // hladanie klucu v tabulke,
    // ak nenajde vrati NULL
    int index = hash_function(nazovZvierata);
    Ht_item* item = table->items[index];
    LinkedList* head = table->overflow_buckets[index];

    // aby to nebol NULL
    while (item != NULL) {
        if (strcmp(item->nazovZvierata, nazovZvierata) == 0) {
            NAJDENYCH++;
            //return item->value;
            return item->pocetNoh;
        }
        if (head == NULL)
            return NULL;
        item = head->item;
        head = head->next;
    }
    return NULL;
}

// print
void print_search(HashTable* table, char* nazovZvierata) {
    char* val;
    if ((val = ht_search(table, nazovZvierata)) == NULL) {
        printf("%s does not exist\n", nazovZvierata);
        return;
    }
    else {
        printf("nazovZvierata:%s, Value:%s\n", nazovZvierata, val);
    }
}

// print
void print_table(HashTable* table) {
    printf("\n-------------------\n");
    for (int i=0; i<table->size; i++) {
        if (table->items[i]) {
            printf("Index: %d, nazovZvierata: %s, Values: %d %d ", i, table->items[i]->nazovZvierata, table->items[i]->pocetNoh, table->items[i]->pocetOci);
            if (table->overflow_buckets[i]) {
                LinkedList* head = table->overflow_buckets[i];
                while (head) {
                    printf("\n\t\t=> ");
                    printf("nazovZvierata: %s, Values: %d %d ", head->item->nazovZvierata, head->item->pocetNoh, table->items[i]->pocetOci);
                    head = head->next;
                }
            }
            printf("\n");
        }
    }
    printf("-------------------\n");
}


// TEST ----------------------------------------------------------------------------------------------------

// testovacia funkcia (pocet operacii vkladania/vyhladavania)
void testCompare(int velkostTestu) {

    struct node *node = NULL; // AVL strom
    HashTable* ht = create_table(CAPACITY); // hash tabulka

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

    // vkladanie HASH
    begin = clock(); // meranie - start
    for (int i = 0; i < velkostTestu; i++) {

        int indexZvierata = (rand() % ((pocetPrvkov - 1) - 0 + 1)) + 0;
        int randPocetNoh = (rand() % (100000 - 0 + 1)) + 0;
        int randPocetOci = (rand() % (100000 - 2 + 1)) + 2;

        //printf ("%s %d %d\n", poleZvierat[indexZvierata], randPocetNoh, randPocetOci);

        ht_insert(ht, poleZvierat[indexZvierata], randPocetNoh, randPocetOci);

    }
    end = clock(); // meranie koniec
    time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
    efektivita = (time_spent / (double) POCET_VLOZENI) * 1000;

    CELKOVY_CAS_HASH_INSERT += time_spent;
    CELKOVY_POCET_VLOZENYCH_HASH = velkostTestu - POCET_DUPLIKATOV;

    printf("TEST VKLADANIA HASH FUNKCIE (%d prvkov) :\n", velkostTestu);
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

    // hladanie v HASH
    begin = clock(); // meranie - start
    for (int i = 0; i < velkostTestu; i++) {
        int indexZvierata = (rand() % ((pocetPrvkov - 1) - 0 + 1)) + 0;
        ht_search(ht, poleZvierat[indexZvierata]);
    }
    end = clock(); // meranie koniec
    time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
    efektivita = (time_spent / (double) NAJDENYCH) * 1000;

    CELKOVY_CAS_HASH_SEARCH += time_spent;
    CELKOVY_POCET_HASH_NAJDENYCH += NAJDENYCH;

    NENAJDENYCH = velkostTestu - NAJDENYCH;

    printf("TEST HLADANIA HASH FUNKCIE (%d prvkov) :\n", velkostTestu);
    printf("\t-> pocet najdenych zvierat: %d,\n\t-> pocet nenajdenych: %d\n", NAJDENYCH, NENAJDENYCH);
    printf("VYSLEDNY CAS %.3lf s (%lf ms/prvok)\n\n", time_spent, efektivita);

    NAJDENYCH = NENAJDENYCH = 0;
    efektivita = 0;
}


int main() {

    // pre zmenu testov upravit
    int randVelkost;
    int maxPocet = 900000;
    int minPocet = 200000;
    int pocetTestov = 20;

    double efektivitaAVL, efektivitaHASH;

    for (int i = 1; i <= pocetTestov; i++) {
        printf("---------- TEST CISLO %d ---------------------------- \n\n", i);
        randVelkost = (rand() % (maxPocet - minPocet + 1)) + minPocet;
        //randVelkost /= i;
        testCompare(randVelkost);
    }

    efektivitaAVL = (CELKOVY_POCET_VLOZENYCH_AVL / CELKOVY_CAS_AVL_INSERT);
    efektivitaHASH = (CELKOVY_POCET_VLOZENYCH_HASH / CELKOVY_CAS_HASH_INSERT);

    printf ("VYSLEDOK VKLADANIE:\npocet vlozenych prvkov:\n\tAVL:  %d,\n\tHASH: %d,\n", CELKOVY_POCET_VLOZENYCH_AVL, CELKOVY_POCET_VLOZENYCH_HASH);
    printf ("cas potrebny na beh:\n\tAVL:  %.3lf sekund,\n\tHASH: %.3lf sekund,\n", CELKOVY_CAS_AVL_INSERT, CELKOVY_CAS_HASH_INSERT);
    printf ("pomer vlozeny prvok / sekundu:\n\tAVL:  %lf,\n\tHASH: %lf,\n", efektivitaAVL, efektivitaHASH);

    efektivitaAVL = (CELKOVY_POCET_NAJDENYCH_AVL / CELKOVY_CAS_AVL_SEARCH);
    efektivitaHASH = (CELKOVY_POCET_HASH_NAJDENYCH / CELKOVY_CAS_HASH_SEARCH);

    printf ("\nVYSLEDOK HLADANIE:\npocet najdenych prvkov:\n\tAVL:  %d,\n\tHASH: %d,\n", CELKOVY_POCET_NAJDENYCH_AVL, CELKOVY_POCET_HASH_NAJDENYCH);
    printf ("cas potrebny na beh:\n\tAVL:  %.3lf sekund,\n\tHASH: %.3lf sekund,\n", CELKOVY_CAS_AVL_SEARCH, CELKOVY_CAS_HASH_SEARCH);
    printf ("pomer najdeny prvok / sekundu:\n\tAVL:  %lf,\n\tHASH: %lf,\n", efektivitaAVL, efektivitaHASH);

    printf("end\n");

    return 0;
}
