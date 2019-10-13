// break a continue vo for cykle
#include <stdio.h>

int main() {
	int i;

	for (i=5; i<=10; i=i+1) {
		//if(i == 8)
		//   break;
		printf("prvy for - i: %d\n", i);
	}

	putchar('\n');
	for (i=5; i<=10; i=i+1) {
		//if(i == 8)
		//   continue;
		printf("druhy for - i: %d\n", i);
	}
	return 0;
}


