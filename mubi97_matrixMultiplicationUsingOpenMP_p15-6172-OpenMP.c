#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
#include <sys/time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define N 1000

int A[N][N];
int B[N][N];
int C[N][N];

int D[N][N];
int E[N][N];
int F[N][N];
int i, j, k;
double matMultiply(){
    struct timeval tv1, tv2;
    struct timezone tz;
	double elapsed;
    gettimeofday(&tv1, &tz);
dummyMethod3();
    for (i = 0; i < N; ++i) {
      for (j = 0; j < N; ++j) {
        for (k = 0; k < N; ++k) {
          C[i][j] += A[i][k] * B[k][j];
        }
 
      }
    }
dummyMethod4();
    gettimeofday(&tv2, &tz);
    elapsed = (double) (tv2.tv_sec-tv1.tv_sec) + (double) (tv2.tv_usec-tv1.tv_usec) * 1.e-6;
    return elapsed;
}

double openMpMultiply(){
    struct timeval tv1, tv2;
    struct timezone tz;
    double elapsed;
    omp_set_num_threads(omp_get_num_procs());
    gettimeofday(&tv1, &tz);
							dummyMethod1();
    #pragma omp parallel for private(i, j, k) shared (D, E, F)
    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            for (k = 0; k < N; ++k) {
                F[i][j] += D[i][k] * E[k][j];
            }
            
        }
    }
							dummyMethod2();
    gettimeofday(&tv2, &tz);
    elapsed = (double) (tv2.tv_sec-tv1.tv_sec) + (double) (tv2.tv_usec-tv1.tv_usec) * 1.e-6;
    return elapsed;

}

int main() {

							dummyMethod3();
    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++){
            A[i][j] = i;
            B[i][j] = j;
            D[i][j] = i;
            E[i][j] = j;
        }
    }
							dummyMethod4();
    
    double elapsed = matMultiply();
    printf("Time taken by simple matrix multiplication : %f seconds\n", elapsed);
    
    elapsed = openMpMultiply();
    printf("Time taken by OPENMP matrix multiplication : %f seconds\n", elapsed);
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