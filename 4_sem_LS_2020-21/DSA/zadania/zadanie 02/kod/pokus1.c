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
    char nazovZvierata[10];

    int hlbka;

    struct node *left;
    struct node *right;
    struct node *parent;
} NODE;

struct node *rotate (struct node *middle, int smer) {

    struct node *top;
    struct node *bottom;
    int middleLeftHlbka = 0, middleRightHlbka = 0;
    int topLeftHlbka = 0, topRightHlbka = 0;

    if (smer > 0) { // doprava
        top = middle->left;
        bottom = top->right;

        top->right = middle;
        middle->left = bottom;
    }

    else if (smer < 0) { // dolava
        top = middle->right;
        bottom = top->left;

        top->left = middle;
        middle->right = bottom;
    }

    if (middleLeftHlbka > middleRightHlbka) {
        middle->hlbka = middleLeftHlbka;
        middle->hlbka++;
    }
    else {
        middle->hlbka = middleRightHlbka;
        middle->hlbka++;
    }

    if (topLeftHlbka > topRightHlbka) {
        top->hlbka = topLeftHlbka;
        top->hlbka++;
    }
    else {
        top->hlbka = topRightHlbka;
        top->hlbka++;
    }

    return top;
}

struct node *search (struct node *root, int key) {

    if (root == NULL) {
        printf("Nebol vytvoreny strom alebo zviera nebolo najdene\n\n");
        return root;
    }
    else if (root->pocetNoh == key) {
        printf("Najdene zviera s poctom noh %d - je to %s\n\n", key, root->nazovZvierata);
        return root;
    }
    else if (root->pocetNoh > key) {
        return search(root->left, key);
    }
    else { // (root->pocetNoh < key)
        return search (root->right, key);
    }
}

struct node *insert (struct node *root, int key, int pocetOci, char *nazovZvierata) {
    // vlozenie noveho uzlu
    if (root == NULL) {
        struct node *newNode;
        newNode = malloc(sizeof(struct node));

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

    // AVL ------------------------------------------------------------------
    if ((root->right != NULL) && (root->left != NULL)) {
        int presah = 0;
        int hlbkaLeft = 0; 
        int hlbkaRight = 0;
        int leftPocetNoh = 0;
        int rightPocetNoh = 0;

        if ((root->left != NULL) && (root->right != NULL)) {
            presah = root->left->hlbka - root->right->hlbka;
            hlbkaLeft = root->left->hlbka;
            hlbkaRight = root->right->hlbka;
            leftPocetNoh = root->left->pocetNoh;
            rightPocetNoh = root->right->pocetNoh;
        }
        

        if (hlbkaLeft > hlbkaRight) {
            root->hlbka = hlbkaLeft;
            root->hlbka++;
        }
        else {
            root->hlbka = hlbkaRight;
            root->hlbka++;
        }

        
        // PODLA POCTU NOH ------------------------------------------

        // LL
        if ((presah > 1) && (key < leftPocetNoh)) {
            return rotate(root, RIGHT);
        }
        // LR
        else if ((presah > 1) && (key > leftPocetNoh)) {
            root->left = rotate(root->left, LEFT);
            return rotate(root, RIGHT);
        }
        // RR
        else if ((presah < -1) && (key > rightPocetNoh)) {
            return rotate(root, LEFT);
        }
        // RL
        else if ((presah < -1) && (key < rightPocetNoh)) {
            root->right = rotate(root->right, RIGHT);
            return rotate(root, LEFT);
        }
    
        // PODLA POCTU OCI ------------------------------------------

        // LL
        else if ((presah > 1) && (key < root->left->pocetOci)) {
            return rotate(root, RIGHT);
        }
        // LR
        else if ((presah > 1) && (key > root->left->pocetOci)) {
            root->left = rotate(root->left, LEFT);
            return rotate(root, RIGHT);
        }
        // RR
        else if ((presah < -1) && (key > root->right->pocetOci)) {
            return rotate(root, LEFT);
        }
        // RL
        else if ((presah < -1) && (key < root->right->pocetOci)) {
            root->right = rotate(root->right, RIGHT);
            return rotate(root, LEFT);
        }
    }
    

    return root;
}

void printOut (struct node *root) {

    if (root != NULL) {

        // zostupne
        printOut(root->left);
        printf("\tzviera: %s, pocet noh: %d, pocet oci: %d\n", root->nazovZvierata, root->pocetNoh, root->pocetOci);
        printOut(root->right);

        // vzostupne
        /*printOut(root->right);
        printf("\tzviera: %s, pocet noh: %d, pocet oci: %d\n", root->nazovZvierata, root->pocetNoh, root->pocetOci);
        printOut(root->left);*/
    }

}



int main() {
    struct node *root = NULL;

    root = insert (root, 20, 2, "pes" );
    insert (root, 4, 2, "macka" );
    insert (root, 6, 2, "kon" );
    insert (root, 10, 2, "zaba" );
    insert (root, 0, 2, "hadica" );
    insert (root, 10, 2, "zaba" );
    insert (root, 10, 2, "zaba" );
    insert (root, 0, 12, "rybicka" );
    insert (root, 0, 2, "had" );
    insert (root, 100, 2, "stonozka" );
    insert (root, 0, 0, "balon" );
    insert (root, 15, 2, "patnastnozec" );

    printOut(root);
    printf ("\n");

    return 0;
}
