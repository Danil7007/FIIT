// zliezanie kopca - najdenie cesty v mape (2D staticke pole)
// najdeme policko s najvyssou vyskou
// budeme hladat cestu (4-mi smermi) tak, aby sa robili co najmensie skoky
#include <stdio.h>
#include <string.h>
#define SUBOR "kopec.txt"
#define N 12

// nacitanie obsahu dvojrozmerneho pola zo suboru
int nacitaj_mapu(int mapa[][N]) {
	int i=0, j=0;
	char riadok[100];
	char *r;
	FILE *f;
	f = fopen(SUBOR, "r");
	while(i < N && fgets(riadok, 100, f)) {
		j = 0;
		r = riadok;
		while(j < N && r != NULL && sscanf(r, "%d", &mapa[i][j]) == 1) {
			//printf("%d %d: %d\n", i, j, mapa[i][j]);
			r = strchr(r, ' ');
			if(r != NULL) r++;
			j++;
		}
		i++;
	}	
	if (j != i) return 0;
	else return i;
}

// najdenie maximalneho prvku: vratenie hodnot cez argumenty
void najdi_kopec(int mapa[][N], int n, int *ki, int *kj) {
	int i, j;
	*ki = *kj = 0;
	for(i=0; i<n; i++) 
		for(j=0; j<n; j++) 
			if(mapa[i][j] > mapa[*ki][*kj]) {
				*ki = i;
				*kj = j;
				//printf("i: %d, j: %d, mapa: %d\n", *ki, *kj, mapa[*ki][*kj]);
			}	
}

// hladanie v vypis cesty, kde sa robia lokalne o najmensie vyskove rozdiely
void zidi_kopec(int mapa[][N], int n, int ki, int kj) {
	int i, j, max;
	while (ki != 0 && ki != n-1 && kj != 0 && kj != n-1) {  
		max = 0;
		// sever
		if(ki-1 >=0 && mapa[ki-1][kj] > max && mapa[ki-1][kj] < mapa[ki][kj]) {
			i = ki-1;
			j = kj;
			max = mapa[i][j];
		}
		// vychod
		if(kj+1 <n && mapa[ki][kj+1] > max && mapa[ki][kj+1] < mapa[ki][kj]) {
			i = ki;
			j = kj+1;
			max = mapa[i][j];
		}
		// juh
		if(ki+1 <n && mapa[ki+1][kj] > max && mapa[ki+1][kj] < mapa[ki][kj]) {
			i = ki+1;
			j = kj;
			max = mapa[i][j];
		}
		// zapad
		if(kj-1 >=0 && mapa[ki][kj-1] > max && mapa[ki][kj-1] < mapa[ki][kj]) {
			i = ki;
			j = kj-1;
			max = mapa[i][j];
		}
		printf("i: %d, j: %d, vyska: %d\n", i, j, max);
		ki = i;
		kj = j;
	}
}

// hladanie v vypis cesty, kde sa robia lokalne o najmensie vyskove rozdiely
// rekurzivna verzia
void zidi_kopec_rek(int mapa[][N], int n, int ki, int kj) {
	int i, j, max;
	if (ki != 0 && ki != n-1 && kj != 0 && kj != n-1) {  
		max = 0;
		// sever
		if(ki-1 >=0 && mapa[ki-1][kj] > max && mapa[ki-1][kj] < mapa[ki][kj]) {
			i = ki-1;
			j = kj;
			max = mapa[i][j];
		}
		// vychod
		if(kj+1 <n && mapa[ki][kj+1] > max && mapa[ki][kj+1] < mapa[ki][kj]) {
			i = ki;
			j = kj+1;
			max = mapa[i][j];
		}
		// juh
		if(ki+1 <n && mapa[ki+1][kj] > max && mapa[ki+1][kj] < mapa[ki][kj]) {
			i = ki+1;
			j = kj;
			max = mapa[i][j];
		}
		// zapad
		if(kj-1 >=0 && mapa[ki][kj-1] > max && mapa[ki][kj-1] < mapa[ki][kj]) {
			i = ki;
			j = kj-1;
			max = mapa[i][j];
		}
		printf("i: %d, j: %d, vyska: %d\n", i, j, max);
		zidi_kopec_rek(mapa, n, i, j);
	}
}

int main() {
	
	int mapa[N][N], n;
	int ki, kj;
	
	n = nacitaj_mapu(mapa);
	printf("rozmer stvorcovej mapy: %d\n", n);
	najdi_kopec(mapa, n, &ki, &kj);
	printf("suradnice kopca: %d, %d\n", ki, kj);
	zidi_kopec(mapa, n, ki, kj);
	printf("rekurzivne:\n");
	zidi_kopec_rek(mapa, n, ki, kj);

	return 0;
}

