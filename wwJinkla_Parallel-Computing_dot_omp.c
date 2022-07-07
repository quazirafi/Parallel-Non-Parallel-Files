#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main (int argc, char **argv){

  int size = atoi(argv[argc-1]);

  int N = 100;
  double *a = (double*) calloc(N,sizeof(double));
  double *b = (double*) calloc(N,sizeof(double));
  double *c = (double*) calloc(N,sizeof(double));  

  // structured block
dummyMethod1();
#pragma omp parallel for num_threads(size) shared(a,b) 
  for (int i = 0; i < N; ++i){
    a[i] = 10./(i+1.);
    b[i] = (i+1.)/10.;
  }
dummyMethod2();

  // need reduction clause to avoid race conditions
  double d = 0.0;
dummyMethod1();
#pragma omp parallel for num_threads(size) shared(a,b) reduction(+:d)
  for (int i = 0; i < N; ++i){
    d += a[i]*b[i];
  }
dummyMethod2();

  printf("d = %f\n",d);
  free(a);
  free(b);    
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