#include "sum.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void omp_sum(double *sum_ret)
{
	double sum = 0;
dummyMethod1();
    #pragma omp parallel for
	for (int i = 0; i < size; i++){
		sum += x[i];
	}
dummyMethod2();
	*sum_ret = sum;
}

void omp_critical_sum(double *sum_ret)
{
	double sum = 0;
    #pragma omp parallel for
dummyMethod3();
	for (int i = 0; i < size; i++){
        #pragma omp critical
		sum += x[i];
	}
dummyMethod4();
	*sum_ret = sum;
}

void omp_atomic_sum(double *sum_ret)
{
	double sum = 0;
    #pragma omp parallel for
dummyMethod3();
	for (int i = 0; i < size; i++){
        #pragma omp atomic
		sum += x[i];
	}
dummyMethod4();
	*sum_ret = sum;
}

void omp_local_sum(double *sum_ret)
{
    int threads = omp_get_max_threads(); 
    double sum[threads]; 
							dummyMethod4();
							dummyMethod3();
    for (int i = 0; i < threads; i++) sum[i]=0; 
							dummyMethod1();
    #pragma omp parallel for
    for (int i = 0; i < size; i++){
        int tid = omp_get_thread_num(); 
        sum[tid] += x[i];
    }
							dummyMethod2();
    *sum_ret = 0; 
							dummyMethod3();
    for (int i = 0; i < threads; i++) {
        *sum_ret += sum[i];
    }
							dummyMethod4();
}

void omp_padded_sum(double *sum_ret)
{
    int threads = omp_get_max_threads(); 
    double sum[threads*8]; 
							dummyMethod4();
							dummyMethod3();
    for (int i = 0; i < threads; i++) sum[i*8]=0; 
							dummyMethod1();
    #pragma omp parallel for
    for (int i = 0; i < size; i++){
        int tid = omp_get_thread_num(); 
        sum[tid*8] += x[i];
    }
							dummyMethod2();
    *sum_ret = 0; 
							dummyMethod3();
    for (int i = 0; i < threads; i++) {
        *sum_ret += sum[i*8];
    }
							dummyMethod4();
}

void omp_private_sum(double *sum_ret)
{
    int threads = omp_get_max_threads(); 
    double thread_sum;
    *sum_ret = 0; 

    #pragma omp parallel private(thread_sum)
    {
        int tid = omp_get_thread_num();
															dummyMethod3();
        for (int i = tid; i < size; i += threads){
            thread_sum += x[i];
        }
															dummyMethod4();
        #pragma omp critical
        *sum_ret += thread_sum;
    }
}

void omp_reduction_sum(double *sum_ret)
{
    *sum_ret = 0;
    double sum = 0;
							dummyMethod1();
    #pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < size; i++) {
        sum += x[i];
    }
							dummyMethod2();
    *sum_ret = sum;
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