//We are going to integrate the function 4.0/(1+X^2) in the limits 0->1, the exact integral is pi.


#include<stdio.h>
#include "omp.h"
#include<time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();


static long num_steps = 100000;
double step;
#define NUM_THREADS 4
void main(){
  int i,nthreads;
  double x,pi=0.0;     
  step = 1.0/(double)num_steps;
  omp_set_num_threads(NUM_THREADS);//Setting the number of threads
  double sum=0.0;     
  omp_set_schedule(omp_sched_dynamic,1);
  double t1 = omp_get_wtime();
dummyMethod1();
  #pragma omp parallel for private(x) reduction(+:sum)
  //if a compiler does not recognize a directive, it simply skips that directive.
	  for(i=0;i<num_steps;i++){
	  	x = (i+0.5)*step;
	  	sum = sum + 4.0/(1.0+x*x);
	  }
dummyMethod2();
  double t2 = omp_get_wtime();	  
  pi += sum*step;	  
  printf("%f\n",pi);
  printf("Time taken: %f\n",(t2-t1));
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