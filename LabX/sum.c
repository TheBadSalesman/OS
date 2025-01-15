#include <stdio.h>


int add(int *a, int *b, int *c) {
	return (*a + *b + *c);
}



int main(void) {
	int x, y, z, sum;

	printf("Input first integer and press Enter\n");
	scanf("%d", &x);
        printf("Input second integer and press Enter\n");
        scanf("%d", &y);
        printf("Input third integer and press Enter\n");
        scanf("%d", &z);

	sum = add(&x, &y, &z);

	printf("The sum of %d + %d + %d is: %d.\n", x, y, z, sum);



	return 0;
}
