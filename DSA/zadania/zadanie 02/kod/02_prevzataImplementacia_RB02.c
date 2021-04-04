// PREVZATA IMPLEMENTACIA
// https://gist.github.com/aagontuk/38b4070911391dd2806f

// uzly su bud cierne alebo cervene
// koren je cierny
// listy su null - NIL
// kazdy cerveny uzol ma cierneho parenta
// kazda vetva obsahuje rovnaky pocet ciernych uzlov

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define RED 0
#define BLACK 1

// doplnene - pre vyhodnocovanie testov
#define velkostPola(pole) (sizeof (pole) / sizeof (char *))
int POCET_VLOZENI, POCET_DUPLIKATOV, OTOCENIE_DOPRAVA, OTOCENIE_DOLAVA;
int NAJDENYCH, NENAJDENYCH;

struct node{
    int key;
    int color;

    char string [20]; // doplnene
    int key2;

    struct node *parent;
    struct node *left;
    struct node *right;
};

// globalne premenne
struct node *ROOT;
struct node *NILL;

void left_rotate(struct node *x);
void right_rotate(struct node *x);
void tree_print(struct node *x);
void red_black_insert (int key, int key2, char* string);
void red_black_insert_fixup(struct node *z);
struct node *tree_search(int key);
struct node *tree_minimum(struct node *x);
void test (int velkostTestu); // vlastna funkcia


int main(){
    NILL = malloc(sizeof(struct node));
    NILL->color = BLACK;

    ROOT = NILL; // koren

    test (10000);
    tree_print(ROOT);

    return 0;
}

// vypis
void tree_print(struct node *x){
    if(x != NILL){
        tree_print(x->left);
        printf("%d %d %s\n", x->key, x->key2, x->string); // doplnene key2, string
        tree_print(x->right);
    }
}

// search
struct node *tree_search (int key) {
    struct node *x;

    x = ROOT;
    while (x != NILL && x->key != key){
        if (key < x->key){
            x = x->left;
        }
        else if (key > x->key) { // upravene
            x = x->right;
        }
    }

    if (key == x->key) { // doplnene
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

    z->key = key; // novy uzol
    z->color = RED;
    z->left = NILL;
    z->right = NILL;

    z->key2 = key2; // doplnene
    strcpy(z->string, string);

    x = ROOT;
    y = NILL;


    // prejdi strom kym nenajdes list (NILL)
    // y je pomocny uzol, drzi posledny nie NILL uzol, tento bude rodic noveho uzlu
    while(x != NILL){
        y = x;

        // doplnene - kontrola duplicity
        if (z->key == x->key) {
            POCET_DUPLIKATOV++;
            return;
        }

        if(z->key < x->key){
            x = x->left;
        }
        else{
            x = x->right;
        }
    }

    if(y == NILL){
        ROOT = z;
    }
    else if(z->key <= y->key){
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
    // kym je rodic noveho uzlu cerveny
    while(z->parent->color == RED){

        // ak je pravy stryko alebo prave dieta stareho rodica noveho uzlu cerveny
        if(z->parent == z->parent->parent->left){
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
            if(z->parent->parent->left->color == RED){
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

                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                left_rotate(z->parent->parent);
                OTOCENIE_DOLAVA++;
            }
        }
    }

    ROOT->color = BLACK;
}

// lava rotacia
void left_rotate(struct node *x){
    struct node *y;

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

// vlastna testovacia funkcia (pocet operacii vkladania/vyhladavania)
void test (int velkostTestu) {

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
        int randPocetNoh = (rand() % (10 - 0 + 1)) + 0;
        int randPocetOci = (rand() % (10 - 2 + 1)) + 2;

        //printf ("%s %d %d\n", poleZvierat[indexZvierata], randPocetNoh, randPocetOci);

        red_black_insert (randPocetNoh, randPocetOci, poleZvierat[indexZvierata]);

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
        int randPocetNoh = (rand() % (10 - 0 + 1)) + 0;
        node = tree_search (randPocetNoh);
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

