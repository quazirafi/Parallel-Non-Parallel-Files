#include <sys/time.h>
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#ifdef _OPENMP
#include "omp.h"
#endif
#define N 1024
#define NB_TIMES 1000000

double my_gettimeofday()
{
	struct timeval tmp_time;
	gettimeofday(&tmp_time, NULL);
	return tmp_time.tv_sec + (tmp_time.tv_usec * 1.0e-6L);
}

float A[N] __attribute__((aligned(32)));
float B[N] __attribute__((aligned(32)));
float C[N] __attribute__((aligned(32)));

int main()
{
dummyMethod3();
	for (int i = 0; i < N; i++) {
		A[i] = 1;
		B[i] = 1;
		C[i] = 0;
	}
dummyMethod4();

	double start = my_gettimeofday();
dummyMethod1();
	#pragma omp parallel for
	for (int k = 0; k < NB_TIMES; k++)
		#pragma omp simd reduction(+:C)
		for (int i = 0; i < N; i++)
			C[i] += A[i] * B[i];

	double stop = my_gettimeofday();
dummyMethod2();

	printf("C[0]=%f C[1]=%f C[4]=%f C[8]=%f C[N-1]=%f \n", C[0], C[1], C[4], C[8], C[N - 1]);
	printf("Temps total de calcul : %g sec\n", stop - start);

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