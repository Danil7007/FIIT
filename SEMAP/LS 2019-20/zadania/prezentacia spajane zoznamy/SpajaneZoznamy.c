#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

// deklaracia struktury kniha a jej parametrov
typedef struct kniha {
	int poradie_zaznamu;
	char signatura[100];
	long long isbn; // long nestacil a int uz vobec
	// mohol by byt string teoreticky ak vieme ze isbn ma 13 znakov
	char nazov[100];
	char autori[100];
	int datum;
	int preukaz;
	struct kniha* dalsia;
} KNIHA;

// funkcie, ktore sa budu pouzivat
// vsetky, v ktorych sa moze zmenit nieco o zaznamoch (nacitanie novych, mazanie, pridavanie...) musia vracat ukazovatel na
// realne aktualne funkcny prvy zaznam - head, aby dalsie funkcie pracovali s up-to-date udajmi
KNIHA* nacitaj (KNIHA* head); // nacitanie
int skontroluj (KNIHA* head); // kontrola, ci je nieco nacitane
void vypis (KNIHA* head); // vypis zoznamu
KNIHA* uvolni (KNIHA* head); // uvolnenie pamate
KNIHA* pridaj (KNIHA* head); // pridanie zaznamu

// main funkcia
void main () {
	KNIHA* head = NULL; // head node zoznamu knih
	char pokyn, enter;	// vstup od pouzivatela

	// cyklus na nacitavanie prikazov z klavesnice od pouzivatela
	do {
		// nacitaj prikaz
		if (scanf ("%c%c", &pokyn, &enter) != 1) continue; // aj enter
		// slo by to spravit aj inym sposobom, ako "%c%*c", alebo " %c", aby sa nenacitavalo do premennej ktora sa nepouzije,
		// ale uz som to mala spravene tymto sposobom

		// ak n => nacitaj
		if (pokyn == 'n') {
			head = nacitaj (head); // funkcia vrati aktualizovany zaciatok
		}
		// ak v => vypis
		if (pokyn == 'v') {
			vypis (head);
		}
		// ak p => pridaj
		if (pokyn == 'p') {
			head = pridaj (head);
		}
		// ak k => koniec
		if (pokyn == 'k') {
			head = uvolni (head);
		}

	} while (pokyn != 'k');

	return;
}

// tato funkcia nacitava zaznamy o knihach zo subora kniznica.txt
// je typu KNIHA*, pretoze vracia ukazovatel na prvy zaznam, ktory tiez dostava ako argument
KNIHA* nacitaj (KNIHA* head) {

	KNIHA* predchadzajuca = NULL; // ukazovatel na predchadzajucu knihu - na posuvanie zaznamov
	FILE* subor = fopen("kniznica.txt", "r"); // subor, z ktoreho su citane zaznamy
	char pokracuj[4], enter; // pokracuj sluzi na nacitanie --- zo subora, a enter na citanie entrov \n
	int pocet_knih = 0; // sluzi na cislovanie zaznamv

	if (subor == NULL) {
		printf ("ZAZNAMY NEBOLI NACITANE\n"); // ak sa subor nepodarilo otvorit
		return head;
	}

	if (skontroluj (head)) { // funkcia skontroluj vracia 0 alebo 1 podla toho, ci boli nacitane filmy
		head = uvolni (head); // ak uz boli nacitane nejake filmy uvolni pamat
	}

	// kym su v subore vstupy na precitanie (---)
	while (fscanf (subor, "%s", pokracuj) > 0) {
		fscanf (subor, "%c", &enter); // nacitanie \n ktory nasleduje

		// vytvorenie samostatneho nespojeneho uzlu pre knihu
		KNIHA* temp = malloc(sizeof(struct kniha));
		assert (temp != NULL); // okrem chybnej alokacie, -> exit  
		temp->dalsia = NULL; // neukazuje na ziadnu dalsiu knihu 
		// (je dolezite aby posledny zaznam ukazoval na NULL lebo inak vypis padne)

		pocet_knih++; // kazdou dalsou vytvorenou knihou sa zvysi pocet knih

		// nacitanie jednotlivych hodnot - informacie idu v stanovenom poradi, staci nacitat
		temp->poradie_zaznamu = pocet_knih; // pocet knih sme si vypocitali sami
		fscanf (subor, "%s%c", temp->signatura, &enter); // treba nacitat aj enter lebo by ho potom bral dalsi scanf
		fscanf (subor, "%lld%c", &temp->isbn, &enter);	// a myslelo by si to ze to ma ovela viac vstupov a neslo by to
		fgets (temp->nazov, 100, subor); // cely nazov aj s medzerami, nacita aj enter 
		// tento enter by sa dal odstranit kebyze dalej chceme napr. porovnavat nazov knihy 
		// so vstupom od pouzivatela alebo pod., kebyze chceme knihy mazat podla nazvu...
		// ale v tomto pripade je to zbytocne, lebo ajtak kazdy vypis ma byt ukonceny \n
		fgets (temp->autori, 100, subor);
		fscanf (subor, "%d%c", &temp->datum, &enter);
		fscanf (subor, "%d%c", &temp->preukaz, &enter);


		// spojenie do zoznamu
		if (head == NULL) { // ak nebolo este nic nacitane a toto je prva kniha
			head = temp; // to co sme nacitali ako prve bude head
			predchadzajuca = temp; // a zatial aj predchadzajuca, vyuzivat sa bude na svoj ucel az pri dalsich zaznamoch
		}
		else { // ak uz zoznam existuje pripojime knihu na koniec zoznamu
			predchadzajuca->dalsia = temp; // v pripade druheho zaznamu teda head ukazuje na prave nacitanu knihu
			predchadzajuca = temp; // a nacitana kniha sa akoby posunie na miesto predchadzanucej, 
			// bude sa k nej pripajat (ak existuje) dalsi temp 
		}
	}

	printf ("NACITALO SA %d ZAZNAMOV\n", pocet_knih); // podla zadania vypiseme kolko knih sa nacitalo
	fclose (subor); // zavrieme subor
	return head; // funkcia vrati ukazovatel na prvy zaznam
}

// kontroluje ci uz bli nacitane nejake zaznamy a vracia podla toho bud 0 alebo 1
// a.k.a. snaha o dekompoziciu programu
int skontroluj (KNIHA* head) {
	if (head == NULL) {
		return 0; // neboli nacitane filmy
	}
	else {
		return 1; // boli nacitane filmy
	}
}

// rekurzivna funkcia na vypis zaznamov
void vypis (KNIHA* head) {

	if (!(skontroluj (head))) {
		return; // ak nie je co vypisat
	}

	// vypis dat
	printf("%d.\n", head->poradie_zaznamu);
	printf("SIGNATURA: %s\n", head->signatura);
	printf("ISBN: %lld\n", head->isbn);
	printf("NAZOV: %s", head->nazov);
	printf("AUTORI: %s", head->autori);
	printf("DATUM: %d\n", head->datum);
	printf("PREUKAZ: %d\n", head->preukaz);

	// ak nasleduje dallsia kniha
	if (head->dalsia != NULL) {
		vypis (head->dalsia); // sprav vyis aj s dalsou knihou
	}
	// volba nazvat parameter tejto funkcie head moze byt mozno trochu matuca 
	// kedze nie vzdy naozaj predstavuje prvy zaznam, nakolko sa funkcia posuva zoznamom

	return;
}

// uvolnenie alokovanej pamate pre zaznamy knih
KNIHA* uvolni (KNIHA* head) {
	KNIHA* temp; // potrebujeme temp aby sme sa vedeli posuvat po zaznamoch

	while (head != NULL) {
		temp = head;
		head = head->dalsia;
		free (temp); // postupne od zaciatku uvolnime vsetky uzly
	}
	head = NULL;
	return head;
	// tato funkcia by nemusela vraciat nic ak by bola volana len pri ukoncovani programu,
	// ale kedze treba uvolnit pamat aj ak pri nacitani uz zaznamy existuju
	// potrebujeme poznat head
}

// pridava individualne zaznamy (zo vstupu od pouzivatela) na urcene miesto C1
KNIHA* pridaj (KNIHA* head) {
	int c1; // pozicia kam sa ma zaznam pridat
	int prazdny=0; // urcuje ci pridavane novy zaznam do prazdneho zoznamu alebo pridavame do uz existujuceho
	int najdeny=0; // urcuje, ci C1 reprezentuje existujucu poziciu v zozname
	char enter; // pre nacitanie \n
	KNIHA* prechadzanie = NULL; // na prechadzanie cez zaznamy
	KNIHA* posledna = NULL; // posledny existujuci zaznam v zozname

	scanf ("%d", &c1);
	assert (c1 > 0); // ma byt vacsie ako 0 (lebo zaznamy pocitame od prveho)

	if (!(skontroluj (head))) {
		prazdny = 1; // ak nie je nic nacitane
	}

	// na najdenie uzlu s poradim == C1 a uzlu pred nim, 
	// alebo na najdenie celkovo posledneho uzlu v zozname v pripade ze pozicia C1 neexistuje
	if (prazdny == 0) { // ak mame nacitane polozky
		prechadzanie = head; // prejdeme zoznam od zaciatku
		// kym nenajdeme zelanu poziciu alebo kym neprideme na koniec zoznamu
		while (prechadzanie != NULL) {
			// v pripade ze prejdeme cely zoznam a nenajdeme zhodu, posledna drzi adresu posledneho ne-NULL-oveho zaznamu
			// ak zhodu najdeme, posledna ukazuje na uzol pred tym, kde je najdena zhoda
			if (prechadzanie->poradie_zaznamu != c1) {
				posledna = prechadzanie; 
			}		
			else { // ak najdeme zelany zaznam
				najdeny = 1;
				break; 
			}
			prechadzanie = prechadzanie->dalsia; // posuvanie sa zoznamom
		}
	}

	// novy uzol
	KNIHA* nova = malloc(sizeof(struct kniha));
	assert (nova != NULL);

	// nacitanie jednotlivych hodnot
	scanf ("%s%c", nova->signatura, &enter);
	scanf ("%lld%c", &nova->isbn, &enter);
	fgets (nova->nazov, 100, stdin); // cely nazov aj s medzerami
	fgets (nova->autori, 100, stdin);
	scanf ("%d%c", &nova->datum, &enter);
	scanf ("%d%c", &nova->preukaz, &enter);

	// MOZNOST A - ak je to prvy a jediny zaznam
	if (prazdny == 1) {
		nova->poradie_zaznamu = 1;
		nova->dalsia = NULL;
		return head = nova;
	}

	// MOZNOST B - ak ideme pridat na koniec zoznamu
	else if (najdeny == 0) {
		nova->poradie_zaznamu = (posledna->poradie_zaznamu) + 1; // v poradi nasleduje za poslednou knihou
		nova->dalsia = NULL; // dalsi zaznam neexistuje
		posledna->dalsia = nova; // posledna ukazuje na novu
		return head;
	}

	// MOZNOST C - ideme nahradit existujuci uzol 
	// ak sme C1 nasli prechadzanie  dzri hodnotu zaznamu s poradim == C1 a posledna toho zaznamu pred nim
	else {
		nova->poradie_zaznamu = c1; // poradie noveho zaznamu

		// treba vsetkym dalsim kniham posunut poradie
		KNIHA* temp = prechadzanie;
		while (temp != NULL) {
			temp->poradie_zaznamu += 1;
			temp = temp->dalsia;
		}
		
		// AK NAHRADZAME POZICIU UZLU HEAD
		if (prechadzanie == head) {
			nova->dalsia = head; // ukazuje na tu, co mala poradie C1
			head = nova;
		}
		// AK NAHRADZAME KNIHU NIEKDE DALEJ V ZOZNAME
		else {
			nova->dalsia = posledna->dalsia; // nova ukazuje na tu, co mala poradie C1
			posledna->dalsia = nova; // a nahradi jej miesto
		}
		

		return head; // vrati ukazovatel na prvy zaznam
	}
}