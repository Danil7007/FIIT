// uloha5-1.c -- Emma Macháčová, 14.10.2020 14:38

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct obciansky {
	char id[100];
	struct obciansky *prev, *next;

} OBCIANSKY;

// spracuje cisla OP: vrati pocet najdenych duplikatov.
int vyhadzovac(OBCIANSKY* head) {
	int pocet = 0;
	OBCIANSKY* temp;
	OBCIANSKY* porovnavam;

	temp = head;
	while (temp != NULL) {
		
		porovnavam = temp->next;

		while (porovnavam != NULL) {

			if (strcmp (temp->id, porovnavam->id) == 0) { // ak su zhodne
				pocet++; // pocet duplikatov
				temp->next = porovnavam->next; // odstranenie zo zoznamu
			}

			porovnavam = porovnavam->next;
		}

		temp = temp->next;
	}
	
	//printf ("%d\n", pocet);
	return pocet;
}


int main(void) {
	int n = 0;
	char buff[100];
	OBCIANSKY* head = NULL;
	OBCIANSKY* predchadzajuci = NULL;
	//OBCIANSKY* last = NULL;
	//OBCIANSKY* temp = NULL;

	while (scanf ("%s", buff) > 0) { // nacitanie
		OBCIANSKY* temp = malloc(sizeof(struct obciansky)); // novy obc
		temp->next = NULL;
		temp->prev = NULL;
		strcpy (temp->id, buff);

		if (head == NULL) { // ak je prvy
			head = temp;
			predchadzajuci = temp;
			n++; // pocet zaznamov
		}
		else { // ak uz su zaznamy
			temp->prev = predchadzajuci;
			predchadzajuci->next = temp;
			predchadzajuci = temp;
			n++; // pocet zaznamov
		}
	}
	//last = predchadzajuci; // posledny nacitany zaznam

	/*/ funguje
	temp = head;
	while (temp != NULL) {
		printf ("%s\n", temp->id);
		temp = temp->next;
	}*/

	/*/ funguje
	temp = last;
	while (temp != NULL) {
		printf ("%s\n", temp->id);
		temp = temp->prev;
	}*/
	

	printf("Pocet duplikatov: %d\n", vyhadzovac(head));

	return 0;
}