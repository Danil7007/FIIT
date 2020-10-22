// uloha4-1.c -- Emma Macháčová, 7.10.2020 11:17
/*
Na vstupe je daných niekoľko čísel, ktoré postupne vkladáte do tohto stromu. Strom nevyvažujte. Pre každé číslo zistite, ako hlboko je v strome uložené. Ak sa číslo v strome nenachádza, tak ho najprv pridajte do stromu.

Špecifikácia vstupu: Na vstupe je niekoľko čísel, ktoré postupne vkladáte do stromu. Čísla sú oddelené medzerou alebo novým riadkom.

Špecifikácia výstupu: Pre každé číslo na vstupe vypíšte jedno číslo -- ako hlboko je dané číslo uložené v strome.

Ukážka vstupu:
5
3
2
1
3
Výstup pre ukážkový vstup:
0
1
2
3
1
*/

#include <stdio.h>
#include <stdlib.h>
   
struct node { 
  long long key; 
  struct node *left, *right; 
}; 

long long pole[200000];

// novy uzol
struct node *newNode(long long item, long long hlbka) { 
  struct node *temp =  (struct node *)malloc(sizeof(struct node)); 
  temp->key = item; 
  temp->left = temp->right = NULL; 

  //printf ("hlbka: %llu, hodnota: %llu\n", hlbka, temp->key);
  printf ("%llu\n", hlbka);
  //pole[temp->key] = hlbka;
  //printf ("%llu\n", pole[temp->key]);

  return temp; 
} 
   
// pridanie do BST
struct node* insert(struct node* node, long long key, long long hlbka) { 
  
  // prazdny strom
  if (node == NULL) {
    return newNode(key, hlbka); 
  }

  if (key == node->key) {
    //printf ("hlbka: %llu, hodnota: %llu\n", hlbka, node->key);
    printf ("%llu\n", hlbka);
  }

  // rekurzia
  if (key < node->key) {
    node->left  = insert(node->left, key, hlbka+1); 
  }
    
  else if (key > node->key) {
    node->right = insert(node->right, key, hlbka+1); 
  }
       
  
  // head
  return node; 
} 
   
void inorder(struct node *root) 
{ 
    if (root != NULL) 
    { 
        inorder(root->left); 
        printf("%llu \n", root->key); 
        inorder(root->right); 
    } 
} 

int main() { 
  struct node *root = NULL; 
  long long hlbka = 0, cislo;

  while (scanf ("%llu", &cislo) > 0) {
    root = insert(root, cislo, 0); 
    //printf ("%llu\n", pole[cislo]);
  }

  return 0; 
} 