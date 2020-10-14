// uloha4-1.c -- Emma Macháčová, 7.10.2020 11:17

#include <stdio.h>
#include <stdlib.h>

int vystup[500];

// uzol
struct node {
  int key;
  int level;
  struct node *left, *right;
};

// Create a node
struct node *newNode(int item, int lvl) {
  struct node *temp = (struct node *)malloc(sizeof(struct node));
  temp->key = item;
  temp->level = lvl;
  temp->left = temp->right = NULL;
  return temp;
}

// prejdenie po rade
void inorder(struct node *root) {
  if (root != NULL) {
    // do lava
    inorder(root->left);

    // root
    //printf("\n%d (%d)", root->key, root->level);
    vystup[root->key] = root->level; // priradenie do pola

    // do prava
    inorder(root->right);
  }
}

// novy uzol
struct node *insert(struct node *node, int key, int pocetVnoreni) {
  
  // prvy
  if (node == NULL) return newNode(key, pocetVnoreni);

  // do lava
  if (key < node->key ) {
    pocetVnoreni++;
    node->left = insert(node->left, key, pocetVnoreni);
  }
  // do prava
  else if (key > node->key ) {
    pocetVnoreni++;
    node->right = insert(node->right, key, pocetVnoreni);
  }
  
  return node;
}

// hladanie hodnoty
struct node* search(struct node* root, int key) { 
    // root == null || key == at root 
    if (root == NULL || root->key == key) 
       return root; 
     
    // Key > root's key 
    if (root->key < key) 
       return search(root->right, key); 
  
    // Key < root's key 
    return search(root->left, key); 
} 


int main() {
  int pocetVnoreni = 0;
  int pole[150000000];
  int i=0, prvok, pocet=0;

  struct node *root = NULL;

  while (scanf ("%d", &prvok) > 0) {
    root = insert (root, prvok, pocetVnoreni);
    pole[i] = prvok;
    i++;
    pocet++;
  }


  inorder(root);

  for (i=0; i<pocet; i++) {
    //printf ("%d\n", vystup[pole[i]]);
    printf ("%d\n", search(root, pole[i])->level);
  }

  return 0;
}