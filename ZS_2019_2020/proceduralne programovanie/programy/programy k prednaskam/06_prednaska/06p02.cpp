// vypise najvacsi a druhy najvacsi prvok pola
#include <stdio.h> 

int main() { 
	int cisla[10] = {101, 11, 3, 4, 50, 69, 7, 8, 9, 0}; 
	int i, max, max2; 
	
	// inicializacia premennych max, max2
	if(cisla[0] > cisla[1]) { 
		max = cisla[0]; 
		max2 = cisla[1]; 
	} 
	else { 
		max = cisla[1]; 
		max2 = cisla[0]; 
	} 
	
	for(i = 2; i < 10; i++) { 
		if(max < cisla[i]) { 
			max2 = max; 
			max = cisla[i]; 
		} else if(max2 < cisla[i]) { 
			max2 = cisla[i]; 
		} 
	} 
	
	printf("maximalny prvok: %d \ndruhy maximalny prvok: %d \n", max, max2); 
	return 0; 
} 

