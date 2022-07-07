#include <math.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define NUM_THREADS 4
#define N 10000
#define factor 1.0
int main(){
    double sum = 0.0,Pi = 0.0;
    int k;
    omp_set_num_threads(NUM_THREADS);
    #pragma omp parallel num_threads(NUM_THREADS)
    {
    printf("Hello! threadID=%d\n",omp_get_thread_num());
    }
dummyMethod1();
    #pragma omp parallel for private(k) reduction(+:sum)
    for(k=0;k<N;k++){
        sum = sum + pow(-1,k) / (2.0*k+1.0);
    }
dummyMethod2();
    Pi = 4.0 * sum;
    printf("Pi = %lf",Pi);
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