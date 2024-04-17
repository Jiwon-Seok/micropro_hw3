#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Rand_seq(int* arr, int n);
void InsertionSort_C(int* arr, int n);
void InsertionSort_ASM(int* arr, int n);

int main(int argc, char* argv[]) {

	srand(time(NULL)); // Seed for random number generation

	int n;
	int i = 0;
	double start_C, end_C, time_C;
	double start_ASM, end_ASM, time_ASM;

	n = atoi(argv[1]);
	int* arr = (int*)malloc(sizeof(int) * n); // memory allocation for arr
	int* sorted_arr_C = (int*)malloc(sizeof(int) * n);
	int* sorted_arr_ASM = (int*)malloc(sizeof(int) * n);

	Rand_seq(arr, n);

	for (i = 0;i < n;i++) {
		sorted_arr_C[i] = arr[i];
		sorted_arr_ASM[i] = arr[i];
	}

	if (n <= 20) {
		printf("Before sort     : [ ");
		for (i = 0;i < n;i++) {
			printf("%d ", arr[i]);
		}
		printf("]\n");
	}

	start_C = (double)clock() / CLOCKS_PER_SEC;
	InsertionSort_C(sorted_arr_C, n);
	end_C = (double)clock() / CLOCKS_PER_SEC;
	time_C = end_C - start_C;

	/*
	start_ASM = (double)clock() / CLOCKS_PER_SEC;
	InsertionSort_ASM(sorted_arr_ASM, 0, n - 1, n);
	end_ASM = (double)clock() / CLOCKS_PER_SEC;
	time_ASM = end_ASM - start_ASM;
	*/

	if (n <= 20) {
		printf("After sort   (C): [ ");
		for (i = 0;i < n;i++) {
			printf("%d ", sorted_arr_C[i]);
		}
		printf("]\n");

		/*
		printf("After sort (ASM): [ ");
		for (i = 0;i < n;i++) {
			printf("%d ", arr[i]);
		}
		printf("]\n");
		*/
	}

	printf("Execution Time   (C): %.6lf[s]\n", time_C);
	//printf("Execution Time (ASM): %.6lf[s]\n", time_ASM);

	free(arr);
	free(sorted_arr_C);
	free(sorted_arr_ASM);
}

// Generate a random sequence of integers
void Rand_seq(int* arr, int n) {
	int random;
	int temp;
	int i = 0;

	for (i = 0;i < n;i++) {
		arr[i] = i + 1;
	}

	// Shuffle the array
	for (i = 0;i < n;i++) {
		random = rand() % n;
		temp = arr[i];
		arr[i] = arr[random];
		arr[random] = temp;
	}
}

void InsertionSort_C(int* arr, int n) {
	int i, j, v;
	for (i = 1;i <= n - 1;i++) {
		v = arr[i];
		j = i;
		while (arr[j - 1] > v && j >= 1) {
			arr[j] = arr[j - 1];
			j--;
		}
		arr[j] = v;
	}
}
