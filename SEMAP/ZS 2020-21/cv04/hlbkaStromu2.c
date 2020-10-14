// uloha4-1.c -- Emma Macháčová, 7.10.2020 11:17

#include <stdio.h>
#include <stdlib.h>

// uzol
struct node {
  int key;
  struct node *left, *right;
};

// Create a node
struct node *newNode(int item) {
  struct node *temp = (struct node *)malloc(sizeof(struct node));
  temp->key = item;
  temp->left = temp->right = NULL;
  return temp;
}

// Inorder Traversal
void inorder(struct node *root) {
  if (root != NULL) {
    // Traverse left
    inorder(root->left);

    // Traverse root
    printf("%d -> ", root->key);

    // Traverse right
    inorder(root->right);
  }
}

// Insert a node
struct node *insert(struct node *node, int key) {
  // Return a new node if the tree is empty
  if (node == NULL) return newNode(key);

  // Traverse to the right place and insert the node
  if (key < node->key)
    node->left = insert(node->left, key);
  else
    node->right = insert(node->right, key);

  return node;
}

// Find the inorder successor
struct node *minValueNode(struct node *node) {
  struct node *current = node;

  // Find the leftmost leaf
  while (current && current->left != NULL)
    current = current->left;

  return current;
}

// Deleting a node
struct node *deleteNode(struct node *root, int key) {
  // Return if the tree is empty
  if (root == NULL) return root;

  // Find the node to be deleted
  if (key < root->key)
    root->left = deleteNode(root->left, key);
  else if (key > root->key)
    root->right = deleteNode(root->right, key);

  else {
    // If the node is with only one child or no child
    if (root->left == NULL) {
      struct node *temp = root->right;
      free(root);
      return temp;
    } else if (root->right == NULL) {
      struct node *temp = root->left;
      free(root);
      return temp;
    }

    // If the node has two children
    struct node *temp = minValueNode(root->right);

    // Place the inorder successor in position of the node to be deleted
    root->key = temp->key;

    // Delete the inorder successor
    root->right = deleteNode(root->right, temp->key);
  }
  return root;
}

// ------------------------------------------------
int getLevelUtil(struct node *node, int key, int level) { 
  if (node == NULL) 
    return 0; 
  
  if (node->key == key) 
    return level; 
  
  int downlevel = getLevelUtil(node->left, key, level+1); 
  if (downlevel != 0) 
    return downlevel; 
  
  downlevel = getLevelUtil(node->right, key, level+1); 
  return downlevel; 
} 

int getLevel(struct node *node, int key) { 
  return getLevelUtil(node,key,1); 
} 
// ------------------------------------------------
// Driver code
int main() {
  int pole[10000], i=0, prvok, pocet=0;

  struct node *root = NULL;

  while (scanf ("%d", &prvok) > 0) {
    root = insert (root, prvok);
    pole[i] = prvok;
    i++;
    pocet++;
  }
  /*root = insert(root, 8);
  root = insert(root, 3);
  root = insert(root, 1);
  root = insert(root, 6);
  root = insert(root, 7);
  root = insert(root, 10);
  root = insert(root, 14);
  root = insert(root, 4);*/

  for (i=0; i<pocet; i++) {
    printf ("%d\n", getLevel (root, pole[i]) - 1);
  }
  

  /*printf("Inorder traversal: ");
  inorder(root);*/

  return 0;
}