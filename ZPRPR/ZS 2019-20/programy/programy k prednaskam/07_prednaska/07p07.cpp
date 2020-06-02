// vypis velkosti roznych smernikov a typov
#include <stdio.h>

int main() {
	char* ch;
	int* in;
	float* flt;
	double* doub;
	printf("Velkost v bytoch: %u", sizeof(ch));
	printf("\nVelkost v bytoch: %u", sizeof(in));
	printf("\nVelkost v bytoch: %u", sizeof(flt));
	printf("\nVelkost v bytoch: %u", sizeof(doub));
	
	printf("\n\nVelkost pre znak: %u ",sizeof(char));
	printf("\nVelkost pre int: %u ",sizeof(int));
	printf("\nVelkost pre float: %u ",sizeof(float));
	printf("\nVelkost pre double: %u ",sizeof(double));
	
	return 0;
}
