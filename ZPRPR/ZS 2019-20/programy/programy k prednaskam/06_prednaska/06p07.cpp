// program zisti pocet neopakujucich sa prvko pola
#include <stdio.h> 


int pocet_neopakujucich(int cisla[], int velkost);

int main() { 
	int cisla[] = {3, 4, 3, 4, 6, 3, 7, 8, 8, 0, -3}; 
	int velkost = sizeof(cisla) / sizeof(int);
	
	printf("Pocet neopakujucich sa prvkov: %d \n", pocet_neopakujucich(cisla, velkost)); 
	return 0; 
} 

int pocet_neopakujucich(int cisla[], int velkost) {
	int i, j, pocet = 0;
	
	for(i=0; i<velkost; i++) {
		for(j=0; j<velkost; j++) 	// ktore cisla nezapocitame, ak pojdeme od i
			if(i!=j && cisla[i] == cisla[j])
				break;
		if(j==velkost)
			pocet++;
	}
	return pocet;
}
