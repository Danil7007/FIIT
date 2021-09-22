// Zadanie 2 - Vyhladavanie v dynamickych mnozinah -- Emma Macháčová, 22.3.2021 17:25
// (1 bod) Prevzatú (nie vlastnú!) implementáciu hašovania s riešením kolízií iným spôsobom ako v
// predchádzajúcom bode. Zdroj musí byť uvedený.

// kód prevzatý zo stránky https://www.journaldev.com/35238/hash-table-in-c-plus-plus#conclusion


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
    char* key;
    char* value;
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
    free(temp->item->key);
    free(temp->item->value);
    free(temp->item);
    free(temp);
    return it;
}

static void free_linkedlist(LinkedList* list) {
    LinkedList* temp = list;
    while (list) {
        temp = list;
        list = list->next;
        free(temp->item->key);
        free(temp->item->value);
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
Ht_item* create_item(char* key, char* value) {
    // vytvori pointer na novu polozku hash tabulky
    Ht_item* item = (Ht_item*) malloc (sizeof(Ht_item));
    item->key = (char*) malloc (strlen(key) + 1);
    item->value = (char*) malloc (strlen(value) + 1);

    strcpy(item->key, key);
    strcpy(item->value, value);

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
    free(item->key);
    free(item->value);
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
void ht_insert(HashTable* table, char* key, char* value) {
    // vytvorenie polozky
    Ht_item* item = create_item(key, value);

    // vypocitanie indexu
    unsigned long index = hash_function(key);

    Ht_item* current_item = table->items[index];

    if (current_item == NULL) {
        // klud neexistuje
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
        if (strcmp(current_item->key, key) == 0) {
            strcpy(table->items[index]->value, value);
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
char* ht_search(HashTable* table, char* key) {
    // hladanie klucu v tabulke,
    // ak nenajde vrati NULL
    int index = hash_function(key);
    Ht_item* item = table->items[index];
    LinkedList* head = table->overflow_buckets[index];

    // aby to nebol NULL
    while (item != NULL) {
        if (strcmp(item->key, key) == 0) {
            NAJDENYCH++;
            return item->value;
        }
        if (head == NULL)
            return NULL;
        item = head->item;
        head = head->next;
    }
    return NULL;
}

// print
void print_search(HashTable* table, char* key) {
    char* val;
    if ((val = ht_search(table, key)) == NULL) {
        printf("%s does not exist\n", key);
        return;
    }
    else {
        printf("Key:%s, Value:%s\n", key, val);
    }
}

// print
void print_table(HashTable* table) {
    printf("\n-------------------\n");
    for (int i=0; i<table->size; i++) {
        if (table->items[i]) {
            printf("Index:%d, Key:%s, Value:%s", i, table->items[i]->key, table->items[i]->value);
            if (table->overflow_buckets[i]) {
                LinkedList* head = table->overflow_buckets[i];
                while (head) {
                    printf("\n\t\t=> ");
                    printf("Key:%s, Value:%s ", head->item->key, head->item->value);
                    head = head->next;
                }
            }
            printf("\n");
        }
    }
    printf("-------------------\n");
}

// test
int main() {
    int celkovoNajdenych = 0;
    double celkovyCasHladania = 0;

    int minVelkost, maxVelkost, pocetTestov;

    clock_t begin;
    clock_t end;
    double time_spent;
    double efektivita;
    int velkostTestu;

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
    int pocetPrvkov = sizeof(poleZvierat) / sizeof (char*);


    pocetTestov = 20;
    minVelkost = 100;
    maxVelkost = 5000;

    for (int j=0; j < pocetTestov; j++) {
        printf ("------- TEST CISLO: %d ------------------\n\n", j+1);
        HashTable* ht = create_table(CAPACITY);

        velkostTestu = (rand() % ((maxVelkost - minVelkost) - 0 + minVelkost)) + 0;

        begin = clock(); // meranie - start
        for (int i = 0; i < velkostTestu; i++) {

            int indexZvierata1 = (rand() % ((pocetPrvkov - 1) - 0 + 1)) + 0;
            int indexZvierata2 = (rand() % ((pocetPrvkov - 1) - 0 + 1)) + 0;

            ht_insert(ht, poleZvierat[indexZvierata1], poleZvierat[indexZvierata2]);
        }
        end = clock(); // meranie koniec

        time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
        POCET_VLOZENI = velkostTestu - POCET_DUPLIKATOV;

        CELKOVY_CAS_VKLADANIA += time_spent;
        CELKOVY_POCET_VLOZENYCH += POCET_VLOZENI;

        efektivita = time_spent / POCET_VLOZENI * 1000;

        printf("TEST VKLADANIA (%d prvkov) :\n", velkostTestu);
        printf("\t-> pocet vlozenych zvierat: %d\n\t-> pocet duplikatov: %d\n",
               POCET_VLOZENI, POCET_DUPLIKATOV);
        printf("VYSLEDNY CAS %.3lf s (%lf ms/prvok)\n\n", time_spent, efektivita);
        POCET_VLOZENI = POCET_DUPLIKATOV = efektivita = 0;


        // hladanie
        begin = clock(); // meranie - start
        for (int i = 0; i < velkostTestu; i++) {
            int indexZvierata1 = (rand() % ((pocetPrvkov - 1) - 0 + 1)) + 0;
            ht_search(ht, poleZvierat[indexZvierata1]);
        }
        end = clock(); // meranie koniec
        time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
        efektivita = (time_spent / (double) NAJDENYCH) * 1000;

        CELKOVY_CAS_HLADANIA += time_spent;
        celkovyCasHladania += time_spent;
        celkovoNajdenych += NAJDENYCH;

        NENAJDENYCH = velkostTestu - NAJDENYCH;

        printf("TEST HLADANIA (%d prvkov) :\n", velkostTestu);
        printf("\t-> pocet najdenych zvierat: %d,\n\t-> pocet nenajdenych: %d\n", NAJDENYCH, NENAJDENYCH);
        printf("VYSLEDNY CAS %.3lf s (%lf ms/prvok)\n\n", time_spent, efektivita);
        NAJDENYCH = NENAJDENYCH = efektivita = 0;

        ht = NULL;
    }

    efektivita = CELKOVY_POCET_VLOZENYCH / CELKOVY_CAS_VKLADANIA;

    printf ("VYSLEDOK VKLADANIE:\npocet vlozenych prvkov: %d,\n", CELKOVY_POCET_VLOZENYCH);
    printf ("cas potrebny na beh: %.3lf sekund,\n", CELKOVY_CAS_VKLADANIA);
    printf ("pomer vlozeny prvok / sekundu: %lf\n", efektivita);

    efektivita = celkovoNajdenych / celkovyCasHladania;

    printf ("\nVYSLEDOK HLADANIE:\npocet najdenych prvkov: %d\n", celkovoNajdenych);
    printf ("cas potrebny na beh: %.3lf sekund,\n", celkovyCasHladania);
    printf ("pomer najdeny prvok / sekundu: %lf,\n", efektivita);


    return 0;
}