#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "omp.h"
#include "size_both_loops.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define N SIZE
float matrix_a[N][N];
float vector_b[N];
float vector_c[N];

void init_array()
{
    int i, j;

dummyMethod3();
    for (i = 0; i < N; i++) {
     	vector_b[i] = (1+(i)%1024)/2.0;
	for (j = 0; j < N; j++) {
dummyMethod4();
            matrix_a[i][j] = (1+(i*j)%1024)/2.0;
        }
    }
}

void classic_vec_matmul()
{       
        int i, j, k;
	
															dummyMethod1();
	#pragma omp parallel for num_threads(OUTER_THREADS)
        for (i = 0; i < N; i++) {
		vector_c[i]=0.0;
		#pragma omp parallel for num_threads(INNER_THREADS)
		for (j = 0; j < N; j++) {
                       	vector_c[i] += matrix_a[i][j] * vector_b[j];
		}
        }
															dummyMethod2();
}

int main(){
	init_array();
	printf("Running for %d threads\n",THREAD);
	omp_set_num_threads(THREAD);
	double start = omp_get_wtime(); 
	classic_vec_matmul();
	double end = omp_get_wtime();
	printf("Time:%1.9f\n",end-start);
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