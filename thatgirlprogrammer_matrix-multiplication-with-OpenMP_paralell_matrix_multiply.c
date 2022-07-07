#include <string.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
#include <sys/time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define FactorIntToDouble 1.1;
#define N 2048
int mat1[N][N];
int mat2[N][N];
int res[N][N];

void fill_matrix(){
    int row, col;
dummyMethod3();
    for (row = 0; row < N; row++){
        for (col = 0; col < N; col++){
            mat1[row][col] = ( rand() % 10 ) * FactorIntToDouble;
            mat2[row][col] = ( rand() % 10 ) * FactorIntToDouble;
        }
   }
dummyMethod4();
}


void multiply(){
    int row, col, cell;
							dummyMethod1();
    #pragma omp parallel for private(row,col,cell) shared(mat1,mat2,res)
    for (row = 0; row < N; ++row) {
        for (col = 0; col < N; ++col) {
            for (cell = 0; cell < N; ++cell) {
                res[row][col] += mat1[row][cell] * mat2[cell][col];
            }
        }
    }
							dummyMethod2();

}

int main(){
    int row,col;
    struct timeval tv1, tv2;
    struct timezone tz;
    double elapsed;

    memset(res, 0, sizeof(res[0][0]) * N * N);
    omp_set_num_threads(omp_get_num_procs());
    fill_matrix();
    gettimeofday(&tv1, &tz);
    multiply();
    gettimeofday(&tv2, &tz);
    elapsed = (double) (tv2.tv_sec-tv1.tv_sec) + (double) (tv2.tv_usec-tv1.tv_usec) * 1.e-6;
    printf("elapsed time = %f seconds.\n", elapsed);
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