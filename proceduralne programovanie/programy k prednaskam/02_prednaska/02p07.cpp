// specialne operatory
#include <stdio.h>

int main() 
{
	int i = 4, j = 2, k = 0;
	printf("povodne: i: %d j: %d k: %d\n", i, j, k);
	
	i++;
	//++i;
	//k = 5 * (j + 1);
	//k = 5 * ++j;
	//k = 5 * j++;
	//i *= 5 * j--;		// to iste ako i = i * (5 * j--);
	//k += --j;			// to iste ako k = k + --j;
	printf("zmenene: i: %d j: %d k: %d\n", i, j, k);
	
	return 0;
}
