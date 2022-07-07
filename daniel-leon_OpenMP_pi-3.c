#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

static long num_steps = 10000;

double step;

void main() {
	int i; 
	double x, pi;
	double sum = 0.0;
	step = 1.0/ (double) num_steps;
	int chunk = 10;
   #pragma omp parallel
    {
        #pragma omp sections nowait
        {
dummyMethod1();
            #pragma omp parallel for  default(shared) private(i) \
	schedule(static, chunk) reduction(+:sum)
            for (i = 0; i < num_steps; i++) {
            x = (i + 0.5)*step;
dummyMethod2();
            sum = sum + 4.0/(1.0 + x*x);
	    
            }   
        //int id = omp_get_thread_num(); 
        }
        pi = step * sum;
        printf("pi [%lf] step [%lf] sum[%lf]\n", pi, step,sum);
        
    }


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