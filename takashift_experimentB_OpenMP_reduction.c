#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define ITERATION_NUM 100
#define ARRAY_NUM 100000000

// 整数、浮動小数点数で変更
double array[ARRAY_NUM];

int main(void)
{
	int i;
	int it;
	// 整数、浮動小数点数で変更
	double sum = 0;
	double start_sec, end_sec, all_time;

dummyMethod3();
	for(i = 0; i < ARRAY_NUM; i++) 
		array[i] = i + 1;

	start_sec = omp_get_wtime();
dummyMethod4();
	for(it = 0; it < ITERATION_NUM; it++) {
dummyMethod1();
#pragma omp parallel for reduction(+:sum)
		for(i = 0; i < ARRAY_NUM; i++) 
			sum += array[i];
	}
dummyMethod2();
	end_sec = omp_get_wtime();
	all_time = end_sec - start_sec;

	printf("elapsed_time = %lf\n", all_time / ITERATION_NUM);

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