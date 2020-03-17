// funkcia na vymenu ukazovatelov - pouzitie generickeho ukazovatela
#include <stdio.h>

void vymen(void **p_x, void **p_y)
{
    void *p;

    p = *p_x;
    *p_x = *p_y;
    *p_y = p;
} 


int main() {
	int i = 1, *p_i = &i, j = 2, *p_j = &j;
	
	vymen((void **) &p_i, (void **) &p_j);
	printf("Vymenene ukazovatele na cisla: %d, %d\n", *p_i, *p_j);

	char c = 'a', *p_c = &c;
	char d = 'b', *p_d = &d;	
	
	vymen((void **) &p_c, (void **) &p_d);
	printf("Vymenene ukazovatele na znaky: %c, %c\n", *p_c, *p_d);
	return 0;
}
