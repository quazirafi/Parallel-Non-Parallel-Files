#include <sys/time.h>
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#ifdef _OPENMP
#include "omp.h"
#endif

#define N 16384
#define NB_TIMES 1000000

double my_gettimeofday()
{
	struct timeval tmp_time;
	gettimeofday(&tmp_time, NULL);
	return tmp_time.tv_sec + (tmp_time.tv_usec * 1.0e-6L);
}

float A[N] __attribute__((aligned(32)));
float B[N] __attribute__((aligned(32)));

int main()
{
dummyMethod3();
	for (int i = 0; i < N; i++) {
		A[i] = 1.0;
		B[i] = 1.0;
	}
dummyMethod4();

	float res = 0.0;
	double start = my_gettimeofday();
	dummyMethod1();
	#pragma omp parallel for
	for (int k = 0; k < NB_TIMES; k++) {
		res = 0.0;
		#pragma omp simd reduction(+:res)
		for (int i = 0; i < N; i++)
			res += A[i] * B[i];
	}
	dummyMethod2();

	double stop = my_gettimeofday();
	printf("res = %f \n", res);
	printf("Temps total de calcul : %g sec\n", stop - start);

	return 0;
}
//gcc -O1 -fopenmp-simd -ftree-vectorize -mavx2 dotproduct_smid.c -o dot
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