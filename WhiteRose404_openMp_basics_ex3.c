#include <stdio.h>
#include "omp.h"
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define THREADS 20

/*
        the chalelnge is to add critical section and for section using openmp with minimum changes
*/


int main(){
        int num_steps = 1000000000,tsize;
        double step = 1.0 /( (double) num_steps),PI = 0;
        //double* psum = malloc(sizeof(double)*THREADS);
	omp_set_num_threads(THREADS);
        double start = omp_get_wtime();
	int data=0;
	omp_sched_t ok;
	omp_get_schedule(&ok,&data);
	printf("%d\n",data);
dummyMethod1();
        #pragma omp parallel for reduction(+: PI)
        for(int i=0;i<num_steps;i++){
        	double x = (0.5+i)*step;
                double f = 4.0 /( (double) 1+x*x);
		PI+=f;
dummyMethod2();
        }
        double time = omp_get_wtime()-start;
        PI*=step;
        printf("PI=%lf took around %lf\n",PI,time);
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