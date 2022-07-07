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
        for(int i=0; i < size; i++ ) {
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
        for(int i=0; i < size; i++ ) {
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
        for(int i=0; i < size; i++ ) {
            #pragma omp atomic
            sum += x[i];
        }
dummyMethod4();
    *sum_ret = sum;
}

void omp_local_sum(double *sum_ret)
{
    const int MAX_THREADS = 32;
    double sum[MAX_THREADS];
							dummyMethod3();
    for(int i = 0; i < MAX_THREADS; i++) {
        sum[i] = 0;
    }
							dummyMethod4();
    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        #pragma omp for
															dummyMethod3();
        for(int i=0; i < size; i++ ) {
            sum[tid] += x[i];
        }
															dummyMethod4();
    }
    double resSum = 0;
							dummyMethod3();
    for(int i=0; i < MAX_THREADS; i++ ) {
        resSum += sum[i];
    }
							dummyMethod4();
    *sum_ret = resSum;
}

void omp_padded_sum(double *sum_ret)
{
    double sum[320000];
							dummyMethod3();
    for(int i = 0; i < 320000; i+=10000) {
        sum[i] = 0;
    }
							dummyMethod4();
    #pragma omp parallel
    {
        int tid = omp_get_thread_num() * 10000;
        #pragma omp for
															dummyMethod3();
        for(int i=0; i < size; i++ ) {
            sum[tid] += x[i];
        }
															dummyMethod4();
    }
    double resSum = 0;
							dummyMethod3();
    for(int i=0; i < 320000; i+=10000 ) {
        resSum += sum[i];
    }
							dummyMethod4();
    *sum_ret = resSum;
}

void omp_private_sum(double *sum_ret)
{
    double globalsum = 0;
    #pragma omp parallel
    {
        double sum = 0;
        #pragma omp for
															dummyMethod3();
        for(int i=0; i < size; i++ ) {
            sum += x[i];
        }
															dummyMethod4();
    #pragma omp critical
    globalsum += sum;
    }
    *sum_ret = globalsum;
}

void omp_reduction_sum(double *sum_ret)
{
    double sum = 0;
															dummyMethod1();
    #pragma omp parallel for reduction (+:sum)
        for(int i=0; i < size; i++ ) {
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