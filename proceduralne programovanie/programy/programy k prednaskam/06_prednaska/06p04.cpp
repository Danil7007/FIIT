// najdenie vsetkych vyskytov prvku v poli
#include<stdio.h>

int main() { 
	int x[] = {12,67,56,60,12,88,34,12,123};
	int hodnota, velkost, i, najdene = -1;
	scanf("%d", &hodnota);
	velkost = sizeof(x) / sizeof(int);

	for(i=0; i<velkost; i++) {
		if(x[i] == hodnota) 
			if(najdene == -1) {		// vypis prveho najdeneho vyskytu
				printf("%d je na pozicii %d", hodnota, i);
				najdene = 1;		// vypis ostatnych vyskytov
			}
		else 
			printf(", %d", i);
	}   

	if (najdene == -1) 
		printf("%d sa v poli nenachadza.\n", hodnota); 
	else
		printf("\n");
	return 0; 
} 

