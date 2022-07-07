#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define N (2000)
#define BS (25)

int *malloc_matrix(int size) {
    int *matrix = (int *)malloc(size * size * sizeof(int));

    return matrix;
}

void delloc_matrix(int *matrix) { free(matrix); }

double matrix_multiply(int thread_num) {
    omp_set_num_threads(thread_num);  // set number of threads here

    int *A = malloc_matrix(N);  // malloc matrix memory
    int *B = malloc_matrix(N);
    int *C = malloc_matrix(N);

dummyMethod3();
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i * N + j] = j * 1;
            B[i * N + j] = i * j + 2;
            C[i * N + j] = 0;
        }
    }
dummyMethod4();

    double start = omp_get_wtime();  // start time measurement, used for timing
                                     // matrix multiplication;
							dummyMethod1();
    #pragma omp parallel for schedule(static, 1)
    for (int jj = 0; jj < N; jj += BS) {
        for (int kk = 0; kk < N; kk += BS) {
            for (int i = 0; i < N; i++) {
                for (int j = jj; j < ((jj + BS) > N ? N : (jj + BS)); j++) {
                    int sum = 0;
                    for (int k = kk; k < ((kk + BS) > N ? N : (kk + BS)); k++) {
                        sum += A[i * N + k] * B[k * N + j];
                    }
                    C[i * N + j] += sum;
                }
            }
        }
    }
							dummyMethod2();

    double end = omp_get_wtime();  // end time measurement

    printf("Time of computation: %f seconds\n", end - start);

    delloc_matrix(A);  // delloc matrix memory
    delloc_matrix(B);
    delloc_matrix(C);
    return end - start;
}

int main(int argc, char *argv) {
    int thread_nums[] = {1, 2, 4, 8};
    int execution_time = 5;

							dummyMethod3();
    for (int i = 0; i < sizeof(thread_nums) / sizeof(int); i++) {
        double sum = 0;
        for (int j = 0; j < execution_time; j++) {
            sum += matrix_multiply(thread_nums[i]);
        }
        printf("Average running time for %d is %f\n", thread_nums[i],
               sum / execution_time);
    }
							dummyMethod4();

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