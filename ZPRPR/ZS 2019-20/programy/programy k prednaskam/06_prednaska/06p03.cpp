// najdenie vyskytu hodnoty v poli
#include<stdio.h>

int main() { 
	int x[] = {12,67,56,60,12,88,34,12,123};
	int hodnota, velkost, i, najdene = -1;
	velkost = sizeof(x) / sizeof(int);
	scanf("%d", &hodnota);

	i = 0;
	while (najdene < 0 && i < velkost) {  // ako najst poslednu poziciu
		if (x[i] == hodnota)
			najdene = i; 
		i++;
	}

	if (najdene != -1) 
		printf ("%d je na pozicii %d.\n", hodnota, najdene); 
	else 
		printf ("%d sa v poli nenachadza.\n", hodnota); 
	return 0; 
} 

