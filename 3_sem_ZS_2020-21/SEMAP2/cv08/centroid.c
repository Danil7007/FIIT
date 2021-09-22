// uloha8-1.c -- Emma Macháčová, 4.11.2020 10:00

// C++ program to implement the  
// above approach 
  
#include <stdio.h>
#include <stdlib.h>
  
int find_Centroid (int n) { 
    double ansX=0, ansY=0;
    int* poleX;
    int* poleY;  
    
    double signedArea = 0; 
    
    poleX = (int*)calloc(n, sizeof(int));
    poleY = (int*)calloc(n, sizeof(int));

    for (int i=0; i<n; i++) {
      scanf("%d", &poleX[i]);
      scanf("%d", &poleY[i]);
    }

    // For all vertices 
    for (int i = 0; i < n; i++) { 
          
        double x0 = poleX[i]; 
        double y0 = poleY[i]; 

        double x1 = poleX[i+1] % n;
        double y1 = poleY[i+1] % n;
                              
        // Calculate value of A 
        // using shoelace formula 
        double A = (x0 * y1) - (x1 * y0); 
        signedArea += A; 
          
        // Calculating coordinates of 
        // centroid of polygon 
        ansX += (x0 + x1) * A; 
        ansY += (y0 + y1) * A; 
    } 
  
    signedArea *= 0.5; 
    ansX = (ansX) / (6 * signedArea); 
    ansY = (ansY) / (6 * signedArea); 
  
    printf ("%.3lf %.3lf\n", ansX, ansY);
    free(poleX);
    free(poleY);
    return 0;
} 
  


int main() { 
  int n;

  while (scanf("%d", &n) > 0) {
    find_Centroid(n);
  }

  return 0; 
} 