// uloha5-1.c -- Emma Macháčová, 14.10.2020 14:38

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct obciansky {
	char id[100];
	struct obciansky *left, *right;
};

// novy obciansky
struct obciansky *newObciansky(char *item) { 
  struct obciansky *temp =  (struct obciansky *)malloc(sizeof(struct obciansky)); 

  strcpy (temp->id, item); 
  //printf ("%s", temp->id);
  temp->left = temp->right = NULL; 

  return temp; 
}

// pridanie do BST
struct obciansky* insert(struct obciansky* obciansky, char* item, int *dupl) { 
  
  // prazdny strom
  if (obciansky == NULL) {
    return newObciansky(item); 
  }

  if (strcmp (item, obciansky->id) == 0) {
    //printf ("duplikat\n");
	*dupl += 1;

  }

  // rekurzia
  if (strcmp (item, obciansky->id) < 0) {
    obciansky->left  = insert(obciansky->left, item, dupl); 
  }
    
  else if (strcmp (item, obciansky->id) > 0) {
    obciansky->right = insert(obciansky->right, item, dupl); 
  }
       
  // head
  return obciansky; 
} 

// spracuje cisla OP: vrati pocet najdenych duplikatov.
int vyhadzovac(char *a[], int n) {
	struct obciansky *root = NULL; 
	int i, dupl=0;

	for (i=0; i<n; i++) {
		root = insert(root, a[i], &dupl); 
	}
	printf ("Pocet duplikatov: %d\n", dupl);

	return 0;
}

// ukazkovy test
int main(void) {
	char **a = NULL, buf[100];
	int n = 0, len = 0;

	// nacitanie retazcov
	while (scanf("%s", buf) > 0)
	{
		if (n == len)
		{
			len = len + len + (len == 0);
			a = (char**)realloc(a, len * sizeof(char*));
		}
		a[n++] = strdup(buf); 
		// na konci bude v n pocet nacitanych obcianskych
	}

	//printf("Pocet duplikatov: %d\n", vyhadzovac(a, n));

	vyhadzovac(a, n);

	return 0;
}