// uloha5-1.c -- Emma Macháčová, 14.10.2020 14:38
/*
Určite ste to už zažili... večer, diskotéka, pri vchode sympatickí vyhadzovači nekompromisne odmietajú vstup neplnoletým mládežníkom, ktorí sa už nedočkavo tlačia na parket. Mladí ale vedia byť vynaliezaví, zaobstarali si občiansky preukaz so “správnym” dátumom narodenia a po prekonaní poslednej prekážky si ho poza chrbát posunú spať a na vstupe je opäť použitý ďalším nedočkavcom. Takto to ale nemôže ísť ďalej!! Pomôžte ochrániť zdravý morálny vývin našej mládeže a pomôžte vyhadzovačom identifikovať preukazy, ktoré boli na vstup už raz použité.

Na vstupe je daná postupnosť reťazcov (identifikátorov občianskych preukazov), v poradí ako sa nimi návštevníci preukazujú. Vašou úlohou je zistiť počet, koľko z nich sa pokúšali použiť opakovane. Číslo OP je reťazec čísel a písmen, môžu byť rôzne dlhé. Riešenie musí pracovať v optimálnej očakávanej časovej zložitosti O(N), kde N je počet čísel občianskych preukazov na vstupe. Identifikátor občianskeho preukazu môže byť ľubovoľný reťazec písmen a číslic.

Naprogramujte funkciu v nasledovnom tvare:

// spracuje cisla OP: vrati pocet najdenych duplikatov.
int vyhadzovac(char *a[], int n)
{
  // ...
}
Poznámka: Všetky potrebné operácie by ste mali implementovať vlastnými silami. Pomalšie ako optimálne lineárne riešenie nesplní časový limit v testovači.

Napr. pre čísla OP:
AA123456
BA987689
AA123123
AA312312
BB345345
AA123123
je
Pocet duplikatov: 1
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* qsort C-string comparison function */ 
int cstring_cmp (const void *a, const void *b) { 
	const char **ia = (const char **)a;
	const char **ib = (const char **)b;
	return strcmp(*ia, *ib);
} 

int porovnaj (char *a[], int n) {
	int akt=0, porovn=0;
	int dupl=0;

	for (akt = 0, porovn = akt+1; akt < n-1; akt++, porovn++) {

		if (strcmp (a[akt], a[porovn]) == 0) {
			//printf ("duplikat\n");
			dupl++;
		}

	}

	return dupl;
}

// spracuje cisla OP: vrati pocet najdenych duplikatov.
int vyhadzovac(char *a[], int n) {
 
    qsort(a, n, sizeof(char *), cstring_cmp);

	/*for (int i=0; i<n; i++) {
		printf ("%s\n", a[i]);
	}*/

	printf ("Pocet duplikatov: %d\n", porovnaj (a, n));

	return porovnaj (a, n);
}

// ukazkovy test
int main(void)
{
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