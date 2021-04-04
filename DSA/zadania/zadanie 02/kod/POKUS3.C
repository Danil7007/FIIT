// Zadanie 2 - Vyhladavanie v dynamickych mnozinah -- Emma Macháčová, 22.3.2021 17:25

// Vašou úlohou v rámci tohto zadania je porovnať viacero implementácií dátových
// štruktúr z hľadiska efektivity operácií insert a search
// v rozličných situáciách (operáciu delete nemusíte implementovať):

// (2 body) Vlastnú implementáciu binárneho vyhľadávacieho stromu (BVS)
// s ľubovoľným algoritmom na vyvažovanie,
// napr. AVL, Červeno-Čierne stromy, (2,3) stromy, (2,3,4) stromy, Splay stromy, ...

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define compare(a, b) ((a > b) ? a : b)
#define dlzkaPodstromu(node) ((node == NULL) ? 0 : node->dlzkaPodstromu)
#define rozdielHlbok(node) ((node == NULL) ? 0 : (dlzkaPodstromu(node->left) - dlzkaPodstromu(node->right)))
#define maxDlzka(node) (compare(dlzkaPodstromu(node->left), dlzkaPodstromu(node->right)) + 1)

#define velkostPola(pole) (sizeof (pole) / sizeof (char *))

#define TRUE 1
#define FALSE 0

typedef struct node {
    int pocetNoh;
    int pocetOci;
    char nazovZvierata[20];

    struct node *left;
    struct node *right;
    struct node *parent;

    int dlzkaPodstromu;
} NODE;


void printOut (struct node *node, int order);
void test (int velkostTestu);

struct node *search (struct node *node, int pocetNoh);
struct node *insert(struct node *node, int pocetNoh, int pocetOci, char *nazovZvierata);

struct node* avl (struct node *node, int pocetNoh, int pocetOci, char *nazovZvierata);

struct node *rotateRight(struct node *middle);
struct node *rightLeft (struct node *node);
struct node *rotateLeft(struct node *middle);
struct node *leftRight (struct node *node);

int POCET_VLOZENI, POCET_DUPLIKATOV, OTOCENIE_DOPRAVA, OTOCENIE_DOLAVA;
int NAJDENYCH, NENAJDENYCH;


// otacania
struct node *rotateRight(struct node *middle) {

    if (middle->left != NULL) {

        struct node *top;
        struct node *bottom;

        top = middle->left;
        bottom = top->right;

        middle->left = bottom;
        top->right = middle;

        middle->dlzkaPodstromu = maxDlzka(middle);
        top->dlzkaPodstromu = maxDlzka(top);

        OTOCENIE_DOPRAVA++;

        return top;
    }

    return middle;
}

struct node *rotateLeft(struct node *middle) {

    if (middle->right != NULL) {
        struct node *top;
        struct node *bottom;

        top = middle->right;
        bottom = top->left;

        top->left = middle;
        middle->right = bottom;

        top->dlzkaPodstromu = maxDlzka(top);
        middle->dlzkaPodstromu = maxDlzka(middle);

        OTOCENIE_DOLAVA++;

        return top;
    }
    return middle;
}

struct node *rightLeft (struct node *node) {
    if (node->right != NULL) {
        node->right = rotateRight(node->right);
        return node = rotateLeft(node);
    }
    return node;
}

struct node *leftRight (struct node *node) {
    if (node->left != NULL) {
        node->left = rotateLeft(node->left);
        return node = rotateRight(node);
    }
    return node;
}


// search
struct node *search (struct node *node, int pocetNoh) {

    if (node == NULL) {
        //printf("Nebol vytvoreny strom alebo zviera nebolo najdene\n\n");
        NENAJDENYCH++;
        return node;
    }
    else if (node->pocetNoh == pocetNoh) {
        //printf("Najdene zviera s poctom noh %d - je to %s\n", pocetNoh, node->nazovZvierata);
        NAJDENYCH++;
        return node;
    }
    else if (node->pocetNoh > pocetNoh) {
        return search(node->left, pocetNoh);
    }
    else { // (root->pocetNoh < pocetNoh)
        return search (node->right, pocetNoh);
    }
}

// insert
struct node *insert(struct node *node, int pocetNoh, int pocetOci, char *nazovZvierata) {

    if (node == NULL) {
        struct node *newNode = (struct node *)malloc(sizeof(struct node));
        newNode->pocetNoh = pocetNoh;
        newNode->pocetOci = pocetOci;
        strcpy (newNode->nazovZvierata, nazovZvierata);

        newNode->left = NULL;
        newNode->right = NULL;

        newNode->dlzkaPodstromu = 1;

        //printf ("-> %s\n", newNode->nazovZvierata);

        POCET_VLOZENI++;
        return (newNode);
    }

        // ZORADENIE PODLA NOH -------------------------------------------------
    else if (node->pocetNoh > pocetNoh) {
        node->left = insert (node->left, pocetNoh, pocetOci, nazovZvierata);
    }
    else if (node->pocetNoh < pocetNoh) {
        node->right = insert(node->right, pocetNoh, pocetOci, nazovZvierata);
    }
        // ZORADENIE PODLA OCI -------------------------------------------------
    else if (node->pocetOci > pocetOci) {
        node->left = insert (node->left, pocetNoh, pocetOci, nazovZvierata);
    }
    else if (node->pocetOci < pocetOci) {
        node->right = insert(node->right, pocetNoh, pocetOci, nazovZvierata);
    }
        // ZORADENIE PODLA NAZVU -----------------------------------------------
    else if (strcmp (node->nazovZvierata, nazovZvierata) > 0) {
        node->left = insert (node->left, pocetNoh, pocetOci, nazovZvierata);
    }
    else if (strcmp (node->nazovZvierata, nazovZvierata) < 0) {
        node->right = insert(node->right, pocetNoh, pocetOci, nazovZvierata);
    }
    else {
        //printf("Zviera uz je v zozname\n");
        POCET_DUPLIKATOV++;
    }


    node = avl (node, pocetNoh, pocetOci, nazovZvierata);

    return node;
}

// vyvazovanie
struct node* avl (struct node *node, int pocetNoh, int pocetOci, char *nazovZvierata) {
    int rozdiel;

    node->dlzkaPodstromu = compare(dlzkaPodstromu(node->left), dlzkaPodstromu(node->right));
    node->dlzkaPodstromu++;

    //printf ("%d\n", node->dlzkaPodstromu);

    rozdiel = rozdielHlbok(node);

    // vyvazovanie z lava --------------------------------------------
    if (rozdiel > 1) {
        // podla noh
        if (pocetNoh < node->left->pocetNoh) {
            return rotateRight(node);
        }
        else if (pocetNoh > node->left->pocetNoh) {
            return leftRight(node);
        }
            // podla oci
        else if (pocetOci < node->left->pocetOci) {
            return rotateRight(node);
        }
        else if (pocetOci > node->left->pocetOci) {
            return leftRight(node);
        }
            // podla nazvu
        else if (strcmp(nazovZvierata, node->nazovZvierata) < 0) {
            return rotateRight(node);
        }
        else if (strcmp(nazovZvierata, node->nazovZvierata) > 0) {
            return leftRight(node);
        }
    }
        // vyvazovanie z prava -------------------------------------------
    else if (rozdiel < -1) {
        // podla noh
        if (pocetNoh > node->right->pocetNoh) {
            return rotateLeft(node);
        }
        else if (pocetNoh < node->right->pocetNoh) {

            return rightLeft(node);
        }
            // podla oci
        else if (pocetOci > node->right->pocetOci) {
            return rotateLeft(node);
        }
        else if (pocetOci < node->right->pocetOci) {
            return rightLeft(node);
        }
            // podla nazvu
        else if (strcmp(nazovZvierata, node->nazovZvierata) > 0) {
            return rotateLeft(node);
        }
        else if (strcmp(nazovZvierata, node->nazovZvierata) < 0) {
            return rightLeft(node);
        }
    }


    return node;
}


// vypis
void printOut (struct node *node, int order) {

    if (node != NULL) {

        if (order) { // zostupne
            printOut(node->left, TRUE);
            printf("\tzviera: %s, pocet noh: %d, pocet oci: %d, dlzka (pod)stromu: %d\n", node->nazovZvierata, node->pocetNoh, node->pocetOci, node->dlzkaPodstromu);
            printOut(node->right, TRUE);
        }
        else {
            // vzostupne
            printOut(node->right, FALSE);
            printf("\tzviera: %s, pocet noh: %d, pocet oci: %d, dlzka (pod)stromu: %d\n", node->nazovZvierata, node->pocetNoh, node->pocetOci, node->dlzkaPodstromu);
            printOut(node->left, FALSE);
        }
    }
}


// --------------------------------------------------------------------------- VYMAZAT
void print2DUtil(struct node *root, int space)
{
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += 15;

    // Process right child first
    print2DUtil(root->right, space);

    // Print current node after space
    // count
    printf("\n");
    for (int i = 15; i < space; i++)
        printf(" ");
    printf("%s (%d, %d)\n", root->nazovZvierata, root->pocetNoh, root->pocetOci);

    // Process left child
    print2DUtil(root->left, space);
}

// Wrapper over print2DUtil()
void print2D(struct node *root)
{
    // Pass initial space count as 0
    print2DUtil(root, 0);
} // -------------------------------------------------------------------------------

void test (int velkostTestu) {

    struct node *node = NULL;

    char *poleZvierat[] = {
            "pes",
            "macka",
            "kacka",
            "chobotnica",
            "lama",
            "jasterica",
            "stonozka",
            "kohut",
            "had",
            "hadica",
            "uhor",
            "slon",
            "nosorozec",
            "ryba",
            "tulen",
            "korytnacka",
            "mravec",
            "mroz",
            "riasa",
            "jelen",
            "srnka",
            "vlk",
            "gorila",
            "lev",
            "tiger",
            "koza",
            "hyena",
            "zirafa",
            "kon",
            "cap",
            "sliepka",
            "orol",
            "husenica",
            "dazdovka",
            "motyl",
            "alpaka",
            "komar",
            "medved",
            "lienka",
            "krokodil",
            "aligator",
            "pstros",
            "delfin",
            "kapor",
            "veleryba",
            "krab",
            "kreveta",
            "rak",
            "mucha",
            "vcela",
            "osa",
            "srsen",
            "holub",
            "cajka",
            "blcha",
            "zebra",
            "antilopa",
            "zralok",
            "hroch",
            "pakon",
            "byvol",
            "varan",
            "lemur",
            "leguan",
            "agama",
            "simpanz",
            "orangutan",
            "makak",
            "vrestan",
            "lenochod",
            "svina",
            "rys",
            "sova",
            "zubor",
            "muflon",
            "srnec",
            "srnka",
            "zaba",
            "stuka",
            "raja",
            "zizala",
            "cervik",
            "los",
            "losos",
            "sob",
            "sobol",
            "ondatra",
            "vydra",
            "bobor",
            "mys",
            "zajac",
            "kralik",
            "skrecok",
            "kacica",
            "hus",
            "labut",
            "pav",
            "sokol",
            "kormoran",
            "cajka",
            "cajnik",
            "albatros",
            "cincila",
            "hranostaj",
            "vtakopysk",
            "vtakopysk Perry",
            "jezura",
            "pasavec",
            "kiwi",
            "klokan",
            "ovecka",
            "mlok",
            "salamander",
            "koala",
            "panda",

    };
    int pocetPrvkov = velkostPola(poleZvierat);

    // vkladanie
    clock_t begin = clock(); // meranie - start
    for (int i=0; i<velkostTestu; i++) {

        int indexZvierata = (rand() % ((pocetPrvkov-1) - 0 + 1)) + 0;
        //printf ("%d\n", indexZvierata);
        int randPocetNoh = (rand() % (100 - 0 + 1)) + 0;
        int randPocetOci = (rand() % (100 - 2 + 1)) + 2;

        //printf ("%s %d %d\n", poleZvierat[indexZvierata], randPocetNoh, randPocetOci);

        node = insert(node, randPocetNoh, randPocetOci, poleZvierat[indexZvierata]);

    }
    clock_t end = clock(); // meranie koniec
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    double efektivita = (time_spent / (double)POCET_VLOZENI) * 1000;

    printf ("TEST VKLADANIA (%d prvkov) :\n", velkostTestu);
    printf ("\t-> pocet vlozenych zvierat: %d,\n\t-> pocet nevlozenych duplikatov: %d,\n\t-> pocet operacii otacania: %d, \n\t\tz toho %d doprava a %d dolava\n", POCET_VLOZENI, POCET_DUPLIKATOV, OTOCENIE_DOLAVA+OTOCENIE_DOPRAVA, OTOCENIE_DOPRAVA, OTOCENIE_DOLAVA);
    printf("VYSLEDNY CAS %.3lf s (%lf ms/prvok)\n\n", time_spent, efektivita);
    POCET_VLOZENI = POCET_DUPLIKATOV = OTOCENIE_DOLAVA = OTOCENIE_DOPRAVA = efektivita = 0;

    // hladanie
    begin = clock(); // meranie - start
    for (int i=0; i<velkostTestu; i++) {
        int randPocetNoh = (rand() % (100 - 0 + 1)) + 0;
        search(node, randPocetNoh);
    }
    end = clock(); // meranie koniec
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    efektivita = (time_spent / (double)NAJDENYCH) * 1000;

    printf ("TEST HLADANIA (%d prvkov) :\n", velkostTestu);
    printf ("\t-> pocet najdenych zvierat: %d,\n\t-> pocet nenajdenych: %d\n", NAJDENYCH, NENAJDENYCH);
    printf("VYSLEDNY CAS %.3lf s (%lf ms/prvok)\n\n", time_spent, efektivita);
    NAJDENYCH = NENAJDENYCH = efektivita = 0;

}

int main() {

    // pre zmenu testov upravit
    int randVelkost;
    int maxPocet = 500000;
    int minPocet = 2000;
    int pocetTestov = 20;

    for (int i=1; i<= pocetTestov; i++) {
        printf ("---------- TEST CISLO %d ---------------------------- \n\n", i);
        randVelkost = (rand() % (maxPocet - minPocet + 1)) + minPocet;
        //randVelkost /= i;
        test(randVelkost);
    }



    printf("end\n");

    return 0;
}
