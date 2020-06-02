// uloha9-1.c -- Emma Macháčová, 22.4.2020 12:08

#include <stdio.h>
#include <stdlib.h>

typedef struct Polozka
{
  int cislo;
  struct Polozka *dalsi;
} POLOZKA;

POLOZKA *nacitaj();
void vypis(POLOZKA *prvy);

void zmaz(POLOZKA **prvy, int k)
{
  // Store head node 
    POLOZKA* temp = *prvy, *prev; 
  
    // If head node itself holds the key to be deleted 
    if (temp != NULL && temp->cislo == k) 
    { 
        *prvy = temp->dalsi;   // Changed head 
        free(temp);               // free old head 
        return; 
    } 
  
    // Search for the key to be deleted, keep track of the 
    // previous node as we need to change 'prev->next' 
    while (temp != NULL && temp->cislo != k) 
    { 
        prev = temp; 
        temp = temp->dalsi; 
    } 
  
    // If key was not present in linked list 
    if (temp == NULL) return; 
  
    // Unlink the node from linked list 
    prev->dalsi = temp->dalsi; 
  
    free(temp);  // Free memory 

}

int main()
{
  int k;
  POLOZKA *prvy;
  scanf("%d", &k);
  prvy = nacitaj(); // nacitaj zoznam
  zmaz(&prvy, k);
  vypis(prvy); // vypis zoznam
  return 0;
}