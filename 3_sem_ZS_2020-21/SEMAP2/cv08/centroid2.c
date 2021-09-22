// uloha8-1.c -- Emma Macháčová, 4.11.2020 10:00

#include <stdio.h>
#include <stdlib.h> 



int Stred(int vertexCount)
{
    int i=0;
    double stredX=0.0, stredY=0.0;
    double signedArea = 0.0;
    double x0 = 0.0; // Current vertex X
    double y0 = 0.0; // Current vertex Y
    double x1 = 0.0; // Next vertex X
    double y1 = 0.0; // Next vertex Y
    double a = 0.0;  // Partial signed area
    double* bodyX;
    double* bodyY;

    bodyX = (double*)calloc(vertexCount, sizeof(double));
    bodyY = (double*)calloc(vertexCount, sizeof(double));
    for (i=0; i<vertexCount; i++) {
      scanf ("%lf", &bodyX[i]);
      scanf ("%lf", &bodyY[i]);
    }

    // For all vertices except last
    for (i=0; i<vertexCount-1; ++i)
    {
        x0 = bodyX[i];
        y0 = bodyY[i];
        x1 = bodyX[i+1];
        y1 = bodyY[i+1];
        a = x0*y1 - x1*y0;
        signedArea += a;
        stredX += (x0 + x1)*a;
        stredY += (y0 + y1)*a;
    }

    // Do last vertex separately to avoid performing an expensive
    // modulus operation in each iteration.
    x0 = bodyX[i];
    y0 = bodyY[i];
    x1 = bodyX[i+1];
    y1 = bodyY[i+1];
    a = x0*y1 - x1*y0;
    signedArea += a;
    stredX += (x0 + x1)*a;
    stredY += (y0 + y1)*a;

    signedArea *= 0.5;
    stredX /= (6.0*signedArea);
    stredY /= (6.0*signedArea);

    printf ("%.3lf %.3lf", stredX, stredY);
    return 0;
}

int main() {
  int n;

  while (scanf ("%d", &n) > 0) {
    Stred(n);
  }
  return 0;
}