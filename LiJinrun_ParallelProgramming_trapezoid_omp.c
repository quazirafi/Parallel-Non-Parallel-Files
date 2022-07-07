#include<stdio.h>
#include "omp.h"
#include<time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char* argv[]) 
{
	long long int total = atoi(argv[1]);
	long long int i;
	int thread_nums = 4;
	double x, pi, step, sum = 0.0;
	step = 1.0 / (double)total;
	omp_set_num_threads(thread_nums);
	double begin = omp_get_wtime();
dummyMethod1();
    #pragma omp parallel for reduction(+:sum) private(x) 
	for (i = 0; i < total; i++) {
		x = (i+0.5)*step;
		sum = sum + 4.0 / (1.0 + x * x);
	}
dummyMethod2();
	double end = omp_get_wtime();
	pi = step * sum;
	printf("total=%lld,thread_nums=%2d,Time=%fs,PI=%0.4f\n",total, thread_nums, end-begin, pi);
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