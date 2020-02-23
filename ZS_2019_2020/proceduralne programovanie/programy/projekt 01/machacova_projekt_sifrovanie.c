#include <stdio.h>

int vypis_danej_dlzky(int* povodny);
int vypis_upraveny(int* upraveny);
int uprav(int* povodny, int* upraveny);
int vypis_povodny(int* povodny);
int nacitaj(int* povodny);
int c_sifra(int* upraveny);
int histogram(int* upraveny);

int main() {
	int i, vstup_prikaz, povodny[1000], upraveny[1000], * povodny_pointer, * upraveny_pointer, a;
	povodny_pointer = &povodny[0];
	upraveny_pointer = &upraveny[0];
	for (i = 0; i < 1000; ++i) {
		povodny[i] = 0;
		upraveny[i] = 0;
	}
	// switch vstup-prikaz
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
		case 'k': break;
		default: break;
		}
	} while (vstup_prikaz != 'k');

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