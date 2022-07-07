#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
//#include <immintrin.h>
#include <math.h>

#define ITERATION_NUM 100
#define ARRAY_NUM 10000000

// 整数、浮動小数点数で変更
double array[ARRAY_NUM];

// double result[ARRAY_NUM];

int main(void)
{
	int i, it, n_flop;
	double sum = 1; // 整数、浮動小数点数で変更
	double start_sec, end_sec, all_time, elapsed_time, flops;

dummyMethod3();
	for(i = 0; i < ARRAY_NUM; i++){ 
		array[i] = 1;
		// result[i] = 0;
	}
dummyMethod4();
	
	start_sec = omp_get_wtime();
	for(it = 0; it < ITERATION_NUM; it++) {
			dummyMethod1();
#pragma omp parallel for reduction(*:sum)
		for(i = 0; i < ARRAY_NUM; i++) { 
			sum *= array[i] // ここが = sum + だとなぜか演算器が１つしか使われない。+ と * を交互にすると、*でくくられてしまうので、すべて同じ演算子にする。
				* array[i]
				* array[i]
				* array[i]
				* array[i]
				* array[i]
				* array[i]
				* array[i]
				* array[i]
				* array[i]
				* array[i]
				* array[i]
				* array[i]
				* array[i]
				* array[i]
				* array[i];
		}
			dummyMethod2();
	}
	end_sec = omp_get_wtime();
	all_time = end_sec - start_sec;
	elapsed_time = all_time / ITERATION_NUM;
	n_flop =16;
	flops = ARRAY_NUM / elapsed_time * n_flop * 0.000000001;

	printf("sum = %lf,elapsed_time = %lf, FLOPS = %lfGFlops, flop = %d, %lfFLOP/Byte\n", sum, elapsed_time, flops, n_flop, (double)n_flop/(sizeof(double)*3));

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