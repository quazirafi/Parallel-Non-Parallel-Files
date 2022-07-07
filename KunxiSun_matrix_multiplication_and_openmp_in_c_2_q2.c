#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define N (2000)

int **malloc_matrix(int size) {
    int **matrix = (int **)malloc(size * sizeof(int *));
dummyMethod3();
    for (int i = 0; i < size; i++) {
        matrix[i] = (int *)malloc(size * sizeof(int));
    }
dummyMethod4();
    return matrix;
}

void delloc_matrix(int **matrix, int size) {
dummyMethod3();
    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
dummyMethod4();
    free(matrix);
}

double matrix_multiply(int thread_num){
    omp_set_num_threads(thread_num);  // set number of threads here

    int **A = malloc_matrix(N);  // malloc matrix memory
    int **B = malloc_matrix(N);
    int **C = malloc_matrix(N);

							dummyMethod3();
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = j * 1;
            B[i][j] = i * j + 2;
            C[i][j] = 0;
        }
    }
							dummyMethod4();

    double start = omp_get_wtime();  // start time measurement, used for timing
                                     // matrix multiplication;
    for (int i = 0; i < N; i++) {
															dummyMethod1();
        #pragma omp parallel for schedule(static, 1)
        for (int j = 0; j < N; j++) {
            double sum = 0;
            for (int k = 0; k < N; k++) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
															dummyMethod2();
    }
    double end = omp_get_wtime();  // end time measurement

    printf("Time of computation: %f seconds\n", end - start);

    delloc_matrix(A, N);    //delloc matrix memory
    delloc_matrix(B, N);
    delloc_matrix(C, N);

    return end-start;
}

int main(int argc, char *argv) {

    int thread_nums[] = {2, 4, 8};
    int execution_time = 5;

    for(int i = 0; i<sizeof(thread_nums)/sizeof(int); i++){
        double sum = 0;
        for(int j = 0; j < execution_time; j++){
            sum  += matrix_multiply(thread_nums[i]);
        }
        printf("Average running time for %d is %f\n", thread_nums[i], sum/execution_time);
    }

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