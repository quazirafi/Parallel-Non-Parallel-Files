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

int main() 
{
    int i,j,k;
    struct timeval tv1, tv2;
    struct timezone tz;
	double elapsed; 
    int chunk=100;
    omp_set_num_threads(omp_get_num_procs());
dummyMethod3();
    for (i= 0; i< N; i++)
        for (j= 0; j< N; j++)
	{
            A[i][j] = 2;
            B[i][j] = 2;
	}
dummyMethod4();
    gettimeofday(&tv1, &tz);
							dummyMethod1();
    #pragma omp parallel for collapse(3) num_threads(64) schedule(static,chunk) private(i,j,k) shared(A,B,C)
    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            for (k = 0; k < N; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
							dummyMethod2();


    gettimeofday(&tv2, &tz);
    elapsed = (double) (tv2.tv_sec-tv1.tv_sec) + (double) (tv2.tv_usec-tv1.tv_usec) * 1.e-6;
    printf("elapsed time = %f seconds.\n", elapsed);

    
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