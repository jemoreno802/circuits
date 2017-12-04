#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *findIndices(int *numbers, int target);

int *findIndices(int *numbers, int target) {
	for (int i = 0; i < sizeof(numbers); i++) {
		for (int j = 0; j < sizeof(numbers); j++) {
			if (numbers[i] + numbers[j] == target) {
				int *indices = malloc(2 * sizeof(int));
				indices[0] = i;
				indices[1] = j;
				return indices;
			}
		}
	}
	return NULL;
}

int main(int argc, char *argv[]) {
	printf("HI\n");
	printf("Matt's line\n");
	printf("Matt's second line\n");

	int numbers[7] = {1, 3, 5, 7, 9, 2, 8};

	printf("Indices= %d, %d\n", findIndices(numbers, 8)[0], findIndices(numbers, 8)[1]);
}
