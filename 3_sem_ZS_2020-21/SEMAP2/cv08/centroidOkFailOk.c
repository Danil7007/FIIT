// uloha8-1.c -- Emma Macháčová, 4.11.2020 10:00

#include <stdio.h>
#include <stdlib.h> 

void stred (int nVertices)
{
	float centroidX = 0, centroidY = 0;
	float det = 0, tempDet = 0;
	unsigned int j = 0, i=0;
  float* verticesX;
  float* verticesY;

  verticesX = (float*)calloc(nVertices, sizeof(float));
  verticesY = (float*)calloc(nVertices, sizeof(float));
  for (i = 0; i < nVertices; i++) {
    scanf ("%f", &verticesX[i]);
    scanf ("%f", &verticesY[i]);
  }

	for (i = 0; i < nVertices; i++)
	{
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

	printf ("%.3f ", centroidX);
	printf ("%.3f\n", centroidY);

  return;
}


int main () {
  int n;

  while (scanf ("%d", &n) > 0) {
    stred(n);
  }

  return 0;
}