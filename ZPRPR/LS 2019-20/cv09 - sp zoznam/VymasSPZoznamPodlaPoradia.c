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
  // If linked list is empty 
   if (*prvy == NULL) 
      return; 
  
   // Store head node 
    POLOZKA* temp = *prvy; 
  
    // If head needs to be removed 
    if (k == 0) 
    { 
        *prvy = temp->dalsi;   // Change head 
        free(temp);               // free old head 
        return; 
    } 
  
    // Find previous node of the node to be deleted 
    for (int i=0; temp!=NULL && i<k-1; i++) 
         temp = temp->dalsi; 
  
    // If position is more than number of ndoes 
    if (temp == NULL || temp->dalsi == NULL) 
         return; 
  
    // Node temp->next is the node to be deleted 
    // Store pointer to the next of node to be deleted 
    POLOZKA *dalsi = temp->dalsi->dalsi; 
  
    // Unlink the node from linked list 
    free(temp->dalsi);  // Free memory 
  
    temp->dalsi = dalsi;  // Unlink the deleted node from list 

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