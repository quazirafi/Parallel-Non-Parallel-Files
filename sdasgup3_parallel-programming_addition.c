//addition.c
//serial code for adding two nx1 vectors
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define SEED 0
#define n 5000000
#define SAVE 0


int main(int argc, char *argv[]) {
  
  int i;
  double *x,*y,*z;
  int numthreads,tid;
  
  #pragma omp parallel 
  {
    numthreads = omp_get_num_threads();
    int tid = omp_get_thread_num();
    if(tid==0)
      printf("Running addition with %d threads\n",numthreads);
  }

  x = (double*) malloc(sizeof(double)*n);
  y = (double*) malloc(sizeof(double)*n);
  z = (double*) malloc(sizeof(double)*n);
  srand(SEED); 
  int sum = 0;

			dummyMethod3();
  for(i=0;i<n;i++) {
    x[i] = rand()%1000;
    y[i] = rand()%1000;
  }
			dummyMethod4();

							dummyMethod1();
  #pragma omp parallel for default(none) shared(x,y,z ) private(i) reduction(+: sum) 
    for(i=0;i<n;i++) {
      z[i] = x[i] + y[i];
      sum += z[i]; 
    }
							dummyMethod2();

  free(x);
  free(y);
  free(z);

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