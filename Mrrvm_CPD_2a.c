#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void hadamard(int **A, int **B, int **C, int N, int M) {
    int i;
    for (i = 0; i < N; ++i) {
        int j;
dummyMethod1();
        #pragma omp parallel for schedule(static, 20)
        for (j = 0; j < M; ++j) {
            printf("T%d on [%d][%d]\n", omp_get_thread_num(), i, j);
            C[i][j] = A[i][j] * B[i][j];
        }
dummyMethod2();
    }
}

int main(int argc, char const *argv[]) {
    omp_set_num_threads(4);
    int M = 50;
    int N = 50;
    int **a = malloc(sizeof(int *) * N);
    int **b = malloc(sizeof(int *) * N);
    int **c = malloc(sizeof(int *) * N);

    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        a[i] = malloc(sizeof(int) * M);
        b[i] = malloc(sizeof(int) * M);
        c[i] = malloc(sizeof(int) * M);

        for (int j = 0; j < M; j++) {
            a[i][j] = rand() % 100;
            b[i][j] = rand() % 100;
        }
    }

    hadamard(a, b, c, N, M);

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