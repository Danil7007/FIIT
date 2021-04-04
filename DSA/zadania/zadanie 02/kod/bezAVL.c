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

    struct node *left;
    struct node *right;
} NODE;


struct node *search (struct node *node, int key);
struct node *insert (struct node *root, int key, int pocetOci, char *nazovZvierata);
void printOut (struct node *node);


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

        root = newNode;
        return root;
    }
        // ZORADENIE PODLA NOH -------------------------------------------------
    else if (root->pocetNoh > key) {
        root->left = insert (root->left, key, pocetOci, nazovZvierata);
    }
    else if (root->pocetNoh < key) {
        root->right = insert(root->right, key, pocetOci, nazovZvierata);
    }
        // ZORADENIE PODLA OCI -------------------------------------------------
    else if (root->pocetOci > pocetOci) {
        root->left = insert (root->left, key, pocetOci, nazovZvierata);
    }
    else if (root->pocetOci < pocetOci) {
        root->right = insert(root->right, key, pocetOci, nazovZvierata);
    }
        // ZORADENIE PODLA NAZVU -----------------------------------------------
    else if (strcmp (root->nazovZvierata, nazovZvierata) > 0) {
        root->left = insert (root->left, key, pocetOci, nazovZvierata);
    }
    else if (strcmp (root->nazovZvierata, nazovZvierata) < 0) {
        root->right = insert(root->right, key, pocetOci, nazovZvierata);
    }
    else {
        printf("Zviera uz je v zozname\n\n");
    }

    return root;
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
