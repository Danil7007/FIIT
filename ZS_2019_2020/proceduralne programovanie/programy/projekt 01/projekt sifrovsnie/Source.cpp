#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

int vypis_danej_dlzky(int* povodny);
int vypis_upraveny(int* upraveny);
int uprav(int* povodny, int* upraveny);
int vypis_povodny(int* povodny);
int nacitaj(int* povodny);
int c_sifra(int* upraveny);
int histogram(int* upraveny);

int prevrat(int* upraveny);
int vloz(int* upraveny);

int pomer(int* povodny);
int zmaz(int* upraveny);

int najdi(int* upraveny);


int main() {
	int i, vstup_prikaz, povodny[1000], upraveny[1000], * povodny_pointer, * upraveny_pointer, a;
	povodny_pointer = &povodny[0];
	upraveny_pointer = &upraveny[0];
	for (i = 0; i < 1000; ++i) {
		povodny[i] = 0;
		upraveny[i] = 0;
	}
	do {
		vstup_prikaz = getchar();
		switch (vstup_prikaz) {
		case 'n': a = nacitaj(povodny_pointer);
			break;
		case 'v': a = vypis_povodny(povodny_pointer);
			break;
		case 'u': a = uprav(povodny_pointer, upraveny_pointer);
			break;
		case 's': a = vypis_upraveny(upraveny_pointer);
			break;
		case 'd': a = vypis_danej_dlzky(povodny_pointer);
			break;
		case 'h': a = histogram(upraveny_pointer);
			break;
		case 'c': a = c_sifra(upraveny_pointer);
			break;
		case 'o': a = prevrat(upraveny_pointer);
			break;
		case 'z': a = vloz(upraveny_pointer);
			break;
		case 'p': a = pomer(povodny_pointer);
			break;
		case 'z': a = zmaz(upraveny_pointer);
			break;
		case 'b': a = najdi(upraveny_pointer);
			break;
		case 'k': break;
		default: break;
		}
	} while (vstup_prikaz != 'k');

	return 0;
}

int vloz(int* upraveny) {
	int dlzka = 0, retazec[10], c, i = 0, pom_pole[1000], j = 0;

	//pocitanie dlzky upraveneho pola
	do {
		dlzka += 1;
	} while (*(upraveny + dlzka) != 0);

	//retazec do pola
	do {
		c = getchar();
		if (c == ' ') {
			c = getchar();
		}
		if (c != '\n') {
			if (c >= 'A' && c <= 'Z') {
				retazec[i] = c;

				if (i >= 9) {
					//dlzka viac ako 10
					printf("Retazec nie je mozne vlozit - dlzka\n");
					return 0;
				}
				else {
					++i;
				}
			}
			else if ((c < 'A' || c > 'Z')) {
				//iba velke pismena
				printf("Retazec nie je mozne vlozit - velke pismena\n");
				return 0;
			}
		}
	} while (c != '\n');
	int dlzka_retazca = i, k = 0;

	//menej ako 1000 znakov
	if (dlzka + i + 1 > 1000) {
		printf("Retazec nie je mozne vlozit - vela znakov\n");
		return 0;
	}
	//ak nie je stred
	if (dlzka % 2 != 0) {
		printf("Retazec nie je mozne vlozit - bez stredu\n");
		return 0;
	}
	for (i = 0; i < 1000; ++i) {
		if (i < (dlzka / 2) + 1) {
			pom_pole[i] = *(upraveny + j);
			++j;
		}
		if (((i >= (dlzka / 2) + 1)) && (i < ((dlzka / 2) + 1 + dlzka_retazca))) {
			pom_pole[i] = retazec[k];
			++k;
		}
		if (i >= ((dlzka / 2) + 1 + dlzka_retazca)) {
			pom_pole[i] = *(upraveny + j);
			++j;
		}
	}
	//prepisanie pola upraveny
	i = 0;
	do {
		*(upraveny + i) = pom_pole[i];
		i++;
	} 
	while (pom_pole[i] != 0);

	printf("Retazec sa vlozil\n");

	return 0;
}

//najdi --------------------------------------------------------------------------- pisomka
int najdi(int* upraveny) {
	int j = 0, c, k, pocet_c=0, minimum_k=26, minimum_c=1000;

	scanf("%d", &c);

	if (*upraveny == NULL) {
		printf("Nie je k dispozicii upravena sprava\n");
	}

	else {
		for (k = 0; k < 26; ++k) {
			for (j = 0; j < 1000; ++j) {
				if (*(upraveny + j) >= 'A' && *(upraveny + j) <= 'Z') {
					*(upraveny + j) = *(upraveny + j) - k;
					if (*(upraveny + j) < 'A') {
						*(upraveny + j) = 'Z' - k + 1;
					}
					if (*(upraveny + j) == c); {
						++pocet_c;
					}
				}
			}
			if (pocet_c < minimum_c) {
				minimum_c = pocet_c;
				minimum_k = k;
			}
		}
	}
	k = minimum_k;
	printf("%d", k);
	return 0;
}

//zmaz ------------------------------------------------------------------ pisomka
int zmaz(int* upraveny) {
	int dlzka = 0, z, k, i = 0, pom_pole[1000], j = 0;

	if (*upraveny == NULL) {
		printf("Nie je k dispozicii upravena sprava\n");
		return 0;
	}

	//pocitanie dlzky upraveneho pola
	do {
		dlzka += 1;
	} 
	while (*(upraveny + dlzka) != 0);

	//sken cisiel
	scanf("%d %d", &z, &k);

	//nezmyslny index
	if (k < z) {
		printf("Retazec nie je mozne zmazat\n");
		return 0;
	}
	// nekryje sa so znakom
	if (z >= dlzka) {
		printf("Retazec nie je mozne zmazat\n");
		return 0;
	}
	
	for (i = 0; i < 1000; ++i) {
		if ((i < z) || (i > k)) {
			pom_pole[j] = *(upraveny + i); 
			++j;
		}
	}
	//vynulovanie
	for (i = 0; i < 1000; ++i) {
		*(upraveny + i) = 0;
	}

	//prepisanie pola upraveny
	i = 0;
	do {
		*(upraveny + i) = pom_pole[i];
		i++;
	} while (pom_pole[i] != 0);

	printf("Retazec sa zmazal\n");

	return 0;
}

int prevrat(int* upraveny) {
	int dlzka = 0, i, j = 0, prev_pole[1000];
	//pocitanie dlzky upraveneho pola
	do {
		dlzka += 1;
	} while (*(upraveny + dlzka) != 0);
	//pomocne prevratene pole
	for (i = dlzka; i >= 0; --i) {
		if (*(upraveny + i) != 0) {
			prev_pole[j] = *(upraveny + i);
			++j;
		}
	}
	i = 0;
	//prepisanie pola upraveny
	do {

		*(upraveny + i) = prev_pole[i];
		i++;
	} while (prev_pole[i] != 0);
	return 0;
}

// odsifrovanie
int c_sifra(int* upraveny) {
	int j = 0, n;
	scanf("%d", &n);
	if (n < 1 || n > 25) {
		return 0;
	}

	if (*upraveny == NULL) {
		printf("Nie je k dispozicii upravena sprava\n");
	}
	else {
		for (j = 0; j < 1000; ++j) {
			if (*(upraveny + j) >= 'A' && *(upraveny + j) <= 'Z') {
				*(upraveny + j) = *(upraveny + j) - n;
				if (*(upraveny + j) < 'A') {
					*(upraveny + j) = 'Z' - n + 1;
				}
				printf("%c", *(upraveny + j));
			}
		}
		printf("\n");
	}
	return 0;
}

//vypisanie slova zelanej dlzky 
int vypis_danej_dlzky(int* povodny) {
	int i, j = 0, k,c,poc=0;
	scanf("%d", &k);
	int slovo[1000];
	for (i = 0; i < 1000; ++i) {
		slovo[i] = 0;
	}
	if (k < 1 || k > 100) {
		return 0;
	}
	//k -= 1;
	if (*povodny == NULL) {
		printf("Sprava nie je nacitana\n");
	}
	else {
		/*for (i = 0; i < 1000; ++i) {
			//ak nie je biely znak alebo enter
			if ((*(povodny + i) != 32) && (*(povodny + i) != 10)) {
				slovo[j] = *(povodny + i);
				++j;
			}
			//ak je biely znak a dlzka citaneho slova > 1
			else if ((*(povodny + i) == 32 || *(povodny + i) == 10) && j > 0) {
				//ak je vyhovujuca dlzka
				if (j + 1 == k) {
					for (j = 0; j < k; ++j) {
						printf("%c", slovo[j]);
						slovo[j] = 0;
					}
					j = 0;
					printf("\n");
				}
			}
		}
		printf("\n");
	*/
		for (i = 0; i<1000; ++i) {
			if (*(povodny + i) != ' ' && *(povodny + i) != '\0' && *(povodny + i) != 0) {
				slovo[j] = *(povodny + i);
				++j;
				++poc;
			}
			if (*(povodny + i) == ' ' || *(povodny + i) == '\0') {
				if (poc == k) {
					for (j = 0; j < k; ++j) {
						printf("%c", slovo[j]);
						slovo[j] = 0;
					}
					printf("\n");
				}
				
				j = 0;
				poc = 0;
			}
		}
	}
	return 0;
}

// vypisanie upraveneho pola
int vypis_upraveny(int* upraveny) {
	int i;

	if (*upraveny == NULL) {
		printf("Nie je k dispozicii upravena sprava\n");
	}
	else {
		for (i = 0; i < 1000; ++i) {
			printf("%c", *(upraveny + i));
		}
		printf("\n");
	}

	return 0;
}

// uprava povodneho pola
int uprav(int* povodny, int* upraveny) {
	int i, j = 0;

	if (*povodny == NULL) {
		printf("Sprava nie je nacitana\n");
	}
	else {
		for (i = 0; i < 1000; ++i) {
			if ((*(povodny + i) >= 'A' && *(povodny + i) <= 'Z') || (*(povodny + i) >= 'a' && *(povodny + i) <= 'z')) {
				if (*(povodny + i) >= 'a' && *(povodny + i) <= 'z') {
					*(upraveny + j) = *(povodny + i) - 32;
				}
				else {
					*(upraveny + j) = *(povodny + i);
				}
				++j;
			}
		}
	}

	return 0;
}

// pomer ------------------------------------------------------------------------- pisomka
int pomer(int* povodny) {
	int i, pocet_malych,pocet_velkych;

	if (*povodny == NULL) {
		printf("Sprava nie je nacitana\n");
	}
	else {
		for (i = 0; i < 1000; ++i) {
			if ((*(povodny + i) >= 'A' && *(povodny + i) <= 'Z') || (*(povodny + i) >= 'a' && *(povodny + i) <= 'z')) {
				if (*(povodny + i) >= 'a' && *(povodny + i) <= 'z') {
					++pocet_malych;
				}
				else {
					++pocet_velkych;
				}
			}
		}
		printf("%d:%d\n", pocet_velkych, pocet_malych);
	}
	return 0;
}

// vypisanie povodneho pola
int vypis_povodny(int* povodny) {
	int i;

	if (*povodny == NULL) {
		printf("Sprava nie je nacitana\n");
	}
	else {
		for (i = 0; i < 1000; ++i) {
			printf("%c", *(povodny + i));
		}
		printf("\n");
	}

	return 0;
}

// nacitanie do pola povodny
int nacitaj(int* povodny) {
	FILE* subor;
	int c, i = 0;

	if ((subor = fopen("sifra.txt", "r")) == NULL) {
		printf("Spravu sa nepodarilo nacitat\n");
		return 0;
	}

	while ((c = getc(subor)) != EOF) {
		if (i < 1000) {
			*(povodny + i) = c;
			++i;
		}
		else {
			break;
		}
	}

	if (fclose(subor) == EOF) {
		printf("Subor sa nepodarilo zatvorit\n");
	}

	return 0;
}

//vypis histogramu
int histogram(int* upraveny) {
	int i = 0, j, pocet = 0, pocet_pismen[26];
	double percenta[26], max = 0;
	if (*upraveny == NULL) {
		printf("Nie je k dispozicii upravena sprava\n");
		return 0;
	}

	for (i = 0; i < 26; ++i) {
		pocet_pismen[i] = 0;
	}
	i = 0;
	do {
		j = *(upraveny + i) - 65;
		if (j + 65 >= 'A' && j + 65 <= 'Z') {
			pocet_pismen[j]++;
			pocet++;
		}
		++i;
	} while (*(upraveny + i) >= 'A' && *(upraveny + i) <= 'Z');

	for (i = 0; i < 26; ++i) {
		percenta[i] = pocet_pismen[i];
		percenta[i] /= pocet;
		percenta[i] *= 100;
		if (percenta[i] > max) {
			max = percenta[i];
		}

	}

	//>90%
	if (max >= 90) {
		for (i = 0; i < 26; ++i) {
			if (percenta[i] > 90) {
				printf("* ");
			}
			else {
				printf("  ");
			}
		}
		printf("\n");
	}
	//>80%
	if (max >= 80) {
		for (i = 0; i < 26; ++i) {
			if (percenta[i] > 80) {
				printf("* ");
			}
			else {
				printf("  ");
			}
		}
		printf("\n");
	}	//>70%
	if (max >= 70) {
		for (i = 0; i < 26; ++i) {
			if (percenta[i] > 70) {
				printf("* ");
			}
			else {
				printf("  ");
			}
		}
		printf("\n");
	}
	//>60%
	if (max >= 60) {
		for (i = 0; i < 26; ++i) {
			if (percenta[i] > 60) {
				printf("* ");
			}
			else {
				printf("  ");
			}
		}
		printf("\n");
	}
	//>50%
	if (max >= 50) {
		for (i = 0; i < 26; ++i) {
			if (percenta[i] > 50) {
				printf("* ");
			}
			else {
				printf("  ");
			}
		}
		printf("\n");
	}
	//>40%
	if (max >= 40) {
		for (i = 0; i < 26; ++i) {
			if (percenta[i] > 40) {
				printf("* ");
			}
			else {
				printf("  ");
			}
		}
		printf("\n");
	}
	//>30%
	if (max >= 30) {
		for (i = 0; i < 26; ++i) {
			if (percenta[i] > 30) {
				printf("* ");
			}
			else {
				printf("  ");
			}
		}
		printf("\n");
	}
	//>20%
	if (max >= 20) {
		for (i = 0; i < 26; ++i) {
			if (percenta[i] > 20) {
				printf("* ");
			}
			else {
				printf("  ");
			}
		}
		printf("\n");
	}
	//>10%
	if (max >= 10) {
		for (i = 0; i < 26; ++i) {
			if (percenta[i] > 10) {
				printf("* ");
			}
			else {
				printf("  ");
			}
		}
		printf("\n");
	}
	//>0%
	if (max >= 0) {
		for (i = 0; i < 26; ++i) {
			if (percenta[i] > 0) {
				printf("* ");
			}
			else {
				printf("  ");
			}
		}
		printf("\n");
	}
	//pismena
	for (i = 0; i < 26; ++i) {
		printf("%c ", i + 65);
	}
	printf("\n");

	return 0;
}
