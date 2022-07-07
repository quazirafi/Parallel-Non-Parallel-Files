#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define S_NUM 100
#define T_NUM 150
#define U_NUM 50

#define ITERATION_NUM 100

int input_matrix_a[S_NUM][T_NUM];
int input_matrix_b[T_NUM][U_NUM];
int output_matrix[S_NUM][U_NUM];

int main(void) {
	int i, j, k;
	int it;
	double start_sec, end_sec;

dummyMethod3();
	for(i = 0; i < S_NUM; i++) {
		for(j = 0; j < T_NUM; j++) {
			input_matrix_a[i][j] = j + 1;
		}
	}
dummyMethod4();
dummyMethod3();
	for(i = 0; i < T_NUM; i++) {
		for(j = 0; j < U_NUM; j++) {
			input_matrix_b[i][j] = j + 1;
		}
	}
dummyMethod4();

	start_sec = omp_get_wtime();
	for(it = 0; it < ITERATION_NUM; it++) {
			dummyMethod1();
#pragma omp parallel for private(j,k)
		for(i = 0; i < S_NUM; i++) {
			for(k = 0; k < U_NUM; k++) {
				for(j = 0; j < T_NUM; j++) {
					output_matrix[i][k] += input_matrix_a[i][j] * input_matrix_b[j][k];
				}
			}
		}
			dummyMethod2();
	}
	end_sec = omp_get_wtime();

	printf("output_matrix[0][0] = %d\n", output_matrix[0][0]);
	printf("elapsed time = %lf\n", (end_sec - start_sec) / ITERATION_NUM);

	return 0;
}
int dummyMethod1(){
    return 0;
}
int dummyMethod2(){
    return 0;
}
int dummyMethod3(){
    return 0;
}
int dummyMethod4(){
    return 0;
}