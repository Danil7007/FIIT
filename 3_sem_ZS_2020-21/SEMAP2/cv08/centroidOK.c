// uloha8-1.c -- Emma Macháčová, 4.11.2020 10:00
/*
Jakubko sa začal venovať vyrezávaniu drevených dekorácií všakovakých tvarov. Zatiaľ len začína, a tvary ktoré vyrezáva sú ploché dosky tvaru mnohouholníka s N < 1000 vrcholmi. Po vytvorení dekorácie by ju chcel zavesiť na šnúrku tak, aby zo stropu visela vodorovne. Šnúrku upevní v ťažisku klinčekom. Pri komplikovanejších tvaroch sa mu stáva, že do ťažiska nemôže klinček priklincovať pretože sa ťažisko jednoducho nenachádza vo vnútri tohto mnohouholníka (je tam vzduch).

Pomôžte Jakubkovi a pre mnohouholník na vstupe určite súradnice ťažiska.

Vstup: Štandardný vstup obsahuje zápis vyrezanej drevenej dekorácie v tvare mnohouholníka. Na prvom riadku je celé číslo N (do 1000) počet vrcholov, a nasleduje N dvojíc celých čísel: x-ová a y-ová súradnica i-teho vrcholu, pričom vrcholy sú uvedené v poradí ako idú po obvode.

Výstup: Na štandardný výstup vypíšte súradnice ťažiska mnohouholníka na vstupe, zaokrúhlené na tri desatinné miesta.

Ukážka vstupu:
8
0 0
3 0
3 3
2 3
2 1
1 1
1 3
0 3
Výstup pre ukážkový vstup:
1.500 1.357
*/

#include <stdio.h>
#include <stdlib.h> 

void stred (int nVertices) {
    double centroidX = 0, centroidY = 0;
	double det = 0, tempDet = 0;
	unsigned int j = 0, i=0;
    double* verticesX;
    double* verticesY;

    verticesX = (double*)calloc(nVertices, sizeof(double));
    verticesY = (double*)calloc(nVertices, sizeof(double));
    for (i = 0; i < nVertices; i++) {
        scanf ("%lf", &verticesX[i]);
        scanf ("%lf", &verticesY[i]);
    }

	for (i = 0; i < nVertices; i++) {
		// closed polygon
		if (i + 1 == nVertices)
			j = 0;
		else
			j = i + 1;

		// compute the determinant
		tempDet = verticesX[i] * verticesY[j] - verticesX[j]*verticesY[i];
		det += tempDet;

		centroidX += (verticesX[i] + verticesX[j])*tempDet;
		centroidY += (verticesY[i] + verticesY[j])*tempDet;
	}

	// divide by the total mass of the polygon
	centroidX /= 3*det;
	centroidY /= 3*det;

	printf ("%.3lf ", centroidX);
	printf ("%.3lf\n", centroidY);

  return;
}


int main () {
  int n;

  while (scanf ("%d", &n) > 0) {
    stred(n);
  }

  return 0;
}