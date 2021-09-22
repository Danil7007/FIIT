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

#define velkostPola(pole) (sizeof (pole) / sizeof (char *))

// globalne premenne pre vyhodnocovanie testov
int POCET_VLOZENI, POCET_DUPLIKATOV, OTOCENIE_DOPRAVA, OTOCENIE_DOLAVA;
int NAJDENYCH, NENAJDENYCH;


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
        // ak narazi na duplikat
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
                    OTOCENIE_DOPRAVA++;
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


// vlastna testovacia funkcia (pocet operacii vkladania/vyhladavania)
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

        node = insertion(node, randPocetNoh, randPocetOci, poleZvierat[indexZvierata]);

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
        searchRedBlack(node, randPocetNoh);
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
    int minPocet = 2000;
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