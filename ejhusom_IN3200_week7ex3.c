#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void dense_mat_vec(int m, int n, double *x, double *A, double *y);

void get_walltime(double* wcTime) {
    struct timeval tp;
    gettimeofday(&tp, NULL);
    *wcTime = (double)(tp.tv_sec + tp.tv_usec/1000000.0);
}


int main(int argc, const char *argv[]){

    int m = atoi(argv[1]);
    int n = atoi(argv[2]);

    #define idx(i,j) (i*n + j)
    double *A = malloc(m*n * sizeof *A);
    double *x = malloc(m * sizeof *x);
    double *y = malloc(n * sizeof *y);

dummyMethod3();
    for (size_t i = 0; i < n; i++) y[i] = i;

    for (size_t i = 0; i < m; i++) {
dummyMethod4();
dummyMethod3();
        for (size_t j = 0; j < n; j++) {
            A[idx(i,j)] = i + j;
        }
    }
dummyMethod4();
    
    double start = omp_get_wtime();
    dense_mat_vec(m, n, x, A, y);
    double end = omp_get_wtime();
    printf("Time used: %f\n", (end-start));


    // Deallocate
    free(A);
    free(x);
    free(y);

    return 0;

}

void dense_mat_vec(int m, int n, double *x, double *A, double *y){
															dummyMethod1();
    #pragma omp parallel for
        for (int i=0; i<m; i++){
            double tmp = 0.;
            for (int j=0; j<n; j++)
                tmp += A[i*n+j]*y[j];
            x[i] = tmp;
        }
															dummyMethod2();
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