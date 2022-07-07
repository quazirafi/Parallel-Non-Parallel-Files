#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
double step;
static long num_steps = 100000000;

int main() {
    int i;
    double x, pi, sum=0.0;
    step = 1.0/(double) num_steps;
    double start_time, run_time;
    start_time = omp_get_wtime();
    omp_set_num_threads(4);

dummyMethod1();
    #pragma omp parallel for reduction(+:sum)
        for(i=0;i<num_steps;i++) {
            x = (i+0.5)*step;
            sum = sum + 4.0/(1.0+x*x);
        }
dummyMethod2();

    pi = step*sum;
    run_time = omp_get_wtime() - start_time;
	printf("\n pi with %ld steps is %lf in %lf milli-seconds\n ",num_steps,pi,run_time);
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