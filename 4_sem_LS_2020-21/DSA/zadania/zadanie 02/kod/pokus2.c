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

#define RIGHT 1
#define LEFT (-1)

typedef struct node {
    int pocetNoh;
    int pocetOci;
    char nazovZvierata[15];

    int hlbka;

    struct node *left;
    struct node *right;
    struct node *parent;
} NODE;


int getHlbka (struct node *node);
int getRozdielHlbok (struct node *node);
struct node *search (struct node *node, int key);
struct node *insert (struct node *root, int key, int pocetOci, char *nazovZvierata);
struct node *rotate(struct node *middle, int otocenie);
struct node *avl (struct node *node, int key);



int getHlbka (struct node *node) {
    if (node == NULL) {
        return 0;
    }
    else {
        return node->hlbka;
    }
}

int getRozdielHlbok (struct node *node) {
    if (node == NULL) {
        return 0;
    }
    else {
        return (getHlbka(node->left) - getHlbka(node->right));
    }
}

struct node *search (struct node *node, int key) {

    if (node == NULL) {
        printf("Nebol vytvoreny strom alebo zviera nebolo najdene\n\n");
        return node;
    }
    else if (node->pocetNoh == key) {
        printf("Najdene zviera s poctom noh %d - je to %s\n\n", key, node->nazovZvierata);
        return node;
    }
    else if (node->pocetNoh > key) {
        return search(node->left, key);
    }
    else { // (root->pocetNoh < key)
        return search (node->right, key);
    }
}

struct node *insert (struct node *root, int key, int pocetOci, char *nazovZvierata) {

    // vlozenie noveho uzlu
    if (root == NULL) {
        struct node *newNode;
        newNode = (struct node*)malloc(sizeof(struct node));

        newNode->pocetNoh = key;
        newNode->pocetOci = pocetOci;
        strcpy (newNode->nazovZvierata, nazovZvierata);

        newNode->right = NULL;
        newNode->left = NULL;
        newNode->parent = root;
        newNode->hlbka = 1;
        root = newNode;
        return root;
    }
        // ZORADENIE PODLA NOH -------------------------------------------------
    else if (root->pocetNoh > key) {
        root->left = insert (root->left, key, pocetOci, nazovZvierata);
        root->left->parent = root;
    }
    else if (root->pocetNoh < key) {
        root->right = insert(root->right, key, pocetOci, nazovZvierata);
        root->right->parent = root;
    }
        // ZORADENIE PODLA OCI -------------------------------------------------
    else if (root->pocetOci > pocetOci) {
        root->left = insert (root->left, key, pocetOci, nazovZvierata);
        root->left->parent = root;
    }
    else if (root->pocetOci < pocetOci) {
        root->right = insert(root->right, key, pocetOci, nazovZvierata);
        root->right->parent = root;
    }
        // ZORADENIE PODLA NAZVU -----------------------------------------------
    else if (strcmp (root->nazovZvierata, nazovZvierata) > 0) {
        root->left = insert (root->left, key, pocetOci, nazovZvierata);
        root->left->parent = root;
    }
    else if (strcmp (root->nazovZvierata, nazovZvierata) < 0) {
        root->right = insert(root->right, key, pocetOci, nazovZvierata);
        root->right->parent = root;
    }
    else {
        printf("Zviera uz je v zozname\n\n");
    }

    root = avl(root, key);

    return root;
}

struct node *avl (struct node *node, int key) {
    int rozdielHlbok = 0;

    // nastavenie dlzky podstromu
    if (getHlbka(node->left) > getHlbka(node->right + 1)) {
        node->hlbka = getHlbka(node->left);
    }
    else {
        node->hlbka = getHlbka(node->right) + 1;
    }


    rozdielHlbok = getRozdielHlbok(node);

    if ((node->left != NULL) && (node->right != NULL)) {
        if (rozdielHlbok > 0) { // vyvazovanie dolava
            if (node->left->pocetNoh > key) {
                printf("LL\n");
                return rotate (node, RIGHT);
            }
            else if (node->left->pocetNoh < key) {
                printf("LR\n");
                node->left = rotate(node->left, LEFT);
                return rotate(node, RIGHT);
            }
        }
        else if (rozdielHlbok < 0) { // vyvazovanie doprava
            if (node->right->pocetNoh > key) {
                printf("RL\n");
                node->right = rotate(node->right, RIGHT);
                return rotate (node, LEFT);
            }
            else if (node->right->pocetNoh < key) {
                printf("RR\n");
                return rotate(node, LEFT);
            }
        }
    }

}

struct node *rotate(struct node *middle, int otocenie)
{
    struct node *top;
    struct node *bottom;

    // dolava
    if (otocenie <= LEFT) {
        top = middle->right;
        bottom = top->left;

        top->left = middle; // otocenie
        middle->right = bottom;
    }
    // doprava
    else if (otocenie >= RIGHT){
        top = middle->left;
        bottom = top->right;

        // otocenie
        top->right = middle;
        middle->left = bottom;
    }

    // prepisanie dlzok podstromov
    if (getHlbka(middle->left) > getHlbka(middle->right) + 1) {
        middle->hlbka = getHlbka(middle->left);
    }
    else {
        middle->hlbka = getHlbka(middle->right) + 1;
    }

    if (getHlbka(top->left) > getHlbka(top->right) + 1) {
        top->hlbka = getHlbka(top->left);
    }
    else {
        top->hlbka = getHlbka(top->right) + 1;
    }


    return top;
}


void printOut (struct node *node) {

    if (node != NULL) {

        // zostupne
        printOut(node->left);
        printf("\tzviera: %s, pocet noh: %d, pocet oci: %d\n", node->nazovZvierata, node->pocetNoh, node->pocetOci);
        printOut(node->right);

        // vzostupne
        /*printOut(node->right);
        printf("\tzviera: %s, pocet noh: %d, pocet oci: %d\n", node->nazovZvierata, node->pocetNoh, node->pocetOci);
        printOut(node->left);*/
    }

}



int main() {
    struct node *root = NULL;

    root = insert (root, 10, 2, "pes" );
    insert (root, 20, 2, "macka" );
    insert (root, 30, 2, "kon" );
    insert (root, 40, 2, "zaba" );
    insert (root, 0, 2, "hadica" );
    insert (root, 25, 2, "zaba" );
    insert (root, 10, 2, "zaba" );
    insert (root, 0, 12, "rybicka" );
    insert (root, 0, 2, "had" );
    insert (root, 100, 2, "stonozka" );
    insert (root, 0, 0, "balon" );
    insert (root, 15, 2, "rebkre" );

    printOut(root);
    printf ("\n");

    return 0;
}
