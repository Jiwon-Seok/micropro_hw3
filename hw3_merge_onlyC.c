#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Rand_seq(int* arr, int n);
void MergeSort_C(int* arr, int l, int r);
void merge_C(int* arr, int l, int m, int r);
void MergeSort_ASM(int* arr, int l, int r);
void merge_ASM(int* arr, int l, int m, int r);

int main(int argc, char* argv[]) {

	srand(time(NULL)); // Seed for random number generation

	int n;
	int i = 0;
	double start_C, end_C, time_C;
	double start_ASM, end_ASM, time_ASM;

	n = atoi(argv[1]);
	int* arr = (int*)malloc(sizeof(int) * n); // memory allocation for random array which size is n
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
	MergeSort_C(sorted_arr_C, 0, n-1, n);
	end_C = (double)clock() / CLOCKS_PER_SEC;
	time_C = end_C - start_C;

	/*
	start_ASM = (double)clock() / CLOCKS_PER_SEC;
	MergeSort_ASM(sorted_arr_ASM, 0, n - 1, n);
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

void MergeSort_C(int* arr, int l, int r) {

	if (r > l) {
		int m = (l + r) / 2;
		MergeSort_C(arr, l, m);
		/*
		printf("l값: %d, m값: %d, r값: %d\n", l, m, r);
		for (int i = 0;i < n;i++) {
			printf("%d ", arr[i]);
		}
		printf("\n\n");
		*/

		MergeSort_C(arr, m + 1, r);
		merge_C(arr, l, m, r);

		/*
		printf("l값: %d, m값: %d, r값: %d\n", l, m, r);
		for (int i = 0;i < n;i++) {
			printf("%d ", arr[i]);
		}
		printf("\n\n");
		*/
	}
}

void merge_C(int* arr, int l, int m, int r) {
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	int* L = (int*)malloc(sizeof(int) * n1);
	int* R = (int*)malloc(sizeof(int) * n2);
	
	for (i = 0;i < n1;i++) {
		L[i] = arr[l + i];
	}
	for (j = 0;j < n2;j++) {
		R[j] = arr[m + 1 + j];
	}
	i = 0;
	j = 0;
	k = l;
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			arr[k] = L[i];
			i++;
		}
		else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}
	while (i < n1) {
		arr[k] = L[i];
		i++;
		k++;
	}
	while (j < n2) {
		arr[k] = R[j];
		j++;
		k++;
	}

	free(L);
	free(R);
}
