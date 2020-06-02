// v poli znakov najst najdlhsiu postupnost opakujucich sa znakov
#include <stdio.h>
#define N 100

int najdlhsieRovnake(char pole[], int n);

int main() {
	char pole[N];
	int c, n = 0;
	
	while((c=getchar()) != '\n' && c != EOF && n<100) {
		pole[n++] = c;
	}
	
	printf("Dlzka najdlhsieho useku rovnakych pismen: %d\n", 
		najdlhsieRovnake(pole, n));
	
	return 0;
}

int najdlhsieRovnake(char pole[], int n) {
	int i = 0, j, max = 1;
	
	while(i<n) {
		j=i+1;
		while(j<n && pole[j] == pole[i])
			j++;
		if(j-i > max)
			max = j-i;
		i = j;
	}
	return max;	
}

