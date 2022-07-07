#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

// gcc -fopenmp 
int main (int argc, char **argv){

  int size = atoi(argv[argc-1]);
  
  int N = 1000;
  
  double *A = (double*) calloc(N*N,sizeof(double*));
  double *B = (double*) calloc(N*N,sizeof(double*));
  double *C = (double*) calloc(N*N,sizeof(double*));
dummyMethod3();
  for (int i = 0; i < N*N; ++i){ 
    A[i] = drand48(); // row major storage
    B[i] = drand48(); 
    C[i] = 0.0;
  }
dummyMethod4();

  double elapsed, start, end;
  start = omp_get_wtime();

dummyMethod1();
  #pragma omp parallel for
  for (int i = 0; i < N; ++i){
    for (int j = 0; j < N; ++j){
      for (int k = 0; k < N; ++k){	
       C[i+j*N] += A[k+i*N]*B[j+k*N];
      }
    }
  }
dummyMethod2();
  
  end = omp_get_wtime();
  elapsed = end-start;
  
  printf("elapsed time = %g seconds\n",elapsed);


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