// uloha4-1.c -- Emma Macháčová, 7.10.2020 11:17

#include<stdio.h> 
#include<stdlib.h> 
   
struct node { 
    int key; 
    int level;
    struct node *left, *right; 
}; 

// A utility function to create a new BST node 
struct node *newNode(int item, int lvl) { 
    struct node *temp =  (struct node *)malloc(sizeof(struct node)); 
    temp->key = item; 
    temp->level = lvl;
    temp->left = temp->right = NULL; 
    return temp; 
} 
   
// A utility function to do inorder traversal of BST 
void inorder(struct node *root)  { 
  if (root != NULL) { 
    inorder(root->left); 
    printf("%d (%d)\n", root->key, root->level); 
    inorder(root->right); 
  } 
} 
   
/* A utility function to insert a new node with given key in BST */
struct node* insert(struct node* node, int key, int pocetVnoreni)  { 

    /* If the tree is empty, return a new node */
    if (node == NULL) {
      return newNode(key, pocetVnoreni); 
    } 
  
    /* Otherwise, recur down the tree */
    if (key < node->key) {
      pocetVnoreni++;
      node->left  = insert(node->left, key, pocetVnoreni);
    }
         
    else if (key >= node->key) {
      pocetVnoreni++;
      node->right = insert(node->right, key, pocetVnoreni);   
    }
         
    /* return the (unchanged) node pointer */
    return node; 
} 
   
// Driver Program to test above functions 
int main()  { 
  int pocetVnoreni = 0;
  int pole[500], i=0, pocetPrvkov=0, prvok;

  struct node *root = NULL; 

  /*root = insert(root, 50, pocetVnoreni); 
  insert(root, 30, pocetVnoreni); 
  insert(root, 20, pocetVnoreni); 
  insert(root, 40, pocetVnoreni); 
  insert(root, 70, pocetVnoreni); 
  insert(root, 60, pocetVnoreni); 
  insert(root, 80, pocetVnoreni); */

  scanf ("%d", &prvok);
  root = insert(root, prvok, pocetVnoreni); // head

  while (scanf ("%d", &prvok) > 0) {
    pole[i] = prvok;
    insert (root, prvok, pocetVnoreni);
    i++;
    pocetPrvkov++;
  }
   
  // print inoder traversal of the BST 
  inorder(root); 
   
  return 0; 
} 