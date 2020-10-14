// uloha4-1.c -- Emma Macháčová, 7.10.2020 11:17

#include<stdio.h> 

struct node { 
  int data; 
  struct node *left; 
  struct node *right; 
}; 
  

int getLevelUtil(struct node *node, int data, int level) { 
  if (node == NULL) 
    return 0; 
  
  if (node->data == data) 
    return level; 
  
  int downlevel = getLevelUtil(node->left, data, level+1); 
  if (downlevel != 0) 
    return downlevel; 
  
  downlevel = getLevelUtil(node->right, data, level+1); 
  return downlevel; 
} 

int getLevel(struct node *node, int data) { 
  return getLevelUtil(node,data,1); 
} 
 
  

int main() 
{ 
    struct node *root = struct node; 
    int x, n; 
    int pole[100];

    scanf ("%d", &n);
    while (scanf ("%d", &n) > 0) {

    }
  
    for (x = 1; x <=5; x++) 
    { 
      int level = getLevel(root, x); 
      if (level) 
        printf(" Level of %d is %d\n", x, getLevel(root, x)); 
      else
        printf(" %d is not present in tree \n", x); 
    } 
  
    getchar(); 
    return 0; 
}